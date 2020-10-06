#include "graph.h"



Graph::Graph(int region)
{
    this->region=region;
    QString w=QString::asprintf("select uID,area,id,info from public.vertex where region=%d order by uID;",region);
    QSqlQuery query;
    query.exec(w);
    while(query.next()){
        Vertex *v=new Vertex();
        v->region=region;
        v->longid=query.value(0).toInt();
        v->area=query.value(1).toInt();
        v->id=query.value(2).toInt();
        QString json=query.value(3).toString();
        QJsonParseError jError;
        QJsonDocument jdoc=QJsonDocument::fromJson(json.toUtf8(),&jError);
        if (jError.error!=QJsonParseError::NoError){
            return;
        }
        QMap<QString, QVariant>  map=jdoc.toVariant().toMap();
        v->info=InfoVertex(map);
        addVertex(v);
    }
    w=QString::asprintf("select uIDin,uIDout,info from public.edges where region=%d order by uIDout;",region);
    query.exec(w);
    while(query.next()){
        Edge *e=new Edge();
        e->region=region;
        e->inid=query.value(0).toInt();
        e->outid=query.value(1).toInt();
        QString json=query.value(2).toString();
        QJsonParseError jError;
        QJsonDocument jdoc=QJsonDocument::fromJson(json.toUtf8(),&jError);
        if (jError.error!=QJsonParseError::NoError){
            return;
        }
        QMap<QString, QVariant>  map=jdoc.toVariant().toMap();
        e->info=InfoEdge(map);
        addEdge(e);
    }
    QList<IDs> lc=Support::listCrosses(region);
    foreach (auto c, lc) {
        if(!vertexes.contains(c.getCode().toULong())) {
            protocol.append("Перекресток "+c.toString()+" отсутствует в графе");
            error=true;
            continue;
        }
        auto v=vertexes[c.getCode().toULong()];
        v->info.dgis=c.dgis;
        v->info.description=c.description;
        v->correct=true;
    }
    foreach (auto v, vertexes) {
        if (!v->correct){
            protocol.append("Вершина "+v->toString()+" отсутствует в перечне перекрестков");
            error=true;
            continue;
        }
        v->correct=false;
    }
    foreach (auto el, edges) {
        QMap<ulong,int> count;
        foreach (auto e, el) {
            if(!count.contains(e->inid)){
                count[e->inid]=1;
            }else{
                count[e->inid]++;
            }
        }
        foreach(auto c,count.keys()){
            if(count[c]>1){
                QString list="В последовательности";
                foreach (auto e, el) {
                    list.append(e->toString()+" ");
                }
                protocol.append(list+" есть дубликаты ");
                error=true;
                break;
            }
        }
    }
    if (!controlGraph()) error=true;
}

bool Graph::addVertex(Vertex *vertex)
{
    if(vertexes.contains(vertex->longid) ) {
        protocol.append("Вершина "+vertex->toString()+" дубликатная");
        return false;
    }
    vertexes[vertex->longid]=vertex;
    return true;
}

bool Graph::addEdge(Edge *edge)
{
    if(!vertexes.contains(edge->inid) || !vertexes.contains(edge->outid) ) {
        protocol.append("Ребро "+edge->toString()+" ошибка по связи");
        return false;
    }
    auto v=vertexes[edge->inid];
    if(edge->info.lineIn>v->info.countIn || edge->info.lineIn<1) {
        protocol.append("Ребро "+edge->toString()+" Ошибка по номеру входа");
        return false;
    }
    v=vertexes[edge->outid];
    if(edge->info.lineOut>v->info.countOut || edge->info.lineOut<1) {
        protocol.append("Ребро "+edge->toString()+" Ошибка по номеру выхода");
        return false;
    }
    if (!edges.contains(edge->outid)){
        QList<Edge*> list;
        edges[edge->outid]=list;
    }
    QList<Edge*> list=edges[edge->outid];
    list.append(edge);
    edges[edge->outid]=list;
    return true;
}

bool Graph::controlGraph()
{
    //Проверим граф на связность
    g.clear();
    QMap<ulong,bool> used;
    QList<ulong> l;
    ulong first=0;
    //Грузим вершины
    foreach (auto v, vertexes) {
        g[v->longid]=l;
        used[v->longid]=false;
        if (first==0) first=v->longid;
    }
    //Теперь графы
    foreach (auto en, edges.keys()) {
        foreach (auto e, edges[en]) {
            appendSingle(e);
        }
    }
    QQueue<ulong> q;
    q.push_back(first);
    used[first]=true;
    while (!q.empty()){
        ulong v=q.front();
        q.pop_front();
        foreach (ulong to, g[v]) {
            if(!used[to]){
                used[to]=true;
                q.push_back(to);
            }
        }
    }
    bool error=false;
    foreach (auto i, used.keys()) {
        if(!used[i]){
            protocol.append(QString::asprintf("Вершина %ld не в связанном графе",i));
            error=true;
        }
    }
    return !error;
}

void Graph::appendSingle( Edge *edge)
{
    QList<ulong> l=g[edge->outid];
    bool is=false;
    foreach (auto v, l) {
        if (v==edge->inid) {
            is=true;
            break;
        }
    }
    if (!is){
        l.append(edge->inid);
        g[edge->outid]=l;
    }
    is=false;
    l=g[edge->inid];
    foreach (auto v, l) {
        if (v==edge->outid) {
            is=true;
            break;
        }
    }
    if (!is){
        l.append(edge->outid);
        g[edge->inid]=l;
    }
}

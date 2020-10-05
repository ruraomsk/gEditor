#include "graph.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QSqlQuery>


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
                break;
            }
        }
    }
    controlGraph();
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
    QMap<ulong,QList<ulong>> g;
    QList<ulong> l;
    //Грузим вершины
    foreach (auto v, vertexes) {
        g[v->longid]=l;
    }
    //Теперь графы
    foreach (auto en, edges.keys()) {
        foreach (auto e, edges[en]) {
            appendSingle(&g,e);
        }
    }
    return true;
}

void Graph::appendSingle(QMap<ulong, QList<ulong> > *g, Edge *edge)
{
    auto l=g[edge->outid];
    bool is=false;
    foreach (auto v, l) {
    }
}

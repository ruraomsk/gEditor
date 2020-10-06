#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QSqlQuery>

#include "edge.h"
#include "vertex.h"
#include "../support.h"
class Graph
{
public:
    Graph(int region);
    bool addVertex(Vertex *vertex);
    bool addEdge(Edge *edge);
    bool controlGraph();

    QStringList protocol;
    bool error=false;
private:
    int region;
    QMap<ulong,Vertex*> vertexes;
    QMap<ulong,QList<Edge*>> edges;
    void appendSingle(Edge *edge);
    QMap<ulong,QList<ulong>> g;

};

#endif // GRAPH_H

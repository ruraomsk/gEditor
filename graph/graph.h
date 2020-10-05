#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>

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
private:
    int region;
    QMap<ulong,Vertex*> vertexes;
    QMap<ulong,QList<Edge*>> edges;
    QStringList protocol;
    void appendSingle(QMap<ulong,QList<ulong>> *g,Edge *edge);
};

#endif // GRAPH_H

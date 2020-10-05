#ifndef EDGE_H
#define EDGE_H

#include <QString>
#include <QtGlobal>

#include "infoedge.h"
class Edge
{
public:
    Edge();
    ~Edge();
    QString toString();
    ulong inid;
    ulong outid;
    int region;
    InfoEdge info;
};

#endif // EDGE_H

#ifndef VERTEX_H
#define VERTEX_H

#include <QString>
#include <QtGlobal>
#include <QMap>
#include <QVariant>

#include "infovertex.h"
class Vertex
{
public:
    Vertex();
    ~Vertex();

public:
    QString toString();

    ulong longid;
    int region;
    int area;
    int id;
    InfoVertex info;
    bool correct=false;
};

#endif // VERTEX_H

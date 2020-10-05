#include "vertex.h"

Vertex::Vertex()
{

};

Vertex::~Vertex()
{

};

QString Vertex::toString()
{
    return QString::asprintf("регион %d район %d ID %d",region,area,id);
};

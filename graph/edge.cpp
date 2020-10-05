#include "edge.h"

Edge::Edge()
{

}

Edge::~Edge()
{

}

QString Edge::toString()
{
    return QString::asprintf("регион %d %ld --> %ld",region,outid,inid);

}

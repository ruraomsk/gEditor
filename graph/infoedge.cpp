#include "infoedge.h"


InfoEdge::InfoEdge()
{
    this->lineIn=1;
    this->lineOut=1;
}

InfoEdge::InfoEdge(int lineIn, int lineOut)
{
    this->lineIn=lineIn;
    this->lineOut=lineOut;
}

InfoEdge::InfoEdge(QMap<QString, QVariant> map)
{
    lineIn=map["lin"].toInt();
    lineOut=map["lout"].toInt();
}

QMap<QString, QVariant> InfoEdge::ToJson()
{
    QMap<QString, QVariant> map;
    map["lin"]=QVariant(lineIn);
    map["lout"]=QVariant(lineOut);
    return map;
}

InfoEdge::~InfoEdge()
{

}


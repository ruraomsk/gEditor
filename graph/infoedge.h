#ifndef INFOEDGE_H
#define INFOEDGE_H

#include <QMap>
#include <QVariant>

class InfoEdge
{
public:
    InfoEdge();
    InfoEdge(int lineIn,int lineOut);
    InfoEdge(QMap<QString,QVariant> map);
    QMap<QString,QVariant> ToJson();
    ~InfoEdge();

public:
    int lineIn;         //Номер линии на перекрестке входа
    int lineOut;        //Номер линии на перекрестке выхода
};

#endif // INFOEDGE_H

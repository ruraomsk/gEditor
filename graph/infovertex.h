#ifndef INFOVERTEX_H
#define INFOVERTEX_H
#include <QMap>
#include <QVariant>

class InfoVertex
{
public:
    InfoVertex();
    InfoVertex(int countIn,int countOut);
    InfoVertex(int countIn,int countOut,QVector<int> lineIns,QVector<int> lineOuts);
    InfoVertex(QMap<QString,QVariant> map);
    QMap<QString,QVariant> ToJson();
    ~InfoVertex();

public:
    int countOut;                //Кол-во вылетных линий
    int countIn;                 //Кол-во входящих линий
    QVector<int> lineOuts;       //Кол-во полос для каждой линии вылетной
    QVector<int> lineIns;        //Кол-во полос для каждой входной линии
    QString dgis;
    QString description;
};

#endif // INFOVERTEX_H

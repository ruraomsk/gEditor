#ifndef SUPPORT_H
#define SUPPORT_H

#include <QtGlobal>
#include <QApplication>
#include <QString>
#include <QErrorMessage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QList>
#include <QtSql>
#include <QMessageBox>
#include <QRandomGenerator>
class IDs{
public:
    IDs();
    QString toString();
    QString getCode();

public:
    int region;
    int id;
    int area;
    QString description;
    QString dgis;
};

class Support
{

public:
    static int RandomBetween(int low, int high);
    static int RandomBetween(int low, int high, int seed);
    static void ErrorMessage(QString message);
    static void Message(QString message);
    static QList<IDs> listCrosses(int region);
    static QMap<int,QString> getRegions();
    static QString CorrectNameFile(QString namefile,QString list);
    static bool execSQL(QString path);
private:
};


#endif // SUPPORT_H

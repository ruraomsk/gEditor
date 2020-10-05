#include "support.h"


int Support::RandomBetween(int low, int high)
{
    return (QRandomGenerator::global()->generate() % ((high + 1) - low) + low);
}

void Support::ErrorMessage(QString message)
{
    QErrorMessage err;
    err.setModal(true);
    err.showMessage(message);
    err.exec();
    return;
}

void Support::Message(QString message)
{
    QMessageBox msg;
    msg.setModal(true);
    msg.setText(message);
    msg.exec();
    return;
}


QList<IDs> Support::listCrosses(int region)
{
    QList<IDs> result;
    QString w;
    QSqlQuery query;
    w.append(QString::asprintf("select id,area,describ,dgis from public.cross where region=%d  order by id ;",region));
    query.exec(w);
    while(query.next()){
        IDs ww;
        ww.region=region;
        ww.id=query.value(0).toInt();
        ww.area=query.value(1).toInt();
        ww.description=query.value(2).toString();
        ww.dgis=query.value(3).toString();
        result.append(ww);
    }
    return result;
}

QMap<int, QString> Support::getRegions()
{
    QMap<int, QString> result;
    QSqlQuery query;
    query.exec("select region,nameregion from public.region order by region;");
    while(query.next()){
        result[query.value(0).toInt()]=query.value(1).toString();
    }
    return result;
}


QString Support::CorrectNameFile(QString namefile,QString list)
{
    QFileInfo info(namefile);
    if (info.completeSuffix().size()!=0) return namefile;
    namefile+="."+list.split(" ")[0].remove("*.");
    return namefile;
}

bool Support::execSQL(QString path)
{
    QFile file(path);
    if (!file.exists()||!file.open(QIODevice::ReadOnly)) return false;
    QString str=file.readAll();
    file.close();
    QSqlQuery query;
    query.exec(str);
    return true;
}

IDs::IDs()
{

}

QString IDs::toString()
{
    return QString::asprintf("регион %d район %d ID %d",region,area,id);
}
//Возвращает Уникальный ключ вершины вида RRRRRAAAAADDDDD
QString IDs::getCode()
{
    return QString::asprintf("%5.5d%5.5d%5.5d",region,area,id);
}

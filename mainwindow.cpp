#include "mainwindow.h"
#include "ui_mainwindow.h"
extern Setup ini;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(ini.getSize("window/size"));
    setWindowTitle(ini.getString("name"));
    setGeometry(ini.getPoint("window/point").x(),ini.getPoint("window/point").y(),ini.getSize("window/size").width(),ini.getSize("window/size").height());
    db=QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(ini.getString("db/hostname"));
    db.setPort(ini.getInt("db/port"));
    db.setDatabaseName(ini.getString("db/dbname"));
    db.setUserName(ini.getString("db/username"));
    db.setPassword(ini.getString("db/password"));
    bool ok=db.open();
    if (!ok){
        return;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *size)
{
    ini.setSize("window/size",size->size());
    QMainWindow::resizeEvent(size);
}

void MainWindow::moveEvent(QMoveEvent *point)
{
    ini.setPoint("window/point",point->pos());
    QMainWindow::moveEvent(point);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
//    //    qDebug()<<"close"<<project.IsEmpty()<<project.isChanged;
//    QMessageBox *msg=new QMessageBox(this);
//    msg->setText("Есть несохраненные измения");
//    msg->setInformativeText("Может все-таки их сохраним?");
//    msg->setStandardButtons(QMessageBox::Save | QMessageBox::Discard );
//    msg->setDefaultButton(QMessageBox::Save);
//    msg->exec();
//    msg->close();
//    QMainWindow::closeEvent(event);
}

void MainWindow::openFile()
{
    qDebug()<<"open";
}

void MainWindow::createMenus()
{
//    QMenu *menu=new QMenu;
//    menu=menuBar->addMenu("&Граф");
//    menu->addAction("Открыть",&MainWindow::openFile);
}

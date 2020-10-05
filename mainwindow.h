#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QResizeEvent>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QStyleFactory>
#include "setup/setup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void resizeEvent(QResizeEvent *size);
    virtual void moveEvent(QMoveEvent *point);
    virtual void closeEvent(QCloseEvent *event);

private:
private slots:
    void openFile();
private:
    Ui::MainWindow *ui;
    void createMenus();
//    QWidget *centralwidget;
//    QMenuBar *menuBar;
//    QStatusBar *statusBar;
//    QToolBar   *toolBar;

    QSqlDatabase db;


};
#endif // MAINWINDOW_H

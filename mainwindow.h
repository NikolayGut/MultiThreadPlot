#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <coordinates.h>
#include <mythread.h>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addPoint(double x, double y);
    void clearData();
    void plot();
    Coordinates *coord;
    MyThread *thread;

private slots:
    void on_pushBtnStart_clicked();
    void clearPlot();
    void handleData(const double &x,const double &y);
    void catchAction();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y;

};

#endif // MAINWINDOW_H

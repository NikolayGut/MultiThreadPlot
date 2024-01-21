#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "coordinates.h"

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
    Coordinates *coord;

private slots:
    void on_pushBtnStart_clicked();
    void clearPlot();

public slots:
    void plot();
    void handleData(const double &x,const double &y);
    void catchStop();
    void catchClear();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y;

};

#endif // MAINWINDOW_H

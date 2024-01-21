#include "mainwindow.h"
#include "qcustomplot.h"
#include "mythread.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->xAxis->setRange(0, 100);
    ui->plot->yAxis->setRange(0, 100);
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph()->setLineStyle(QCPGraph::lsNone);
}

MainWindow::~MainWindow()
{
    delete coord;
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
    qDebug() << QThread::currentThreadId();
    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::handleData(const double &x, const double &y)
{
    addPoint(x, y);
    plot();
}

void MainWindow::on_pushBtnStart_clicked()
{
    coord = new Coordinates();
    MyThread *thread = new MyThread();

    coord->moveToThread(thread);
    coord->requestedStop = false;
    coord->requestedClear = false;
    coord->pauseManager.wakeAll();

    QObject::connect(thread, &MyThread::started, coord, &Coordinates::makeCoordinates);

    QObject::connect(coord, &Coordinates::dataReady, this, &MainWindow::handleData);

    QObject::connect(coord, &Coordinates::finishThread, thread, &MyThread::quit);

    QObject::connect(thread, &MyThread::finished, this, &MainWindow::clearPlot);

    QObject::connect(ui->pushBtnStop, &QPushButton::clicked, this, &MainWindow::catchStop);

    QObject::connect(ui->pushBtnClear, &QPushButton::clicked, this, &MainWindow::catchClear);

    thread->start();

}

void MainWindow::clearPlot()
{
    clearData();
    plot();
}

void MainWindow::catchClear()
{
    if (coord->thread()->isRunning()) {
        coord->requestedClear = true;
        coord->pauseManager.wakeAll();
    }
    else {
        QMessageBox::warning(this, "Warning!", "MyThread is not running!");
    }
}

void MainWindow::catchStop()
{
    if (coord->thread()->isRunning())
        coord->requestedStop = true;
    else {
        QMessageBox::warning(this, "Warning!", "MyThread is not running!");
    }
}

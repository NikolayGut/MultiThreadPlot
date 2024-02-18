#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    coord = new Coordinates();
    thread = new MyThread();
    coord->moveToThread(thread);

    ui->setupUi(this);
    ui->plot->xAxis->setRange(0, 100);
    ui->plot->yAxis->setRange(0, 100);
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph()->setLineStyle(QCPGraph::lsNone);

    QObject::connect(thread, &MyThread::started, coord, &Coordinates::makeCoordinates);

    QObject::connect(coord, &Coordinates::dataReady, this, &MainWindow::handleData);

    QObject::connect(coord, &Coordinates::finishThread, thread, &MyThread::quit);

    QObject::connect(thread, &MyThread::finished, this, &MainWindow::clearPlot);

    QObject::connect(ui->pushBtnStop, &QPushButton::clicked, this, &MainWindow::catchAction);

    QObject::connect(ui->pushBtnClear, &QPushButton::clicked, this, &MainWindow::catchAction);
}

MainWindow::~MainWindow()
{
    delete coord;
    delete thread;
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
    coord->requestedStop = false;
    coord->requestedClear = false;
    coord->pauseManager.wakeAll();

    if(!thread->isRunning())
        thread->start();
}

void MainWindow::clearPlot()
{
    clearData();
    plot();
}

void MainWindow::catchAction()
{
    QString senderName = sender()->objectName();
    if (coord->thread()->isRunning()) {
        if (senderName == "pushBtnStop")
            coord->requestedStop = true;
        else if (senderName == "pushBtnClear") {
            coord->requestedClear = true;
            coord->pauseManager.wakeAll();
        }
    }
    else {
        QMessageBox::warning(this, "Warning!", "MyThread is not running!");
    }
}


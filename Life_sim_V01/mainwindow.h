#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QtCore>
#include <QDir>
#include "Logger.h"
#include "load_data.h"
#include "qcustomplot.h"
#include "axistag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString fileName;
    Logger *logger;
    _load_data *load = nullptr;



private slots:
    void on_loadDirectory_clicked();

    void on_directoryBox_currentIndexChanged(int index);

    void on_patientBox_currentIndexChanged(int index);

    void on_startbutton_clicked();

    void defineElements(double e, int index);

    double obtemElements(int index);

    void criaGrafico();

    void on_stopbutton_clicked();

    void on_SET_clicked();

    void timerSlot();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    double elements[12] = {0.0};
    bool stop = false;
    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    //QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
    QTimer mDataTimer;

};
#endif // MAINWINDOW_H

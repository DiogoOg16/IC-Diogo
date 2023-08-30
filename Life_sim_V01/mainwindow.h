#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDir>
#include "Logger.h"
#include "load_data.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString fileName;
    Logger *logger;
    _load_data *load = nullptr;

    //void addPoint(float x, float y);
    //void clearData();
    //void plot();

private slots:
    void on_loadDirectory_clicked();

    void on_directoryBox_currentIndexChanged(int index);

    void on_patientBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
   // QVector<float> qv_x, qv_y;
};
#endif // MAINWINDOW_H

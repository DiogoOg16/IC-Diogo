#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <QObject>
#include <QList>
#include <vector>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include "Logger.h"
#include <iostream>

class load_data : public QObject
{
    Q_OBJECT
public:
        load_data(Logger *logger = nullptr, QString file = "");
        ~load_data();
        

    QVector<double> obtemRel_time();
    QVector<double> obtemAcc_x();
    QVector<double> obtemAcc_y();
    QVector<double> obtemAcc_z();
    QVector<double> obtemGyr_x();
    QVector<double> obtemGyr_y();
    QVector<double> obtemGyr_z();
    QVector<double> obtemAzi();
    QVector<double> obtemPitch();
    QVector<double> obtemRoll();
    QString obtemFile();

    double elem1Acc_x();
    void acc_x_Pop();
    void defineRel_time(double rt);
    void defineAcc_x(double accx);
    void defineAcc_y(double accy);
    void defineAcc_z(double accz);
    void defineGyr_x(double gyrx);
    void defineGyr_y(double gyry);
    void defineGyr_z(double gyrz);
    void defineAzi(double azi);
    void definePitch(double p);
    void defineRoll(double r);
    void defineFileDyr(QString f);

    void data_parser();
    void printParser();

private:
    Logger* logger;
    QString fileDyr;
    QStringList activity_list;
    QVector<double> rel_time;
    QVector<double> acc_x;
    QVector<double> acc_y;
    QVector<double> acc_z;
    QVector<double> gyr_x;
    QVector<double> gyr_y;
    QVector<double> gyr_z;
    QVector<double> azi;
    QVector<double> pitch;
    QVector<double> roll;
    
signals:

public slots:
    QStringList get_activity_list(void);    
};

#endif // LOAD_DATA_H

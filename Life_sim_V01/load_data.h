#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <QObject>
#include <QList>

#include "Logger.h"

class _load_data : public QObject
{
    Q_OBJECT
public:
    explicit _load_data(QObject *parent = nullptr, Logger *logger = nullptr, QString file = "", QString dirPath = "" );

private:
    Logger* logger;
    QStringList activity_list;

signals:

public slots:
    QStringList get_activity_list(void);
};

#endif // LOAD_DATA_H

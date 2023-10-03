#include "load_data.h"

_load_data::_load_data(QObject *parent, Logger *logger, QString filename)
    : QObject{parent}
{
    this->logger = logger;

    if(filename.isEmpty())
    {
        this->logger->write("No file was founded!");
        //return;
    }


    /* Open file */
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        this->logger->write("Cannot open " + filename + " file!");
        return;
    }


}

QStringList _load_data::get_activity_list(void)
{
    return activity_list;
}

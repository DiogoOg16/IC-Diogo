#include "load_data.h"


_load_data::_load_data(QObject *parent, Logger *logger, QString filename)
    : QObject{parent}
{
    //QString temp_string;
    //QStringList raw_line;

    this->logger = logger;

    //label_list.begin();
    activity_list.begin();
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


    QString conteudo = file.readAll();
    this->logger->write(conteudo);
    /* Get labels */
    /*while (!file.atEnd())
    {
        temp_string = file.readLine();
        raw_line = temp_string.split('\n');
        label_list.append(raw_line[0]);
    }*/

    file.close();
}

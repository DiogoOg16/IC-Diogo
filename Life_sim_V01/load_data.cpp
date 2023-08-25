#include "load_data.h"

_load_data::_load_data(QObject *parent, Logger *logger, QString filename, QString directory)
    : QObject{parent}
{
    this->logger = logger;

    //label_list.begin();
    //activity_list.begin();
    if(filename.isEmpty())
    {
        this->logger->write("No file was founded!");
        //return;
    }
    QString path = "C:/Users/diogo/OneDrive/Área de Trabalho/MobiAct_Dataset_v2.0/Annotated Data/";
    path += directory + "/";
    //filename =  "C:/Users/diogo/OneDrive/Área de Trabalho/MobiAct_Dataset_v2.0/Annotated Data/BSC/BSC_1_1_annotated.csv";
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

QStringList _load_data::get_activity_list(void)
{
    return activity_list;
}

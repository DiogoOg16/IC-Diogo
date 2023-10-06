#include "load_data.h"

load_data::load_data(Logger *logger, QString filename)
    //: QObject{parent}
{
    this->logger = logger;
    fileDyr = filename;
}
load_data::~load_data(){}


void load_data::printParser(){
    for (int i = 0; i < obtemAcc_x().size(); i++){
         std::cout << "printParser:"<< std::endl;
        std::cout <<  obtemAcc_x()[i] << std::endl;
    }
}


void load_data::data_parser(){
     /* Open file */
    QString arq = obtemFile();
    QFile file(arq);
    if (!file.open(QIODevice::ReadOnly)) {
    std::cerr << "Failed to open file" << std::endl;
    }

    QTextStream stream(&file);

    // Read the first line of the file and ignore it.
    stream.readLine();
    
    while (!file.atEnd()) {
        double valor = stream.readLine().split(",").at(2).toDouble();
        defineAcc_x(valor);
        //obtemAcc_x().push_back(valor);
        //defineAcc_x(valor);
    }
      file.close();
}

QStringList load_data::get_activity_list(void)
{
    return activity_list;
}
void load_data::defineFileDyr(QString f){
    fileDyr = f;
}
void load_data::defineRel_time(double rt){
    rel_time.push_back(rt);
}
void load_data::defineAcc_x(double accx){
        acc_x.push_back(accx);
}
void load_data::defineAcc_y(double accy){
        acc_y.push_back(accy);
}
void load_data::defineAcc_z(double accz){}
void load_data::defineGyr_x(double gyrx){}
void load_data::defineGyr_y(double gyry){}
void load_data::defineGyr_z(double gyrz){}
void load_data::defineAzi(double azi){}
void load_data::definePitch(double p){}
void load_data::defineRoll(double r){}

QString load_data::obtemFile(){
    return fileDyr;
}
QVector<double> load_data::obtemRel_time(){
    return rel_time;
}
QVector<double> load_data::obtemAcc_x(){
    return acc_x;
}
QVector<double> load_data::obtemAcc_y(){
    return acc_y;
}
QVector<double> load_data::obtemAcc_z(){
    return acc_z;
}
QVector<double> load_data::obtemGyr_x(){
    return gyr_x;
}
QVector<double> load_data::obtemGyr_y(){
    return gyr_y;
}
QVector<double> load_data::obtemGyr_z(){
    return gyr_z;
}
QVector<double> load_data::obtemAzi(){
    return azi;
}
QVector<double> load_data::obtemPitch(){
    return pitch;
}
QVector<double> load_data::obtemRoll(){
    return gyr_x;
}
double load_data::elem1Acc_x(){
    return acc_x[0];
}
void load_data::acc_x_Pop(){
    acc_x.pop_front();
}

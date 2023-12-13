#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLegend>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <string>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <QDateTime>
#include <Qlabel>
#include <iostream>
#include <string.h>
#include <vector>
#include <QHostAddress>
#include "lifes_protocol.h"

//#include <QHostAddress>
//#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    mPlot(0),
    mTag1(0),
    mTag2(0),
    mTag3(0),
    mTag4(0),
    mTag5(0),
    mTag6(0),
    mTag7(0),
    mTag8(0),
    mTag9(0)
{
    ui->setupUi(this);



    //LOG File
    fileName = "logger.txt";
    logger = new Logger(this, fileName, this->ui->plainTextEdit);
    logger->write("Hello Qt");
    Lifes_Protocol.Init_Lifes_SIM(logger);
    //load->data_parser();
    timerTCP = new QTimer(this);
    connect(timerTCP, SIGNAL(timeout()), this, SLOT(SendInFreq()));
    timerCheck = new QTimer(this);
    connect(timerCheck, SIGNAL(timeout()), this, SLOT(obtemAmostras()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString Dpath;
QString caminho;
void MainWindow::on_loadDirectory_clicked()
{
    // Get the path of the directory that the user selected.
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Select a Directory");
    Dpath = directoryPath;

    // Clear the list widget.
    this->ui->directoryBox->clear();

    // Create a list of the folders in the directory.
    QDir directory(Dpath);
    QStringList folders = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);


    // Add the folders to the list widget.
    this->ui->directoryBox->addItems(folders);

}




void MainWindow::on_directoryBox_currentIndexChanged(int index)
{
    // Get the selected folder name.
    QString selectedFolderName =  this->ui->directoryBox->currentText();

    // Create a list of the files in the selected folder.
    QDir fileDir(Dpath + "/" + selectedFolderName);
    //Convertendo o path do diretorio em uma string
    caminho = fileDir.path();

    //Pegando a lista de arquivos dentro da atividade escolhida
    QStringList files = fileDir.entryList(QDir::Files);

    this->ui->patientBox->clear();
    this->ui->patientBox->addItems(files);
}


void MainWindow::setLabel(QString label)
{
     //Identificar a atividade para mostrar na label
setLocation();
    if(label == "BSC") ui->labelAtividadeDado->setText("Back sitting chair");
    else if (label == "CHU") ui->labelAtividadeDado->setText("Chair Up");
    else if (label == "CSI") ui->labelAtividadeDado->setText("Car Stepping-In");
    else if (label == "CSO") ui->labelAtividadeDado->setText("Chair Stepping-Out");
    else if (label == "FKL") ui->labelAtividadeDado->setText("Fall Front Knees Lying");
    else if (label == "FOL") ui->labelAtividadeDado->setText("Fall Forward Lying");
    else if (label == "JOG") ui->labelAtividadeDado->setText("Jogging");
    else if (label == "JUM") ui->labelAtividadeDado->setText("Jumping");
    else if (label == "SBE") ui->labelAtividadeDado->setText("Exercising");
    else if (label == "SBW") ui->labelAtividadeDado->setText("Working");
    else if (label == "SCH") ui->labelAtividadeDado->setText("Sit Chair");
    else if (label == "SDL") ui->labelAtividadeDado->setText("Side Ward Lying");
    else if (label == "SIT") ui->labelAtividadeDado->setText("Sitting On Chair");
    else if (label == "SLH") ui->labelAtividadeDado->setText("Leaving Home");
    else if (label == "SLW") ui->labelAtividadeDado->setText("Leaving Work");
    else if (label == "SRH") ui->labelAtividadeDado->setText("Return Home");
    else if (label == "STD") ui->labelAtividadeDado->setText("Standing");
    else if (label == "STN") ui->labelAtividadeDado->setText("Stairs Down");
    else if (label == "STU") ui->labelAtividadeDado->setText("Stairs Up");
    else if (label == "WAL") ui->labelAtividadeDado->setText("Walking");
    else if (label == "LYI") ui->labelAtividadeDado->setText("Laying");
    else ui->labelAtividadeDado->setText("Atividade não reconhecida");

}
QString joj;
void MainWindow::setLocation()
{
     //Identificar a atividade para mostrar na label
    QString local1 = "ROM";
    QString local2 = "LRM";
    QString local3 = "KTC";
    QString local4 = "BTH";
    QString local5 = "GRG";
    QString local = "";

    local = local1;
    joj = local1;
    if(local == "ROM") ui->lDado->setText("Room");
    else if (local == "LRM") ui->lDado->setText("Living Room");
    else if (local == "KTC") ui->lDado->setText("Kitchen");
    else if (local == "BTH") ui->lDado->setText("Bathroom");
    else if (local == "GRG") ui->lDado->setText("Garage");
    else ui->lDado->setText("Local não reconhecido");

}

QString temp;
void MainWindow::on_patientBox_currentIndexChanged(int index)
{
    //adicionar a primeira linha e jogar numa QStringList
    QString arquivoSelecionado =  this->ui->patientBox->currentText();
    QDir d(caminho + "/" + arquivoSelecionado);
    QString bloco = d.path();
    temp = bloco;
    this->logger->write(temp);
    temp = temp.replace("/", "\\");
    bloco = bloco.replace("/", "\\");
    load = new load_data(bloco);

    load->defineFileDyr(bloco);
}



QVector<double> dados;
void MainWindow::on_SET_clicked()
{
    load->data_parser();
    logger->write("DataSet definido!");

    //load->data_parser();
    //lp->defineLoad(load);
    //this->logger->write(lp->obtemLoad());

}


void MainWindow::criaGrafico()
{
    criaGraficoAccX();
    criaGraficoAccY();
    criaGraficoAccZ();
    criaGraficoGyrX();
    criaGraficoGyrY();
    criaGraficoGyrZ();
    criaGraficoAzimuth();
    criaGraficoPitch();
    criaGraficoRoll();
}
bool pGrafico =0;
bool pEnvio = 0;


int tempoTimer = 5000;

void MainWindow::on_stopbutton_clicked()
{
    //stop = true;
    if(mDataTimer.isActive()) mDataTimer.stop();
    if(timerTCP->isActive()) timerTCP->stop();
    timerCheck->stop();
}

void MainWindow::on_startbutton_clicked()
{
    logger->write("Started!");
    //timerTCP->start(tempoTimer);
    timerCheck->start(1000);
    if(pGrafico == 0 && pEnvio == 0)
    {
        criaGrafico();
        pGrafico = 1;
    }
    if(pGrafico == 1){
        mDataTimer.start();
    }
    if(pEnvio == 1){
        timerTCP->start();
    }

}

void MainWindow::on_connectbutton_clicked()
{
 //socket
    Lifes_Protocol.lifes_sim_tools.socketTCP.Connect(this->ui->ipTextBox->text(), this->ui->portTextBox->text().toUInt());
    if(Lifes_Protocol.lifes_sim_tools.socketTCP.isConnected())logger->write("Connected!");
    else logger->write("Something is wrong!");
}

unsigned int timestamp = 1;
void MainWindow::SendInFreq()
{
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_CRV_ACCEL);
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_CRV_GYR);
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_CRV_MAG);
        Lifes_Protocol.lifes_SIM_comando(CMD_LABEL);
        Lifes_Protocol.lifes_SIM_comando(CMD_ROOM);

        timestamp++;
        //logger->write("Sent Accel Curve!");
        //contador += 9;
        desativaTimer();
}

QString amostrasPorSegundo;
void MainWindow::obtemAmostras()
{

        amostrasPorSegundo = QString::number(contador);
        logger->write(amostrasPorSegundo);
        contador = 0;
}

void MainWindow::ativaTimer(){
        //jogar isso pro desativa timer
        /*if(load->obtemRoll().size() != 1){

        load->pop_all();
     }else{
        logger->write("Acabou o envio!!!");
     }*/

        mDataTimer.stop();
        pGrafico = 0;
        pEnvio = 1;
        timerTCP->start(tempoTimer);
}

void MainWindow::desativaTimer(){
        if(Lifes_Protocol.semaforo()){
        if(load->obtemRoll().size() != 1){

            load->pop_all();
        }else{
            logger->write("Acabou o envio!!!");
        }
        contador++;
        timerTCP->stop();
        pGrafico = 1;
        pEnvio = 0;
        Lifes_Protocol.reset();
        mDataTimer.start(tempoTimer);
        }
}




void MainWindow::timerSlot()
{

    double ponto = load->elem1Acc_x();
    Lifes_Protocol.atualiza_acc_x(ponto,timestamp);
    setLabel(load->elem1Label());
    // calculate and add a new data point to each graph:
    mGraph1->addData(mGraph1->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->acc_x_widget->xAxis->rescale();
    mGraph1->rescaleValueAxis(false, true);
    ui->acc_x_widget->xAxis->setRange(ui->acc_x_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
    mTag1->updatePosition(graph1Value);
    mTag1->setText(QString::number(graph1Value, 'f', 2));

    ui->acc_x_widget->replot();

}


void MainWindow::timerSlotY()
{
    double ponto = load->elem1Acc_y();
    Lifes_Protocol.atualiza_acc_y(ponto);

    // calculate and add a new data point to each graph:
    mGraph2->addData(mGraph2->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->acc_y_widget->xAxis->rescale();
    mGraph2->rescaleValueAxis(false, true);
    ui->acc_y_widget->xAxis->setRange(ui->acc_y_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
    mTag2->updatePosition(graph2Value);
    mTag2->setText(QString::number(graph2Value, 'f', 2));

    ui->acc_y_widget->replot();
}


void MainWindow::timerSlotAccZ(){

    double ponto = load->elem1Acc_z();
    Lifes_Protocol.atualiza_acc_z(ponto);

    // calculate and add a new data point to each graph:
    mGraph3->addData(mGraph3->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->acc_z_widget->xAxis->rescale();
    mGraph3->rescaleValueAxis(false, true);
    ui->acc_z_widget->xAxis->setRange(ui->acc_z_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph3->dataMainValue(mGraph3->dataCount()-1);
    mTag3->updatePosition(graph2Value);
    mTag3->setText(QString::number(graph2Value, 'f', 2));

    ui->acc_z_widget->replot();

}

void MainWindow::timerSlotGyrX(){
    double ponto = load->elem1Gyr_x();
    Lifes_Protocol.atualiza_gyr_x(ponto,timestamp);

    // calculate and add a new data point to each graph:
    mGraph4->addData(mGraph4->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->gyr_x_widget->xAxis->rescale();
    mGraph4->rescaleValueAxis(false, true);
    ui->gyr_x_widget->xAxis->setRange(ui->gyr_x_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph4->dataMainValue(mGraph4->dataCount()-1);
    mTag4->updatePosition(graph2Value);
    mTag4->setText(QString::number(graph2Value, 'f', 2));

    ui->gyr_x_widget->replot();
}

void MainWindow::timerSlotGyrY(){
    double ponto = load->elem1Gyr_y();
    Lifes_Protocol.atualiza_gyr_y(ponto);
    if(load->obtemGyr_y().size() != 1){
        //load->gyr_y_Pop();
    }
    // calculate and add a new data point to each graph:
    mGraph5->addData(mGraph5->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->gyr_y_widget->xAxis->rescale();
    mGraph5->rescaleValueAxis(false, true);
    ui->gyr_y_widget->xAxis->setRange(ui->gyr_y_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph5->dataMainValue(mGraph5->dataCount()-1);
    mTag5->updatePosition(graph2Value);
    mTag5->setText(QString::number(graph2Value, 'f', 2));

    ui->gyr_y_widget->replot();
}

void MainWindow::timerSlotGyrZ(){
    double ponto = load->elem1Gyr_z();
    Lifes_Protocol.atualiza_gyr_z(ponto);

    // calculate and add a new data point to each graph:
    mGraph6->addData(mGraph6->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->gyr_z_widget->xAxis->rescale();
    mGraph6->rescaleValueAxis(false, true);
    ui->gyr_z_widget->xAxis->setRange(ui->gyr_z_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph6->dataMainValue(mGraph6->dataCount()-1);
    mTag6->updatePosition(graph2Value);
    mTag6->setText(QString::number(graph2Value, 'f', 2));
    ui->gyr_z_widget->replot();
}

void MainWindow::timerSlotAzimuth(){
    double ponto = load->elem1Azi();
    Lifes_Protocol.atualiza_azi(ponto,timestamp);

    // calculate and add a new data point to each graph:
    mGraph7->addData(mGraph7->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->azimuth_widget->xAxis->rescale();
    mGraph7->rescaleValueAxis(false, true);
    ui->azimuth_widget->xAxis->setRange(ui->azimuth_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph7->dataMainValue(mGraph7->dataCount()-1);
    mTag7->updatePosition(graph2Value);
    mTag7->setText(QString::number(graph2Value, 'f', 2));

    ui->azimuth_widget->replot();
}

void MainWindow::timerSlotPitch(){
    double ponto = load->elem1Pitch();
    Lifes_Protocol.atualiza_pitch(ponto);

    // calculate and add a new data point to each graph:
    mGraph8->addData(mGraph8->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->pitch_widget->xAxis->rescale();
    mGraph8->rescaleValueAxis(false, true);
    ui->pitch_widget->xAxis->setRange(ui->pitch_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph8->dataMainValue(mGraph8->dataCount()-1);
    mTag8->updatePosition(graph2Value);
    mTag8->setText(QString::number(graph2Value, 'f', 2));

    ui->pitch_widget->replot();
}

void MainWindow::timerSlotRoll(){
    double ponto = load->elem1Roll();
    Lifes_Protocol.atualiza_roll(ponto);

    // calculate and add a new data point to each graph:
    mGraph9->addData(mGraph9->dataCount(), ponto);

    // make key axis range scroll with the data:
    ui->roll_widget->xAxis->rescale();
    mGraph9->rescaleValueAxis(false, true);
    ui->roll_widget->xAxis->setRange(ui->roll_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph2Value = mGraph9->dataMainValue(mGraph9->dataCount()-1);
    mTag9->updatePosition(graph2Value);
    mTag9->setText(QString::number(graph2Value, 'f', 2));

    ui->roll_widget->replot();

    QString acao = load->elem1Label();
    Lifes_Protocol.atualiza_label(acao, timestamp);

    QString gps = joj;
        //load->elem1Local();
    Lifes_Protocol.atualiza_gps(gps, timestamp);

    ativaTimer();

}






void MainWindow::criaGraficoAccX(){
    // configure plot to have two right axes:
    ui->acc_x_widget->yAxis->setTickLabels(false);
    connect(ui->acc_x_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->acc_x_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->acc_x_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph1 = ui->acc_x_widget->addGraph(ui->acc_x_widget->xAxis, ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph1->setPen(QPen(QColor(0, 180, 60)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(tempoTimer);

}

void MainWindow::criaGraficoAccY(){
    ui->acc_y_widget->yAxis->setTickLabels(false);
    connect(ui->acc_y_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->acc_y_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->acc_y_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->acc_y_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->acc_y_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph2 = ui->acc_y_widget->addGraph(ui->acc_y_widget->xAxis, ui->acc_y_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph2->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotY()));

}

void MainWindow::criaGraficoAccZ(){
    ui->acc_z_widget->yAxis->setTickLabels(false);
    connect(ui->acc_z_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->acc_z_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->acc_z_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->acc_z_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->acc_z_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph3 = ui->acc_z_widget->addGraph(ui->acc_z_widget->xAxis, ui->acc_z_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph3->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag3 = new AxisTag(mGraph3->valueAxis());
    mTag3->setPen(mGraph3->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotAccZ()));
}

void MainWindow::criaGraficoGyrX(){
    ui->gyr_x_widget->yAxis->setTickLabels(false);
    connect(ui->gyr_x_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->gyr_x_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->gyr_x_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->gyr_x_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->gyr_x_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph4 = ui->gyr_x_widget->addGraph(ui->gyr_x_widget->xAxis, ui->gyr_x_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph4->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag4 = new AxisTag(mGraph4->valueAxis());
    mTag4->setPen(mGraph4->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotGyrX()));
}

void MainWindow::criaGraficoGyrY(){
    ui->gyr_y_widget->yAxis->setTickLabels(false);
    connect(ui->gyr_y_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->gyr_y_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->gyr_y_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->gyr_y_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->gyr_y_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph5 = ui->gyr_y_widget->addGraph(ui->gyr_y_widget->xAxis, ui->gyr_y_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph5->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag5 = new AxisTag(mGraph5->valueAxis());
    mTag5->setPen(mGraph5->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotGyrY()));
}

void MainWindow::criaGraficoGyrZ(){
    ui->gyr_z_widget->yAxis->setTickLabels(false);
    connect(ui->gyr_z_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->gyr_z_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->gyr_z_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->gyr_z_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->gyr_z_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph6 = ui->gyr_z_widget->addGraph(ui->gyr_z_widget->xAxis, ui->gyr_z_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph6->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag6 = new AxisTag(mGraph6->valueAxis());
    mTag6->setPen(mGraph6->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotGyrZ()));
}

void MainWindow::criaGraficoAzimuth(){
    ui->azimuth_widget->yAxis->setTickLabels(false);
    connect(ui->azimuth_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->azimuth_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->azimuth_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->azimuth_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->azimuth_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph7 = ui->azimuth_widget->addGraph(ui->azimuth_widget->xAxis, ui->azimuth_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph7->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag7 = new AxisTag(mGraph7->valueAxis());
    mTag7->setPen(mGraph7->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotAzimuth()));
}

void MainWindow::criaGraficoPitch(){
    ui->pitch_widget->yAxis->setTickLabels(false);
    connect(ui->pitch_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->pitch_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->pitch_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->pitch_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->pitch_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph8 = ui->pitch_widget->addGraph(ui->pitch_widget->xAxis, ui->pitch_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph8->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag8 = new AxisTag(mGraph8->valueAxis());
    mTag8->setPen(mGraph8->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotPitch()));
}

void MainWindow::criaGraficoRoll(){
    ui->roll_widget->yAxis->setTickLabels(false);
    connect(ui->roll_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->roll_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->roll_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->roll_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->roll_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph9 = ui->roll_widget->addGraph(ui->roll_widget->xAxis, ui->roll_widget->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph9->setPen(QPen(QColor(0, 0, 255)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag9 = new AxisTag(mGraph9->valueAxis());
    mTag9->setPen(mGraph9->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlotRoll()));
}






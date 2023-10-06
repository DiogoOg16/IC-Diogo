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

//#include <QHostAddress>
//#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    mPlot(0),
    mTag1(0),
    mTag2(0)
{
    ui->setupUi(this);

    //LOG File
    fileName = "logger.txt";
    logger = new Logger(this, fileName, this->ui->plainTextEdit);
    logger->write("Hello Qt");

//QVBoxLayout *layout = new QVBoxLayout;
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
    //this->logger->write(files);


    this->ui->patientBox->clear();
    this->ui->patientBox->addItems(files);


    //Identificar a atividade para mostrar na label

    if(selectedFolderName == "BSC") ui->labelAtividadeDado->setText("Back sitting chair");
    else if (selectedFolderName == "CHU") ui->labelAtividadeDado->setText("Chair Up");
    else if (selectedFolderName == "CSI") ui->labelAtividadeDado->setText("Car Stepping-In");
    else if (selectedFolderName == "CSO") ui->labelAtividadeDado->setText("Chair Stepping-Out");
    else if (selectedFolderName == "FKL") ui->labelAtividadeDado->setText("Fall Front Knees Lying");
    else if (selectedFolderName == "FOL") ui->labelAtividadeDado->setText("Fall Forward Lying");
    else if (selectedFolderName == "JOG") ui->labelAtividadeDado->setText("Jogging");
    else if (selectedFolderName == "JUM") ui->labelAtividadeDado->setText("Jumping");
    else if (selectedFolderName == "SBE") ui->labelAtividadeDado->setText("Exercising");
    else if (selectedFolderName == "SBW") ui->labelAtividadeDado->setText("Working");
    else if (selectedFolderName == "SCH") ui->labelAtividadeDado->setText("Sit Chair");
    else if (selectedFolderName == "SDL") ui->labelAtividadeDado->setText("Side Ward Lying");
    else if (selectedFolderName == "SIT") ui->labelAtividadeDado->setText("Sitting On Chair");
    else if (selectedFolderName == "SLH") ui->labelAtividadeDado->setText("Leaving Home");
    else if (selectedFolderName == "SLW") ui->labelAtividadeDado->setText("Leaving Work");
    else if (selectedFolderName == "SRH") ui->labelAtividadeDado->setText("Return Home");
    else if (selectedFolderName == "STD") ui->labelAtividadeDado->setText("Standing");
    else if (selectedFolderName == "STN") ui->labelAtividadeDado->setText("Stairs Down");
    else if (selectedFolderName == "STU") ui->labelAtividadeDado->setText("Stairs Up");
    else if (selectedFolderName == "WAL") ui->labelAtividadeDado->setText("Walking");
    else ui->labelAtividadeDado->setText("Atividade não reconhecida");



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
    load = new load_data(logger,bloco);
    load->defineFileDyr(bloco);
}



QVector<double> dados;
void MainWindow::on_SET_clicked()
{
    /* Open file */
  /*  QFile file(temp);
    if (!file.open(QIODevice::ReadOnly)) {
    std::cerr << "Failed to open file" << std::endl;
    }

    QTextStream stream(&file);

    // Read the first line of the file and ignore it.
    stream.readLine();

    while (!file.atEnd()) {
        double valor = stream.readLine().split(",").at(2).toDouble();
        dados.push_back(valor);
    }
      file.close();
*/
    load->data_parser();
    this->logger->write("SETADO");
    //std::cout<<"PUTS" << std::endl;
    //load->printParser();
    //this->logger->write("SETADO");

    /*for (int i = 0; i < dados.size(); i++){
        std::cout << dados[i] << std::endl;
    }*/

    //std::reverse(dados.begin(), dados.end());

  //QVector<double> vec =  load->obtemAcc_x();

}




void MainWindow::on_startbutton_clicked()
{

    //mPlot = new QCustomPlot();
    //setCentralWidget(mPlot);
    criaGraficoAccX();

    // configure plot to have two right axes:
    /*ui->acc_x_widget->yAxis->setTickLabels(false);
    connect(ui->acc_x_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->acc_x_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->acc_x_widget->yAxis2->setVisible(true);
    ui->acc_x_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph1 = ui->acc_x_widget->addGraph(ui->acc_x_widget->xAxis, ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0));
    //mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    //mGraph2->setPen(QPen(QColor(0, 180, 60)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    //mTag2 = new AxisTag(mGraph2->valueAxis());
    //mTag2->setPen(mGraph2->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(40);*/



}



void MainWindow::timerSlot()
{
    //QVector<double> vec =  load->obtemAcc_x();
    //QVector<double> t = load->obtemAcc_x;
    double ponto = load->elem1Acc_x();
    if(load->obtemAcc_x().size() != 1){
        load->acc_x_Pop();
    }
    // calculate and add a new data point to each graph:
    mGraph1->addData(mGraph1->dataCount(), ponto);
    //mGraph2->addData(mGraph2->dataCount(), qCos(mGraph2->dataCount()/50.0)+qSin(mGraph2->dataCount()/50.0/0.4364)*0.15);

    // make key axis range scroll with the data:
    ui->acc_x_widget->xAxis->rescale();
    mGraph1->rescaleValueAxis(false, true);
    //mGraph2->rescaleValueAxis(false, true);
    ui->acc_x_widget->xAxis->setRange(ui->acc_x_widget->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
    //double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
    mTag1->updatePosition(graph1Value);
    //mTag2->updatePosition(graph2Value);
    mTag1->setText(QString::number(graph1Value, 'f', 2));
    //mTag2->setText(QString::number(graph2Value, 'f', 2));

    ui->acc_x_widget->replot();

}


void MainWindow::defineElements(double e, int index){
    elements[index] = e;
}

double MainWindow::obtemElements(int index){
    return elements[index];
}

void MainWindow::on_stopbutton_clicked()
{
    stop = true;
}

void MainWindow::criaGraficoAccX(){
    // configure plot to have two right axes:
    ui->acc_x_widget->yAxis->setTickLabels(false);
    connect(ui->acc_x_widget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->acc_x_widget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->acc_x_widget->yAxis2->setVisible(true);
    ui->acc_x_widget->axisRect()->addAxis(QCPAxis::atRight);
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph1 = ui->acc_x_widget->addGraph(ui->acc_x_widget->xAxis, ui->acc_x_widget->axisRect()->axis(QCPAxis::atRight, 0));
    //mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(0, 180, 60)));
    //mGraph2->setPen(QPen(QColor(0, 180, 60)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    //mTag2 = new AxisTag(mGraph2->valueAxis());
    //mTag2->setPen(mGraph2->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(40);
}

void MainWindow::criaGraficoAccY(){}

void MainWindow::criaGraficoAccZ(){}

void MainWindow::criaGraficoGyrX(){}

void MainWindow::criaGraficoGyrY(){}

void MainWindow::criaGraficoGyrZ(){}

void MainWindow::criaGraficoAzimuth(){}

void MainWindow::criaGraficoPitch(){}

void MainWindow::criaGraficoRoll(){}



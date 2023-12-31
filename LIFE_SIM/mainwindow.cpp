#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QHostAddress>
#include <QPixmap> //modificado


bool verificador = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Imagem
    QPixmap pix("C:/QT_pic/images.png");
    //QPixmap pix;
    //pix.load("C:/QT_pic/PUCRS.png");
    ui->labelPNG->setPixmap(pix.scaled(200,100,Qt::KeepAspectRatio));
    //LOG File
    fileName = "logger.txt";
    logger = new Logger(this, fileName, this->ui->logplaintextedit);
    logger->write("Hello Qt");

    //Init Protocol
    Lifes_Protocol.Init_Lifes_SIM(logger);

    timerTCP = new QTimer(this);
    connect(timerTCP, SIGNAL(timeout()), this, SLOT(SendInFreq()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectbutton_clicked()
{
    //socket
    //socketTCP.Connect();
    Lifes_Protocol.lifes_sim_tools.socketTCP.Connect(this->ui->ipTextBox->text(), this->ui->portTextBox->text().toUInt());
    logger->write("Connected!");
}

void MainWindow::on_startbutton_clicked()
{

    if (!verificador){
         logger->write("No file was inserted");
    }else{

    _ConfigPub config = Lifes_Protocol.Configuracoes_de_Publicacao();

    // Caso o gateway nao tenha configurado, utiliza as configuracoes da interface
    if (config.sampleRate == 0)
    {
        config.bitarray_enabled_sensors = 0;
        if (this->ui->enableACC->isChecked()) config.bitarray_enabled_sensors |= CONFIG_ENABLED_ACC;
        if (this->ui->enableBVP->isChecked()) config.bitarray_enabled_sensors |= CONFIG_ENABLED_BVP;
        if (this->ui->enableEDA->isChecked()) config.bitarray_enabled_sensors |= CONFIG_ENABLED_EDA;
        if (this->ui->enableHR->isChecked()) config.bitarray_enabled_sensors |= CONFIG_ENABLED_HR;
        if (this->ui->enableTemp->isChecked()) config.bitarray_enabled_sensors |= CONFIG_ENABLED_TEMP;
        config.sampleRate = this->ui->sampleRate->value();
        Lifes_Protocol.Configuracoes_pela_Interface(config);
    }

    if (parser->get_size())
    {
        parsed_index_sent = 0;
        logger->write("Started!");
        timerTCP->start(config.sampleRate * this->ui->pubInterval->value());
    }
    else
    {
        logger->write("Any data parsed to send!");
    }
    }
}

void MainWindow::on_stopbutton_clicked()
{
    logger->write("Stoped!");
    timerTCP->stop();
}

void MainWindow::SendInFreq()
{
    static unsigned char result;
    static _life_sim_csv_dataset value;
    _ConfigPub config = Lifes_Protocol.Configuracoes_de_Publicacao();

    if (parser->get_item(parsed_index_sent, &value))
    {
        /*  Update data to send */
        result = Lifes_Protocol.Atualiza_Curvas(CMD_TYPE_SENSOR_DATA_ACC, value.data.acc, parsed_index_sent);
        result += Lifes_Protocol.Atualiza_Curvas(CMD_TYPE_SENSOR_DATA_BVP, &value.data.bvp, parsed_index_sent);
        result += Lifes_Protocol.Atualiza_Curvas(CMD_TYPE_SENSOR_DATA_EDA, &value.data.eda, parsed_index_sent);
        result += Lifes_Protocol.Atualiza_Curvas(CMD_TYPE_SENSOR_DATA_HR, &value.data.hr, parsed_index_sent);
        result += Lifes_Protocol.Atualiza_Curvas(CMD_TYPE_SENSOR_DATA_TEMP, &value.data.temp, parsed_index_sent);

        /*  Error */
        if (result != 0)
            logger->write("Fail updating data structure");
    }
    else
    {
        logger->write("Get CSV parsed information fails");
        logger->write("Stopped!");
        timerTCP->stop();
        return;
    }

    /*  Enabled sensors to send */
    if (config.bitarray_enabled_sensors & CONFIG_ENABLED_ACC)
    {
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_SENSOR_DATA_ACC);
        logger->write("sent acc data");
    }
    if (config.bitarray_enabled_sensors & CONFIG_ENABLED_BVP)
    {
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_SENSOR_DATA_BVP);
        logger->write("sent bvp data");
    }
    if (config.bitarray_enabled_sensors & CONFIG_ENABLED_EDA)
    {
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_SENSOR_DATA_EDA);
        logger->write("sent eda data");
    }
    if (config.bitarray_enabled_sensors & CONFIG_ENABLED_HR)
    {
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_SENSOR_DATA_HR);
        logger->write("sent hr data");
    }
    if (config.bitarray_enabled_sensors & CONFIG_ENABLED_TEMP)
    {
        Lifes_Protocol.lifes_SIM_comando(CMD_TYPE_SENSOR_DATA_TEMP);
        logger->write("sent temp data");
    }

    // move pointer
    parsed_index_sent += config.sampleRate;
}

void MainWindow::on_loadLabel_clicked()
{
    parser = new _dataset_parser(this, logger, QFileDialog::getOpenFileName(this,
                                                                            tr("Open LABEL file"),
                                                                            "..\\lifesenior-dataset",
                                                                            tr("Dataset label file (*csv)")));
    //  explicit _dataset_parser(QObject *parent = nullptr, Logger *logger = nullptr, QString dirpath = "");

    this->ui->personActivity_Selector->addItems(parser->get_personactivity_list());


    verificador = 1;
}

void MainWindow::on_loadSensors_clicked()
{
    QString path;


    path = QFileDialog::getExistingDirectory(this,
                                             tr("Open Dataset directory"),
                                             "..\\lifesenior-dataset",
                                             QFileDialog::ShowDirsOnly);
    if (parser == nullptr)
    {
        parser = new _dataset_parser(this, logger);
        logger->write("Loading first line from sensors");
    }
    else
    {
        logger->write("Loading data of " + this->ui->personActivity_Selector->currentText());
    }
    parser->load_sensor_data(path + '/', this->ui->personActivity_Selector->currentIndex());
}



QString Dpath;

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
    QStringList files = fileDir.entryList(QDir::Files);

    // Iterate over the files and remove the "_annotated" word.
    for (int i = 0; i < files.size(); i++) {
        QString fileName = files[i];
        int index = fileName.indexOf("_annotated");
        if (index != -1) {
            files[i] = fileName.left(index);
        }
    }

    // Add the files to the other QComboBox.

    this->ui->patientBox->clear();
    this->ui->patientBox->addItems(files);


    //adicionar a primeira linha e jogar numa QStringList
    QString arquivoSelecionado =  this->ui->patientBox->currentText();
    arquivoSelecionado += "_annotated.csv";

    // Create a QFile object for the selected file.
    QFile file(arquivoSelecionado);

    // Open the file in read mode.
    file.open(QIODevice::ReadOnly);

    // Read the first line of the file.
    QString linha = file.readLine();

    // Close the file.
    file.close();

   //parser = new _dataset_parser(this, logger, QFileDialog::getOpenFileName(this,
                                                                      //      tr("Open LABEL file"),
                                                                       //     "..\\lifesenior-dataset",
                                                                        //    tr("Dataset label file (*csv)")));
    //this->ui->personActivity_Selector->addItems(parser->get_personactivity_list());
    //this->ui->personActivity_Selector->addItems(parser->get_personactivity_list());
    // parser = new _dataset_parser(this, logger);
    //QString selectedFolderName =  this->ui->directoryBox->currentText();









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


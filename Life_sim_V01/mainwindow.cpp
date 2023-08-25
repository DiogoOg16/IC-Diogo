#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
//#include <QHostAddress>
//#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //LOG File
    fileName = "logger.txt";
    logger = new Logger(this, fileName, this->ui->plainTextEdit);
    logger->write("Hello Qt");

}

MainWindow::~MainWindow()
{
    delete ui;
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
    //this->logger->write(files);

    // Iterate over the files and remove the "_annotated" word.
    /*for (int i = 0; i < files.size(); i++) {
        QString fileName = files[i];
        int index = fileName.indexOf("_annotated");
        if (index != -1) {
            files[i] = fileName.left(index);
        }
    }*/
    // Add the files to the other QComboBox.

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

    //adicionar a primeira linha e jogar numa QStringList
    QString arquivoSelecionado =  this->ui->patientBox->currentText();
    //arquivoSelecionado += "_annotated.csv";
    load =  new _load_data(this, logger, arquivoSelecionado, selectedFolderName);

}


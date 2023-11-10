#ifndef LIFES_PROTOCOL_H
#define LIFES_PROTOCOL_H


#include <QObject>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "lifes_sim_tools.h"
#include "Logger.h"
#include "protocol.h"
#include "load_data.h"

class _Lifes_Protocol : public QObject {

Q_OBJECT
public:
load_data lDataT;
//load_data **ld;
_lifes_sim_tools lifes_sim_tools;
bool accx = false;
bool accy = false;
bool accz = false;
private:
Logger* logger;
//load_data *lData;

public slots:
void Init_Lifes_SIM(Logger*);
void Atualiza_inicial();
unsigned char TestaCRC(unsigned char crc, unsigned char data);
unsigned char lifes_SIM_comando(_command_types comando);
void Atualiza_Estrutura(_command_types comando);
void atualiza_acc_x(double ponto);
void atualiza_acc_y(double ponto);
void atualiza_acc_z(double ponto);

bool semaforo();
void reset();
_ConfigPub Configuracoes_de_Publicacao(void);
unsigned char Atualiza_Curvas(_command_types comando, unsigned short* curvas, unsigned int timestamp);
void lifes_sim_in(void);
//void defineLoad(load_data *load);
//load_data* obtemLoad();
//bool checaLData();

};


#endif // LIFES_PROTOCOL_H
//10.32.160.81
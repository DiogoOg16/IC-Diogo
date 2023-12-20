#include "Lifes_Protocol.h"


_lifes_sim lifes_sim;
_lifes_sim lifes_sim_ant;

unsigned char bufferIn[255];
unsigned char bufferOUT[255];
unsigned short crcOUT[2];
unsigned short iOUT;

//CRC Look-up table
const unsigned char crcTable[256] = {
        0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65, 157,
        195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220, 35, 125,
        159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98, 190, 224, 2,
        92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255, 70, 24, 250, 164,
        39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7, 219, 133, 103, 57,
        186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154, 101, 59, 217, 135, 4,
        90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36, 248, 166, 68, 26, 153,
        199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185, 140, 210, 48, 110, 237,
        179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205, 17, 79, 173, 243, 112, 46,
        204, 146, 211, 141, 111, 49, 178, 236, 14, 80, 175, 241, 19, 77, 206, 144,
        114, 44, 109, 51, 209, 143, 12, 82, 176, 238, 50, 108, 142, 208, 83, 13,
        239, 177, 240, 174, 76, 18, 145, 207, 45, 115, 202, 148, 118, 40, 171, 245,
        23, 73, 8, 86, 180, 234, 105, 55, 213, 139, 87, 9, 235, 181, 54, 104, 138,
        212, 149, 203, 41, 119, 244, 170, 72, 22, 233, 183, 85, 11, 136, 214, 52,
        106, 43, 117, 151, 201, 74, 20, 246, 168, 116, 42, 200, 150, 21, 75, 169,
        247, 182, 232, 10, 84, 215, 137, 107, 53 };

void _Lifes_Protocol::Init_Lifes_SIM(Logger* logger_pointer)
{
    logger = logger_pointer;
    //lData = new load_data();
    //tamanhos estruturas
    lifes_sim.size[CMD_TYPE_SYNC_CLOCK]         = (int) sizeof(_Relogio);
    lifes_sim.size[CMD_TYPE_CRV_ACCEL]          = (int) sizeof(_CurvaAccel);
    lifes_sim.size[CMD_TYPE_CRV_MAG]            = (int) sizeof(_CurvaMag);
    lifes_sim.size[CMD_TYPE_CRV_GYR]            = (int) sizeof(_CurvaGyro);
    lifes_sim.size[CMD_TYPE_PARAM_ACCEL]        = (int) sizeof(_ParametrosAccel);
    lifes_sim.size[CMD_TYPE_PARAM_GYR]          = (int) sizeof(_ParametrosGyro);
    lifes_sim.size[CMD_TYPE_PARAM_MAG]          = (int) sizeof(_ParametrosMag);
    lifes_sim.size[CMD_TYPE_CFG_ACCEL]          = (int) sizeof(_ConfigAccel);
    lifes_sim.size[CMD_TYPE_CFG_GYR]            = (int) sizeof(_ConfigGyro);
    lifes_sim.size[CMD_TYPE_CFG_MAG]            = (int) sizeof(_ConfigMag);
    lifes_sim.size[CMD_TYPE_CFG_PUB]            = (int) sizeof(_ConfigPub);
    lifes_sim.size[CMD_LABEL]                   = (int) sizeof(_label);
    lifes_sim.size[CMD_ROOM]                    = (int) sizeof(_local);


    //ponteiros para estruturas
    lifes_sim.address[CMD_TYPE_SYNC_CLOCK]      = &lifes_sim.dados.relogio;
    lifes_sim.address[CMD_TYPE_CRV_ACCEL]       = &lifes_sim.dados.curvas.acelerometer;
    lifes_sim.address[CMD_TYPE_CRV_MAG]         = &lifes_sim.dados.curvas.magnetometer;
    lifes_sim.address[CMD_TYPE_CRV_GYR]         = &lifes_sim.dados.curvas.gyroscope;
    lifes_sim.address[CMD_TYPE_PARAM_ACCEL]     = &lifes_sim.dados.parametros.accelerometer;
    lifes_sim.address[CMD_TYPE_PARAM_GYR]       = &lifes_sim.dados.parametros.gyroscope;
    lifes_sim.address[CMD_TYPE_PARAM_MAG]       = &lifes_sim.dados.parametros.magnetometer;
    lifes_sim.address[CMD_TYPE_CFG_ACCEL]       = &lifes_sim.dados.config.accelerometer;
    lifes_sim.address[CMD_TYPE_CFG_GYR]         = &lifes_sim.dados.config.gyroscope;
    lifes_sim.address[CMD_TYPE_CFG_MAG]         = &lifes_sim.dados.config.magnetometer;
    lifes_sim.address[CMD_TYPE_CFG_PUB]         = &lifes_sim.dados.config.publisher;
    lifes_sim.address[CMD_LABEL]                = &lifes_sim.dados.curvas.actions;
    lifes_sim.address[CMD_ROOM]                 = &lifes_sim.dados.curvas.room;

    lifes_sim_tools.init_FIFO_out();

    // conecta evento de recebimento com funcao de tratamento dos dados
    connect(&lifes_sim_tools.socketTCP._socket, SIGNAL(readyRead()), this, SLOT(lifes_sim_in()));

    Atualiza_inicial();

    lifes_sim.st = lifes_sim.ACTIVE;  //Stream constante de dados



}


void _Lifes_Protocol::Atualiza_inicial()
{
    Atualiza_Estrutura(CMD_TYPE_SYNC_CLOCK);
    Atualiza_Estrutura(CMD_TYPE_CRV_ACCEL);
    Atualiza_Estrutura(CMD_TYPE_CRV_GYR);
    Atualiza_Estrutura(CMD_TYPE_CRV_MAG);
    Atualiza_Estrutura(CMD_TYPE_CRV_ACCEL);
    Atualiza_Estrutura(CMD_TYPE_CRV_GYR);
    Atualiza_Estrutura(CMD_TYPE_CRV_MAG);
    Atualiza_Estrutura(CMD_TYPE_CFG_ACCEL);
    Atualiza_Estrutura(CMD_TYPE_CFG_GYR);
    Atualiza_Estrutura(CMD_TYPE_CFG_MAG);
    Atualiza_Estrutura(CMD_TYPE_CFG_PUB);
    Atualiza_Estrutura(CMD_LABEL);
    Atualiza_Estrutura(CMD_ROOM);


    lifes_sim_ant = lifes_sim; //iguala estruturas
}

unsigned char _Lifes_Protocol::TestaCRC(unsigned char crc, unsigned char data)
{
    return (crcTable[crc ^ data]);
}

/*	Mandar estrutura 'comando' para fifo de saida*/
unsigned char _Lifes_Protocol::lifes_SIM_comando(_command_types comando)
{
    static unsigned char block_function = 0;

    if (block_function) return 0;
    else block_function = 1;

    //insere na fila COMANDO
    //n entra nos calculos de crc0/1
    lifes_sim_tools.fifo_out_push(comando);		// Manda comando pra fila
    crcOUT[0] = comando;		// Salva comando no buff local
    //crcOUT[1] = 0;
    //crcOUT[1] = TestaCRC(crcOUT[1], comando);	// inicia CRC

    //calcula tamanho do pacote de dados (=tamanho estrutura mais 2)
    lifes_sim_tools.fifo_out_push(lifes_sim.size[comando] + 1);	// Manda tamanho+2 pra fila
    crcOUT[0] ^= lifes_sim.size[comando] + 1;	// Segue no CRC
    //crcOUT[1] = TestaCRC(crcOUT[1], lifes_sim.size[comando] + 2);

    //envia para fifo estrutura de dados
    memcpy(bufferOUT, (void *) lifes_sim.address[comando], lifes_sim.size[comando]);

    for (iOUT = 0; iOUT < lifes_sim.size[comando]; iOUT++)
    {
        lifes_sim_tools.fifo_out_push(bufferOUT[iOUT]);
        crcOUT[0] ^= bufferOUT[iOUT];
    //    crcOUT[1] = TestaCRC(crcOUT[1], bufferOUT[iOUT]);
    }

    //coloca crc na fifo
    lifes_sim_tools.fifo_out_push(crcOUT[0]);
    //lifes_sim_tools.fifo_out_push(crcOUT[1]);

    block_function = 0;

    return 1;
}

//void _Lifes_Protocol::incrementaTimeStamp(){}

bool _Lifes_Protocol::semaforo()
{
    if(accx == true && accy == true && accz == true &&
        gyrx == true && gyry == true && gyrz == true &&
        azi == true && pitch == true && roll == true && 
        label == true)
    {
        
        return true;
    }
    else return false;
}

void _Lifes_Protocol::reset()
{
    accx = false;
    accy = false;
    accz = false;
    gyrx = false;
    gyry = false;
    gyrz = false;
    azi = false;
    pitch = false;
    roll = false;
    label = false;
    gps = false;
}

void _Lifes_Protocol::atualiza_acc_x(double ponto, unsigned int t)
{
    lifes_sim.dados.curvas.acelerometer.curvas[0] = (float)ponto;
    lifes_sim.dados.curvas.acelerometer.timestamp = t;
    accx = true;
}

void _Lifes_Protocol::atualiza_acc_y(double ponto)
{
    lifes_sim.dados.curvas.acelerometer.curvas[1] = (float)ponto;
    accy = true;
}

void _Lifes_Protocol::atualiza_acc_z(double ponto)
{
    lifes_sim.dados.curvas.acelerometer.curvas[2] = (float)ponto;
    accz = true;
}

void _Lifes_Protocol::atualiza_gyr_x(double ponto, unsigned int t)
{
    lifes_sim.dados.curvas.gyroscope.curvas[0] = (float)ponto;
    lifes_sim.dados.curvas.gyroscope.timestamp = t;
    gyrx = true;
}

void _Lifes_Protocol::atualiza_gyr_y(double ponto)
{
    lifes_sim.dados.curvas.gyroscope.curvas[1] = (float)ponto;
    gyry = true;
}

void _Lifes_Protocol::atualiza_gyr_z(double ponto)
{
    lifes_sim.dados.curvas.gyroscope.curvas[2] = (float)ponto;
    gyrz = true;
}

void _Lifes_Protocol::atualiza_azi(double ponto, unsigned int t){
    lifes_sim.dados.curvas.magnetometer.curvas[0] = (float)ponto;
    lifes_sim.dados.curvas.magnetometer.timestamp = t;
    azi = true;
}

void _Lifes_Protocol::atualiza_pitch(double ponto){
    lifes_sim.dados.curvas.magnetometer.curvas[1] = (float)ponto;
    pitch = true;
}

void _Lifes_Protocol::atualiza_roll(double ponto){
    lifes_sim.dados.curvas.magnetometer.curvas[2] = (float)ponto;
    roll = true;
}


void _Lifes_Protocol::atualiza_label(QString l, unsigned int t){
    if(l == "BSC")        lifes_sim.dados.curvas.actions.tipos = 0x00;
    else if (l == "CHU")  lifes_sim.dados.curvas.actions.tipos = 0x01;
    else if (l == "CSI")  lifes_sim.dados.curvas.actions.tipos = 0x02;
    else if (l == "CSO")  lifes_sim.dados.curvas.actions.tipos = 0x03;
    else if (l == "FKL")  lifes_sim.dados.curvas.actions.tipos = 0x04;
    else if (l == "FOL")  lifes_sim.dados.curvas.actions.tipos = 0x05;
    else if (l == "JOG")  lifes_sim.dados.curvas.actions.tipos = 0x06;
    else if (l == "JUM")  lifes_sim.dados.curvas.actions.tipos = 0x07;
    else if (l == "SBE")  lifes_sim.dados.curvas.actions.tipos = 0x08;
    else if (l == "SBW")  lifes_sim.dados.curvas.actions.tipos = 0x09;
    else if (l == "SCH")  lifes_sim.dados.curvas.actions.tipos = 0x0A;
    else if (l == "SDL")  lifes_sim.dados.curvas.actions.tipos = 0x0B;
    else if (l == "SIT")  lifes_sim.dados.curvas.actions.tipos = 0x0C;
    else if (l == "SLH")  lifes_sim.dados.curvas.actions.tipos = 0x0D;
    else if (l == "SLW")  lifes_sim.dados.curvas.actions.tipos = 0x0E;
    else if (l == "SRH")  lifes_sim.dados.curvas.actions.tipos = 0x0F;
    else if (l == "STD")  lifes_sim.dados.curvas.actions.tipos = 0x10;
    else if (l == "STN")  lifes_sim.dados.curvas.actions.tipos = 0x11;
    else if (l == "STU")  lifes_sim.dados.curvas.actions.tipos = 0x12;
    else if (l == "WAL")  lifes_sim.dados.curvas.actions.tipos = 0x13;
    else if (l == "LYI")  lifes_sim.dados.curvas.actions.tipos = 0x14;
    else  lifes_sim.dados.curvas.actions.tipos = 0xFF;
    lifes_sim.dados.curvas.actions.timestamp = t;
    label = true;
}

void _Lifes_Protocol::atualiza_gps(QString g, unsigned int t){
    if(g == "ROM")          lifes_sim.dados.curvas.room.gps = 0x00;
    else if (g == "LRM")    lifes_sim.dados.curvas.room.gps = 0x01;
    else if (g == "KTC")    lifes_sim.dados.curvas.room.gps = 0x02;
    else if (g == "BTH")    lifes_sim.dados.curvas.room.gps = 0x03;
    else if (g == "GRG")    lifes_sim.dados.curvas.room.gps = 0x04;
    else                        lifes_sim.dados.curvas.room.gps = 0xFF;

    lifes_sim.dados.curvas.room.timestamp = t;
    gps = true;
}

/*	Tras os dados do fluxo principal para o fluxo de envio*/
void _Lifes_Protocol::Atualiza_Estrutura(_command_types comando)
{
    double ponto;
    switch (comando)
    {
        case CMD_TYPE_SYNC_CLOCK:
            lifes_sim.dados.relogio.Segundo = 10;
            lifes_sim.dados.relogio.Minuto = 20;
            lifes_sim.dados.relogio.Hora = 8;
            lifes_sim.dados.curvas.acelerometer.curvas[0] = 550;
            lifes_sim.dados.relogio.Dia = 20;
            lifes_sim.dados.relogio.Mes = 02;
            lifes_sim.dados.relogio.Ano = 22;
            break;
        case CMD_TYPE_CRV_ACCEL:
            //std::cout << lData << std::endl;
           // lifes_sim.dados.curvas.acelerometer.curvas[0] = (*ld)->testedefuncao();
            //lifes_sim.dados.curvas.acelerometer.curvas[1] = 1.0;
            //lifes_sim.dados.curvas.acelerometer.curvas[2] = 1.0;
            //static_cast<float>(lData->elem1Acc_x())
            break;

        case CMD_TYPE_CRV_MAG:
            //memset(lifes_sim.dados.curvas.magnetometer.curvas, 0x38, sizeof(lifes_sim.dados.curvas.magnetometer.curvas));
            break;

        case CMD_TYPE_CRV_GYR:
            //memset(lifes_sim.dados.curvas.gyroscope.curvas, 0x39, sizeof(lifes_sim.dados.curvas.gyroscope.curvas));
            break;

        case CMD_TYPE_CFG_PUB:
            lifes_sim.dados.config.publisher.bitarray_enabled_sensors = (CONFIG_ENABLED_ACCEL | CONFIG_ENABLED_GYR | CONFIG_ENABLED_MAG);
            lifes_sim.dados.config.publisher.interval_ms = 500;

        default:
            break;
    }
}

_ConfigPub _Lifes_Protocol::Configuracoes_de_Publicacao(void)
{
    return lifes_sim.dados.config.publisher;
}

unsigned char _Lifes_Protocol::Atualiza_Curvas(_command_types comando, unsigned short* curvas, unsigned int timestamp)
{
    switch(comando)
    {
        case CMD_TYPE_CRV_ACCEL:
            memcpy(lifes_sim.dados.curvas.acelerometer.curvas, curvas, sizeof(lifes_sim.dados.curvas.acelerometer.curvas));
            lifes_sim.dados.curvas.acelerometer.timestamp = timestamp;
        break;

        case CMD_TYPE_CRV_MAG:
            memcpy(lifes_sim.dados.curvas.magnetometer.curvas, curvas, sizeof(lifes_sim.dados.curvas.magnetometer.curvas));
            //lifes_sim.dados.curvas.magnetometer.timestamp = timestamp;
        break;

        case CMD_TYPE_CRV_GYR:
            memcpy(lifes_sim.dados.curvas.gyroscope.curvas, curvas, sizeof(lifes_sim.dados.curvas.gyroscope.curvas));
            //lifes_sim.dados.curvas.gyroscope.timestamp = timestamp;
        break;

        default:
            return 1;
    }
    return 0;
}

/* - Verifica CRC dos dados recebidos pela central
 * - Aplica Comando recebido pela central
 */
void _Lifes_Protocol::lifes_sim_in(void)
{
    unsigned int size = lifes_sim_tools.socketTCP._socket.read((char*) bufferIn, sizeof(bufferIn));
    //recepção de dados
    if (--size > 0) // remove ultimo byte do crc
    {
        unsigned char crc = 0;
        // Verifica CRC
        for (unsigned short pos=0; pos < size; pos++)
        {
            crc = TestaCRC(crc, bufferIn[pos]);
        }
        // CRC valido (CRC-8/MAXIM)
        if (crc == bufferIn[size] && size >= 3)
        {
            _command_types command = (_command_types) bufferIn[0];
            size = bufferIn[1];

            switch (command)
            {
                case CMD_TYPE_CFG_ACCEL:
                    if (size == sizeof(_ConfigAccel))
                    {
                        memcpy((unsigned char*) &lifes_sim.dados.config.accelerometer, &bufferIn[2], size);
                        logger->write("Accelorometer config received");
                    }
                break;

                case CMD_TYPE_CFG_GYR:
                    if (size == sizeof(_ConfigGyro))
                    {
                        memcpy((unsigned char*) &lifes_sim.dados.config.gyroscope, &bufferIn[2], size);
                        logger->write("Gyroscope config received");
                    }
                break;

                case CMD_TYPE_CFG_MAG:
                    if (size == sizeof(_ConfigMag))
                    {
                        memcpy((unsigned char*) &lifes_sim.dados.config.magnetometer, &bufferIn[2], size);
                        logger->write("Magnetometer config received");
                    }
                break;

                case CMD_TYPE_CFG_PUB:
                    if (size == sizeof(_ConfigPub))
                    {
                        memcpy((unsigned char*) &lifes_sim.dados.config.publisher, &bufferIn[2], size);
                        logger->write("Publisher config received");
                    }
                break;
            }
        }
    }
}

#ifndef DTMFGENERATOR_H
#define DTMFGENERATOR_H

#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QIODevice>
#include "qmath.h"
#include "qendian.h"
#include <QLabel>
class DTMFGenerator: public QIODevice
{
    Q_OBJECT

    qint64 m_pos;
    int f[8];
    int Duration;
    int BufferSize;
    int step;
    int fmin;
    int SampleRate;
    int total_sent;
    unsigned int bufferpos;

    QLabel* text;
    QByteArray Buffer;
    unsigned char* BufferPtr;
    QByteArray data;


    void FillBuffer(char Data);


public:
    DTMFGenerator(int Fmin, int Step, QObject *parent);
    void prepareBufferToSend(QString str);    
    qint64 readData(char *data, qint64 len);
    qint64 writeData(const char *data, qint64 len);
     void setptr(QLabel* ptr);


    ~DTMFGenerator();

};

#endif // DTMFGENERATOR_H

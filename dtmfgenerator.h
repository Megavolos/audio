#ifndef DTMFGENERATOR_H
#define DTMFGENERATOR_H

#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QIODevice>
#include "qmath.h"
#include "qendian.h"

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
    unsigned int bufferpos;

    QByteArray Buffer;
    unsigned char* BufferPtr;
    QByteArray data;


    void FillBuffer(char Data);

public:
    DTMFGenerator(int Fmin, int Step, QObject *parent);
    void prepareBufferToSend(QString str);    
    qint64 readData(char *data, qint64 len);
    qint64 writeData(const char *data, qint64 len);

    ~DTMFGenerator();

};

#endif // DTMFGENERATOR_H

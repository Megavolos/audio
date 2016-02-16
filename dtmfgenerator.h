#ifndef DTMFGENERATOR_H
#define DTMFGENERATOR_H
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QIODevice>
#include "qmath.h"

class DTMFGenerator: public QIODevice
{
    Q_OBJECT

    qint64 m_pos;
    int f[8];
    int Duration = 0;
    int BufferSize=0;
    int step;
    int fmin;
    const int SampleRate = 44100;
    unsigned int bufferpos;
    QAudioFormat AudioFormat;
    QVector<qint16> Buffer;
    short* BufferPtr;
    QByteArray data;

    qint64 readData(char *data, qint64 len);
    qint64 writeData(const char *data, qint64 len);
    void FillBuffer(char Data);

public:
    DTMFGenerator(int Fmin, int Step, QObject *parent);
    int* DataToFreq(char Data);
    ~DTMFGenerator();

};

#endif // DTMFGENERATOR_H

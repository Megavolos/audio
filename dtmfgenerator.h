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
    int Duration;
    int BufferSize;
    int step;
    int fmin;
    int SampleRate;
    unsigned int bufferpos;
    QAudioFormat AudioFormat;
    QVector<qint16> Buffer;
    qint16* BufferPtr;
    QByteArray data;

    qint64 readData(char *data, qint64 len);
    qint64 writeData(const char *data, qint64 len);
    void FillBuffer(char Data);

public:
    DTMFGenerator(int Fmin, int Step, QObject *parent);
    int* DataToFreq(char Data);
    void setData(QByteArray* dataArray);
    void DataString(QString str);
    void FillOne(char Data, unsigned int pos);
    void FillData();
    ~DTMFGenerator();

};

#endif // DTMFGENERATOR_H

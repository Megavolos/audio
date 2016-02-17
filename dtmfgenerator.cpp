#include "dtmfgenerator.h"

DTMFGenerator::DTMFGenerator(int Fmin, int Step, QObject *parent): QIODevice(parent)
{
    for (int i=0;i<8;i++)
    {
        f[i]=Fmin+Step*i;
    }
    SampleRate=44100;
    step=Step;
    fmin=Fmin;

    AudioFormat.setSampleSize(16);
    AudioFormat.setSampleRate(44100);
    AudioFormat.setChannelCount(1);
    AudioFormat.setCodec("audio/pcm");
    AudioFormat.setSampleType(QAudioFormat::SignedInt);
    AudioFormat.setByteOrder(QAudioFormat::LittleEndian);



}




void DTMFGenerator::prepareBufferToSend(QString str)
{
    bool ok;
    unsigned int samples_per_frame=SampleRate/step;
    Buffer.resize((str.length())*samples_per_frame);
    BufferPtr = Buffer.data();
    for (int n = 0; n<str.length(); n++)
    {
        for (unsigned int i = 0; i<(samples_per_frame);i++)
        {
            char digit=QString(str[n]).toInt(&ok,16);
            int f1=f[digit%4];
            int f2=f[digit/4 + 4];
            qreal sin1 = qSin(2*M_PI*f1*i/SampleRate);
            qreal sin2 = qSin(2*M_PI*f2*i/SampleRate);
            qreal sum = (sin1+sin2)/2;
            BufferPtr[i+samples_per_frame*n]=(qint16)(32767*sum);
        }
    }
}

qint64 DTMFGenerator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    while (len - total > 0)
    {
       const qint64 chunk = qMin((Buffer.size() - m_pos), len - total);
       memcpy(data + total, Buffer.constData() + m_pos, chunk);
       m_pos = (m_pos + chunk) % Buffer.size();
       total += chunk;
    }

       return total;

}
qint64 DTMFGenerator::writeData(const char *data, qint64 len)
{

}

DTMFGenerator::~DTMFGenerator()
{

}


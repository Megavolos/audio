#include "dtmfgenerator.h"

DTMFGenerator::DTMFGenerator(int Fmin, int Step, QObject *parent): QIODevice(parent)
{
    for (int i=0;i<8;i++)
    {
        f[i]=Fmin+Step*i;
    }
    step=Step;
    fmin=Fmin;
    Buffer.resize(44100);
    AudioFormat.setSampleSize(16);
    AudioFormat.setSampleRate(44100);
    AudioFormat.setChannelCount(1);
    AudioFormat.setCodec("audio/pcm");
    AudioFormat.setSampleType(QAudioFormat::SignedInt);
    AudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    BufferPtr = Buffer.data();



}
void DTMFGenerator::setData(QByteArray* dataArray)
{
    *data=dataArray;
}

void DTMFGenerator::getDataString(QString str)
{

}

void DTMFGenerator::FillBuffer(char Data)
{
    if (Data>0x0F) return;
    //заполнить буфер семплов

}

void DTMFGenerator::FillOne(char Data, unsigned int pos)
{
    int samples_per_frame=SampleRate/step;
    if (Data>0x0F) Data=0x0F;
    if (pos*samples_per_frame>(44100-samples_per_frame)) pos=44100-samples_per_frame;
    for (unsigned int i = 0; i<(samples_per_frame);i++)
    {
         BufferPtr[i+(samples_per_frame*pos)]=32767*(qint16)((qSin(2*M_PI*f[Data%4]*i/SampleRate)+qSin(2*M_PI*f[Data/4]*i/SampleRate))/2);
    }
}

int* DTMFGenerator::DataToFreq(char Data)
{
    int freqs[2];
    freqs[0]=f[Data%4];
    freqs[1]=f[Data/4];
    return freqs;
}
qint64 DTMFGenerator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    while (len - total > 0)
    {
       const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
       memcpy(data + total, m_buffer.constData() + m_pos, chunk);
       m_pos = (m_pos + chunk) % m_buffer.size();
       total += chunk;
    }

       return total;

}




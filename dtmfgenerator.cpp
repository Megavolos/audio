#include "dtmfgenerator.h"

DTMFGenerator::DTMFGenerator(int Fmin, int Step, QObject *parent): QIODevice(parent),m_pos(0)
{
    for (int i=0;i<8;i++)
    {
        f[i]=Fmin+Step*i;
    }
    SampleRate=44100;
    step=Step;
    fmin=Fmin;
    open(QIODevice::ReadWrite);
    total_sent=0;
}

void DTMFGenerator::setptr(QLabel *ptr)
{
    text=ptr;
}

void DTMFGenerator::prepareBufferToSend(QString str)
{
    bool ok;
    unsigned int samples_per_frame=SampleRate/step;
   // Buffer.resize((str.length())*samples_per_frame);
    Buffer.resize(44100/3);
    BufferPtr = reinterpret_cast<unsigned char *>(Buffer.data());
    for (int n = 0; n<str.length(); n++)
    {
        for (unsigned int i = 0; i<(samples_per_frame);i++)
        {
            char digit=QString(str[n]).toInt(&ok,16);
            int f1=f[digit%4];
            int f2=f[digit/4 + 4];
            qreal sin1 = qSin(2*M_PI*f1*i/SampleRate);
            qreal sin2 = qSin(2*M_PI*f2*i/SampleRate+M_PI);
            qreal sum = (sin1+sin2)/2;
            qint16 val = static_cast<qint16>(32767*sum*0.7);
            qToLittleEndian<qint16>(val,BufferPtr);
            BufferPtr+=2;

        }
        for (unsigned int i = 0; i<(samples_per_frame+400);i++)
        {
            qToLittleEndian<qint16>(0,BufferPtr);
            BufferPtr+=2;
        }
    }
//   for (int i=0;i<44100;i++)
//    {
//        int f1=f[0%4];
//        int f2=f[0/4 + 4];
//       // qreal sin1 = qSin(2*M_PI*f1*i/SampleRate);
//       // qreal sin2 = qSin(2*M_PI*f2*i/SampleRate);
//        //qreal sum = (sin1+sin2)/2;
//        qreal sum = qSin(2*M_PI*17400*i/SampleRate);
//        qint16 value=static_cast<qint16>(32767*sum);
//        qToLittleEndian<qint16>(value,BufferPtr);
//        BufferPtr+=2;
//    }
}


qint64 DTMFGenerator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    while (len - total > 0)
    {
       if (m_pos==0)
       {
           total_sent+=2;
           text->setText(QString::number(total_sent,10));
       }

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
    Buffer.clear();
    close();
}


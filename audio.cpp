#include "audio.h"

Audio::Audio(int sampleRate, QObject *parent)
{
    QAudioDeviceInfo audioDeviceInfo(QAudioDeviceInfo::defaultOutputDevice());

    audioFormat.setSampleSize(16);
    audioFormat.setSampleRate(sampleRate);
    audioFormat.setChannelCount(1);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setSampleType(QAudioFormat::SignedInt);
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    if (!audioDeviceInfo.isFormatSupported(audioFormat))
    {
        audioFormat=audioDeviceInfo.nearestFormat(audioFormat);
    }
    audioOutput = new QAudioOutput(audioDeviceInfo,audioFormat,parent);

    dtmfgenerator=new DTMFGenerator(17100,300,parent);
    dtmfgenerator->prepareBufferToSend("F3");
}
void Audio::setptr(QLabel *ptr)
{
    dtmfgenerator->setptr(ptr);
}

void Audio::start()
{
    audioOutput->start(dtmfgenerator);
}
Audio::~Audio()
{
    audioOutput->stop();
    delete audioOutput;
    delete dtmfgenerator;
}


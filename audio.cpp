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

    dtmfgenerator=new DTMFGenerator(17000,300,parent);

    dtmfgenerator->prepareBufferToSend("0123456789");

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


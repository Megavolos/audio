#ifndef AUDIO_H
#define AUDIO_H
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QLabel>
#include "dtmfgenerator.h"
class Audio
{
    QAudioFormat audioFormat;
    QAudioOutput* audioOutput;
    DTMFGenerator *dtmfgenerator;


public:
    void setptr(QLabel *ptr);
    Audio(int sampleRate, QObject *parent);
    void start();
    ~Audio();


};

#endif // AUDIO_H

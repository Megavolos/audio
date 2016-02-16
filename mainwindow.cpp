#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Buffer = new QBuffer;
    Data = new QByteArray;
    QAudioFormat format;

    format.setSampleSize(16);
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
    {
        qDebug() << "Format not supported";
        return;
    }

    else
    {
        audio_output = new QAudioOutput(format,this);
    }

    for (int i=0;i<44100*6;i++)
    {
        Data->append((char)(127*qSin(2*M_PI*(11000/2)*i/44100)));
    }
    Buffer->setBuffer(Data);
    Buffer->open(QIODevice::ReadWrite);
    audio_output->setNotifyInterval(3000);
    int n=audio_output->notifyInterval();
    audio_output->start(Buffer);

    connect(audio_output, SIGNAL(notify()),this,SLOT(notify()));
    connect(audio_output, SIGNAL(stateChanged(QAudio::State)),this,SLOT(state_changed(QAudio::State)));
}
void MainWindow::notify()
{
    int s;
}

void MainWindow::state_changed(QAudio::State state)
{
    switch (state)
    {
        case QAudio::IdleState:
            audio_output->stop();
            Buffer->close();
        break;
        case QAudio::StoppedState:
            if (audio_output->error() != QAudio::NoError)
            {
                // Error handling
            }
        break;
        default:
        break;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete Buffer;
    delete Data;
    delete audio_output;
}

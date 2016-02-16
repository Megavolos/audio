#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QAudioFormat"
#include "QAudioOutput"
#include <QAudio>
#include "QAudioDeviceInfo"
#include "QBuffer"
#include "QByteArray"
#include "QDebug"
#include "qmath.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAudioOutput* audio_output;
    QBuffer* Buffer;
    QByteArray* Data;
private slots:
    void state_changed(QAudio::State);
    void notify(void);
};

#endif // MAINWINDOW_H

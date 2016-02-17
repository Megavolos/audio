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
#include "dtmfgenerator.h"
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

private slots:

};

#endif // MAINWINDOW_H

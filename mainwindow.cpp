#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   DTMFGenerator dtmfgenerator(17000,300,this);
   dtmfgenerator.DataString("03AF2B");
   dtmfgenerator.FillData();
}

MainWindow::~MainWindow()
{

}

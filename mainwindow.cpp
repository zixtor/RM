#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setCheckable(false);
    ui->checkBox_2->setCheckable(false);
    ui->comboBox->setDisabled(true);
    this->hole = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->holes_file = ui->lineEdit->text().toStdString();
    this->holes_info_file = ui->lineEdit_2->text().toStdString();
    ui->checkBox->setCheckable(true);
    ui->checkBox_2->setCheckable(true);
    ui->checkBox_2->setChecked(true);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox->isCheckable()){
        if(ui->checkBox_2->isChecked()){
            this->hole = new DrawHole(this->holes_file.c_str(),this->holes_info_file.c_str(),0);
            ui->checkBox->setChecked(false);
            ui->comboBox->setDisabled(true);
        }
        else {
            this->hole = new DrawHole(this->holes_file.c_str(),this->holes_info_file.c_str(),1);
            ui->checkBox->setChecked(true);
            ui->comboBox->setDisabled(false);
            this->updateHoles(this->hole->getHoleCount());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(this->hole != NULL){
        if(ui->checkBox->isChecked()){
            this->hole->setHole(ui->comboBox->currentIndex());
        }
        this->hole->show();
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(this->hole != NULL){
        if(ui->checkBox->isChecked()){
            this->hole->setDisplayType(1);
            ui->checkBox_2->setChecked(false);
        }
        else {
            this->hole->setDisplayType(0);
            ui->checkBox_2->setChecked(true);
        }
    }
}

std::string append_number(std::string const& x, unsigned int num) {
        std::stringstream s;
        s << x << num;
        return s.str();
    }

void MainWindow::updateHoles(int h){
    for(int i=1;i<=h;i++){
        ui->comboBox->addItem(QString(append_number("Hole ",i).c_str()));
    }
}

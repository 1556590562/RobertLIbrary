#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    ui->progressBar->setValue(100);
}

Loading::~Loading()
{
    delete ui;
}

void Loading::on_progressBar_valueChanged(int value)
{

}

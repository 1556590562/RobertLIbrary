#include "dialogorgan.h"
#include "ui_dialogorgan.h"

DialogOrgan::DialogOrgan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOrgan)
{
    ui->setupUi(this);
    InitCbB();
    OrganScores=0;
    this->setWindowTitle("组织能力（任职情况）");
}

DialogOrgan::~DialogOrgan()
{
    delete ui;
}

void DialogOrgan::InitCbB()
{
    QStringList strc,strl;
    strc<<"第一级"<<"第二级"<<"第三级"<<"第四级";
    strl<<"优秀"<<"良好"<<"称职"<<"不称职";
    ui->cbB_PositionClass->addItems(strc);
    ui->cbB_TLevel->addItems(strl);

    float PClass[4]={1.0,0.8,0.5,0.3};
    float TLevel[4]={10,8,6,0};
    for(int i=0;i<strc.count();i++){
        ui->cbB_PositionClass->setItemData(i,PClass[i],Qt::UserRole);
    }
    for(int i=0;i<strl.count();i++){
        ui->cbB_TLevel->setItemData(i,TLevel[i],Qt::UserRole);
    }
}

float DialogOrgan::Get_OrganScores()
{
    return OrganScores;
}

QString DialogOrgan::Get_ObjectName()
{
    return ObjectName;
}

void DialogOrgan::on_pbt_Ok_clicked()
{
    float S1,S2;
    S1=ui->cbB_TLevel->currentData(Qt::UserRole).toFloat();
    S2=ui->cbB_PositionClass->currentData(Qt::UserRole).toFloat();
    OrganScores=S1*S2;
    ui->textBrowser->setText(QString::asprintf("组织管理能力加分：%0.2f",OrganScores));
    ObjectName=ui->lineEdit->text()+"+"+ui->cbB_PositionClass->currentText()+"+"+ui->cbB_TLevel->currentText();
}

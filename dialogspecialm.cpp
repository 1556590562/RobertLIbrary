#include "dialogspecialm.h"
#include "ui_dialogspecialm.h"

DialogSpecialM::DialogSpecialM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSpecialM)
{
    ui->setupUi(this);
    theList=new QStringList;
    theListModel=new QStringListModel;
    ui->listView->setModel(theListModel);
    InitUi();
    SMScores=0;
    this->setWindowTitle("特殊表彰情况");
}

DialogSpecialM::~DialogSpecialM()
{
    delete ui;
}

float DialogSpecialM::Get_SMScores()
{
    return SMScores;
}

QStringList DialogSpecialM::Get_ObjectName()
{
    return *theList;
}

void DialogSpecialM::on_pbt_SMAdd_clicked()
{
    QString str;

    float S,S1,S2;
    S1=ui->cbB_PRT->currentData(Qt::UserRole).toFloat();
    S2=ui->cbB_HLevel->currentData(Qt::UserRole).toFloat();
    S=S1*S2;
    SMScores+=S;
    str=ui->lineEdit->text()+":"+"("+ui->cbB_PRT->currentText()+")"+ui->cbB_HLevel->currentText()+QString::asprintf(",加分:%0.2f",S);
    theList->insert(theList->count(),str);
    theListModel->setStringList(*theList);
}

void DialogSpecialM::InitUi()
{
    QStringList str1,str2;
    float HS[4]={10,8,5,2},PTS[2]={1.0,0.2};
    str1<<"国家级荣誉"<<"省级荣誉"<<"校级荣誉"<<"院级荣誉";
    str2<<"个人荣誉"<<"团队荣誉";

    ui->cbB_HLevel->addItems(str1);
    for(int i=0;i<str1.count();i++){
        ui->cbB_HLevel->setItemData(i,HS[i],Qt::UserRole);
    }
    ui->cbB_PRT->addItems(str2);
    for(int i=0;i<str2.count();i++){
        ui->cbB_PRT->setItemData(i,PTS[i],Qt::UserRole);
    }
}

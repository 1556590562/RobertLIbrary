#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QObject>
#include <QColorDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QFileDevice>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DeScores1=0;
    DeScores2=0;
    ZhiScores=0;
    TiScores=0;
    SumScores=0;
    this->setWindowTitle("添加或修改测评信息");
}

MainWindow::~MainWindow()
{
    delete ui;
}

float MainWindow::Get_DeScore()
{
    return DeScores1;
}
float MainWindow::Get_DeScore2()
{
    return DeScores2;
}
float MainWindow::Get_TiScore()
{
    return TiScores;
}
float MainWindow::Get_ZhiScore()
{
    return ZhiScores;
}
float MainWindow::Get_SumScore()
{
    if(ui->lineEdit->text().isNull()){
        return SumScores;
    }else{
        return ui->lineEdit->text().toFloat();
    }
}

QString MainWindow::Get_CPinfo()
{
    return ui->lineEdit_Other->text();
}
QString MainWindow::Get_StuNum()
{
    return ui->lineEdit_StudentNum->text();
}
QString MainWindow::Get_StuName()
{
    return ui->lineEdit_Name->text();
}

void MainWindow::Set_AlterStuNum(QString stuName, QString stuNum, QString Dexz, QString Dexb, QString Zhi, QString Ti, QString Fz)
{
    ui->lineEdit_Name->setText(stuName);
    ui->lineEdit_StudentNum->setText(stuNum);
    ui->lineEdit_DeScores->setText(Dexz);
    ui->lineEdit_DeScores2->setText(Dexb);
    ui->lineEdit_ZhiScores->setText(Zhi);
    ui->lineEdit_TiScores->setText(Ti);
    ui->lineEdit->setText(Fz);
    QMessageBox::information(this,"修改提示","修改发展素质分数时请重新添加加分项，或直接修改发展素质总分;\n修改其他内容只需要修改相应选框内容即可;\n学号无法修改，修改学号请直接在大表格中进行;");
}

void MainWindow::on_pushButton_clicked()
{
    SumScores=0;
    if(ui->lineEdit_StudentNum->text()==nullptr){
        QMessageBox::information(this,"tip","必须先输入一个学号");
        return;
    }
    DeScores1=ui->lineEdit_DeScores->text().toFloat();
    DeScores2=ui->lineEdit_DeScores2->text().toFloat();
    float DeScores=DeScores1+DeScores2;

    QPalette pen;
    pen.setColor(QPalette::Active,QPalette::Text,Qt::blue);
    ui->plainTextEdit->clear();

    ui->plainTextEdit->setTextColor(Qt::blue);
    ui->plainTextEdit->append("一、个人信息:");
    ui->plainTextEdit->setTextColor(Qt::black);
    ui->plainTextEdit->append("姓名："+ui->lineEdit_Name->text()+"\n学号: "+ui->lineEdit_StudentNum->text());
    ui->plainTextEdit->append("年级："+ui->lineEdit_Greates->text());
    ui->plainTextEdit->append("----------------------------------------------\n");

    ui->plainTextEdit->setTextColor(Qt::blue);
    ui->plainTextEdit->append("二、基础素质评分:");
    ui->plainTextEdit->setTextColor(Qt::black);

    ZhiScores=ui->lineEdit_ZhiScores->text().toFloat();
    TiScores=ui->lineEdit_TiScores->text().toFloat();
    ui->plainTextEdit->append(QString::asprintf("德育分数：%0.2f\n智育分数：%0.2f\n体育分数：%0.2f\n总分：%0.2f",
                                                         DeScores,ZhiScores,TiScores,DeScores+ZhiScores+TiScores));
    ui->plainTextEdit->append("----------------------------------------------\n");

    ui->plainTextEdit->setTextColor(Qt::blue);
    ui->plainTextEdit->append("三、发展素质评分:");
    ui->plainTextEdit->setTextColor(Qt::black);
    //-----------------------------------------------------------------创新创造能力显示部分
    ui->plainTextEdit->setTextColor(Qt::green);
    ui->plainTextEdit->append("1.创新能力：");
    ui->plainTextEdit->setTextColor(Qt::black);
    if(dlgAdds!=nullptr){
        QStringList AddsList=dlgAdds->Get_ObjectList();
        for(int i=0;i<AddsList.count();i++){
            ui->plainTextEdit->append(QString::asprintf("%d.",i+1)+AddsList.at(i));
        }
        ui->plainTextEdit->append("\n");
        float score=dlgAdds->Get_InnovativeScores();
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append(QString::asprintf("该项总分：%0.2f",score));
        ui->plainTextEdit->setTextColor(Qt::black);
        SumScores+=score;
    }else{
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append("该项总分：0.0");
        ui->plainTextEdit->setTextColor(Qt::black);
    }
        ui->plainTextEdit->append("----------------------------------------------");

    //-----------------------------------------------------------------组织能力显示部分
        ui->plainTextEdit->setTextColor(Qt::green);
    ui->plainTextEdit->append("2.组织能力：");
    ui->plainTextEdit->setTextColor(Qt::black);
    if(dlgOrgan!=nullptr){
        QString ObjectName=dlgOrgan->Get_ObjectName();
        ui->plainTextEdit->append(ObjectName);
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append(QString::asprintf("\n该项总分：%0.2f",dlgOrgan->Get_OrganScores()));
        ui->plainTextEdit->setTextColor(Qt::black);
        SumScores+=dlgOrgan->Get_OrganScores();
    }else{
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append("该项总分：0.0");
        ui->plainTextEdit->setTextColor(Qt::black);
    }
        ui->plainTextEdit->append("----------------------------------------------");

    //-----------------------------------------------------------------综合能力显示部分
    ui->plainTextEdit->setTextColor(Qt::green);
    ui->plainTextEdit->append("3.综合能力：");
    ui->plainTextEdit->setTextColor(Qt::black);
    if(dlgComprehensive!=nullptr){
        QStringList strlist=dlgComprehensive->Get_ObjectName();
        for(int i=0;i<strlist.count();i++){
            ui->plainTextEdit->append(QString::asprintf("%d.",i)+strlist.at(i));
        }
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append(QString::asprintf("该项总分：%0.2f",dlgComprehensive->Get_ComScores()));
        ui->plainTextEdit->setTextColor(Qt::black);
        SumScores+=dlgComprehensive->Get_ComScores();
    }else{
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append("该项总分：0.0");
        ui->plainTextEdit->setTextColor(Qt::black);
    }
        ui->plainTextEdit->append("----------------------------------------------");

    //-----------------------------------------------------------------综合能力显示部分
    ui->plainTextEdit->setTextColor(Qt::green);
    ui->plainTextEdit->append("4.特殊表彰：");
    ui->plainTextEdit->setTextColor(Qt::black);
    if(dlgSpecialM!=nullptr){
        QStringList strlist=dlgSpecialM->Get_ObjectName();
        for(int i;i<strlist.count();i++){
            ui->plainTextEdit->append(QString::asprintf("%d.",i)+strlist.at(i));
        }
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append(QString::asprintf("该项总分：%0.2f",dlgSpecialM->Get_SMScores()));
        ui->plainTextEdit->setTextColor(Qt::black);
        SumScores+=dlgSpecialM->Get_SMScores();
    }else{
        ui->plainTextEdit->setTextColor("#FF00FF");
        ui->plainTextEdit->append("该项总分：0.0");
        ui->plainTextEdit->setTextColor(Qt::black);
    }
        ui->plainTextEdit->append("----------------------------------------------");

    ui->plainTextEdit->setTextColor(Qt::red);
    ui->plainTextEdit->append(QString::asprintf("综合测评总分为：%0.2f",SumScores+DeScores*0.2+ZhiScores*0.7+TiScores*0.1));
    ui->plainTextEdit->setTextColor(Qt::black);
    emit Update_Completed();
}

void MainWindow::on_pbt_AddScores_clicked()
{
    if(dlgAdds==nullptr){
        dlgAdds=new DialogAddS(this);
    }
    int ret=dlgAdds->exec();
    if(ret==QDialog::Accepted){
        //accepted函数关联内容
    }
}

void MainWindow::on_pbt_AddOtherScores_clicked()
{
    if(dlgOrgan==nullptr){
        dlgOrgan=new DialogOrgan(this);
    }
    int ret=dlgOrgan->exec();
    if(ret==QDialog::Accepted){
        //
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(dlgComprehensive==nullptr){
        dlgComprehensive=new DialogComprehensive(this);
    }
    int ret=dlgComprehensive->exec();
    if(ret==QDialog::Accepted){
        //
    }
}

void MainWindow::on_pbt_SMAdd_clicked()
{
    if(dlgSpecialM==nullptr){
        dlgSpecialM=new DialogSpecialM(this);
    }
    int ret=dlgSpecialM->exec();
    if(ret==QDialog::Accepted){
        //
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    on_pushButton_clicked();
    QString curPath=QDir::currentPath();
    QString dlgTitle="保存文件";
    QString filter="信息文件(*.txt)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(aFileName.isEmpty()){
        return;
    }
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    QString str=ui->plainTextEdit->toPlainText();
    aStream<<str;
    aFile.close();
    QMessageBox::information(this,"完成","文件保存完成!");
    return;
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pbt_ReSet_clicked()
{
    delete dlgAdds;
    delete dlgOrgan;
    delete dlgSpecialM;
    delete dlgComprehensive;
    ui->plainTextEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_Name->clear();
    ui->lineEdit_Other->clear();
    ui->lineEdit_Greates->clear();
    ui->lineEdit_DeScores->clear();
    ui->lineEdit_TiScores->clear();
    ui->lineEdit_DeScores2->clear();
    ui->lineEdit_ZhiScores->clear();
    ui->lineEdit_StudentNum->clear();
    DeScores1=0;
    DeScores2=0;
    ZhiScores=0;
    TiScores=0;
    SumScores=0;
}

void MainWindow::on_pbt_Finish_clicked()
{
    emit Update_Completed();
    this->close();
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"提示","设置发展素质总分后将直接忽略所添加计算的内容");
}

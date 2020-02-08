 #include "dialogcomprehensive.h"
#include "ui_dialogcomprehensive.h"

DialogComprehensive::DialogComprehensive(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogComprehensive)
{
    ui->setupUi(this);
    InitUi();
    ComScores=0;
    preSP2=0;
    preSP=0;
    for(int i=0;i<MAXSIZE;i++){
        preScores[i]=0;
        preScores2[i]=0;
    }
    this->setWindowTitle("综合技能");
}

DialogComprehensive::~DialogComprehensive()
{
    delete ui;
}

float DialogComprehensive::Get_ComScores()
{
    return ComScores;
}

QStringList DialogComprehensive::Get_ObjectName()
{
    return *slist;
}

void DialogComprehensive::InitUi()
{
    QStringList strAL,strAC,strEC;
    strAL<<"一等奖（第1名）"<<"二等奖（第2,3名）"<<"三等奖（第4-6名）"<<"优胜奖（第7及以后）"<<"参与";
    float FAL[5]={10,8,5,3,1};
    ui->cbB_AwardLevel->addItems(strAL);
    for(int i=0;i<strAL.count();i++){
        ui->cbB_AwardLevel->setItemData(i,FAL[i],Qt::UserRole);
    }

    strAC<<"国家级"<<"省级"<<"校级"<<"院级";
    float FAC[4]={1.0,0.5,0.3,0.2};
    ui->cbB_AwardClass->addItems(strAC);
    for(int i=0;i<strAC.count();i++){
        ui->cbB_AwardClass->setItemData(i,FAC[i],Qt::UserRole);
    }

    strEC<<"CET6"<<"CET4"<<"英语口语A级"<<"英语口语B级"<<"英语口语C级"<<"英语口语D级"<<"雅思、托福、GRE等"<<"计算机三级"<<"计算机二级"<<
           "普通话一甲"<<"普通话一乙"<<"普通话二甲"<<"普通话二乙"<<"心理咨询师，营养师等专业职业证书"<<"艺术类考级证书（6级以上)";
    float FEC[15]={8,5,4,3,2,1,6,4,2,4,3,2,1,2,2};
    ui->cbB_Exam->addItems(strEC);
    for(int i=0;i<strEC.count();i++){
        ui->cbB_Exam->setItemData(i,FEC[i],Qt::UserRole);
    }

    strlist=new QStringListModel;
    slist=new QStringList;
}

void DialogComprehensive::on_pbt_AwardAdd_clicked()
{
    float Score,S1,S2;
    S1=ui->cbB_AwardClass->currentData(Qt::UserRole).toFloat();
    S2=ui->cbB_AwardLevel->currentData(Qt::UserRole).toFloat();
    Score=S1*S2;
    slist->insert(slist->count(),ui->cbB_AwardClass->currentText()+"+"+ui->cbB_AwardLevel->currentText()+":"+
                  QString::asprintf("%0.2f",Score));
    strlist->setStringList(*slist);
    ui->listView->setModel(strlist);
    ComScores+=Score;
    ui->label_Score->setText(QString::asprintf("当该项前总分为：%0.2f",ComScores));
}

void DialogComprehensive::on_pbt_SCOk_clicked()
{
    int count=ui->spinBox_SCount->value();
    float Score;
    if(count<=10){
        Score=0.5*count;
    }else if(count>10){
        Score=5;
    }
    if(ui->pbt_SCOk->text()=="确定"){
        slist->insert(slist->count(),QString::asprintf("志愿者服务次数：%d,得分：%0.2f",count,Score));
        ui->pbt_SCOk->setText("修改");
        ComScores+=Score;
        preScores[preSP++]=Score;
    }else if(ui->pbt_SCOk->text()=="修改"){
        int i,j;
        bool flag=false;
        for(i=0;i<slist->count()||flag==true;i++){
            QString tmpstr="志愿者服务次数";
            for(j=0;j<tmpstr.count();j++){
                if(slist->at(i).at(j)!=tmpstr.at(j)){
                    break;
                }
            }
            if(j>=slist->count()){
                flag=true;
                break;
            }
        }
        slist->replace(i,QString::asprintf("志愿者服务次数：%d,得分：%0.2f",count,Score));
        ComScores+=Score;
        ComScores-=preScores[--preSP];
        preScores[preSP++]=Score;
    }
    strlist->setStringList(*slist);
    ui->listView->setModel(strlist);
    ui->label_Score->setText(QString::asprintf("当该项前总分为：%0.2f",ComScores));
}

void DialogComprehensive::on_pbt_SLPCOk_clicked()
{
    int count=ui->spinBox_TPCount->value();
    float Score;
    if(count<=3){
        Score=0.5*count;
    }else if(count>3){
        Score=3;
    }
    if(ui->pbt_SLPCOk->text()=="确定"){
        slist->insert(slist->count(),QString::asprintf("第二学位考试通过数：%d,得分：%0.2f",count,Score));
        ui->pbt_SLPCOk->setText("修改");
        ComScores+=Score;
        preScores2[preSP2++]=Score;
    }else if(ui->pbt_SLPCOk->text()=="修改"){
        int i,j;
        bool flag=false;
        for(i=0;i<slist->count()||flag==true;i++){
            QString tmpstr="第二学位考试通过数";
            for(j=0;j<tmpstr.count();j++){
                if(slist->at(i).at(j)!=tmpstr.at(j)){
                    break;
                }
            }
            if(j>=slist->count()){
                flag=true;
                break;
            }
        }
        slist->replace(i,QString::asprintf("第二学位考试通过数：%d,得分：%0.2f",count,Score));
        ComScores+=Score;
        ComScores-=preScores2[--preSP2];
        preScores2[preSP2++]=Score;
    }
    strlist->setStringList(*slist);
    ui->listView->setModel(strlist);
    ui->label_Score->setText(QString::asprintf("当该项前总分为：%0.2f",ComScores));
}

void DialogComprehensive::on_pbt_ECAdd_clicked()
{
    QString str,str1;
    float score=ui->cbB_Exam->currentData(Qt::UserRole).toFloat();
    str1=ui->cbB_Exam->currentText();
    str="通过"+str1+"考试"+QString::asprintf("，加分：%0.2f",score);
    slist->insert(slist->count(),str);
    strlist->setStringList(*slist);
    ui->listView->setModel(strlist);
    ComScores+=score;
    ui->label_Score->setText(QString::asprintf("当该项前总分为：%0.2f",ComScores));

    ui->cbB_Exam->removeItem(ui->cbB_Exam->currentIndex());
}

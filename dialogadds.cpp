#include "dialogadds.h"
#include "ui_dialogadds.h"
#include <QMessageBox>

DialogAddS::DialogAddS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddS)
{
    ui->setupUi(this);
    theListModel=new QStringListModel;
    ui->listView->setModel(theListModel);

    InnovativeScores=0.0;
    this->setWindowTitle("创新创造能力");
}

DialogAddS::~DialogAddS()
{
    delete ui;
}

float DialogAddS::Get_InnovativeScores()
{
    return InnovativeScores;
}

QStringList DialogAddS::Get_ObjectList()
{
    return ObjectList;
}

void DialogAddS::on_pbt_Ok_clicked()
{
    float S,S1,S2;
    S1=ui->comboBox_Range->currentData().toFloat();
    S2=ui->comboBox_LevelClass->currentData().toFloat();
    S=S1*S2;
    QString NoObjectName="无项目名";

    InnovativeScores+=S;
    if(!ui->lineEdit_ObjectName->text().isEmpty()){
        ObjectList.insert(ObjectList.count(),ui->lineEdit_ObjectName->text()+"+"+ui->comboBox_AwardClass->currentText()+"+"+
                          ui->comboBox_LevelClass->currentText()+"+"+ui->comboBox_Range->currentText());
    }else{
        ObjectList.insert(ObjectList.count(),NoObjectName+"+"+ui->comboBox_AwardClass->currentText()+"+"+
                          ui->comboBox_LevelClass->currentText()+"+"+ui->comboBox_Range->currentText());
    }
    ui->label_Show->setText(QString::asprintf("得分：%0.2f\n当前创新能力总分:%0.2f",S,InnovativeScores));

    if(strList==nullptr){
        strList=new QStringList;
    }
    strList->append(ui->lineEdit_ObjectName->text()+":"+QString::asprintf("%f",S));
    theListModel->setStringList(*strList);

}

void DialogAddS::on_comboBox_AwardClass_activated(const QString &arg1)
{
    if(ui->comboBox_AwardClass->currentText()=="院级以上竞赛"){
        //----------------------------------------------------------奖励类型分类一
        ui->comboBox_Range->clear();
        QStringList RangeList;
        RangeList<<"一等奖"<<"二等奖"<<"三等奖"<<"优胜奖"<<"参与";
        ui->comboBox_Range->addItems(RangeList);
        float RScoreList[5]={10,8,5,3,1};
        for(int i=0; i<RangeList.count();i++){
            ui->comboBox_Range->setItemData(i,RScoreList[i],Qt::UserRole);
        }

        //----------------------------------------------------------奖励类型分类二
        ui->comboBox_LevelClass->clear();
        QStringList LevelList;
        LevelList<<"国家级"<<"省级"<<"校级"<<"院级";
        ui->comboBox_LevelClass->addItems(LevelList);
        float LScoreList[4]={1.0,0.5,0.3,0.1};
        for(int i=0; i<LevelList.count(); i++){
            ui->comboBox_LevelClass->setItemData(i,LScoreList[i],Qt::UserRole);
        }



    }else if(ui->comboBox_AwardClass->currentText()=="科技学术论文"){
        ui->comboBox_Range->clear();
        QStringList RangeList;
        RangeList<<"第一作者"<<"第2-3作者"<<"第4-5作者"<<"第6及以后作者";
        ui->comboBox_Range->addItems(RangeList);
        float RScore[4]={10,5,3,1};
        for(int i=0;i<RangeList.count();i++){
            ui->comboBox_Range->setItemData(i,RScore[i],Qt::UserRole);
        }

        ui->comboBox_LevelClass->clear();
        QStringList LevelList;
        LevelList<<"CSSCI期刊"<<"中文核心期刊"<<"其他期刊正刊"<<"或中文核心期刊（CSSCI）增刊"<<"其他期刊";
        ui->comboBox_LevelClass->addItems(LevelList);
        float LScore[5]={1.0,0.6,0.4,0.2,0.1};
        for(int i=0;i<LevelList.count();i++){
            ui->comboBox_LevelClass->setItemData(i,LScore[i],Qt::UserRole);
        }
    }
}

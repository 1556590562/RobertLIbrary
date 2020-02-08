#include "maintablewindow.h"
#include "ui_maintablewindow.h"
#include <QMessageBox>
#include <QDir>
#include <qstandardpaths.h>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QFileDevice>
#include <QCloseEvent>
#include <QColorDialog>
#include <myfunctions.h>
#include <windows.h>

MainTableWindow::MainTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainTableWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);
    this->setWindowState(Qt::WindowMaximized);

    statuLabel=new QLabel;
    ui->statusBar->addWidget(statuLabel);
    statuLabel->setText("欢迎!");

    Init_Table();
    Init_PrivateData();

    connect(ui->tableView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(on_headClicked(int)));
    connect(this,SIGNAL(Data_Changed()),this,SLOT(Auto_Save()));

}

MainTableWindow::~MainTableWindow()
{
    QFile Delete_File;
    QString curpath=QDir::currentPath();
    QString aFileName;
    for(int i=0;i<Buffcount;i++){
        aFileName=FileName[i];
        Delete_File.remove(aFileName);
    }
    delete ui;
}

void MainTableWindow::Init_Table()
{
    theMTModel=new QStandardItemModel(36,TABLECOLUMNCOUNT,this);
    theMTSModel=new QItemSelectionModel(theMTModel);

    //-----------------------------------------------------------------------------------------------------------表头制作
    QStringList str;
    str<<"        学    号        "<<"   姓  名   "<<" 是否 \n 挂科 "<<" 是否 \n 干部 "<<"测评小组\n 评分"
       <<"学办评分"<<"德育总分"<<" 评 分 "<<" 智  育 "<<" 评 分 "<<" 体  育 "<<" 评 分 "<<" 基 础 素 质 "<<" 名次 "<<" 发 展 素 质 "
       <<" 名次 "<<" 综 合 素 质 "<<" 名次 "<<"   评   定   类   型   "<<"                备                 注                ";
    theMTModel->setHorizontalHeaderLabels(str);
    //-------------------------------------------------------------------------------------------------------------------

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(theMTSModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theMTModel);
    ui->tableView->setSelectionModel(theMTSModel);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    ui->tableView->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color:gray;"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}");
    ui->tableView->verticalHeader()->setStyleSheet
    ("QHeaderView::section {background-color:gray;"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}");
    ui->tableView->setStyleSheet
            ("background-color: rgb(250, 250, 250);"
             "selection-background-color: rgb(200,200,200);"
             "gridline-color: rgb(160, 160, 160);");
    ui->tableView->verticalHeader()->setDefaultSectionSize(10);
}

void MainTableWindow::Init_PrivateData()
{
    StudenCount=0;
    for(int i=0;i<Buffcount;i++){
        FileName[i]=QString::asprintf("tempfile%d",i);
    }
    CURSTEP=0;
    UndoCount=-2;
    RedoCount=0;
    CurFileName="\0";
}

void MainTableWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton defaultBtn=QMessageBox::NoButton;
    QMessageBox::StandardButton result;
    result=QMessageBox::question(this,"退出","退出前是否保存修改",
                                 QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,defaultBtn);
    if(result==QMessageBox::Yes){
        on_act_SaveTable_triggered();
        event->accept();
    }else if(result==QMessageBox::No){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainTableWindow::MtoTupdata()
{
    if(theMainWindow==nullptr){
        QMessageBox::information(this,"tip","stuinfo = nullptr\nlocation:MtoTupdate()");
        return;
    }
    stuInfo->Set_stuNum(theMainWindow->Get_StuNum());
    stuInfo->Set_stuName(theMainWindow->Get_StuName());
    stuInfo->Set_Dexz(theMainWindow->Get_DeScore());
    stuInfo->Set_Dexb(theMainWindow->Get_DeScore2());
    stuInfo->Set_ScoreTi(theMainWindow->Get_TiScore());
    stuInfo->Set_ScoreZhi(theMainWindow->Get_ZhiScore());
    stuInfo->Set_ScoreDev(theMainWindow->Get_SumScore());
    //表格填写------------------------------------------------------------------------------------
    int Flag=0,i=0;
    for(i=0;i<=StudenCount;i++){
        Flag=i;
        if(i!=StudenCount&&theMainWindow->Get_StuNum()==theMTModel->item(i,0)->text()){
            QMessageBox::information(this,"tip","学号相同进行表格更改\nlocation:MtoTupdate()");
            break;
        }
    }
    if(Flag>=StudenCount){
        StudenCount++;
    }
    QStandardItem *aItem;
        int Ccount=0;
        aItem=new QStandardItem(stuInfo->Get_stuNum()); //学号t
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem(stuInfo->Get_stuName());    //姓名t
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem(stuInfo->Get_isPassAllExam());  //是否挂科t
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem(stuInfo->Get_isCLeader());  //是否班干部t
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                              //德育小组评分d
        aItem->setData(stuInfo->Get_Dexz(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                                  //德育学办评分d
        aItem->setData(stuInfo->Get_Dexb(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                                  //德育总分d
        aItem->setData(stuInfo->Get_Dexb()+stuInfo->Get_Dexz(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                                              //德育评分d
        float s1=(stuInfo->Get_Dexb()+stuInfo->Get_Dexz())*0.2;
        aItem->setData(s1,Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                              //智育总分d
        aItem->setData(stuInfo->Get_ScoreZhi(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                  //智育评分d
        float s2=stuInfo->Get_ScoreZhi()*0.7;
        aItem->setData(s2,Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                              //体育总分d
        aItem->setData(stuInfo->Get_ScoreTi(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();              //体育评分d
        float s3=stuInfo->Get_ScoreTi()*0.1;
        aItem->setData(s3,Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                  //基础素质得分d
        aItem->setData(s1+s2+s3,Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();              //基础素质排名（未完成）d
        aItem->setData(1,Qt::DisplayRole);
        aItem->setForeground(QBrush(QColor(255,0,0)));
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                  //发展素质得分d
        aItem->setData(stuInfo->Get_ScoreDev(),Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                   //发展素质排名（未完成）d
        aItem->setData(1,Qt::DisplayRole);
        aItem->setForeground(QBrush(QColor(255,0,0)));
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                      //综合素质得分d
        float Sum=s1+s2+s3+stuInfo->Get_ScoreDev();
        aItem->setData(Sum,Qt::DisplayRole);
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem();                     //综合素质排名d
        aItem->setData(1,Qt::DisplayRole);
        aItem->setForeground(QBrush(QColor(255,0,0)));
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem("xxxxx");            //评定类型t
        theMTModel->setItem(Flag,Ccount++,aItem);

        aItem=new QStandardItem(theMainWindow->Get_CPinfo());       //测评人信息t
        theMTModel->setItem(Flag,Ccount++,aItem);


        for(int i =0;i<StudenCount;i++){
            for(int j=0;j<Ccount;j++){
                theMTModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }

        }

    emit Data_Changed();
}

void MainTableWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //
    if(current.isValid()){
        QStandardItem *aItem=theMTModel->itemFromIndex(current);
        QFont font=aItem->font();
        statuLabel->setText(QString::asprintf("当前学生人数:%d\t当前行:%d\t当前列:%d",StudenCount,current.row()+1,current.column()+1));
    }
}

void MainTableWindow::on_act_Add_triggered()
{
    if(theMainWindow==nullptr){
        theMainWindow=new MainWindow(this);
    }else{
        delete theMainWindow;
        theMainWindow=new MainWindow(this);
    }
    if(stuInfo==nullptr){
        stuInfo=new StudentInfo;
    }
    connect(theMainWindow,SIGNAL(Update_Completed()),this,SLOT(MtoTupdata()));
    theMainWindow->show();

    theMTSModel->currentChanged(theMTSModel->currentIndex(),theMTSModel->currentIndex());
}

void MainTableWindow::on_act_Alter_triggered()
{
    if(theMainWindow==nullptr){
        theMainWindow=new MainWindow(this);
    }else{
        delete theMainWindow;
        theMainWindow=new MainWindow(this);
    }

    if(theMTSModel->hasSelection()&&theMTSModel->currentIndex().row()<=StudenCount){
        theMainWindow->Set_AlterStuNum(theMTModel->item(theMTSModel->currentIndex().row(),1)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),0)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),4)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),5)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),10)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),8)->data(Qt::DisplayRole).toString(),
                                       theMTModel->item(theMTSModel->currentIndex().row(),14)->data(Qt::DisplayRole).toString());
    }else{
        QMessageBox::information(this,"tip","请选择一项在点击修改");
        return;
    }

    if(stuInfo==nullptr){
        stuInfo=new StudentInfo;
    }
    connect(theMainWindow,SIGNAL(Update_Completed()),this,SLOT(MtoTupdata()));
    theMainWindow->show();

    theMTSModel->currentChanged(theMTSModel->currentIndex(),theMTSModel->currentIndex());
}

void MainTableWindow::on_act_About_triggered()
{
    QString str;
    str="据重庆医科大学学生手册定制\n仅适用于重庆医科大学综合测评\n如有需要请联系作者\n\n该软件仅为个人创作\n并未作商业用途\n\n版本1.0\n联系方式:QQ1556590562";
    QMessageBox::information(this,"About",str);
}

void MainTableWindow::on_act_ToPrintFile_triggered()     //生成打印文件（另存为）
{
    QString curPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString aFileName=QFileDialog::getSaveFileName(this,"选择一个文件",curPath,"文本文件(*.txt)");
    if(aFileName.isEmpty()){
        QMessageBox::information(this,"失败","文件创建失败");
        return;
    }
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))){
        QMessageBox::information(this,"失败","该文件不存在");
        return;
    }
    QTextStream aStream(&aFile);
    QStandardItem *aItem;
    int i,j;
    QString str;
    for(i=0;i<StudenCount;i++){
        for(j=0;j<20;j++){
            aItem=theMTModel->item(i,j);
            if((j>=0&&j<4)||(j>=18&&j<20)){
                str=aItem->text()+QString::asprintf("\t");
            }else if(j>=4&&j<18){
                str=aItem->data(Qt::DisplayRole).toString()+QString::asprintf("\t");
            }
            aStream<<str;
        }
        aStream<<"\n";
    }
}

void MainTableWindow::on_act_OpenFile_triggered()
{
    //从文件中读入数据到缓存链表
    QString curPath=QDir::currentPath();
    QString title="选择一个文件";
    QString fliter="数据文件(*.zcd);;所有文件(*.*)";
    QString aFileName=QFileDialog::getOpenFileName(this,title,curPath,fliter);
    if(aFileName.isEmpty()){
        QMessageBox::information(this,"失败","文件不存在");
        return;
    }
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);
        while(!aFile.atEnd()){
            QString str=aStream.readAll();
            fFileContent=str.split(QRegExp("\n"),QString::SkipEmptyParts);
        }
        CurFileName=aFileName;
        aFile.close();
    }else{
        QMessageBox::information(this,"失败","文件打开失败");
    }
    StudenCount=fFileContent.count();
    QString str;
    if(fFileContent.count()==1){
       QMessageBox::information(this,"tip","只读了一行");
    }

    //设置表格数据
    QStandardItem *aItem;
    QStringList tmpList;
    float tmpfloat;
    int j;
    for(int i=0;i<StudenCount;i++){
        QString aLineText=fFileContent.at(i);
        tmpList=aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);       //跳过Tab&空格符号
        for(j=0;j<TABLECOLUMNCOUNT;j++){
            if((j>=0&&j<4)||(j>=18&&j<20)){
                aItem=new QStandardItem(tmpList.at(j));
                theMTModel->setItem(i,j,aItem);
            }else if(j>=4&&j<18){
                if(j==13||j==15||j==17){
                    aItem=new QStandardItem();
                    aItem->setData(MyFunctions::KeepTwo_Float(tmpList.at(j).toFloat(),0),Qt::DisplayRole);
                    aItem->setData(tmpList.at(j).toFloat(),Qt::UserRole);
                    theMTModel->setItem(i,j,aItem);
                }else{
                    aItem=new QStandardItem();
                    tmpfloat=tmpList.at(j).toFloat();
                    aItem->setData(tmpfloat,Qt::UserRole);
                    aItem->setData(MyFunctions::KeepTwo_Float(tmpfloat),Qt::DisplayRole);
                    theMTModel->setItem(i,j,aItem);
                }
            }
        }
    }
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<20;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
            if(j==13||j==15||j==17){
                theMTModel->item(i,j)->setForeground(QBrush(QColor(250,0,0)));
            }
        }
    }
    theMTSModel->currentChanged(theMTSModel->currentIndex(),theMTSModel->currentIndex());
    emit Data_Changed();
}

void MainTableWindow::on_act_SaveTable_triggered()
{
    //创建文件
    QDir tempDir;
    QString aFileName=CurFileName;
    QString curPath=QDir::currentPath();
    if(aFileName.isEmpty()){
        aFileName=QFileDialog::getSaveFileName(this,"保存文件",curPath,"(*数据文件.zcd);;(*文本文件.txt)");
        return;
    }
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))){
        QMessageBox::information(this,"失败","该文件不存在");
        return;
    }
    QTextStream aStream(&aFile);
    QStandardItem *aItem;
    int i,j;
    QString str;
    for(i=0;i<StudenCount;i++){
        for(j=0;j<20;j++){
            aItem=theMTModel->item(i,j);
            if((j>=0&&j<4)||(j>=18&&j<20)){
                str=aItem->text()+QString::asprintf("\t");
            }else if(j>=4&&j<18){
                str=aItem->data(Qt::DisplayRole).toString()+QString::asprintf("\t");
            }
            aStream<<str;
        }
        aStream<<"\n";
    }
}

void MainTableWindow::on_act_Exit_triggered()
{

}

void MainTableWindow::on_act_Delete_triggered()     //删除
{
    if(StudenCount<=0){
        QMessageBox::warning(this,"Warning","没有可删除的对象");
        return;
    }
    QModelIndex curIndex=theMTSModel->currentIndex();
    if(curIndex.row()==theMTModel->rowCount()-1){
        theMTModel->removeRow(curIndex.row());
    }else{
        theMTModel->removeRow(curIndex.row());
        theMTSModel->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
    StudenCount--;
    emit Data_Changed();
    theMTSModel->currentChanged(theMTSModel->currentIndex(),theMTSModel->currentIndex());
}

void MainTableWindow::on_act_Left_triggered()
{
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<TABLECOLUMNCOUNT;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignLeft);
        }
    }
    emit Data_Changed();
}

void MainTableWindow::on_act_Center_triggered()
{
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<TABLECOLUMNCOUNT;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    emit Data_Changed();
}

void MainTableWindow::on_act_Full_triggered()
{
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<TABLECOLUMNCOUNT;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignVCenter);
        }
    }
    emit Data_Changed();
}

void MainTableWindow::on_act_Right_triggered()
{
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<TABLECOLUMNCOUNT;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignRight);
        }
    }
    emit Data_Changed();
}

void MainTableWindow::on_act_SetFontColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"选择字体颜色");
    if(theMTSModel->hasSelection()){
        QModelIndexList selectedIndex=theMTSModel->selectedIndexes();
        for(int i=0;i<selectedIndex.count();i++){
            QModelIndex aIndex=selectedIndex.at(i);
            QStandardItem *aItem=theMTModel->itemFromIndex(aIndex);
            aItem->setForeground(QBrush(color));
        }
    }else{
        for(int i=0;i<StudenCount;i++){
            for(int j=0;j<TABLECOLUMNCOUNT;j++){
                theMTModel->item(i,j)->setForeground(QBrush(color));
            }
        }
    }
    emit Data_Changed();
}

void MainTableWindow::on_headClicked(int currentcol)
{

    if(currentcol==0||currentcol==13||currentcol==15||currentcol==17){
        theMTModel->sort(currentcol,Qt::AscendingOrder);
    }else{
        theMTModel->setSortRole(Qt::UserRole);
        theMTModel->sort(currentcol,Qt::DescendingOrder);
    }
}

void MainTableWindow::on_act_DataCheck_triggered()
{
    Loading *loadingWindow=new Loading(this);
    loadingWindow->setAttribute(Qt::WA_DeleteOnClose);
    loadingWindow->setWindowTitle("如有卡顿，请稍等片刻...");
    loadingWindow->show();
    connect(this,SIGNAL(FinishSituaion(int s)),loadingWindow,SLOT(on_progressBar_valueChanged(int value)));
    float DPS1,DPS2,ZPS,TPS,FZS;
    QString str;
    for(int i=0;i<StudenCount;i++){

        DPS1=theMTModel->item(i,4)->data(Qt::UserRole).toFloat();
        DPS2=theMTModel->item(i,5)->data(Qt::UserRole).toFloat();
        ZPS=theMTModel->item(i,8)->data(Qt::UserRole).toFloat();
        TPS=theMTModel->item(i,10)->data(Qt::UserRole).toFloat();
        FZS=theMTModel->item(i,14)->data(Qt::UserRole).toFloat();

        theMTModel->item(i,4)->setData(str.setNum(DPS1,'f',2),Qt::DisplayRole);
        theMTModel->item(i,5)->setData(str.setNum(DPS2,'f',2),Qt::DisplayRole);
        theMTModel->item(i,8)->setData(str.setNum(ZPS,'f',2).toFloat(),Qt::DisplayRole);
        theMTModel->item(i,10)->setData(str.setNum(TPS,'f',2),Qt::DisplayRole);
        theMTModel->item(i,14)->setData(str.setNum(FZS,'f',2),Qt::DisplayRole);

        theMTModel->item(i,6)->setData(str.setNum(DPS1+DPS2,'f',2),Qt::DisplayRole);
        theMTModel->item(i,7)->setData(str.setNum((DPS1+DPS2)*0.2,'f',2),Qt::DisplayRole);
        theMTModel->item(i,9)->setData(str.setNum(ZPS*0.7,'f',2),Qt::DisplayRole);
        theMTModel->item(i,11)->setData(str.setNum(TPS*0.1,'f',2),Qt::DisplayRole);
        theMTModel->item(i,12)->setData(str.setNum(((DPS1+DPS2)*0.2)+(ZPS*0.7)+(TPS*0.1),'f',2),Qt::DisplayRole);
        theMTModel->item(i,16)->setData(str.setNum(((DPS1+DPS2)*0.2)+(ZPS*0.7)+(TPS*0.1)+FZS,'f',2),Qt::DisplayRole);

        emit FinishSituaion(50);
    }
    emit Data_Changed();
}

void MainTableWindow::Auto_Save()
{
    //创建文件
    if(CURSTEP==Buffcount-1){
        CURSTEP=0;
    }else{
        CURSTEP++;
    }
    QDir tempDir;
    QString aFileName=FileName[CURSTEP];
    QString curPath=QDir::currentPath();
    if(aFileName.isEmpty()){
        return;
    }
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))){
        QMessageBox::information(this,"失败","该文件不存在");
        return;
    }
    QTextStream aStream(&aFile);
    QStandardItem *aItem;
    int i,j;
    QString str;
    for(i=0;i<StudenCount;i++){
        for(j=0;j<20;j++){
            aItem=theMTModel->item(i,j);
            if((j>=0&&j<4)||(j>=18&&j<20)){
                str=aItem->text()+QString::asprintf("\t");
            }else if(j>=4&&j<18){
                str=aItem->data(Qt::DisplayRole).toString()+QString::asprintf("\t");
            }
            aStream<<str;
        }
        aStream<<"\n";
    }
    if(UndoCount<Buffcount-1){
        UndoCount++;
    }

    RedoCount=0;
}

void MainTableWindow::on_act_Undo_triggered()
{
    if(UndoCount<=0){
        QMessageBox::warning(this,"Warning","缓存空间仅限撤回5次，超出次数无法撤回");
        UndoCount=0;
        return;
    }
    UndoCount--;
    if(!(RedoCount>Buffcount-1)){
        RedoCount++;
    }
    if(CURSTEP==0){
        CURSTEP=Buffcount-1;
    }else{
        CURSTEP--;
    }

    QString curPath=QDir::currentPath();
    QString aFileName=FileName[CURSTEP];
    if(aFileName.isEmpty()){
        QMessageBox::information(this,"失败","文件不存在");
        return;
    }
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);
        while(!aFile.atEnd()){
            QString str=aStream.readAll();
            fFileContent=str.split(QRegExp("\n"),QString::SkipEmptyParts);
        }
        aFile.close();
    }else{
        QMessageBox::information(this,"失败","文件打开失败");
    }
    StudenCount=fFileContent.count();
    QString str;
    if(fFileContent.count()==1){
       QMessageBox::information(this,"tip","只读了一行");
    }

    //设置表格数据
    QStandardItem *aItem;
    QStringList tmpList;
    int j;
    for(int i=0;i<StudenCount;i++){
        QString aLineText=fFileContent.at(i);
        tmpList=aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);       //跳过Tab&空格符号
        for(j=0;j<20;j++){
            if((j>=0&&j<4)||(j>=18&&j<20)){
                aItem=new QStandardItem(tmpList.at(j));
                theMTModel->setItem(i,j,aItem);
            }else if(j>=4&&j<18){
                aItem=new QStandardItem();
                aItem->setData(tmpList.at(j).toFloat(),Qt::DisplayRole);
                theMTModel->setItem(i,j,aItem);
            }
        }
    }
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<20;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
            if(j==13||j==15||j==17){
                theMTModel->item(i,j)->setForeground(QBrush(QColor(250,0,0)));
            }
        }
    }
}

void MainTableWindow::on_act_Redo_triggered()
{
    if(RedoCount<=0){
        QMessageBox::warning(this,"Warning","前进（重做）无内容");
        RedoCount=0;
        return;
    }
    RedoCount--;
    if(!(UndoCount>Buffcount-1)){
        UndoCount++;
    }
    if(CURSTEP==0){
        CURSTEP=Buffcount-1;
    }else{
        CURSTEP++;
    }

    QString curPath=QDir::currentPath();
    QString aFileName=FileName[CURSTEP];
    if(aFileName.isEmpty()){
        QMessageBox::information(this,"失败","文件不存在");
        return;
    }
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);
        while(!aFile.atEnd()){
            QString str=aStream.readAll();
            fFileContent=str.split(QRegExp("\n"),QString::SkipEmptyParts);
        }
        aFile.close();
    }else{
        QMessageBox::information(this,"失败","文件打开失败");
    }
    StudenCount=fFileContent.count();
    QString str;
    if(fFileContent.count()==1){
       QMessageBox::information(this,"tip","只读了一行");
    }

    //设置表格数据
    QStandardItem *aItem;
    QStringList tmpList;
    int j;
    for(int i=0;i<StudenCount;i++){
        QString aLineText=fFileContent.at(i);
        tmpList=aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);       //跳过Tab&空格符号
        for(j=0;j<20;j++){
            if((j>=0&&j<4)||(j>=18&&j<20)){
                aItem=new QStandardItem(tmpList.at(j));
                theMTModel->setItem(i,j,aItem);
            }else if(j>=4&&j<18){
                aItem=new QStandardItem();
                aItem->setData(tmpList.at(j).toFloat(),Qt::DisplayRole);
                theMTModel->setItem(i,j,aItem);
            }
        }
    }
    for(int i=0;i<StudenCount;i++){
        for(int j=0;j<20;j++){
            theMTModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
            if(j==13||j==15||j==17){
                theMTModel->item(i,j)->setForeground(QBrush(QColor(250,0,0)));
            }
        }
    }
}

void MainTableWindow::on_act_CloseFile_triggered()
{
    QMessageBox::StandardButton defaultBtn=QMessageBox::NoButton;
    QMessageBox::StandardButton result;
    result=QMessageBox::question(this,"退出","退出前是否保存修改",
                                 QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,defaultBtn);
    if(result==QMessageBox::Yes){
        on_act_SaveTable_triggered();
        Init_Table();
        Init_PrivateData();
    }else if(result==QMessageBox::No){
        Init_Table();
        Init_PrivateData();
    }else{
        return;
    }
}

void MainTableWindow::on_act_Search_triggered()
{
    theSearchWindow=new SearchData(this);
    theSearchWindow->setAttribute(Qt::WA_DeleteOnClose);
    int result = theSearchWindow->exec();

    //稍等窗口调用

    //数据搜索
    QString SearchName,SearchNum,SearchPost,SearchOther,SearchScore,SearchRange;
    SearchName=theSearchWindow->Get_SearchName();
    SearchNum=theSearchWindow->Get_SearchNum();
    SearchPost=theSearchWindow->Get_SearchPost();
    SearchOther=theSearchWindow->Get_SearchOther();
    SearchScore=theSearchWindow->Get_SearchScores();
    SearchRange=theSearchWindow->Get_SearchRange();
    QBrush greenBrush(Qt::green);

    Loading loading(this);
    loading.setAttribute(Qt::WA_DeleteOnClose);
    loading.show();

    if(result==QDialog::Accepted){
        if(SearchName!="none"){
            for(int i=0;i<StudenCount;i++){
                if(theMTModel->item(i,2)->data(Qt::DisplayRole).toString()==SearchName){
                    theMTModel->item(i,2)->setBackground(greenBrush);
                }
            }
        }
        if(SearchNum!="none"){
            for(int i=0;i<StudenCount;i++){
                if(theMTModel->item(i,1)->data(Qt::DisplayRole).toString()==SearchNum){
                    theMTModel->item(i,1)->setBackground(greenBrush);
                }
            }
        }
        if(SearchPost!="none"){
            for(int i=0;i<StudenCount;i++){
                if(theMTModel->item(i,3)->data(Qt::DisplayRole).toString()==SearchPost){
                    theMTModel->item(i,3)->setBackground(greenBrush);
                }
            }
        }
        if(SearchScore!="none"){
            for(int i=0;i<StudenCount;i++){
                for(int j=4;j<17;j++){
                    if(j==13||j==15){
                        continue;
                    }
                    if(theMTModel->item(i,j)->data(Qt::DisplayRole).toString()==SearchScore){
                        theMTModel->item(i,j)->setBackground(greenBrush);
                    }
                }
            }
        }
        if(SearchOther!="\0"){
            for(int i=0;i<StudenCount;i++){
                for(int j=TABLECOLUMNCOUNT-2;j<TABLECOLUMNCOUNT;j++){
                    if(theMTModel->item(i,j)->data(Qt::DisplayRole).toString()==SearchOther){
                        theMTModel->item(i,j)->setBackground(greenBrush);
                    }
                }
            }
        }
        if(SearchRange!="\0"){
            for(int i=0;i<StudenCount;i++){
                for(int j=13;j<18;j++){
                    if(j==14||j==16){
                        continue;
                    }
                    if(theMTModel->item(i,j)->data(Qt::DisplayRole).toString()==SearchRange){
                        theMTModel->item(i,j)->setBackground(greenBrush);
                    }
                }
            }
        }
    }else{
        return;
    }
}



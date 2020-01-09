#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedLayout>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , view(new QWebEngineView(parent))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStackedLayout* layout = new QStackedLayout(ui->frame_view);
    ui->frame_view->setLayout(layout);
    layout->addWidget(view);
    view->show();

    QSettings settings("./config.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF8");

    settings.beginGroup("login");
    QString inputNameId = settings.value("inputNameId").toString();
    QString inputPwdId = settings.value("inputPwdId").toString();
    settings.endGroup();

    if(inputNameId.isEmpty()){
        settings.beginGroup("login");
        settings.setValue("inputNameId",page_name_Id);
        settings.setValue("inputPwdId",page_password_Id);
        settings.endGroup();
    }
    settings.beginGroup("login");
    page_name_Id = settings.value("inputNameId").toString();
    page_password_Id = settings.value("inputPwdId").toString();
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    delete view;
    delete ui;
}

QUrl MainWindow::getInputUrl(){

    QString str =ui->url_Input->text().trimmed();
    if(str.isEmpty()){
        return QUrl(QStringLiteral("https://www.baidu.com"));
    }
    if(str.indexOf("://") == -1 ){
        str = "http://"+ str;
    }
    return QUrl(str);
}



void MainWindow::loadWeb()
{
    QUrl url= getInputUrl();
    view->setUrl(url);
    view->page()->load(url);
}

void MainWindow::on_go_clicked()
{
    loadWeb();
}


void MainWindow::setUserData()
{
    QString uid,pwd;
    if(userList.isEmpty() && pwdList.isEmpty()){
        return;
    }
    if(uidIndex < userList.size()){
        uid  = userList.at(uidIndex).trimmed();
        if(this->isUniformPwd){
            pwd  = pwdList.at(0).trimmed();
        }else{
            pwd  = pwdList.at(uidIndex).trimmed();
        }
        QString strUidjs= QString("document.getElementById('%1').value='%2';").arg(page_name_Id).arg(uid);
        QString strPwdjs= QString("document.getElementById('%1').value='%2';").arg(page_password_Id).arg(pwd);
        view->page()->runJavaScript(strUidjs);
        view->page()->runJavaScript(strPwdjs);
        ui->label->setText(uid);
        ui->label_2->setText(pwd);
    }
}

void MainWindow::setUserlist(QStringList list)
{

    userList.clear();
    userList.append(list);
    ui->spinBox->setValue(1);

}

void MainWindow::setPwdlist(QStringList list)
{
    pwdList.clear();
    pwdList.append(list);
}
void MainWindow::updateSpinbox(int size = 1)
{
    if(size)
    {
        ui->spinBox->setRange(1,size);
        QString str ="all:"+QString("%1").arg(size);
        ui->label_3->setText(str);
        ui->spinBox->setValue(1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int value = ui->spinBox->value()+1;
    if(value && value <= userList.size()){
        ui->spinBox->setValue(value);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int value =ui->spinBox->value()-1;
    if(value && value <= userList.size()){
        ui->spinBox->setValue(value);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    uidIndex = arg1 - 1;
    setUserData();
}

void MainWindow::updateUserlist()
{
    QStringList list ;
    QString str= ui->plainTextEdit_users->toPlainText();
    str.replace("\r","");
    list = str.split('\n');
    list.removeDuplicates();
    list.removeAll("");
    updateSpinbox(list.size());
    setUserlist(list);

}

void MainWindow::updatePwdlist()
{
    QStringList list ;
    QString str= ui->plainTextEdit_pwds->toPlainText().trimmed();
    str.replace("\r","");
    list = str.split('\n');
    list.removeDuplicates();
    list.removeAll("");
    setPwdlist(list);
}
void MainWindow::on_pushButton_3_clicked()
{
    updateUserlist();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    isUniformPwd = ui->checkBox->isChecked();
    if(isUniformPwd){
        pwdList.clear();
        QString pwd = ui->plainTextEdit_pwds->toPlainText().trimmed();
        pwdList.append(pwd);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    view->back();
}

void MainWindow::on_pushButton_5_clicked()
{
    setUserData();
    QString str = ui->lineEdit_code->text().trimmed();
    view->page()->runJavaScript(
                QString("document.getElementById('txtCode').value='%1';").arg(str));
    view->page()->runJavaScript(
                QString("document.getElementById('btnSignIn').click();"));

    //    view->page()
}

void MainWindow::on_pushButton_6_clicked()
{
    updatePwdlist();
}

void MainWindow::on_pushButton_7_clicked()
{
    view->forward();
}

void MainWindow::on_pushButton_8_clicked()
{
    view->reload();
}

void MainWindow::on_pushButton_9_clicked()
{
    QString js = ui->plainTextEdit_pwds_2->toPlainText().trimmed();
    view->page()->runJavaScript(js);
}

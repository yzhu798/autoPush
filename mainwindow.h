#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QSettings>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_go_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    void setUserData();

    void updateUserlist();

    void updateSpinbox(int size);

    void setPwdlist(QStringList list);

    void setUserlist(QStringList list);

    void updatePwdlist();

    QUrl getInputUrl();

    void loadWeb();
private:
    Ui::MainWindow *ui;
    QWebEngineView *view;

    QString page_name_Id ="txtUsername";
    QString page_password_Id="txtPassword";

    QStringList userList;
    QStringList pwdList;
    bool isUniformPwd = false;
    uint uidIndex = 0;

};
#endif // MAINWINDOW_H

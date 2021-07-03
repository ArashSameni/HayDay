#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_lblSignup_clicked();

    void on_lblLogin_clicked();

    void on_btnSignup_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginWindow *ui;
    bool isPasswordStrong(const QString& password);
    void showSignup();
    void showLogin();
};

#endif // LOGINWINDOW_H

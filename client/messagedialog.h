#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QString text, QString title = "Error", QWidget *parent = nullptr);
    ~MessageDialog();

private slots:
    void on_btnOk_clicked();

private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOG_H

#ifndef SCOREBOARDDIALOG_H
#define SCOREBOARDDIALOG_H

#include <QDialog>
#include "globals.h"
#include <QVector>
#include <QLabel>
#include <QSound>

namespace Ui {
class ScoreboardDialog;
}

class ScoreboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreboardDialog(QWidget *parent = nullptr);
    ~ScoreboardDialog();

private slots:
    void on_btnLeftArrow_clicked();

    void on_btnRightArrow_clicked();

private:
    Ui::ScoreboardDialog *ui;
    QSound* clickSound;

    int pagesCount = 0;
    int currentPage = 0;
    int currentRank = 0;
    QVector<QLabel*> labels;
    void createLabels();
    void showCurrentPage();
    void calcPagesCount();
    void fetchFarmers();
    void showFarmer(const QString &nickname, int gender, int level, int xp, int max_xp);
    void clearScoreboard();
};

#endif // SCOREBOARDDIALOG_H

#include "scoreboarddialog.h"
#include "ui_scoreboarddialog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QtMath>

ScoreboardDialog::ScoreboardDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::ScoreboardDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    calcPagesCount();
    ui->lblCurrentPage->setText("1/" + QString::number(pagesCount));
    createLabels();
    fetchFarmers();

    clickSound = new QSound("://sounds/clickSound.wav", this);
}

ScoreboardDialog::~ScoreboardDialog()
{
    delete ui;
}

void ScoreboardDialog::calcPagesCount()
{
    QString query = "SELECT COUNT(*) FROM Farmers";

    socket.write(query);
    QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

    if (!servers_answer.isNull())
    {
        QJsonArray data = servers_answer.array()[0].toArray();
        int farmersCount = data[0].toString().toInt();
        pagesCount = qCeil(farmersCount / 5.0);
    }
}

void ScoreboardDialog::fetchFarmers()
{
    currentRank = 0;
    QString query = "SELECT nickname, gender, level, xp, max_xp FROM Farmers ORDER BY level DESC, xp DESC limit " + QString::number(currentPage * 5) + ", 5";

    socket.write(query);
    QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

    if (!servers_answer.isNull())
    {
        QJsonArray datas = servers_answer.array();
        for (int i = 0; i < datas.size(); i++)
        {
            QJsonArray data = datas[i].toArray();
            showFarmer(data[0].toString(), data[1].toString().toInt(),
                       data[2].toString().toInt(), data[3].toString().toInt(),
                       data[4].toString().toInt());
        }
    }
}

void ScoreboardDialog::showFarmer(const QString &nickname, int gender, int level, int xp, int max_xp)
{
    //Rank Label
    int player_rank = (currentPage * 5) + currentRank + 1;
    labels[currentRank * 6]->setNum(player_rank);
    labels[currentRank * 6]->show();

    //Gender Label
    if(gender == 0) //man
        labels[currentRank * 6 + 1]->setStyleSheet("image: url(:/img/farmer-man.png);");
    else
        labels[currentRank * 6 + 1]->setStyleSheet("image: url(:/img/farmer-woman.png);");
    labels[currentRank * 6 + 1]->show();

    //Nickname label
    labels[currentRank * 6 + 2]->setText(nickname);
    labels[currentRank * 6 + 2]->show();

    //Star label
    labels[currentRank * 6 + 3]->show();

    //Level label
    labels[currentRank * 6 + 4]->setNum(level);
    labels[currentRank * 6 + 4]->show();

    int percentage = static_cast<int>((static_cast<float>(xp) / max_xp) * 100);
    labels[currentRank * 6 + 5]->setText(QString::number(percentage) + "%");
    labels[currentRank * 6 + 5]->show();

    currentRank += 1;
}

void ScoreboardDialog::clearScoreboard()
{
    for (int i = 0; i < labels.size(); ++i)
        labels[i]->hide();
}

void ScoreboardDialog::on_btnLeftArrow_clicked()
{
    if(!is_sound_muted)
        clickSound->play();
    if(currentPage > 0)
    {
        currentPage -= 1;
        showCurrentPage();
        clearScoreboard();
        fetchFarmers();
    }
}

void ScoreboardDialog::showCurrentPage()
{
    ui->lblCurrentPage->setText(QString::number(currentPage + 1) + "/" + QString::number(pagesCount));
}

void ScoreboardDialog::on_btnRightArrow_clicked()
{
    if(!is_sound_muted)
        clickSound->play();
    if(currentPage < pagesCount - 1)
    {
        currentPage += 1;
        showCurrentPage();
        clearScoreboard();
        fetchFarmers();
    }
}

void ScoreboardDialog::createLabels()
{
    for (int i = 0; i < 5; ++i)
    {
        QLabel *lbl_rank = new QLabel(this);
        lbl_rank->setAlignment(Qt::AlignCenter);
        lbl_rank->setGeometry(65, 126 + (79 * i), 31, 31);
        lbl_rank->hide();
        labels.push_back(lbl_rank);

        QLabel *lbl_gender = new QLabel(this);
        lbl_gender->setGeometry(100, 121 + (79 * i), 35, 35);
        lbl_gender->hide();
        labels.push_back(lbl_gender);

        QLabel *lbl_nick_name = new QLabel(this);
        lbl_nick_name->setGeometry(137, 126 + (79 * i), 181, 31);
        lbl_nick_name->hide();
        labels.push_back(lbl_nick_name);

        QLabel *lbl_star = new QLabel(this);
        lbl_star->setGeometry(386, 115 + (79 * i), 50, 49);
        lbl_star->setStyleSheet("image: url(:/img/star.png);");
        lbl_star->hide();
        labels.push_back(lbl_star);

        QLabel *lbl_level = new QLabel(this);
        lbl_level->setAlignment(Qt::AlignCenter);
        lbl_level->setStyleSheet("font-size: 19px;\ncolor: #fff;");
        lbl_level->setGeometry(376, 124 + (79 * i), 70, 31);
        lbl_level->hide();
        labels.push_back(lbl_level);

        QLabel *lbl_percentage = new QLabel(this);
        lbl_percentage->setAlignment(Qt::AlignCenter);
        lbl_percentage->setGeometry(586, 126 + (79 * i), 181, 31);
        lbl_percentage->hide();
        labels.push_back(lbl_percentage);
    }
}

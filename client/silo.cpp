#include "silo.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>

int Silo::id_ = 0;
Silo *Silo::silo = nullptr;

Silo::Silo()
{
    level_ = 1;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    storage_ = 1;
    max_storage_ = 5;
}

Silo &Silo::create()
{
    if (silo != nullptr)
        delete silo;

    silo = new Silo;
    QString query = "INSERT INTO Silos DEFAULT VALUES";

    socket.write(query);
    id_ = socket.read().toInt();

    return *silo;
}

void Silo::save()
{
    QString query = "UPDATE Silos SET storage=:storage, max_storage=:max_storage, "
                    "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                    "WHERE id=:id";
    query.replace(":id", QString::number(id_));
    query.replace(":storage", QString::number(storage_));
    query.replace(":max_storage", QString::number(max_storage_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));

    socket.write(query);
}

Silo &Silo::get(int silo_id)
{
    if (silo == nullptr)
        silo = new Silo;

    if (silo_id != silo->id_)
    {
        silo->id_ = silo_id;

        QString query = "SELECT storage, max_storage, upgrade_day, is_upgrading, level FROM Silos WHERE id=:id";
        query.replace(":id", QString::number(silo_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonObject json_obj = servers_answer.object()["0"].toObject();

            silo->storage_ = json_obj["0"].toInt();
            silo->max_storage_ = json_obj["1"].toInt();
            silo->upgrade_day_ = json_obj["2"].toInt();
            silo->is_upgrading_ = json_obj["3"].toInt();
            silo->level_ = json_obj["4"].toInt();
        }
        else
        {
            std::string err = "Silo with id " + std::to_string(silo_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *silo;
}

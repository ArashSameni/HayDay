#ifndef FARM_H
#define FARM_H

#include "barn.h"
#include "silo.h"
#include "livingplaces.h"
#include "fields.h"

class Farm
{
    static int id_;
    static Farm *farm;

    int barn_id_;
    int silo_id_;
    int alfalfa_field_id_;
    int wheat_field_id_;

    Farm() {}

public:
    Farm(Farm const &) = delete;
    void operator=(Farm const &) = delete;

    Barn &barn() const { return Barn::get(barn_id_); }
    Silo &silo() const { return Silo::get(silo_id_); }
    ChickenCoop &chicken_coop() const { return ChickenCoop::getByFarmId(id_); }
    CowPasture &cow_pasure() const { return CowPasture::getByFarmId(id_); }
    SheepPasture &sheep_pasture() const { return SheepPasture::getByFarmId(id_); }
    WheatField &wheat_field() const { return WheatField::get(wheat_field_id_); }
    AlfalfaField &alfalfa_field() const { return AlfalfaField::get(alfalfa_field_id_); }

    static Farm &get(int farm_id);
    static Farm &create(int barn_id, int silo_id, int alfalfa_field_id, int wheat_field_id);
    static int id() { return id_; }

    ~Farm() {}
};
int Farm::id_ = 0;
Farm *Farm::farm = nullptr;

#endif // FARM_H

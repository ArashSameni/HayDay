#ifndef ENUMS_H
#define ENUMS_H

namespace Enums
{
    enum
    {
        NOT_PLOWED,
        PLOWING,
        PLOWED,


        NOT_PLANTED,
        PLANTED,

        //planting contdition
        AREA_ERROR,
        LACK_OF_SEED,
        ALREADY_PLANTED,
        ALREADY_PLOWED,

        //animals condition
        HUNGRY,
        FED,
        COLLECTABLE,
        ALREADY_FED,
        LACK_OF_ALFALFA,
        LACK_OF_WHEAT,
        LACK_OF_STORAGE,
        NO_ANIMALS,


        LACK_OF_COINS,
        LACK_OF_NAILS,
        LACK_OF_SHOVELS,
        LACK_OF_LEVEL,

        //shop
        WHEAT,
        ALFALFA,
        CHICKEN,
        EGG,
        COW,
        MILK,
        SHEEP,
        WOOL,
        NAIL,
        SHOVEL,


        OK
    };
}

#endif // ENUMS_H

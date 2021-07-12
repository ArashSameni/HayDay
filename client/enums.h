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
        LACK_OF_SPACE,
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


        LACK_OF_COINS,
        LACK_OF_NAILS,
        LACK_OF_SHOVELS,
        LACK_OF_LEVEL,

        OK
    };
}

#endif // ENUMS_H

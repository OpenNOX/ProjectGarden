#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_MAP_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_MAP_H

#include "stack.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Map pair node for storing key / value in a sequence.
     * @class KeyT Key data type.
     * @class ValueT Value data type.
     */
    template <class KeyT, class ValueT>
    struct MapPair
    {
        /**
         * Key.
         */
        KeyT key;

        /**
         * Value.
         */
        ValueT value;
    };

    /**
     * Map data structure, sometimes referred to as a dictionary.
     * @typedef KeyT Keys data type.
     * @typedef ValueT Values data type.
     */
    template <class KeyT, class ValueT>
    class Map : public Stack<MapPair<KeyT, ValueT>>
    {
    };
}
}
}

#endif
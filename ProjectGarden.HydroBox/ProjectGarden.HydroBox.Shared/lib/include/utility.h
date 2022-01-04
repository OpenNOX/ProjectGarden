#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_UTILITY_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_UTILITY_H

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Hard reset board.
     */
    void(*hardResetBoard) (void) = 0;
}
}
}

#endif
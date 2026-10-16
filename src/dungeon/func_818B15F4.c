#include "modules/dungeon_ovl_18d0850.h"

s32 func_80024DF4(void *state_ptr, void *second_ptr, void *third_ptr)
{
    switch (((ovl_18d0850_818B15F4_Func818B15F4Arg *)state_ptr)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    default:
        break;
    case 4:
        dungeonBuildATrigonometricTableProcessesUpEightHeightOffsetSegments(state_ptr, second_ptr, third_ptr);
        break;
    case 5:
        dungeonBuildACircularLookupTableSubmitEightPhaseShiftedEntries(state_ptr, second_ptr, third_ptr);
        break;
    case 6:
        dungeonFadeEffectSpriteToBlack(state_ptr, second_ptr, third_ptr);
        break;
    }
    return 0;
}

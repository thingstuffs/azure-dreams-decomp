#include "modules/town_door.h"

/* Test the object status, reversing the result when the linked record has bit 3 set. */
s32 check_door_status_inverted(void *object) {
    if ((((S_800A0668_1 *)(((Rec_func_800A0668_arg0 *)object)->unk_98))->unk_01 & 8) != 0) {
        return ((Rec_func_800A0668_arg0 *)object)->unk_95 == 0;
    }
    return ((Rec_func_800A0668_arg0 *)object)->unk_95 != 0;
}

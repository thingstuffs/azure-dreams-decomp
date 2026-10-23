#include "common.h"

extern s32 scene_stored_first_value;
extern s32 D_80018E48;

/* Store the supplied values in D_80018E44 and D_80018E48. */
void set_global_entry_pair(s32 value_18e44, s32 value_18e48) {
    scene_stored_first_value = value_18e44;
    D_80018E48 = value_18e48;
}

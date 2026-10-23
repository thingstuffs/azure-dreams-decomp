#include "common.h"

s32 func_80017BA0(s32, s32);
extern s32 scene_stored_first_value;
extern s32 D_80018E48;

/* Pass the two global values to func_80017BA0. */
void forward_stored_pair(void) {
    func_80017BA0(scene_stored_first_value, D_80018E48);
}

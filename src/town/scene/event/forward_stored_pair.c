#include "common.h"

s32 func_80017BA0(s32, s32);
extern s32 D_80018E44;
extern s32 D_80018E48;

/* Pass the two global values to func_80017BA0. */
void forward_stored_pair(void) {
    func_80017BA0(D_80018E44, D_80018E48);
}

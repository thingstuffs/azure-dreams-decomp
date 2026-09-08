#include "common.h"

extern s32 D_800CF874;

/* reserve_tw_mon_load: store the town monster load reservation value. */
void func_8008B550(s32 reservation_value) {
    D_800CF874 = reservation_value;
}

#include "modules/dungeon_ovl_190d6a4.h"

s32 get_a_random_sign_either_n_1_n_1(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}

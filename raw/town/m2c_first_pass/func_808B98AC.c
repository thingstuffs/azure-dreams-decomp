#include "common.h"
#include "m2c_compat.h"

void func_A07008AC(void) {
    *(s32 *)0xA0700A60 = (*(s32 *)0xA0700A60 * 8) + *(s32 *)0xA0700B48;
}

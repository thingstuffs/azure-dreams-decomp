#include "common.h"

void func_800B13CC(void *arg0, s32 arg1) {
    u16 *field;

    for (;;) {
        field = (u16 *)((u8 *)arg0 + 4);
        *field = (u16)(*field | arg1);
        if (*(s8 *)arg0 < 0) {
            return;
        }
        arg0 = (u8 *)arg0 + 12;
    }
}

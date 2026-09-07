#include "common.h"

/* manual g1 strike 2: order the negative-direction compare like retail */
#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

void func_80056800(void *arg0) {
    s32 diff;
    s32 neg_limit;

    if (FIELD(arg0, s32, 8) != 0) {
        if (FIELD(arg0, s32, 0x34) != 0) {
            if ((FIELD(arg0, s16, 0x3A) + FIELD(arg0, s16, 0x38)) < FIELD(arg0, s16, 0x40)) {
                FIELD(arg0, s16, 0x3A) = (u16)FIELD(arg0, s16, 0x3A) + (u16)FIELD(arg0, s16, 0x38);
                return;
            }
            FIELD(arg0, s32, 0x34) = 0;
            FIELD(arg0, s16, 0x3A) = (u16)FIELD(arg0, s16, 0x40);
            return;
        }

        diff = FIELD(arg0, s16, 0x3A) - FIELD(arg0, s16, 0x38);
        neg_limit = -FIELD(arg0, s16, 0x40);
        if (neg_limit < diff) {
            FIELD(arg0, s16, 0x3A) = (u16)FIELD(arg0, s16, 0x3A) - (u16)FIELD(arg0, s16, 0x38);
            return;
        }
        FIELD(arg0, s32, 0x34) = 1;
        FIELD(arg0, s16, 0x3A) = -((s16)(u16)FIELD(arg0, s16, 0x40));
        return;
    }
    FIELD(arg0, s16, 0x3A) = 0;
}

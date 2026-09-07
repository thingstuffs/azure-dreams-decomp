#include "common.h"

s32 func_80094BC0(void);

s32 func_80094B58(s32 arg0) {
    if (arg0 & 0x1000) {
        register s32 temp_v0 ASM_REG("$2");
        register s32 temp_v1 ASM_REG("$3");

        temp_v0 = arg0 & 0x8000;
        ASM_KEEP(temp_v0);
        if (temp_v0 != 0) {
            return 0xA00;
        }
        temp_v1 = arg0 & 0x2000;
        ASM_KEEP(temp_v1);
        if (temp_v1 != 0) {
            return 0x600;
        }
        func_80094BC0();
        return 0x800;
    } else {
        register s32 temp_v0 ASM_REG("$2");

        temp_v0 = arg0 & 0x4000;
        if (temp_v0 != 0) {
            temp_v0 = arg0 & 0x8000;
            if (temp_v0 != 0) {
                func_80094BC0();
                return 0xE00;
            }
            temp_v0 = arg0 & 0x2000;
            ASM_KEEP(temp_v0);
            temp_v0 = temp_v0 != 0;
            ASM_KEEP(temp_v0);
            func_80094BC0();
            ASM_KEEP(temp_v0);
            return temp_v0 << 9;
        } else {
            temp_v0 = arg0 & 0x8000;
            if (temp_v0 != 0) {
                return 0xC00;
            }
            if (arg0 & 0x2000) {
                return 0x400;
            }
            return -1;
        }
    }
}

/* MECHANISM: Disjoint block-local $v0 masks encode the frameless destructive reuse,
   while a short $v1 mask preserves the first arm's pending return constant.
   Split mask/boolean operations expose retail's andi+sltu and three SHAPE-C tails. */

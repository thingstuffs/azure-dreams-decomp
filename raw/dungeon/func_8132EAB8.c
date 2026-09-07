#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s16 D_801760D8;
extern s32 D_800814A0;
extern void *D_80164808[];
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80165C3C(void) __attribute__((noreturn));
extern void func_80165CC8(void) __attribute__((noreturn));
extern void func_80165CF0(void) __attribute__((noreturn));

void func_80165AB8(u8 *arg0, u8 *arg1, u8 *arg2)
{
    static void *const keep_cases[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
    s32 old_height;
    u32 state;

    state = FIELD(arg0, u8, 0x17);
    if (state >= 5) {
        goto done;
    }
    goto *D_80164808[state];

case_0:
        FIELD(arg1, s32, 0x00) += FIELD(arg1, s32, 0x0C);
        FIELD(arg1, s32, 0x04) += FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 0x08) += FIELD(arg1, s32, 0x14);

        old_height = FIELD(arg1, s16, 0x0A);
        FIELD(arg1, s32, 0x14) += FIELD(arg0, s32, 0x60);
        if ((func_800BCB04(FIELD(arg1, u16, 0x02),
                           FIELD(arg1, u16, 0x06),
                           (s16)(FIELD(arg1, u16, 0x0A) - 4)) - 15) < old_height) {
            FIELD(arg0, s32, 0x54) = 0;
            FIELD(arg1, s16, 0x0A) =
                func_800BCB04(FIELD(arg1, u16, 0x02),
                              FIELD(arg1, u16, 0x06),
                              (s16)(FIELD(arg1, u16, 0x0A) - 4)) - 2;
            FIELD(arg1, s16, 0x08) = 0;
            FIELD(arg0, s16, 0x32) = 0;
            FIELD(arg0, u8, 0x17)++;
        }
        {
            register s32 condition ASM_REG("$2");
            register s32 next_counter ASM_REG("$3");

            condition = FIELD(arg0, u16, 0x32);
            next_counter = condition + 1;
            condition = (s16)condition < 60;
            ASM_KEEP(next_counter);
            ASM_TAILSLOT_PIN(condition);
            func_80165CC8();
        }

case_1: {
        register s32 tripled ASM_REG("$3");

        tripled = FIELD(arg2, u16, 0x1E) * 3;
        ASM_KEEP(tripled);
        FIELD(arg2, u16, 0x1E) = tripled;
        FIELD(arg2, u16, 0x1C) = tripled;
        func_80165C3C();
    }

case_2:
        if (D_801760D8 == 0) {
            goto done;
        }
        func_80165C3C();

case_3:
        if ((s16)FIELD(arg0, u16, 0x32)++ < 20) {
            goto done;
        }
        FIELD(arg2, u16, 0x10) = 0;
        FIELD(arg2, u16, 0x14) |= 0xC;

        FIELD(arg0, s16, 0x32) = 0;
        FIELD(arg0, u8, 0x17)++;
        func_80165CF0();

case_4:
        FIELD(arg2, s8, 0x0C) =
            ((10 - FIELD(arg0, s16, 0x32)) * 255) / 10;
        FIELD(arg2, s8, 0x0D) = FIELD(arg2, s8, 0x0E) =
            ((10 - FIELD(arg0, s16, 0x32)) * 32) / 10;
        if ((s16)FIELD(arg0, u16, 0x32)++ < 10) {
            goto done;
        }

finish:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

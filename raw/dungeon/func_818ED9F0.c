#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80024028[8];
extern s32 D_800814A0;
extern void func_80025328(void) __attribute__((noreturn));

void func_800251F0(void *arg0)
{
    static void *const jt_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_2,
        &&case_2, &&case_2, &&case_2, &&case_2
    };
    register u8 *page ASM_REG("$4");
    register u8 *arg1 ASM_REG("$5");
    register u16 old_counter ASM_REG("$2");
    s32 i;

    arg1 = arg0;
    ASM_KEEP(arg1);
    page = (u8 *)0x80020000;
    ASM_KEEP(page);
    old_counter = FIELD(arg1, u16, 0x02);
    FIELD(page, s16, 0x6428) = 1;
    FIELD(arg1, u16, 0x02) = old_counter - 1;
    FIELD(arg1, u16, 0x8C) += 200;
    FIELD(arg1, u16, 0x0A)++;
    if ((s16)FIELD(arg1, u16, 0x0A) < 2) {
        goto counter_done;
    }
    FIELD(arg1, u16, 0x0A) = 0;
    FIELD(arg1, u16, 0x0C)++;
counter_done:
    if (FIELD(arg1, s16, 0x0C) >= 33) {
        FIELD(arg1, s16, 0x0C) = 32;
    }

    i = 0;
    while (i < FIELD(arg1, s16, 0x0C)) {
        u8 *elem;

        elem = arg1 + i;
        elem[0x50] += 2;
        i++;
    }

    {
        s32 state;

        state = *(s16 *)(arg1 + 0x1E);
        if ((u32)state >= 8) {
            goto done;
        }
        (void)jt_keep;
        goto *D_80024028[(u32)state];
    }

case_0:
    FIELD(arg1, u16, 0x1E)++;
    FIELD(arg1, u8, 0x28) += 0x10;
    func_80025328();
    return;

case_1:
    FIELD(arg1, u16, 0x1E)++;
    FIELD(arg1, u8, 0x28) -= 0x30;
    FIELD(arg1, u8, 0x29) += 0x20;
    func_80025328();
    return;

case_2:
    FIELD(arg1, u8, 0x28) -= 0x30;
    FIELD(arg1, u8, 0x29) -= 0x20;
    FIELD(arg1, u16, 0x1E) = 0;

done:
    if (FIELD(arg1, s16, 0x02) <= 0) {
        FIELD(arg1, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

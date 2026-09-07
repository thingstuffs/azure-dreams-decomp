#include "common.h"

#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void func_80038F48(void *);
extern void func_80039148(void *);
extern void func_8003AB44(u8 *, s16, s16, u8, s32, s32, s32);
extern void func_80038128(void);

typedef void (*Callback)(void);

void func_80038CB8(void *arg0)
{
    s32 var_s1;
    s32 temp_v1_2;
    s32 temp_v0_3;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_v1;

    if (FIELD(arg0, u8, 0x2E) != 0) {
        var_a0 = FIELD(arg0, u8 *, 0x1C);
        if (*(s8 *)var_a0 <= 0) {
            do {
            if ((*var_a0 == 0) ||
                (FIELD(arg0, s16, 0x20) < (s32)FIELD(arg0, u8, 0x24))) {
                func_80038F48(arg0);
                if (*(s8 *)FIELD(arg0, u8 *, 0x1C) <= 0) {
                    func_8003AB44(
                        FIELD(arg0, u8 *, 0x1C),
                        FIELD(arg0, s16, 0x20),
                        FIELD(arg0, s16, 0x22),
                        FIELD(arg0, u8, 0x2A),
                        (s32)FIELD(arg0, s16, 0x00),
                        (s32)(s16)(FIELD(arg0, s16, 0x02) + 2),
                        1);
                    temp_v1 = FIELD(arg0, u8 *, 0x1C);
                    FIELD(arg0, s16, 0x20) =
                        (s16)((u16)FIELD(arg0, s16, 0x20) + 1);
                    temp_v0 = temp_v1 + 2;
                    FIELD(arg0, u8 *, 0x1C) = temp_v0;
                    var_a0 = temp_v0;
                    if (*(s8 *)(temp_v1 + 2) <= 0) {
                        continue;
                    }
                }
            } else {
                goto block_15;
            }
            break;
            } while (1);
        }
    } else {
        if (FIELD(arg0, s8, 0x28) >= 0) {
            goto block_16;
        }
        var_v1 = FIELD(arg0, u8 *, 0x1C);
        if (*(s8 *)var_v1 > 0) {
            goto block_14;
        }
        var_s1 = 0;
loop_9:
        if ((*var_v1 != 0) &&
            (FIELD(arg0, s16, 0x20) >= (s32)FIELD(arg0, u8, 0x24))) {
            goto block_15;
        }
        func_80038F48(arg0);
        if (*(s8 *)FIELD(arg0, u8 *, 0x1C) > 0) {
            goto block_end;
        }
        var_s1 -= 1;
        func_8003AB44(
            FIELD(arg0, u8 *, 0x1C),
            FIELD(arg0, s16, 0x20),
            FIELD(arg0, s16, 0x22),
            FIELD(arg0, u8, 0x2A),
            (s32)FIELD(arg0, s16, 0x00),
            (s32)(s16)(FIELD(arg0, s16, 0x02) + 2),
            1);
        temp_v0_3 = FIELD(arg0, u16, 0x20);
        temp_a0 = FIELD(arg0, u8 *, 0x1C);
        temp_v0_3 += 1;
        FIELD(arg0, s16, 0x20) = (s16)temp_v0_3;
        temp_v0_3 = FIELD(arg0, s8, 0x28);
        var_v1 = temp_a0 + 2;
        FIELD(arg0, u8 *, 0x1C) = var_v1;
        if (var_s1 < temp_v0_3) {
            goto block_14;
        }
        if (*(s8 *)(temp_a0 + 2) <= 0) {
            goto loop_9;
        }
block_14:
        FIELD(arg0, s8, 0x28) =
            *(u8 *)(FIELD(arg0, u8 *, 0x80) + 3);
        goto block_end;
block_15:
        func_80039148(arg0);
        goto block_end;
block_16:
        func_80038F48(arg0);
        if (*(s8 *)FIELD(arg0, u8 *, 0x1C) <= 0) {
            func_8003AB44(
                FIELD(arg0, u8 *, 0x1C),
                FIELD(arg0, s16, 0x20),
                FIELD(arg0, s16, 0x22),
                FIELD(arg0, u8, 0x2A),
                (s32)FIELD(arg0, s16, 0x00),
                (s32)(s16)(FIELD(arg0, s16, 0x02) + 2),
                1);
            FIELD(arg0, s16, 0x20) =
                (s16)((u16)FIELD(arg0, s16, 0x20) + 1);
            temp_v1_2 = FIELD(arg0, s8, 0x28);
            FIELD(arg0, u8 *, 0x1C) = FIELD(arg0, u8 *, 0x1C) + 2;
            if (temp_v1_2 != 0) {
                FIELD(arg0, s16, 0x18) = (s16)temp_v1_2;
                FIELD(arg0, Callback, 0x10) = func_80038128;
            }
        }
block_end:
        ;
    }
}

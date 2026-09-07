#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern void *D_80170808[];
extern s32 D_800814A0[3];

void func_80170A84(void *arg0, void *arg1, void *arg2)
{
    u8 *base;
    u32 *source;
    void *volatile *table;
    u16 copied;
    u16 angle;
    u16 state;
    u16 twenty;
    s32 dispatch;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2,
        &&case_3, &&case_4, &&case_5,
        &&done
    };

    base = FIELD(arg0, void *, 0x40);
    source = FIELD(arg0, u32 *, 0x44);
    copied = FIELD(FIELD(base, void *, -0x14), u16, 6);

    angle = FIELD(arg2, u16, 0x1A) + 400;
    FIELD(arg2, u16, 0x1A) = angle;
    FIELD(arg2, u16, 6) = copied;
    if (angle >= 4097) {
        FIELD(arg2, u16, 0x1A) = angle - 4096;
    }

    dispatch = FIELD(arg0, s16, 0x2C);
    if ((u32)dispatch >= 6) {
        goto done;
    }
    table = D_80170808;
    (void)keepalive;
    goto *table[dispatch];

case_0:
    {
        u16 count = FIELD(arg0, u16, 0x36);
        s16 limit = FIELD(arg0, s16, 0x38);
        s32 value;

        count++;
        value = ((count << 16) >> 9) / limit;
        FIELD(arg0, u16, 0x36) = count;
        FIELD(arg2, u8, 0x0C) = value;
        FIELD(arg2, u8, 0x0D) = value;
        FIELD(arg2, u8, 0x0E) = value;
    }
    if (FIELD(arg0, s16, 0x36) < 5) {
        goto done;
    }
    state = FIELD(arg0, u16, 0x2C);
    state++;
    goto skip_counter;

case_5:
    if (FIELD(base, u8, 0x9B) >= 4) {
        FIELD(arg0, u16, 0x36) = 0;
        FIELD(arg0, s16, 0x38) = 20;
        FIELD(arg0, u16, 0x2C)++;
    }
    if (FIELD(base, u8, 0xB3) != 3 || FIELD(base, u8, 0xB1) != 2) {
        goto done;
    }
    FIELD(arg0, u16, 0x2C) = 4;
    FIELD(arg0, s16, 0x38) = 20;
    FIELD(arg0, u16, 0x36) = 20;
    goto done;

case_1:
    {
        u16 count = FIELD(arg0, u16, 0x36);
        s16 limit = FIELD(arg0, s16, 0x38);
        s32 value;

        count++;
        value = ((count << 16) >> 9) / limit;
        FIELD(arg0, u16, 0x36) = count;
        FIELD(arg2, u8, 0x0C) = value;
        FIELD(arg2, u8, 0x0D) = value;
        FIELD(arg2, u8, 0x0E) = value;
    }
    if (FIELD(arg0, s16, 0x36) < FIELD(arg0, s16, 0x38)) {
        goto done;
    }
    state = FIELD(arg0, u16, 0x2C);
    twenty = 20;
    FIELD(arg0, s16, 0x38) = twenty;
    goto common_counter;

case_2:
    {
        u16 count = FIELD(arg0, u16, 0x36);
        s16 limit = FIELD(arg0, s16, 0x38);
        s32 value;

        count--;
        value = ((count << 16) >> 9) / limit;
        FIELD(arg0, u16, 0x36) = count;
        FIELD(arg2, u8, 0x0C) = value;
        FIELD(arg2, u8, 0x0D) = value;
        FIELD(arg2, u8, 0x0E) = value;
    }
    if (FIELD(arg0, s16, 0x36) > 0) {
        goto done;
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto done;

case_3:
    {
        u16 count = FIELD(arg0, u16, 0x36);
        s16 limit = FIELD(arg0, s16, 0x38);
        s32 value;

        count--;
        value = ((count << 16) >> 9) / limit;
        FIELD(arg0, u16, 0x36) = count;
        FIELD(arg2, u8, 0x0C) = value;
        FIELD(arg2, u8, 0x0D) = value;
        FIELD(arg2, u8, 0x0E) = value;
    }
    if (FIELD(arg0, s16, 0x36) > 0) {
        goto done;
    }
    state = FIELD(arg0, u16, 0x2C);
    twenty = 20;

common_counter:
    FIELD(arg0, u16, 0x36) = twenty;
    state++;

skip_counter:
    FIELD(arg0, u16, 0x2C) = state;
    goto done;

case_4:
    {
        u16 count = FIELD(arg0, u16, 0x36);

        FIELD(arg0, u16, 0x36) = count - 1;
        if ((count << 16) > 0) {
            goto done;
        }
    }
    FIELD(arg0, u16, 0x2C) = 2;
    FIELD(arg0, u16, 0x36) = 0;
    FIELD(arg0, s16, 0x38) = 20;

done:
    ((u32 *)arg1)[0] = source[0];
    ((u32 *)arg1)[1] = source[1];
    ((u32 *)arg1)[2] = source[2];
}

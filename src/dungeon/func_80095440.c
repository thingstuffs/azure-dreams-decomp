#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
} Func95440Input;

typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Func95440Actor;

typedef struct {
    u8 pad0[0x14];
    u32 mask14;
    u8 pad18[4];
    u32 flags1c;
    u8 pad20[0x4c];
    s16 value6c;
    s16 value6e;
} Func95440Object;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A8[4];
extern s16 D_80083460[3];

extern s32 func_8009A540(u32, u32, u32, s32);
extern s32 func_8009A350(u8, u8, u32, u16 *);
extern s32 func_800BCB04(s32, s32, s32);
extern Func95440Object *func_8009B25C(s32, s32, s32, s32);

s32 func_8009ABA0(u32 arg0, Func95440Input *arg1, Func95440Actor *arg2, u32 arg3, s32 arg4) {
    u16 sp10;
    s32 delta;
    s16 initial_delta;
    s32 temp_s5;
    u32 index;
    s32 y;
    s32 x;
    u16 xarg;
    u16 yarg;
    s32 value;
    s32 result;
    Func95440Object *object;

    index = (arg0 >> 9) & 7;
    x = arg1->x;
    y = arg1->y;
    initial_delta = (s16)(arg3 - arg4);
    temp_s5 = arg3;
    if ((func_8009A540(index, x >> 6, y >> 6, initial_delta) << 16) == 0) {
        goto return_minus2;
    }
    delta = initial_delta;

    x += D_8006CCD8[index] << 6;
    y += D_8006CCE8[index] << 6;
    if ((func_8009A350(arg2->x, arg2->y, index, &sp10) << 16) == 0) {
        return 0;
    }
    if (sp10 & 0x8000) {
        goto return_minus2;
    }
    if (sp10 & 0x400) {
        return 0;
    }

    if (sp10 & 0x3300) {
        xarg = x;
        yarg = y;
        delta = func_800BCB04(xarg, yarg, delta);
        x = xarg;
        y = yarg;
        object = func_8009B25C(*D_800814A8, x >> 6, y >> 6, (s16)delta);
        if (object != 0) {
            if (!(object->flags1c & 0x2000)) {
                goto object_failure;
            }
            if (object->flags1c & 0x628) {
                goto object_failure;
            }
            if (object->mask14 & 0x40000000) {
                goto object_failure;
            }
            if (object->value6c + ((object->value6e * D_80083460[0]) >> 8) < 0x100) {
                goto object_failure;
            }
        }
        goto compare;

object_failure:
        return -1;
    } else {
        delta = func_800BCB04(x & 0xffff, y & 0xffff, delta);
    }

compare:
    value = (delta << 16) >> 16;
    if (value >= 0x200) {
        goto return_minus2;
    }
    result = 1;
    if (value == (s16)temp_s5) {
        return result;
    }
    if ((s16)temp_s5 < value) {
        if ((value - (s16)temp_s5) >= 0x41) {
            return 4;
        }
        return 2;
    }
    return 3;

return_minus2:
    return -2;
}

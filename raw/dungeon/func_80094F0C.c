#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 flag;
} FuncArg1;

typedef struct {
    u8 pad1c[0x1c];
    u32 flags;
    u8 pad20[0x68];
    u16 height;
} FuncArg2;

typedef struct {
    u8 pad0c[0x0c];
    u16 flags;
    u8 tail[6];
} FuncMonster;

extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_8009A540(s32, s32, s32, s16);
extern void func_8009A890(void);
extern s32 func_8009B25C(FuncArg2 *, s32, s32, s16);
extern s16 func_8009FB34(u16, u16);
extern s32 func_800BCB04(s32, s32, s16);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];
extern FuncMonster D_800E2970[];

s32 func_8009A66C(u32 arg0, FuncArg1 *arg1, FuncArg2 *arg2, s16 arg3) {
    register s32 temp_s2 ASM_REG("$18");
    register s32 call_index ASM_REG("$6");
    register s16 *x_table ASM_REG("$3");
    u16 flags;
    u16 *flags_out;
    s32 index;
    u32 x_shifted;
    u32 y_shifted;
    s32 x_base;
    s32 y_base;
    s32 x_pos;
    s32 y_pos;
    register u16 height ASM_REG("$21");
    s16 monster;
    register s32 result ASM_REG("$4");
    register s32 signed_height ASM_REG("$3");
    register s32 ret ASM_REG("$2");

    index = (arg0 >> 9) & 7;
    height = arg2->height;
    x_shifted = arg1->x << 6;
    y_shifted = arg1->y << 6;
    x_base = x_shifted + 0x20;
    y_base = y_shifted + 0x20;

    if ((func_8009A540(index, x_shifted >> 6, y_shifted >> 6,
                       (s16)(height - arg3)) << 16) != 0) {

    call_index = index;
    flags_out = &flags;
    ASM_KEEP(flags_out);
    x_table = D_800DCEAC;
    temp_s2 = call_index << 1;
    x_pos = *(u16 *)((u8 *)x_table + temp_s2) + x_base;
    y_pos = *(u16 *)((u8 *)D_800DCEBC + temp_s2) + y_base;
    if ((func_8009A350(arg1->x, arg1->y, call_index, flags_out) << 16) == 0) {
        return 0;
    }

    if (arg1->flag < 0) {
        monster = func_8009FB34(
            (u16)(arg1->x +
                  *(u16 *)((u8 *)D_8006CCD8 + temp_s2)),
            (u16)(arg1->y +
                  *(u16 *)((u8 *)D_8006CCE8 + temp_s2)));
        if (monster >= 0 &&
            (D_800E2970[monster].flags & 2) &&
            !(arg2->flags & 0x2000)) {
            return 0;
        }
    }
    ASM_KEEP(temp_s2);

    if (flags & 0x8402) {
        return 0;
    }

    if (flags & 0x3300) {
        register s32 y_norm ASM_REG("$16");
        register s32 call_x ASM_REG("$4");

        if (!(flags & 0x40)) {
            func_8009A890();
            return -1;
        }
        x_pos &= 0xFFFF;
        call_x = x_pos;
        y_norm = y_pos & 0xFFFF;
        temp_s2 = func_800BCB04(call_x, y_norm, (s16)(height - arg3));
        if (func_8009B25C(arg2, (u32)x_pos >> 6, (u32)y_norm >> 6,
                          (s16)temp_s2)) {
            func_8009A890();
            return -1;
        }
    } else {
        temp_s2 = func_800BCB04(x_pos & 0xFFFF, y_pos & 0xFFFF,
                               (s16)(height - arg3));
    }

    ret = (u32)temp_s2 << 16;
    result = ret >> 16;
    if (result >= 0x200) {
        return 0;
    }
    ret = (u32)height << 16;
    signed_height = ret >> 16;
    ret = 1;
    if (result == signed_height) {
        goto done;
    }
    ret = 2;
    if (signed_height < result) {
        goto done;
    }
    func_8009A890();
    return 3;
done:
        return ret;
    }
    return 0;
}

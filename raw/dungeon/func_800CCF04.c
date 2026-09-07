#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef void (*DungeonCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern DungeonCallback D_800E2228[];

extern s16 func_800BCB04(u16, u16, s16);
extern void func_800D276C(s32, s32);
extern void func_800D27F8();
extern void func_800D2810();
extern void func_800D2890();
extern void func_800D28C4();

void func_800D2664(void *arg0, void *arg1, void *arg2) {
    register void *obj ASM_REG("$18") = arg0;
    register void *pos ASM_REG("$17") = arg1;
    register void *ent ASM_REG("$19") = arg2;
    register void *work ASM_REG("$16") = obj;
    DungeonCallback callback;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 fall_accum;
    s32 fall_delta;
    u16 fall_flags;
    s16 result;
    s16 height;
    s32 uheight;

    if (D_80083462 & 0x2000) {
        FIELD(work, u8, 0x71) &= 0x7F;
        func_800D28C4();
        return;
    }

    ASM_KEEP(obj);
    ASM_KEEP(pos);
    ASM_KEEP(ent);
    ASM_KEEP(work);

    callback = FIELD(work, DungeonCallback, 0x8C);
    if (callback != 0) {
        callback(work, pos, ent, work);
    }
    D_800E2228[FIELD(work, u8, 0x9A)](work, pos, ent, work);

    x = FIELD(pos, s32, 0);
    dx = FIELD(pos, s32, 0xC);
    y = FIELD(pos, s32, 4);
    dy = FIELD(pos, s32, 0x10);
    FIELD(pos, s32, 0) = x + dx;
    FIELD(pos, s32, 4) = y + dy;

    if (FIELD(work, u16, 0x98) & 8) {
        FIELD(work, u8, 0x9D) = 0;
        func_800D276C(dx, dy);
        return;
    }

    FIELD(pos, s32, 0x14) += FIELD(work, s8, 0x9D) * 0x14000;
    FIELD(work, u8, 0x9D)++;
    fall_accum = FIELD(obj, s32, 0x90);
    fall_delta = FIELD(pos, s32, 0x14);
    fall_flags = FIELD(obj, u16, 0x98);
    FIELD(obj, s32, 0x90) = fall_accum + fall_delta;

    if (fall_flags & 4) {
        goto clear_fall_flag;
    }

    result = func_800BCB04(
        FIELD(pos, u16, 2),
        FIELD(pos, u16, 6),
        (s16)(FIELD(work, u16, 0x88) - 0x20));
    if (result >= 0x200) {
        goto clear_fall_flag;
    }

    uheight = FIELD(work, u16, 0x88);
    height = FIELD(work, s16, 0x88);
    if (FIELD(obj, s16, 0x92) + height < result) {
        register u16 tail_flags ASM_REG("$2") = FIELD(obj, u16, 0x98);
        ASM_KEEP(tail_flags);
        func_800D2810();
        return;
    }
    if (result >= height) {
        FIELD(obj, s32, 0x90) = 0;
        func_800D27F8();
        return;
    }

    FIELD(obj, s16, 0x92) = result - uheight;
    FIELD(pos, s32, 0x14) = 0;
    FIELD(work, u32, 0x1C) |= 0x08000000;
    FIELD(obj, u8, 0x9D) = 0;

    if (FIELD(work, u32, 0x1C) & 0x40000000) {
        s32 tile_x;
        s32 tile_y;
        FIELD(work, u32, 0x1C) &= ~0x40000000;
        tile_x = (FIELD(ent, u8, 0x24) << 6) | 0x20;
        tile_y = (FIELD(ent, u8, 0x25) << 6) | 0x20;
        result = func_800BCB04(
            tile_x, tile_y, (s16)(FIELD(work, u16, 0x88) - 0x20));
        FIELD(obj, s16, 0x92) += FIELD(work, u16, 0x88) - result;
        FIELD(work, s16, 0x88) = result;
        func_800D2890();
        return;
    }
    goto finish;

clear_fall_flag:
    FIELD(work, u32, 0x1C) &= ~0x08000000;

finish:
    FIELD(pos, u16, 0xA) = FIELD(work, u16, 0x88) + FIELD(obj, u16, 0x92);
    FIELD(ent, u16, 0x14) |= 0x40;
    FIELD(work, u32, 0x1C) |= 0x200;
}

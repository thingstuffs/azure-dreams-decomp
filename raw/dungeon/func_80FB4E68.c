#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
} SpawnOffset;

typedef struct {
    s16 x;
    s16 y;
} Position2;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800AD594(void *, s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_800BCB04(u16, u16, s16);
extern void func_800C8CD8(void *, s32, s32);
extern void func_80174AD8(void) __attribute__((noreturn));
extern void func_80174AF0() __attribute__((noreturn));

extern u8 D_80045340[];
extern s16 D_80083228[];
extern u8 D_8008346C[];
extern u8 D_80083498[];
extern u8 D_800DEC50[];
extern u32 D_800E3DE8[];
extern u8 D_8017086C[];
extern u8 D_80170874[];
extern u8 D_80170F6C[];
extern u8 D_80174B20[];
extern u8 D_80174B98[];
extern u8 D_80175174[];
extern u8 D_80175258[];

void func_80174668(void *arg0, void *arg1, void *arg2, void *arg3)
{
    SpawnOffset spawn = *(SpawnOffset *)D_8017086C;
    Position2 pos;
    s32 state;
    u8 *object;
    register u8 *state_object ASM_REG("$3");
    register u8 *inner ASM_REG("$2");
    register u8 *alloc ASM_REG("$17");
    register u8 *table ASM_REG("$5");
    u8 *prim;
    u8 *tile;
    void *template;
    s32 saved;
    s32 saved_first;
    s32 random;
    s32 value;
    register s32 state_value ASM_REG("$16");

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    func_80174AF0();

state_0:
    object = func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
        FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x2A), 0x10);
    FIELD(arg3, void *, 0x60) = object;
    table = D_80175258;
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 2;
        func_80174AF0();
    }

    FIELD(arg0, u8, 0x9B) = 1;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg3, void *, 0x60) == 0) {
        goto done;
    }

    value = func_80099734(arg3, saved = func_800990FC());
    saved_first = saved;
    saved = value;
    value = func_80099194(D_80170874, saved);
    func_80099290(value);
    func_800A5720(saved_first);
    func_800A56E0(0x60A);

    tile = FIELD(FIELD(arg3, u8 *, 0x60), u8 *, -0x14);
    FIELD(arg3, u8, 0x72) = FIELD(tile, u8, 0x24);
    FIELD(arg3, u8, 0x73) = FIELD(tile, u8, 0x25);
    pos.x = spawn.x + (spawn.dx >> 1);
    pos.y = spawn.y + (spawn.dy >> 1);
    func_800B8FC8(arg0, &spawn, &pos, 1, 0);

    alloc = func_8003FD64(0x201, D_80083498);
    if (alloc == 0) {
        goto done;
    }
    func_8004491C(alloc, D_80174B98);
    template = D_80174B20;
    ASM_KEEP(template);
    FIELD(alloc, void *, 0x10) = template;
    prim = alloc + 0x20;
    FIELD(prim, s16, 0xA2) = (FIELD(arg2, u8, 0x24) << 6) + 0x20;
    FIELD(prim, s16, 0xA4) = (FIELD(arg2, u8, 0x25) << 6) + 0x20;
    {
        register u32 color ASM_REG("$4");
        register s32 countdown ASM_REG("$2");
        register u16 arg1_value ASM_REG("$3");
        color = 0x00808080;
        ASM_KEEP(color);
        arg1_value = FIELD(arg1, u16, 0x0A);
        countdown = 0x3C;
        FIELD(prim, u32, 0xAC) = color;
        FIELD(prim, s16, 0x96) = countdown;
        FIELD(prim, u16, 0xA6) = arg1_value;
        FIELD(arg0, s16, 0x96) = countdown;
        func_80174AF0(color);
    }

state_1:
    state_object = FIELD(arg3, void *, 0x60);
    if ((state_object != 0) && (FIELD(arg0, s16, 0x96) < 0x34)) {
        FIELD(state_object, u16, 0x2A) =
            (FIELD(state_object, u16, 0x2A) + 0x200) & 0x3FFF;
        alloc = func_8003FD64(0x312, D_80083498);
        if (alloc == 0) {
            goto state_1_continue;
        }
            func_8004491C(alloc, D_80045340);
            prim = alloc + 0x20;
            tile = FIELD(alloc, u8 *, 0x0C);
            FIELD(alloc, void *, 0x10) = D_80175174;

            random = rand();
            {
                s32 coord = FIELD(arg3, s8, 0x72);
                FIELD(FIELD(alloc, u8 *, 8), s16, 2) =
                    (coord << 6) + (random % 64);
            }
            random = rand();
            {
                s32 coord = FIELD(arg3, s8, 0x73);
                FIELD(FIELD(alloc, u8 *, 8), s16, 6) =
                    (coord << 6) + (random % 64);
            }
            inner = FIELD(alloc, u8 *, 8);
            state_value = func_800BCB04(FIELD(inner, u16, 2),
                FIELD(inner, u16, 6), -0x400);
            {
                s32 final_random = rand();
                state_value -= final_random % 95;
                state_value -= 0x20;
            }
            FIELD(FIELD(alloc, u8 *, 8), s16, 0x0A) = state_value;

            FIELD(tile, s16, 0x1E) = 0xC04;
            FIELD(tile, s16, 0x1C) = 0xC04;
            FIELD(tile, s16, 0x10) = 0x60;
            FIELD(tile, void *, 0) = D_800DEC50;
            FIELD(tile, u16, 0x14) |= 0x0C;
            {
                u32 tile_word = FIELD(D_800DEC50, u32, 4);
                FIELD(tile, u8, 4) = 0;
                FIELD(tile, u8, 5) = 0;
                FIELD(tile, u32, 0x0C) = 0x00208020;
                FIELD(tile, u32, 8) = tile_word;
            }
            FIELD(prim, u8, 0x9A) = 0;
    }
state_1_continue:
    value = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = value;
    if ((value << 16) > 0) {
        goto done;
    }
    FIELD(arg0, u8, 0x9B)++;
    func_80174AF0();

state_2:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    func_800AD594(arg3, 0x800);
    {
        register void *call_arg ASM_REG("$4");
        call_arg = arg3;
        ASM_KEEP(call_arg);
        FIELD(arg0, void *, 0x8C) = D_80170F6C;
        FIELD(D_8008346C, s32, 0) = 0;
        func_800A4ACC(call_arg);
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_80174AD8();
    }
    D_800E3DE8[0] = (u32)((u8 *)arg3 - 0x20);

    object = FIELD(arg3, u8 *, 0x60);
    if (object != 0) {
        func_800C8CD8(object, 0x28, 0x10);
    }

done:
    return;
}

#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    s16 first;
    u16 second;
} LocalEntry;

typedef struct {
    LocalEntry entries[8];
} LocalTable;

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s16 rand();

extern LocalTable D_80024034;
extern u8 D_800246F0[];
extern s32 D_80045340;
extern u8 D_800DEC00[];

void func_819A1450(void *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4,
                   s16 arg5)
{
    LocalTable table;
    void *node;
    void *part;
    void *coords;
    u8 *setup;
    s16 index;

    table = D_80024034;
    node = func_8003FC64(0x212);
    if (node != 0) {
        setup = (u8 *)node + 0x20;
        FIELD(setup, s16, 0x3A) = 5;
        FIELD(setup, s16, 0x3C) = 5;
        FIELD(node, void *, 0x10) = D_800246F0;
        func_8004491C(node, &D_80045340);

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;
        FIELD(part, s16, 0x1A) = (rand() & 7) << 9;
        FIELD(part, s16, 6) = 0;

        coords = FIELD(node, void *, 8);
        FIELD(coords, s16, 2) = arg3;
        FIELD(coords, s16, 6) = arg4;
        FIELD(coords, s16, 0xA) = arg5;
        FIELD(coords, s16, 2) += FIELD(arg0, u16, 0x84);
        FIELD(coords, s16, 6) += FIELD(arg0, u16, 0x86);
        FIELD(coords, s16, 0xA) += FIELD(arg0, u16, 0x88);

        index = FIELD(arg0, s16, 0x36);
        FIELD(coords, s32, 0xC) =
            (s32)table.entries[index].first << 20;
        index = FIELD(arg0, s16, 0x36);
        FIELD(coords, s32, 0x10) =
            (s32)table.entries[index].second << 20;

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x800;
        FIELD(part, s16, 0x1C) = 0x800;
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
        func_8003DB94(part, D_800DEC00, 0);
    }
}

/* MECHANISM: Preserved the seed's 0x50 frame, eight-register save set, and 32-byte
   stack-local aggregate copy. Typing it as LocalEntry entries[8] made both
   index expressions emit addu $v0,$s6,$v0, closing the two substitutions. */

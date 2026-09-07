#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 rand(void);

extern s32 D_80045340;
extern u8 D_800DEC70[];
extern s32 D_80174300;
extern Pair16 D_8017610C[];

void func_801744DC(void *arg0, void *arg1)
{
    void *node;
    void *work;
    void *part;
    void *coords;
    s32 bias;

    node = func_8003FC64(0x212);
    if (node != 0) {
        work = (u8 *)node + 0x20;
        FIELD(work, s16, 0x1E) = 0xF;
        FIELD(node, void *, 0x10) = &D_80174300;
        func_8004491C(node, &D_80045340);

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;
        FIELD(part, s16, 0x1A) = (rand() & 7) << 9;
        FIELD(part, s16, 6) = 0;

        coords = FIELD(node, void *, 8);
        FIELD(coords, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(coords, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(coords, u16, 0xA) = FIELD(arg1, u16, 0xA);
        FIELD(coords, u16, 2) = ({ FIELD(coords, u16, 2) - 0x20; }) + (rand() & 0x3F);
        FIELD(coords, u16, 6) = ({ FIELD(coords, u16, 6) - 0x20; }) + (rand() & 0x3F);
        FIELD(coords, u16, 0xA) = ({ FIELD(coords, u16, 0xA) - 0x40; }) + (rand() & 0x3F);

        FIELD(work, s32, 0x58) = 0xFFFA0000;
        FIELD(work, s32, 0x64) = 0x20000;
        FIELD(work, s32, 0x50) = D_8017610C[FIELD(arg0, s16, 0x1C)].x << 18;
        FIELD(work, s32, 0x54) = D_8017610C[FIELD(arg0, s16, 0x1C)].y << 18;

        bias = 0xFFF80000;
        FIELD(work, s32, 0x50) = (FIELD(work, s32, 0x50) + bias) + ((rand() & 0x3FFF) << 6);
        FIELD(work, s32, 0x54) = (FIELD(work, s32, 0x54) + bias) + ((rand() & 0x3FFF) << 6);
        FIELD(work, s32, 0x58) = (FIELD(work, s32, 0x58) + bias) + ((rand() & 0x3FFF) << 6);

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
        FIELD(part, u16, 0x14) |= 0x100;
        FIELD(part, s16, 0x12) = 0x7DCE;
        func_8003DB94(part, D_800DEC70, 0);
    }
}

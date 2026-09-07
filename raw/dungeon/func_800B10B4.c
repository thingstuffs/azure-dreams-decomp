#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);

extern s32 D_80045340;
extern s32 D_800B63A8;
extern s32 D_800DEC00;

void func_800B6814(void *arg0)
{
    s32 count;
    s32 step;
    s32 angle;
    s32 i;
    s32 value;
    void *part;
    void *node;
    void *image;
    void *sub;

    count = (rand() & 0xF) | 8;
    step = 0x1000 / count;
    i = 0;
    angle = rand();
    if ((u16)count != 0) {
        do {
            node = func_8003FC64(0x212);
            
            if (node != NULL) {
                part = FIELD(node, void *, 8);
                image = FIELD(node, void *, 0xC);
                FIELD(node, void *, 0x10) = &D_800B63A8;
                func_8004491C(node, &D_80045340);
                FIELD(part, s16, 2) =
                    FIELD(arg0, u16, 2) + (func_80064584(angle) >> 11);
                FIELD(part, s16, 6) =
                    FIELD(arg0, u16, 6) + (func_800644B8(angle) >> 11);
                FIELD(part, u16, 0xA) = FIELD(arg0, u16, 0xA);
                FIELD(part, s32, 0xC) = func_80064584(angle) << 6;
                FIELD(part, s32, 0x10) = func_800644B8(angle) << 6;
                FIELD(part, s32, 0x14) = 0xFFFD0000;
                FIELD(node, s32, 0x20) = -FIELD(part, s32, 0xC) >> 6;
                value = FIELD(part, s32, 0x10);
                sub = (u8 *)node + 0x20;
                FIELD(sub, s32, 8) = 0x2000;
                FIELD(sub, s32, 4) = -value >> 6;
                func_8003DB94(image, &D_800DEC00, 0);
                FIELD(image, s32, 0xC) = 0x808080;
                FIELD(image, s16, 0x1E) = 0x400;
                FIELD(image, s16, 0x1C) = 0x400;
                FIELD(image, s16, 0x10) = 0x60;
                FIELD(image, s16, 0x12) = 0x7E80;
                FIELD(image, u16, 0x14) |= 0x10C;
                FIELD(sub, s16, 0xE) = (rand() & 3) | 0x10;
                FIELD(sub, s16, 0x16) = 0x10;
                FIELD(sub, s16, 0x14) = 0x10;
                FIELD(sub, s16, 0x18) = 8;
            }
            i++;
            angle += step;
        } while (i < count);
    }
}

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *data);
extern void func_80047784(void *object, s32 arg1, s32 arg2);
extern s32 rand(void);
extern u8 D_80045340[];
extern u8 D_801763D0[];

void func_80E3CC80(void *arg0, void *arg1) {
    s32 count;
    s32 image;
    u16 flags;
    u16 y;
    void *object;
    void *a;
    void *b;

    count = 0x10;
    do {
        object = func_8003FC64(0x300);
        if (object != NULL) {
            FIELD(object, void *, 0x10) = D_801763D0;
            func_8004491C(object, D_80045340);
            a = FIELD(object, void *, 0xC);
            FIELD(a, s16, 0x1E) = 0x800;
            FIELD(a, s16, 0x1C) = 0x800;
            FIELD(a, s32, 0xC) = 0x808080;
            FIELD(a, s16, 0x10) = 0x20;
            image = FIELD(arg1, s32, 0x28);
            FIELD(a, s32, 0x28) = image;
            flags = FIELD(a, u16, 0x14);
            y = FIELD(arg1, u16, 0x12);
            FIELD(a, u16, 0x14) = flags | 0xC;
            FIELD(a, s16, 0x12) = y - 0x80;
            func_80047784(a, 0x41, 0);
            b = FIELD(object, void *, 8);
            FIELD(b, u16, 2) = FIELD(arg0, u16, 2);
            FIELD(b, u16, 6) = FIELD(arg0, u16, 6);
            FIELD(b, s16, 0xA) = FIELD(arg0, u16, 0xA) - (rand() & 0x1F);
            FIELD(b, s16, 0x16) = ((0 - (rand() & 0xF)) - 8) * 2;
            FIELD(b, s32, 0xC) = ((rand() & 3) - 2) << 0x10;
            FIELD(b, s32, 0x10) = ((rand() & 3) - 2) << 0x10;
            FIELD(object, s16, 0x40) = 0x10;
        }
        count -= 1;
    } while (count > 0);
}

/* MECHANISM: Named word and halfword read locals extend the arg1 value live ranges,
   reproducing retail's load-before-store emission order in the setup block.
   Natural locals retain the 0x30 frame and s0-s5 roles without register pins. */

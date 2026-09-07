#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80E3CC80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x2C];
    s16 unk_40;
} S_80E3CC80_0;   /* object in func_80E3CC80 */

typedef struct S_80E3CC80_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80E3CC80_1;   /* a in func_80E3CC80 */

typedef struct S_80E3CC80_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80E3CC80_2;   /* arg1 in func_80E3CC80 */

typedef struct S_80E3CC80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80E3CC80_3;   /* b in func_80E3CC80 */

typedef struct S_80E3CC80_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80E3CC80_4;   /* arg0 in func_80E3CC80 */



extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *data);
extern void func_80047784(void *object, s32 arg1, s32 arg2);
extern s32 rand(void);
extern u8 D_80045340[];
extern u8 D_801763D0[];

void func_80E3CC80(S_80E3CC80_4 *arg0, S_80E3CC80_2 *arg1) {
    s32 count;
    s32 image;
    u16 flags;
    u16 y;
    S_80E3CC80_0 *object;
    S_80E3CC80_1 *a;
    S_80E3CC80_3 *b;

    count = 0x10;
    do {
        object = func_8003FC64(0x300);
        if (object != NULL) {
            object->unk_10 = D_801763D0;
            func_8004491C(object, D_80045340);
            a = object->unk_0C;
            a->unk_1E = 0x800;
            a->unk_1C = 0x800;
            a->unk_0C = 0x808080;
            a->unk_10 = 0x20;
            image = arg1->unk_28;
            a->unk_28 = image;
            flags = a->unk_14;
            y = arg1->unk_12;
            a->unk_14 = flags | 0xC;
            a->unk_12 = y - 0x80;
            func_80047784(a, 0x41, 0);
            b = object->unk_08;
            b->unk_02 = arg0->unk_02;
            b->unk_06 = arg0->unk_06;
            b->unk_0A = arg0->unk_0A - (rand() & 0x1F);
            b->unk_16 = ((0 - (rand() & 0xF)) - 8) * 2;
            b->unk_0C = ((rand() & 3) - 2) << 0x10;
            b->unk_10 = ((rand() & 3) - 2) << 0x10;
            object->unk_40 = 0x10;
        }
        count -= 1;
    } while (count > 0);
}

/* MECHANISM: Named word and halfword read locals extend the arg1 value live ranges,
   reproducing retail's load-before-store emission order in the setup block.
   Natural locals retain the 0x30 frame and s0-s5 roles without register pins. */

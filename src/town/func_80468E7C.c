#include "common.h"


typedef void (*Callback)(s32);

typedef struct S_80019E7C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80019E7C_0;   /* root in func_80019E7C */

typedef struct S_80019E7C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    union { s32 * p; u8 * p2; } unk_1C;   /* accessed as both */
} S_80019E7C_1;   /* base in func_80019E7C */


extern s8 D_80016000[];

/* Invokes the root callback and adjusts two object fields using signed offsets. */
void func_80019E7C(void *offsets)
{
    S_80019E7C_0 *root;
    u8 *base;
    s32 *object;
    u16 second_offset;

    root = *(void **)D_80016000;
    (*(Callback *)((u8 *)(root->unk_20) + 0x258))(1);

    base = *(u8 **)D_80016000;
    object = ((S_80019E7C_1 *)base)->unk_1C.p;
    object[1] += *(s16 *)offsets;
    second_offset = *(u16 *)((u8 *)offsets + 2);
    base = ((S_80019E7C_1 *)base)->unk_1C.p2;
    ((S_80019E7C_1 *)base)->unk_08 += (s16)second_offset / 2 - 0x40;
}

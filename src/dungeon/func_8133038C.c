#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct {
    s32 word[3];
} __attribute__((packed)) PackedCopy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80045340;
extern u8 D_801671AC;
extern u8 D_80173B58[48];


typedef struct S_8016738C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_8016738C_0;   /* node in func_8016738C */

typedef struct S_8016738C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016738C_1;   /* ctrl in func_8016738C */

typedef struct S_8016738C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8016738C_2;   /* dst in func_8016738C */

typedef struct S_8016738C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8016738C_3;   /* arg0 in func_8016738C */

/* Create and initialize an object at the supplied position with a fixed Z offset. */
void func_8016738C(S_8016738C_3 *origin)
{
    void *object;
    S_8016738C_2 *position;
    S_8016738C_1 *control;
    S_8016738C_0 *node;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        node = (u8 *)object + 0x20;
        node->unk_18 = 0x1E;
        node->unk_1A = 0x1E;
        (*(void * *)((u8 *)object + 0x10)) = &D_801671AC;
        func_8004491C(object, &D_80045340);

        control = (*(void * *)((u8 *)object + 0xC));

        control->unk_10 = 0x20;
        control->unk_14 = control->unk_14 | 0xC;

        position = (*(void * *)((u8 *)object + 8));
        position->unk_00 = origin->unk_00;
        position->unk_04 = origin->unk_04;
        position->unk_08 = origin->unk_08 + 0x180000;

        control = (*(void * *)((u8 *)object + 0xC));

        control->unk_1C = 0x1400;
        control->unk_1E = 0x1400;
        control->unk_0E = 0;
        control->unk_0D = 0;
        control->unk_0C = 0;
        control->unk_06 = 0;
        control->unk_14 = control->unk_14 | 0x80;

        (*(PackedCopy12 *)((u8 *)object + 0x48)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0));
        (*(PackedCopy12 *)((u8 *)object + 0x54)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0xC));
        (*(PackedCopy12 *)((u8 *)object + 0x60)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x18));
        (*(PackedCopy12 *)((u8 *)object + 0x6C)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x24));
        control->unk_08 = (u8 *)object + 0x48;
    }
}

/* MECHANISM: Four packed 12-byte assignments emit retail's twelve unaligned
   copy quartets without gcc's large-copy loop. A guarded a3 pin preserves the
   control-pointer role while arg0/object remain live in s1/s0 for the 0x20 frame. */

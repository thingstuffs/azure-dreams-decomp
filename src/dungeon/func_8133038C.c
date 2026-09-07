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

void func_8016738C(S_8016738C_3 *arg0)
{
    void *obj;
    S_8016738C_2 *dst;
    S_8016738C_1 *ctrl;
    S_8016738C_0 *node;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        node = (u8 *)obj + 0x20;
        node->unk_18 = 0x1E;
        node->unk_1A = 0x1E;
        (*(void * *)((u8 *)obj + 0x10)) = &D_801671AC;
        func_8004491C(obj, &D_80045340);

        ctrl = (*(void * *)((u8 *)obj + 0xC));
        
        ctrl->unk_10 = 0x20;
        ctrl->unk_14 = ctrl->unk_14 | 0xC;

        dst = (*(void * *)((u8 *)obj + 8));
        dst->unk_00 = arg0->unk_00;
        dst->unk_04 = arg0->unk_04;
        dst->unk_08 = arg0->unk_08 + 0x180000;

        ctrl = (*(void * *)((u8 *)obj + 0xC));
        
        ctrl->unk_1C = 0x1400;
        ctrl->unk_1E = 0x1400;
        ctrl->unk_0E = 0;
        ctrl->unk_0D = 0;
        ctrl->unk_0C = 0;
        ctrl->unk_06 = 0;
        ctrl->unk_14 = ctrl->unk_14 | 0x80;

        (*(PackedCopy12 *)((u8 *)obj + 0x48)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0));
        (*(PackedCopy12 *)((u8 *)obj + 0x54)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0xC));
        (*(PackedCopy12 *)((u8 *)obj + 0x60)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x18));
        (*(PackedCopy12 *)((u8 *)obj + 0x6C)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x24));
        ctrl->unk_08 = (u8 *)obj + 0x48;
    }
}

/* MECHANISM: Four packed 12-byte assignments emit retail's twelve unaligned
   copy quartets without gcc's large-copy loop. A guarded a3 pin preserves the
   control-pointer role while arg0/object remain live in s1/s0 for the 0x20 frame. */

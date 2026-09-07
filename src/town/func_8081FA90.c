#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022290_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80022290_0;   /* obj1 in func_80022290 */

typedef struct S_80022290_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80022290_1;   /* data1 in func_80022290 */

typedef struct S_80022290_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80022290_2;   /* obj2 in func_80022290 */

typedef struct S_80022290_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_80022290_3;   /* data2 in func_80022290 */



typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void *func_8004DA74(void *, void *, s32);
extern void func_800BC1DC(void *, void *, void *);

extern Packed8 D_8002021C;
extern u8 D_800223D8[8];
extern u8 D_800223E0[8];
extern u8 D_800223E8[8];
extern void *D_80024468;
extern void *D_8002446C;
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_800782EC[8];

void func_80022290(void *arg0)
{
    Packed8 local;
    void *obj1;
    S_80022290_1 *data1;
    void *obj2;
    S_80022290_3 *data2;
    void *tail_value;

    local = D_8002021C;
    func_800BC1DC(&local, D_800223D8,
                  func_8004DA74(arg0, D_8002446C, 0));
    func_800BC1DC((u8 *)&local + 4, D_800223D8, D_800782EC);

    obj1 = func_8003FC64(1);
    if (obj1 != NULL) {
        data1 = obj1 + 0x20;
        ((S_80022290_0 *)obj1)->unk_10 = D_800223E0;
        func_8004491C(obj1, &D_80053A88);
        data1->unk_0C = 0xB8;
        data1->unk_0E = 0x14;
        data1->unk_10 = 0x7C;
        data1->unk_12 = 0x18;
        data1->unk_16 = 1;
        data1->unk_08 = 0x402020;
    }

    obj2 = func_8003FC64(1);
    if (obj2 != NULL) {
        data2 = obj2 + 0x20;
        ((S_80022290_2 *)obj2)->unk_10 = D_800223E8;
        func_8004491C(obj2, D_80053858);
        data2->unk_14 = 0xF0;
        data2->unk_16 = 0x20;
        data2->unk_18 = 3;
        tail_value = D_80024468;
        data2->unk_1A = 0x7C80;
        data2->unk_10 = 0x808080;
        data2->unk_04 = tail_value;
    }
}

/* MECHANISM: the true-space ABI preserves incoming arg0; a packed 8-byte local
   produces the lwl/lwr and swl/swr copy, while split object/data names shape s0.
   A one-read tail_value hoists the final global load and removes its delay nop. */

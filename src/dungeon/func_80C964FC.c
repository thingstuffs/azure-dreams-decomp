#include "common.h"
#include "records/Rec_func_80173CFC_arg1.h"


typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80045340;
extern u8 D_80173C0C;
extern u8 D_80175324[12];


typedef struct S_80173CFC_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
} S_80173CFC_0;   /* part in func_80173CFC */

typedef struct S_80173CFC_1 {
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
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80173CFC_1;   /* data in func_80173CFC */

typedef struct S_80173CFC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80173CFC_2;   /* pos in func_80173CFC */


void func_80173CFC(void *arg0, Rec_func_80173CFC_arg1 *arg1, s32 arg2, s16 arg3)
{
    void *node;
    S_80173CFC_0 *part;
    S_80173CFC_1 *data;
    S_80173CFC_2 *pos;

    node = func_8003FC64(0x212);
    if (node != 0) {
        part = (u8 *)node + 0x20;
        part->unk_24 = 5;
        (*(void * *)((u8 *)node + 0x10)) = &D_80173C0C;
        func_8004491C(node, &D_80045340);
        data = (*(void * *)((u8 *)node + 0xC));
        data->unk_10 = 0x60;
        data->unk_14 |= 0xC;
        pos = (*(void * *)((u8 *)node + 8));
        pos->unk_02 = arg1->unk_00.at02_u16.v;
        pos->unk_06 = arg1->unk_04.at02_u16.v;
        pos->unk_0A = arg1->unk_0A - 0x28;
        data = (*(void * *)((u8 *)node + 0xC));
        data->unk_06 = 6;
        data->unk_1E = arg3;
        data->unk_1C = arg3;
        part->unk_01 = 0x30;
        part->unk_02 = 0x30;
        (*(s8 *)((u8 *)node + 0x20)) = 0x30;
        data->unk_0E = 0x30;
        data->unk_0D = 0x30;
        data->unk_0C = 0x30;
        data->unk_1A = rand() & 0xFFF;
        (*(Copy12 *)((u8 *)node + 0x9A)) = (*(Copy12 *)((u8 *)D_80175324 + 0));
        data->unk_08 = (u8 *)node + 0x9A;
    }
}

/* MECHANISM: The four-argument ABI keeps arg1/arg3 in s3/s4 while node, data, and
   node+0x20 occupy s2/s1/s0, producing retail's 0x28 frame and full save set.
   One packed 12-byte assignment emits the retail lwl/lwr and swl/swr copy. */

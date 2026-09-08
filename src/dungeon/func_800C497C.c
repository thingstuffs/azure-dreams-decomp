#include "common.h"
#include "records/Rec_func_800C9F34_arg0.h"


extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800CA1C8(void) __attribute__((noreturn));

extern u16 D_80083462;


typedef struct S_800CA0DC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800CA0DC_0;   /* arg3 in func_800CA0DC */

typedef struct S_800CA0DC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA0DC_1;   /* arg2 in func_800CA0DC */


typedef struct S_800CA0DC_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800CA0DC_3;   /* (u8 *)arg3 + ((S_800CA0DC_0 *)arg3)->unk_8A.s in func_800CA0DC */

void func_800CA0DC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 count;
    s32 old_x;
    s32 old_y;

    if (((S_800CA0DC_0 *)arg3)->unk_71.s <= 0) {
        return;
    }
    if (((S_800CA0DC_0 *)arg3)->unk_71.u <= ((S_800CA0DC_0 *)arg3)->unk_8A.s) {
        return;
    }

    old_x = ((S_800CA0DC_1 *)arg2)->unk_24;
    old_y = ((S_800CA0DC_1 *)arg2)->unk_25;
    ((S_800CA0DC_1 *)arg2)->unk_24 =
        ((S_800CA0DC_3 *)((u8 *)arg3 + ((S_800CA0DC_0 *)arg3)->unk_8A.s))->unk_74;
    ((S_800CA0DC_1 *)arg2)->unk_25 =
        ((S_800CA0DC_3 *)((u8 *)arg3 + ((S_800CA0DC_0 *)arg3)->unk_8A.s))->unk_7C;
    ((S_800CA0DC_0 *)arg3)->unk_8A.u++;

    ((S_800CA0DC_0 *)arg3)->unk_2A =
        func_800A0818(old_x, old_y, ((S_800CA0DC_1 *)arg2)->unk_24,
                      ((S_800CA0DC_1 *)arg2)->unk_25, (u8 *)arg0 + 0x98);
    ((S_800CA0DC_0 *)arg3)->unk_1C |= 0x40000000;
    ((Rec_func_800C9F34_arg0 *)arg0)->unk_9A.as_u8 = 0xF;
    (*(s32 *)((u8 *)arg0 + (0x8C))) = 0;

    if (D_80083462 & 0x80) {
        ((Rec_func_800C9F34_arg0 *)arg0)->unk_96 = 0;
        func_800CA1C8();
    }

    ((Rec_func_800C9F34_arg0 *)arg0)->unk_96 = 8;
    count = ((S_800CA0DC_0 *)arg3)->unk_71.u;
    if (count > 0) {
        ((Rec_func_800C9F34_arg0 *)arg0)->unk_96 = 8 / count;
    }
}

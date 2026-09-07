#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_81977E0C_0_pre {
    u16 unk_00;
} S_81977E0C_0_pre;   /* the 0x2 bytes before arg0 in func_81977E0C, addressed as arg0[-1] */

typedef struct S_81977E0C_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_81977E0C_0;   /* arg0 in func_81977E0C */


typedef struct S_81977E0C_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81977E0C_2;   /* arg1 in func_81977E0C */

typedef struct S_81977E0C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_81977E0C_3;   /* D_80026208 in func_81977E0C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8002579C(void) __attribute__((noreturn));
extern void func_800478B8(void *);
s32 func_800644B8();
s32 func_80064584();
s32 rand();
extern s32 *D_80026208;
extern s32 D_800814A0;

void func_81977E0C(void *arg0, void *arg1, void *arg2) {
    u16 temp_a1;
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_v0_2;

    temp_v0 = ((S_81977E0C_0 *)arg0)->unk_04 + 1;
    ((S_81977E0C_0 *)arg0)->unk_04 = temp_v0;
    if ((s16) temp_v0 >= 0xA) {
        temp_v0_2 = ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v - 0x10;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v = temp_v0_2;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v = temp_v0_2;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v = temp_v0_2;
    }
    ((S_81977E0C_0 *)arg0)->unk_08 = (u16) (((S_81977E0C_0 *)arg0)->unk_08 + 0x100);
    ((S_81977E0C_0 *)arg0)->unk_06 = (u16) (((S_81977E0C_0 *)arg0)->unk_06 + 1);
    temp_a1 = (u16) (((S_81977E0C_0 *)arg0)->unk_0A - 8) - (rand() % 9);
    ((S_81977E0C_0 *)arg0)->unk_0A = temp_a1;
    if ((u16) ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v < 0x400U) {
        temp_v0_3 = ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v + 0x40;
        ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = temp_v0_3;
        ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = temp_v0_3;
    }
    func_800478B8(arg2);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_81977E0C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        func_8002579C();
        return;
    }
    ((S_81977E0C_2 *)arg1)->unk_00 = (s32) (*D_80026208 + (((func_800644B8((s16) ((S_81977E0C_0 *)arg0)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)arg0)->unk_06) << 8));
    ((S_81977E0C_2 *)arg1)->unk_04 = (s32) (D_80026208[1] + (((func_80064584((s16) ((S_81977E0C_0 *)arg0)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)arg0)->unk_06) << 8));
    ((S_81977E0C_2 *)arg1)->unk_0A = (s16) (((S_81977E0C_3 *)D_80026208)->unk_0A + ((S_81977E0C_0 *)arg0)->unk_0A);
}

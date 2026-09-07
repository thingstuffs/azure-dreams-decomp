#include "common.h"


extern void func_800478B8(void *arg0);
extern void func_80099C3C(void);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern GlobalFlags D_800814A0;


typedef struct S_80099B18_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80099B18_0;   /* arg2 in func_80099B18 */

typedef struct S_80099B18_1_pre {
    u16 unk_00;
} S_80099B18_1_pre;   /* the 0x2 bytes before arg0 in func_80099B18, addressed as arg0[-1] */

typedef struct S_80099B18_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u16 unk_10;
} S_80099B18_1;   /* arg0 in func_80099B18 */

typedef struct S_80099B18_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80099B18_2;   /* arg1 in func_80099B18 */

void func_80099B18(void *arg0, S_80099B18_2 *arg1, S_80099B18_0 *arg2)
{
    u16 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v1_2;

    if (arg2->unk_14 & 0xE000) {
        ((S_80099B18_1_pre *)arg0)[-1].unk_00 =
            (s16)(((S_80099B18_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0.value |= 0x8000;
        func_80099C3C();
        return;
    }
    temp_v0 = ((S_80099B18_1 *)arg0)->unk_10 + 1;
    ((S_80099B18_1 *)arg0)->unk_10 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        arg2->unk_14 =
            (u16)(arg2->unk_14 & 0xFF7F);
        func_800478B8(arg2);
    }
    if (((S_80099B18_1 *)arg0)->unk_0E != 0) {
        arg1->unk_00 =
            (s32)(arg1->unk_00 + arg1->unk_0C);
        arg1->unk_04 =
            (s32)(arg1->unk_04 + arg1->unk_10);
        arg1->unk_08 =
            (s32)(arg1->unk_08 + arg1->unk_14);
        arg1->unk_0C =
            (s32)(arg1->unk_0C - (arg1->unk_0C >> 2));
        arg1->unk_10 =
            (s32)(arg1->unk_10 - (arg1->unk_10 >> 2));
        arg1->unk_14 =
            (s32)(arg1->unk_14 - (arg1->unk_14 >> 2));
        temp_v0_3 = arg2->unk_0C;
        temp_v1_2 = arg2->unk_0D;
        arg2->unk_0C =
            (u8)(temp_v0_3 - (temp_v0_3 >> 1));
        temp_v0_4 = arg2->unk_0E;
        arg2->unk_0D =
            (u8)(temp_v1_2 - (temp_v1_2 >> 1));
        arg2->unk_0E =
            (u8)(temp_v0_4 - (temp_v0_4 >> 1));
    }
}

/* MECHANISM: The three arguments stay live as s1/s0/s2, yielding the retail 0x20 frame and save order.
   Direct repeated s32 fields preserve the six-load update group and the required a1-to-a0 copy.
   The natural void tail call lets maspsx retain the global store in the retail jump delay slot. */

#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80176084_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
    s8 unk_B5;
} S_80176084_0;   /* arg0 in func_80176084 */




typedef struct S_80176084_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80176084_4;   /* global in func_80176084 */



extern M2C_UNK func_80042B68();
extern M2C_UNK func_80047784();
extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_801708B8();
extern void func_80176240(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E23E0[];
extern u8 D_800E2448[];
extern u8 D_80171A80[];

void func_80176084(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;
    u8 temp_v1_2;
    u32 one;

    temp_v1 = ((S_80176084_0 *)arg0)->unk_9B;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return;
        }
        goto block_15;
    }
    temp_v1_2 = ((S_80176084_0 *)arg0)->unk_B1;
    one = 1;
    if (temp_v1_2 != 0) {
        if (temp_v1_2 != one) {
            return func_80176240();
        }
        goto block_10;
    }
    ((S_80176084_0 *)arg0)->unk_B1 = one;
    ASM_KEEP(one);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_80176084_0 *)arg0)->unk_96 = 4U;
    (*(M2C_UNK * *)((u8 *)arg2 + 0x2C)) = (M2C_UNK *)D_800E2448;
    func_80047784(arg2, D_800E2448[((s32)(D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    if ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) ||
        (func_800A56E0(0x801), ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) != 0))) {
block_10:
        temp_v0 = ((S_80176084_0 *)arg0)->unk_96;
        ((S_80176084_0 *)arg0)->unk_96 = (u16)(temp_v0 - 1);
        if (((temp_v0 << 0x10) <= 0) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= 0x40000;
            ((S_80176084_0 *)arg0)->unk_B5 = 0;
            ((S_80176084_0 *)arg0)->unk_98 |= 8;
            (*(M2C_UNK * *)((u8 *)arg2 + 0x2C)) = (M2C_UNK *)D_800E23E0;
            func_80047784(arg2, D_800E23E0[((s32)(D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            ((S_80176084_0 *)arg0)->unk_96 = 5U;
            ((S_80176084_0 *)arg0)->unk_9B++;
            ((S_80176084_0 *)arg0)->unk_B1++;
            if (((S_80176084_0 *)arg0)->unk_B0 == 0) {
                func_801708B8(arg0, arg1, arg2);
            }
        }
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
block_15:
            temp_v0_2 = ((S_80176084_0 *)arg0)->unk_96;
            ((S_80176084_0 *)arg0)->unk_96 = (u16)(temp_v0_2 - 1);
            if (((temp_v0_2 << 0x10) <= 0) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
                ((Rec_D_80082E80 *)arg2)->unk_06.as_s16 = 0;
                ((S_80176084_0 *)arg0)->unk_8C = (M2C_UNK *)D_80171A80;
                func_80042B68(arg3, 0x1B);
                if (((S_80176084_0 *)arg0)->unk_B4 == 0) {
                    u8 *global = (u8 *)&D_80083460;
                    ((S_80176084_4 *)global)->unk_0C = 0;
                    ((S_80176084_4 *)global)->unk_0A--;
                    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
                }
                func_800AA36C(arg0, arg1, arg2, arg3);
            }
        }
    }
}

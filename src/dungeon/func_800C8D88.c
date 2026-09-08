#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CE4E8_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0x64];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    union { u16 s; s16 u; } unk_6E;   /* accessed as both */
} S_800CE4E8_0;   /* temp_s3 in func_800CE4E8 */

typedef struct S_800CE4E8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CE4E8_1;   /* global_base in func_800CE4E8 */



typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[0xC];
    s16 field_20;
    s16 field_22;
} DungeonObject;

extern void *func_8003FC64(s32);
extern void func_800419EC(s32, s32);
extern s32 func_800A6DA4(s32, s32);
extern s32 func_800BCA68(s32, s32);

extern u8 D_800CE028[];
extern s32 D_80083460;
extern s32 D_800E296C;

s32 func_800CE4E8(s32 arg0, s32 arg1, s16 arg2, void *arg3, s32 arg4)
{
    u16 subroutine_arg4;
    s32 signed_arg4;
    s32 var_s2;
    s32 var_s4;
    s32 result;
    s32 rand_a0;
    s32 rand_a1;
    s32 coord_x;
    s32 coord_y;
    u16 *temp_s1;
    u16 *var_s0;
    s32 temp_v0_2;
    register u8 *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *temp_s3;
    DungeonObject *temp_v0;
    u8 *var_s5;
    u8 *global_base;
    u8 *temp_s6;

    temp_v0 = func_8003FC64(2);
    subroutine_arg4 = arg4;
    if (temp_v0 != NULL) {
        var_s4 = 0;
        signed_arg4 = (s16)arg4;
        temp_s3 = (u8 *)&temp_v0->field_20;
        var_s5 = temp_s3;
        temp_v0->field_10 = D_800CE028;
        temp_v0->field_20 = arg0 - 2;
        ((S_800CE4E8_0 *)temp_s3)->unk_02 = arg1 - 2;
        do {
            var_s2 = 0;
            temp_s6 = var_s5;
            var_s0 = (u16 *)(var_s5 + 0x36);
            do {
                coord_x = ((S_800CE4E8_0 *)temp_s3)->unk_00;
                coord_y = ((S_800CE4E8_0 *)temp_s3)->unk_02;
                result = func_800BCA68(
                    ((var_s2 + coord_x) << 6) & 0xFFC0,
                    ((var_s4 + coord_y) << 6) & 0xFFC0);
                rand_a0 = 1;
                rand_a1 = 3;
                ASM_KEEP(rand_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                temp_a2 = temp_s6 + 4;
                temp_s1 = (u16 *)((unsigned long)(var_s2 * 2) +
                    (unsigned long)temp_a2);
                *temp_s1 = -result;
                temp_v0_2 = func_800A6DA4(rand_a0, rand_a1);
                temp_v0_2 = (temp_v0_2 & 0xFFFF) << 5;
                *var_s0 = temp_v0_2;
                if (signed_arg4 != 0) {
                    *var_s0 = -temp_v0_2;
                }
                var_s2++;
                *var_s0 += *temp_s1;
                var_s0++;
            } while (var_s2 < 5);
            var_s4++;
            var_s5 += 0xA;
        } while (var_s4 < 5);

        ((S_800CE4E8_0 *)temp_s3)->unk_6C = 0x10;
        ((S_800CE4E8_0 *)temp_s3)->unk_68 = 0x20;
        ((S_800CE4E8_0 *)temp_s3)->unk_6E.s = subroutine_arg4;
        func_800419EC(0x20, 8);

        if (((S_800CE4E8_0 *)temp_s3)->unk_6E.u == 0) {
            D_800E296C |= 0x80080000;
        } else {
            D_800E296C |= 0x40080000;
        }
        global_base = (u8 *)&D_80083460;
        ((S_800CE4E8_1 *)global_base)->unk_0A++;
    }
    return (s32)temp_v0;
}

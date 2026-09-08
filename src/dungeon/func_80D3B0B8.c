#include "common.h"

typedef struct S_80D3B0B8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    u8 * unk_AC;
} S_80D3B0B8_0;   /* temp_s3 in func_80D3B0B8 */

typedef struct S_80D3B0B8_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80D3B0B8_1;   /* temp_v0 in func_80D3B0B8 */

typedef struct S_80D3B0B8_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80D3B0B8_2;   /* saved_arg0 in func_80D3B0B8 */

typedef struct S_80D3B0B8_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80D3B0B8_3;   /* temp_s1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80D3B0B8_4;   /* base_80083160 in func_80D3B0B8 */

typedef struct S_80D3B0B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_5;   /* temp_v1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_6;   /* saved_arg1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80D3B0B8_7;   /* saved_arg2 in func_80D3B0B8 */


typedef struct Copy16 {
    s32 word[4];
} Copy16;


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_800BC26C(void *, s32, void *, void *);

extern s32 D_80045340;
extern u8 D_80083160[];
extern u8 D_80083498[];
extern u8 D_800D5594[];
extern s8 D_800DCECC[];
extern u8 D_800E23F0[];

void func_80D3B0B8(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *saved_arg0 = arg0;
    u8 *saved_arg1 = arg1;
    u8 *saved_arg2 = arg2;
    u8 *temp_v0;
    register u8 *temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *temp_s1;
    u8 *base_80083160;
    u8 *temp_v1;
    Copy16 *var_a2;
    Copy16 *var_a3;
    Copy16 *var_t0;
    u8 *table_800E23F0;

    temp_v0 = func_8003FD64(0x112, D_80083498);
    temp_s3 = temp_v0 + 0x20;
    if (temp_v0 != 0) {
        ((S_80D3B0B8_0 *)temp_s3)->unk_96 = 0x78;
        ((S_80D3B0B8_1 *)temp_v0)->unk_10 = D_800D5594;
        ((S_80D3B0B8_0 *)temp_s3)->unk_AC = saved_arg0 - 0x20;
        ((S_80D3B0B8_0 *)temp_s3)->unk_94 = ((S_80D3B0B8_2 *)saved_arg0)->unk_2A.s;
        var_a3 = (Copy16 *)saved_arg2;
        ((S_80D3B0B8_0 *)temp_s3)->unk_2A = ((S_80D3B0B8_2 *)saved_arg0)->unk_2A.s;
        temp_s1 = ((S_80D3B0B8_1 *)temp_v0)->unk_0C;

        var_t0 = (Copy16 *)(saved_arg2 + 0x30);
        var_a2 = (Copy16 *)temp_s1;
        do {
            *var_a2 = *var_a3;
            var_a3++;
            var_a2++;
        } while (var_a3 != var_t0);
        ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        func_8004491C(temp_v0, &D_80045340);
        table_800E23F0 = D_800E23F0;
        ((S_80D3B0B8_3 *)temp_s1)->unk_2C = table_800E23F0;
        base_80083160 = D_80083160;
        func_80047784(temp_s1,
            table_800E23F0[((((S_80D3B0B8_4 *)base_80083160)->unk_C8 +
                ((S_80D3B0B8_2 *)saved_arg0)->unk_2A.u + 0x100) >> 9) & 7], 0);

        temp_v1 = ((S_80D3B0B8_1 *)temp_v0)->unk_08;
        ((S_80D3B0B8_5 *)temp_v1)->unk_02 = ((S_80D3B0B8_6 *)saved_arg1)->unk_02;
        ((S_80D3B0B8_5 *)temp_v1)->unk_06 = ((S_80D3B0B8_6 *)saved_arg1)->unk_06;
        ((S_80D3B0B8_5 *)temp_v1)->unk_0A = ((S_80D3B0B8_6 *)saved_arg1)->unk_0A;
        {
            u16 field_1c;
            u16 field_1e;

            field_1c = ((S_80D3B0B8_7 *)saved_arg2)->unk_1C;
            ((S_80D3B0B8_3 *)temp_s1)->unk_1C = field_1c;
            field_1e = ((S_80D3B0B8_7 *)saved_arg2)->unk_1E;
            ((S_80D3B0B8_3 *)temp_s1)->unk_0E = 0x80;
            ((S_80D3B0B8_3 *)temp_s1)->unk_0D = 0x80;
            ((S_80D3B0B8_3 *)temp_s1)->unk_0C = 0x80;
            ((S_80D3B0B8_3 *)temp_s1)->unk_1E = field_1e;
        }
        ((S_80D3B0B8_3 *)temp_s1)->unk_06 =
            D_800DCECC[((((S_80D3B0B8_4 *)base_80083160)->unk_C8 +
                ((S_80D3B0B8_2 *)saved_arg0)->unk_2A.u + 0x100) >> 9) & 7] * 4;
        ((S_80D3B0B8_2 *)saved_arg0)->unk_B0++;
        func_800BC26C(temp_v0, 0, temp_s1 + 0x2C, temp_s3 + 0x2A);
        ASM_KEEP(saved_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009C648_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009C648_6;   /* temp_v0 in func_8009C648 */

typedef struct S_8009C648_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C648_7;   /* ((S_8009C648_6 *)temp_v0)->unk_0C in func_8009C648 */




extern s32 rand(void);
extern void *func_8009C390(void *, M2C_UNK, s32, s32);
extern void func_8009C46C(void *, void *, void *);
extern u8 D_80088D78[8];
extern M2C_UNK D_800D06C8[3];

typedef struct S_8009C648_0 {
    s32 unk_00;
    s32 unk_04;
} S_8009C648_0;   /* var_s4 in func_8009C648 */

typedef struct S_8009C648_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8009C648_1;   /* temp_v0 in func_8009C648 */

typedef struct S_8009C648_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_8009C648_2;   /* held_arg0 in func_8009C648 */

typedef struct S_8009C648_3 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_8009C648_3;   /* temp_s1 in func_8009C648 */

typedef struct S_8009C648_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8009C648_4;   /* temp_s0 in func_8009C648 */

typedef struct S_8009C648_5 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C648_5;   /* tail_s0 in func_8009C648 */

void func_8009C648(u8 *arg0, M2C_UNK arg1) {
    s8 sp[6];
    s32 var_s5;
    M2C_UNK *var_s4;
    s32 var_s3;
    S_8009C648_4 *temp_s0;
    S_8009C648_3 *temp_s1;
    void *temp_v0;
    void *var_a0;
    s32 temp_rng;
    S_8009C648_5 *tail_s0;
    register void *held_arg0 ASM_REG("$22") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK held_arg1 = arg1;

    memcpy(sp, D_80088D78, 6);
    var_s3 = 0;
    var_s5 = 0xFFFC0000;
    ASM_KEEP(var_s5);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    var_s4 = D_800D06C8;
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_a0 = (u8 *)held_arg0 - 0x20;
loop_1:
    temp_v0 = func_8009C390(var_a0, held_arg1, ((S_8009C648_0 *)var_s4)->unk_00, ((S_8009C648_0 *)var_s4)->unk_04);
    if (temp_v0 != NULL) {
        temp_s0 = ((S_8009C648_1 *)temp_v0)->unk_08;
        temp_s1 = (u8 *)temp_v0 + 0x20;
        ((S_8009C648_7 *)(((S_8009C648_6 *)temp_v0)->unk_0C))->unk_08 =
            ((s32 *)((S_8009C648_2 *)held_arg0)->unk_80)[sp[var_s3]];
        temp_s1->unk_60 = var_s3;
        temp_s0->unk_0C = (s32)((rand() * 0x10) + var_s5);
        temp_s0->unk_10 = (s32)((rand() * 0x10) + var_s5);
        temp_rng = rand();
        tail_s0 = temp_s0;
        var_s4 += 2;
        tail_s0->unk_14 = (s32)(0xFFF00000 - (temp_rng * 0x10));
        tail_s0->unk_00 =
            (s32)(tail_s0->unk_00 + (tail_s0->unk_0C * 8));
        tail_s0->unk_04 =
            (s32)(tail_s0->unk_04 + (tail_s0->unk_10 * 8));
        func_8009C46C(temp_s1, tail_s0, ((S_8009C648_1 *)temp_v0)->unk_0C);
        var_s3 += 1;
        var_a0 = (u8 *)held_arg0 - 0x20;
        if (var_s3 < 6) {
            goto loop_1;
        }
    }
}

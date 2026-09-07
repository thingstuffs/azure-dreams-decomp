#include "common.h"

typedef struct S_800B61C0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x8];
    s32 unk_2C;
    u8 pad_30[0x8];
    void * unk_38;
} S_800B61C0_0;   /* temp_s0 in func_800B61C0 */

typedef struct S_800B61C0_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B61C0_1;   /* arg0 in func_800B61C0 */

typedef struct S_800B61C0_2 {
    s32 unk_00;
    void * unk_04;
} S_800B61C0_2;   /* ((S_800B61C0_0 *)temp_s0)->unk_38 in func_800B61C0 */

typedef struct S_800B61C0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B61C0_3;   /* ((S_800B61C0_2 *)(((S_800B61C0_0 *)temp_s0)->unk_38))->unk_04 in func_800B61C0 */


extern s32 func_8004A658();
extern s32 func_8004AC3C();
extern s32 func_800B5264();
extern s32 func_800B53BC();
extern s32 func_800B5918();


void func_800B61C0(S_800B61C0_1 *arg0, s32 arg1, s32 arg2)
{
    s32 sp18[4];
    s32 sp28[2];
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_s3;
    register s32 temp_v0 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 *temp_a1;
    S_800B61C0_0 *temp_s0;

    temp_a1 = sp28;
    temp_v0 = func_8004AC3C(arg0, temp_a1);
    do { temp_s2 = arg2 * 0x10; } while (0);
    temp_s3 = temp_s2 + 0xD8;
    temp_s0 = (void *)(arg2 * 4 + arg1);
    func_800B5264(temp_s0->unk_20, temp_v0, sp28[0], 0x58, temp_s3);
    func_800B53BC(temp_s0->unk_2C,
                  func_800B5918(arg0, sp18), 0, 0xA0, temp_s3);
    ((S_800B61C0_2 *)(temp_s0->unk_38))->unk_00 = func_8004A658(
        arg0->unk_01, arg0->unk_00);
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(temp_s0->unk_38))->unk_04))->unk_08 = -0x30;
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(temp_s0->unk_38))->unk_04))->unk_0A =
        (s16)(temp_s2 + 0x66);
}

/* MECHANISM: Sibling sp18/sp28 arrays produce the retail 0x48 frame; keeping the
   sp28 pointer live hoists sp+0x28 and lets the $s2 save fill the first jal slot.
   Guarded $s2/$a1 value pins restore the scaled-index role and immediate return copy. */

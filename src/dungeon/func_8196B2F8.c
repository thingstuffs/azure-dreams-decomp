#include "common.h"
#include "m2c_compat.h"

typedef struct S_8196B2F8_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x64];
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B2F8_0;   /* temp_s1 in func_8196B2F8 */

typedef struct S_8196B2F8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8196B2F8_1;   /* temp_v0 in func_8196B2F8 */

typedef struct S_8196B2F8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8196B2F8_2;   /* temp_a0 in func_8196B2F8 */

typedef struct S_8196B2F8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B2F8_3;   /* temp_s0 in func_8196B2F8 */

typedef struct S_8196B2F8_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8196B2F8_4;   /* temp_a0_2 in func_8196B2F8 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                       /* extern */
extern M2C_UNK D_800244E4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800DE870;

void func_8196B2F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_rand;
    register s32 temp_v0_coords ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    s32 temp_v1_coords;
    s16 temp_v0_2;
    u16 temp_flags;
    register u16 temp_v0_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *temp_a0;
    S_8196B2F8_4 *temp_a0_2;
    S_8196B2F8_3 *temp_s0;
    S_8196B2F8_0 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        temp_v0_2 = (rand() & 7) + 0x20;
        temp_s1->unk_2C = temp_v0_2;
        temp_s1->unk_2E = temp_v0_2;
        ((S_8196B2F8_1 *)temp_v0)->unk_10 = &D_800244E4;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = ((S_8196B2F8_1 *)temp_v0)->unk_0C;
        temp_v0_3 = ((S_8196B2F8_2 *)temp_a0)->unk_14;
        ((S_8196B2F8_2 *)temp_a0)->unk_06.s = 0;
        temp_v0_3 |= 0xC;
        ((S_8196B2F8_2 *)temp_a0)->unk_14 = temp_v0_3;
        ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_flags = temp_v0_3;
        ASM_KEEP(temp_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        temp_v0_3 = 0x60;
        temp_flags |= 2;
        ((S_8196B2F8_2 *)temp_a0)->unk_10 = temp_v0_3;
        ((S_8196B2F8_2 *)temp_a0)->unk_14 = temp_flags;
        temp_a0 = (void *) 0x80080000;
        ASM_KEEP(temp_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_s0 = ((S_8196B2F8_1 *)temp_v0)->unk_08;
        temp_a0 = (void *) ((u8 *) temp_a0 + 0x3780);
        temp_s0->unk_02 = arg3;
        temp_s0->unk_06 = (u16) arg4;
        temp_s0->unk_0A = (u16) arg5;
        temp_v1_coords = ((S_8196B2F8_2 *)temp_a0)->unk_02;
        ASM_KEEP(temp_v1_coords);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_v0_coords = arg3;
        ASM_KEEP(temp_v0_coords);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v0_coords += temp_v1_coords;
        temp_s0->unk_02 = (u16) temp_v0_coords;
        temp_v1_coords = ((S_8196B2F8_2 *)temp_a0)->unk_06.u;
        ASM_KEEP(temp_v1_coords);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_v0_coords = arg4;
        ASM_KEEP(temp_v0_coords);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v0_coords += temp_v1_coords;
        temp_s0->unk_06 = (u16) temp_v0_coords;
        temp_v1_coords = ((S_8196B2F8_2 *)temp_a0)->unk_0A;
        ASM_KEEP(temp_v1_coords);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_v0_coords = arg5;
        ASM_KEEP(temp_v0_coords);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v0_coords += temp_v1_coords;
        temp_s0->unk_0A = (u16) temp_v0_coords;
        temp_rand = rand() & 0x1F;
        temp_v1 = temp_s0->unk_02;
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        temp_s0->unk_02 = (u16) temp_v1;
        temp_rand = rand() & 0x1F;
        temp_v1 = temp_s0->unk_06;
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        temp_s0->unk_06 = (u16) temp_v1;
        temp_rand = rand() & 0x1F;
        temp_v1 = temp_s0->unk_0A;
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        temp_s0->unk_0A = (u16) temp_v1;
        temp_s1->unk_94 = rand();
        temp_s1->unk_A0 = 0x1000;
        temp_a0_2 = ((S_8196B2F8_1 *)temp_v0)->unk_0C;
        temp_a0_2->unk_1C = 0xC00;
        temp_a0_2->unk_1E = 0xC00;
        temp_a0_2->unk_0E = 0x80;
        temp_a0_2->unk_0D = 0x80;
        temp_a0_2->unk_0C = 0x80;
        temp_a0_2->unk_12 = 0x7DCF;
        temp_a0_2->unk_14 = (u16) (temp_a0_2->unk_14 | 0x100);
        func_8003DB94(temp_a0_2, &D_800DE870, 0);
    }
}

/* MECHANISM: The s32 fourth-argument ABI and split RMW live ranges recover the seven-register 0x30 frame.
   Guarded v0/v1 seams preserve the two flag updates and coordinate accumulation order.
   A fenced 0x80080000 page base around the independent s0 load emits retail's lui/lw/addiu sequence. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80175060_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80175060_0;   /* temp_v0 in func_80175060 */

typedef struct S_80175060_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80175060_1;   /* temp_s0 in func_80175060 */


typedef struct S_80175060_3 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175060_3;   /* temp_v1_2 in func_80175060 */

typedef struct S_80175060_4 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80175060_4;   /* arg0 in func_80175060 */


void func_8003DB94(void *, void *, s32);  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEA68;
extern M2C_UNK D_80174F64;

s32 func_80175060(S_80175060_4 *arg0, Rec_D_800E3D7C *arg1) {
    s32 color;
    s32 four;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    S_80175060_1 *temp_s0;
    void *temp_v0;
    S_80175060_3 *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        ((S_80175060_0 *)temp_v0)->unk_10 = &D_80174F64;
        var_v0 = rand();
        temp_a0 = var_v0;
        temp_s0 = temp_v0 + 0x20;
        if (temp_a0 < 0) {
            var_v0 = temp_a0 + 0xFFF;
        }
        color = 0x606060;
        temp_s0->unk_04 = (s16) (temp_a0 - ((var_v0 >> 0xC) << 0xC));
        four = 4;
        ASM_KEEP(four);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_s0->unk_08 = (s16) four;
        temp_s0 = ((S_80175060_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0C = color;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x20);
        func_8003DB94(temp_s0, &D_800DEA68, 0);
        func_800478B8(temp_s0);
        var_v0_2 = rand();
        temp_v1 = var_v0_2;
        if (temp_v1 < 0) {
            var_v0_2 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = (s16) (temp_v1 - ((var_v0_2 >> 0xC) << 0xC));
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        {
            s32 copy0;
            s32 copy1;
            register s32 copy2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register s32 copy3 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            temp_v1_2 = ((S_80175060_0 *)temp_v0)->unk_08;
            ASM_KEEP(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy0 = arg1->unk_00.at00_s32.v;
            copy1 = arg1->unk_04.at00_s32.v;
            copy2 = arg1->unk_08.at00_s32.v;
            copy3 = arg1->unk_0C.as_s32;
            temp_v1_2->unk_00 = copy0;
            temp_v1_2->unk_04 = copy1;
            temp_v1_2->unk_08.at00.v = copy2;
            temp_v1_2->unk_0C = copy3;
            copy0 = arg1->unk_10.at00_s32.v;
            copy1 = arg1->unk_14.as_s32;
            temp_v1_2->unk_10 = copy0;
            temp_v1_2->unk_14 = copy1;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy0 = temp_v1_2->unk_00;
            copy1 = temp_v1_2->unk_04;
            temp_v1_2->unk_0C = copy0;
            temp_v1_2->unk_10 = copy1;
        }
        temp_v1_2->unk_08.at02.v = arg0->unk_88;
        return (s32) temp_v0;
    }
    return 0;
}

/* MECHANISM: The true-space function and one shared scratch/child pointer produce the
   retail 0x28 frame and s3/s2/s1/s0 lifetimes; the success tail returns the object locally.
   Four guarded copy temporaries reproduce the 24-byte v0/a0/a1/a2 copy, with a memory fence.
   A color local, a1 clobber, and kept four order the final li/la/store triplet exactly. */

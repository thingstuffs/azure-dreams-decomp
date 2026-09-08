#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172B00_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    s32 unk_AC;
} S_80172B00_0;   /* temp_s3 in func_80172B00 */

typedef struct S_80172B00_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172B00_1;   /* temp_v0 in func_80172B00 */

typedef struct S_80172B00_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80172B00_2;   /* arg0 in func_80172B00 */

typedef struct S_80172B00_3 {
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
} S_80172B00_3;   /* temp_s1 in func_80172B00 */

typedef struct S_80172B00_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80172B00_4;   /* base_83160 in func_80172B00 */

typedef struct S_80172B00_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172B00_5;   /* temp_v1 in func_80172B00 */

typedef struct S_80172B00_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172B00_6;   /* arg1 in func_80172B00 */

typedef struct S_80172B00_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80172B00_7;   /* arg2 in func_80172B00 */


void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800BC26C(); /* extern */
extern M2C_UNK D_80045340;
extern s8 D_80083160[];
extern s8 D_800DCECC[];
extern M2C_UNK D_80172610;
extern u8 D_80174C74[];

typedef struct {
    s32 words[4];
} CopyBlock;

void func_80172B00(void *arg0, S_80172B00_6 *arg1, void *arg2) {
    s32 temp_s0;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0;
    S_80172B00_5 *temp_v1;
    s8 *base_83160;
    register CopyBlock *var_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    CopyBlock *var_a3;
    register CopyBlock *copy_end ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 word0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 word1;
    s32 word2;
    s32 word3;
    u16 field_1c;
    void *call_arg0;
    s32 table_index;
    s32 angle;
    s32 call_arg1;

    temp_s0 = arg0 - 0x20;
    temp_v0 = func_8003FD64(0x112, temp_s0);
    temp_s3 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        ((S_80172B00_0 *)temp_s3)->unk_96 = 0x78;
        ((S_80172B00_1 *)temp_v0)->unk_10 = &D_80172610;
        ((S_80172B00_0 *)temp_s3)->unk_AC = temp_s0;
        ((S_80172B00_0 *)temp_s3)->unk_94 = (u16) ((S_80172B00_2 *)arg0)->unk_2A.s;
        var_a3 = (CopyBlock *) arg2;
        ((S_80172B00_0 *)temp_s3)->unk_2A = (u16) ((S_80172B00_2 *)arg0)->unk_2A.s;
        temp_s1 = ((S_80172B00_1 *)temp_v0)->unk_0C;
        copy_end = (CopyBlock *) (arg2 + 0x30);
        var_a2 = (CopyBlock *) temp_s1;
        do {
            word0 = var_a3->words[0];
            word1 = var_a3->words[1];
            word2 = var_a3->words[2];
            word3 = var_a3->words[3];
               /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
               /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            var_a2->words[0] = word0;
            var_a2->words[1] = word1;
            var_a2->words[2] = word2;
            var_a2->words[3] = word3;
            ASM_KEEP(var_a3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            var_a3++;
            var_a2++;
        } while (var_a3 != copy_end);
        ASM_KEEP(copy_end);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        ((S_80172B00_3 *)temp_s1)->unk_2C = D_80174C74;
        base_83160 = D_80083160;
        func_80047784(temp_s1, D_80174C74[((s32) (((S_80172B00_4 *)base_83160)->unk_C8 + (s16) ((S_80172B00_2 *)arg0)->unk_2A.s + 0x100) >> 9) & 7], 0);
        temp_v1 = ((S_80172B00_1 *)temp_v0)->unk_08;
        temp_v1->unk_02 = (u16) arg1->unk_02;
        temp_v1->unk_06 = (u16) arg1->unk_06;
        temp_v1->unk_0A = (u16) arg1->unk_0A;
        field_1c = ((S_80172B00_7 *)arg2)->unk_1C;
        ASM_KEEP(field_1c);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_arg0 = temp_v0;
        ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80172B00_3 *)temp_s1)->unk_1C = field_1c;
        ((S_80172B00_3 *)temp_s1)->unk_1E = (u16) ((S_80172B00_7 *)arg2)->unk_1E;
        ((S_80172B00_3 *)temp_s1)->unk_0E = 0x80;
        ((S_80172B00_3 *)temp_s1)->unk_0D = 0x80;
        ((S_80172B00_3 *)temp_s1)->unk_0C = 0x80;
        table_index = ((S_80172B00_4 *)base_83160)->unk_C8;
        angle = ((S_80172B00_2 *)arg0)->unk_2A.u;
           /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        call_arg1 = 0;
        table_index += angle;
        table_index += 0x100;
        table_index >>= 9;
        table_index &= 7;
        ((S_80172B00_3 *)temp_s1)->unk_06 = (s16) (D_800DCECC[table_index] * 4);
        ((S_80172B00_2 *)arg0)->unk_B0 = (u8) (((S_80172B00_2 *)arg0)->unk_B0 + 1);
        func_800BC26C(call_arg0, call_arg1, temp_s1 + 0x2C, temp_s3 + 0x2A);
    }
}
/* MECHANISM: The 0x30 frame follows seven held callee-saved roles, including a reused &D_80083160 base.
   The 16-byte loop pins a3/a2/t0 and v0/v1/a0/a1 roles; guarded seams preserve load-all/store-all order.
   Byte-table types plus pinned call arguments and split v1 accumulator updates close the tail exactly. */

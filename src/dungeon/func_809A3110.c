#include "common.h"
#include "m2c_compat.h"

typedef struct S_80174910_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_6;   /* arg0 in func_80174910 */

typedef struct S_80174910_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80174910_7;   /* temp_v0 in func_80174910 */

typedef struct S_80174910_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174910_8;   /* ((S_80174910_6 *)arg0)->unk_08 in func_80174910 */

typedef struct S_80174910_9 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_80174910_9;   /* ((S_80174910_6 *)arg0)->unk_0C in func_80174910 */

typedef struct S_80174910_10 {
    u8 pad_00[0x10];
    s16 unk_10;
} S_80174910_10;   /* ((S_80174910_7 *)temp_v0)->unk_0C in func_80174910 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800672D8();              /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801747B8;

typedef struct S_80174910_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80174910_0;   /* temp_v0 in func_80174910 */

typedef struct S_80174910_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    void * unk_18;
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
} S_80174910_1;   /* temp_v1 in func_80174910 */

typedef struct S_80174910_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_2;   /* arg0 in func_80174910 */

typedef struct S_80174910_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_80174910_3;   /* temp_v1_2 in func_80174910 */

typedef struct S_80174910_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80174910_4;   /* var_v1 in func_80174910 */

typedef struct S_80174910_5 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80174910_5;   /* temp_v1_3 in func_80174910 */

void func_80174910(S_80174910_2 *arg0, s32 arg1) {
    u16 sp10[4];                                    /* compiler-managed */
    s16 temp_v0_5;
    s32 var_s1;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_6;
    u8 entry_flags;
    u8 *var_v1;
    void *temp_v0;
    S_80174910_1 *temp_v1;
    S_80174910_3 *temp_v1_2;
    S_80174910_5 *temp_v1_3;
    void *object_callback;
    u8 *callback_page;

    var_s1 = 0;
    object_callback = &D_801747B8;
    callback_page = (u8 *) 0x80170000;
    do {
        temp_v0 = func_8003FD64(0x12, arg0);
        temp_v1 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            ((S_80174910_0 *)temp_v0)->unk_10 = object_callback;
            temp_v1->unk_18 = (void *) arg0->unk_0C;
            temp_v1->unk_1C = (void *) arg0->unk_08;
            temp_v0_2 = ((S_80174910_8 *)(((S_80174910_6 *)arg0)->unk_08))->unk_02;
            temp_v1->unk_24 = temp_v0_2;
            temp_v1->unk_22 = temp_v0_2;
            temp_v1->unk_20 = temp_v0_2;
            temp_v0_3 = ((S_80174910_8 *)(((S_80174910_6 *)arg0)->unk_08))->unk_06;
            temp_v1->unk_2A = temp_v0_3;
            temp_v1->unk_28 = temp_v0_3;
            temp_v1->unk_26 = temp_v0_3;
            temp_v0_4 = ((S_80174910_8 *)(((S_80174910_6 *)arg0)->unk_08))->unk_0A;
            temp_v1->unk_0C = arg1;
            temp_v1->unk_34 = var_s1;
            temp_v1->unk_30 = temp_v0_4;
            temp_v1->unk_2E = temp_v0_4;
            temp_v1->unk_2C = temp_v0_4;
            temp_v1_2 = ((S_80174910_0 *)temp_v0)->unk_0C;
            temp_v1_2->unk_1E = 0x1000;
            temp_v1_2->unk_1C = 0x1000;
            func_8004491C(temp_v0, &D_80045340);
            if (var_s1 == 0) {
                var_v1 = ((S_80174910_9 *)(((S_80174910_6 *)arg0)->unk_0C))->unk_08;
                do {
                    entry_flags = *var_v1;
                    var_v1 += 0xC;
                } while (entry_flags & 0x20);
                var_v1 -= 0xC;
                ASM_KEEP(var_v1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                temp_v0_6 = ((S_80174910_4 *)var_v1)->unk_06;
                sp10[3] = 1;
                sp10[2] = 0x10;
                sp10[0] = 0;
                sp10[1] = (s16) ((u32) (((temp_v0_6 & 0xFFC0) - 0x40) & 0xFFFF) >> 6);
                do {
                    func_800672D8((s16 *) sp10, callback_page + 0x5F70);
                    temp_v0_5 = sp10[0] + 0x10;
                    sp10[0] = temp_v0_5;
                } while (temp_v0_5 < 0x100);
            }
            temp_v1_3 = ((S_80174910_0 *)temp_v0)->unk_0C;
            temp_v1_3->unk_12 = (u16) (temp_v1_3->unk_12 - 0x40);
            ((S_80174910_10 *)(((S_80174910_7 *)temp_v0)->unk_0C))->unk_10 = 0x20;
        }
        var_s1 += 1;
    } while (var_s1 < 3);
}

/* MECHANISM: Explicit object and 0x80170000 page bases restore the s4/s3 holds
   and the exact 0x38 frame; one four-halfword array preserves every call-visible slot.
   A 32-bit outer counter removes sign extensions, and ASM_KEEP at the pointer
   decrement prevents lhu -6 folding, emitting retail's addiu -0xC; lhu +6 seam. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BC574_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800BC574_6;   /* temp_v0 in func_800BC574 */

typedef struct S_800BC574_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BC574_7;   /* ((S_800BC574_6 *)temp_v0)->unk_08 in func_800BC574 */




void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BC6CC;
extern M2C_UNK D_800F15E4;

typedef struct S_800BC574_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BC574_0;   /* temp_v0 in func_800BC574 */

typedef struct S_800BC574_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BC574_1;   /* copy_dst in func_800BC574 */

typedef struct S_800BC574_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BC574_2;   /* held_arg0 in func_800BC574 */

typedef struct S_800BC574_3 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800BC574_3;   /* held_base in func_800BC574 */

typedef struct S_800BC574_4 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800BC574_4;   /* temp_s2 in func_800BC574 */

typedef struct S_800BC574_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BC574_5;   /* (void *) tail_v0 in func_800BC574 */

s32 func_800BC574(void *arg0, s32 arg1) {
    s32 copy_value;
    S_800BC574_4 *temp_s2;
    S_800BC574_0 *temp_v0;
    S_800BC574_2 *held_arg0 = arg0;
    u8 *held_base = (u8 *) &D_80083160;
    S_800BC574_1 *copy_dst;
    register s32 held_arg1 ASM_REG("$19") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800BC6CC;
        func_8004491C(temp_v0, &D_80045340);
        temp_s2 = temp_v0->unk_0C;
        copy_dst = temp_v0->unk_08;
        copy_dst->unk_00 = (s32) held_arg0->unk_00;
        copy_dst = temp_v0->unk_08;
        copy_dst->unk_04 = (s32) held_arg0->unk_04;
        copy_dst = temp_v0->unk_08;
        copy_value = held_arg0->unk_08;
        {
            register s32 narrowed_arg1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            narrowed_arg1 = (s16) held_arg1;
            copy_dst->unk_08 = copy_value;
            ((S_800BC574_7 *)(((S_800BC574_6 *)temp_v0)->unk_08))->unk_0C = (s32) (func_80064584(narrowed_arg1 + ((S_800BC574_3 *)held_base)->unk_C8) * 0x30);
            ((S_800BC574_7 *)(((S_800BC574_6 *)temp_v0)->unk_08))->unk_10 = (s32) (func_800644B8(narrowed_arg1 + ((S_800BC574_3 *)held_base)->unk_C8) * 0x30);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        }
        {
            register s32 tail_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

            tail_v0 = 0x1000;
            temp_s2->unk_1E = tail_v0;
            temp_s2->unk_1C = tail_v0;
            tail_v0 = (s32) temp_v0->unk_08;
            tail_v0 = ((S_800BC574_5 *)((void *) tail_v0))->unk_0C;
            if (tail_v0 > 0) {
                temp_s2->unk_14 = (u16) (temp_s2->unk_14 | 1);
            }
            tail_v0 = 0x808080;
            copy_dst = &D_800F15E4;
            temp_s2->unk_00 = copy_dst;
            copy_dst = (void *) copy_dst->unk_04;
            temp_s2->unk_04 = 0;
            temp_s2->unk_05 = 0;
            temp_s2->unk_0C = tail_v0;
            temp_s2->unk_08 = (s32) copy_dst;
        }
    }
    return 0;
}
/* MECHANISM: Split full-width and narrowed arg1 live ranges let dead s0 be reused after the three-word copy while s4 holds D_80083160.
   Guarded v1/v0 overwrite chains reproduce the copy and tail loads; a zero-word fence keeps the second scaled-result store ordered.
   The rebuilt shape is exact at 2.7.2-cdk-G0; 2.95.2-G0 retained six pure-reorder divergences. */

/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B3FB8_arg0.h"


typedef struct S_800B3FB8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B3FB8_4;   /* temp_s3 in func_800B3FB8 */

typedef struct S_800B3FB8_5 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x14];
    void * unk_30;
    u8 pad_34[0x14];
    void * unk_48;
} S_800B3FB8_5;   /* (temp_s1 + arg0->unk_5C) in func_800B3FB8 */

typedef struct S_800B3FB8_6 {
    void * unk_00;
} S_800B3FB8_6;   /* temp_s1 + ((Rec_func_800B3FB8_arg0 *)arg0)->unk_5C in func_800B3FB8 */

typedef struct S_800B3FB8_7 {
    u8 pad_00[0x8];
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800B3FB8_7;   /* ((S_800B3FB8_4 *)temp_s3)->unk_04 in func_800B3FB8 */


s32 func_8004DC14();                    /* extern */

typedef struct S_800B3FB8_0 {
    s32 unk_00;
} S_800B3FB8_0;   /* temp_s3 in func_800B3FB8 */


typedef struct S_800B3FB8_2 {
    s32 unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    s32 unk_10;
} S_800B3FB8_2;   /* arg1 in func_800B3FB8 */

void func_800B3FB8(Rec_func_800B3FB8_arg0 *arg0, S_800B3FB8_2 *arg1, s32 arg2) {
    s32 temp_s1;
    S_800B3FB8_0 *temp_s3;

    temp_s1 = arg2 * 4;
    temp_s3 = ((S_800B3FB8_6 *)(temp_s1 + ((Rec_func_800B3FB8_arg0 *)arg0)->unk_5C))->unk_00;
    temp_s3->unk_00 = (s32) arg0->unk_20;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_08.s = (u16) arg1->unk_04;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_0A.s = (u16) arg1->unk_06;
    temp_s3 = ((S_800B3FB8_5 *)((temp_s1 + arg0->unk_5C)))->unk_30;
    temp_s3->unk_00 = (s32) arg1->unk_10;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_08.s = (u16) arg1->unk_08;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_0A.s = (u16) arg1->unk_0A;
    temp_s3 = ((S_800B3FB8_5 *)((temp_s1 + arg0->unk_5C)))->unk_18;
    temp_s3->unk_00 = func_8004DC14(arg1->unk_00, 1);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_08.s = (u16) arg1->unk_0C;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_0A.s = (u16) arg1->unk_0E;
    temp_s3 = ((S_800B3FB8_5 *)((temp_s1 + arg0->unk_5C)))->unk_48;
    temp_s3->unk_00 = func_8004DC14(arg1->unk_00, 0x90);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_08.u = (s16) (arg1->unk_0C - 1);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)temp_s3)->unk_04))->unk_0A.u = (s16) (arg1->unk_0E + 1);
}

/* MECHANISM: Model arg2*4 as an integer byte displacement, avoiding scaled-pointer slls.
   Reuse one slot-pointer local across all four regions so gcc holds it in s3.
   That restores the retail s2/s1/s3/s0 hold set and the exact 0x28 frame. */

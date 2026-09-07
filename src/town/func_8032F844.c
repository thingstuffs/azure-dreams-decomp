#include "common.h"
#include "records/Rec_D_80016000.h"


typedef s32 (*TownCallback)(void *, void *, s32);

typedef struct S_8001A044_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001A044_0;   /* page in func_8001A044 */

typedef struct S_8001A044_1 {
    void * unk_00;
} S_8001A044_1;   /* l1_v0 in func_8001A044 */

typedef struct S_8001A044_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001A044_2;   /* l1_v1 in func_8001A044 */

typedef struct S_8001A044_3 {
    s32 unk_00;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_8001A044_3;   /* temp_s0 in func_8001A044 */

typedef struct S_8001A044_4 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8001A044_4;   /* temp_v0_2_ptr in func_8001A044 */


typedef struct S_8001A044_6 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001A044_6;   /* page2 in func_8001A044 */

typedef struct S_8001A044_7 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    s32 unk_04;
} S_8001A044_7;   /* temp_v0_4 in func_8001A044 */

typedef struct S_8001A044_8 {
    u8 pad_00[0x18];
    s32 * unk_18;
} S_8001A044_8;   /* temp_v0_3 in func_8001A044 */

typedef struct S_8001A044_9 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A044_9;   /* var_v1 in func_8001A044 */

typedef struct S_8001A044_10 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x18];
    void * unk_30;
} S_8001A044_10;   /* ((S_8001A044_0 *)page)->unk_6000 in func_8001A044 */

typedef struct S_8001A044_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001A044_11;   /* (temp_v0_2 * 0x10) +
                                    (u8 *)((S_8001A044_3 *)temp_s0)->unk_10 in func_8001A044 */

typedef struct S_8001A044_12 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001A044_12;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_8001A044 */

typedef struct S_8001A044_13 {
    u8 pad_00[0x30];
    void * unk_30;
} S_8001A044_13;   /* ((S_8001A044_6 *)page2)->unk_6000 in func_8001A044 */


extern void *func_800196E4(void *, void *);
extern void *func_8001976C(void *, void *, s32, s32);
extern s32 func_80019F94(void *, s32);

extern u8 D_80016000[];
extern u8 D_80016094[];
extern u8 D_800160A0[];
extern u8 D_800160CC[];
extern u8 D_800160FC[];
extern u8 D_8001DC10[];

void func_8001A044(s32 *arg0, void *arg1, void *arg2)
{
    register u8 *var_v1;
    s32 *var_a2;
    s32 temp_a0;
    s32 temp_a1;
    register s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    register s32 temp_v1;
    s32 temp_v1_2;
    register s32 var_a0;
    s32 var_a2_2;
    register s32 var_s1;
    s32 var_v0;
    S_8001A044_3 *temp_s0;
    S_8001A044_4 *temp_v0_2_ptr;
    register void *temp_v0_3;
    register void *temp_v0_4;
    register u8 *page;
    register u8 *page2;
    register void *root1;
    TownCallback temp_callback;
    void *l1_v0;
    void *l1_v1;

    {
    u8 *next_s3;
    u8 *current;

    var_s1 = 0;
    current = arg1;
    if (*arg0 != 0) {
        page = (u8 *)0x80010000;
        goto first_scale;
loop_2:
        var_v0 = var_s1 * 8;
        goto loop_body;
first_scale:
        var_v0 = var_s1 * 8;
loop_body:
        temp_v0 = *(s32 *)(((var_v0 - var_s1) * 4) + (u8 *)arg0);
        temp_a1 = temp_v0 >> 0x13;
        temp_v0 = temp_v0 >> 0x17;
        temp_a0 = temp_v0 & 1;
        l1_v1 = ((S_8001A044_10 *)(((S_8001A044_0 *)page)->unk_6000))->unk_30;
        l1_v0 = (void *)(temp_a0 * 4);
        l1_v0 = (void *)((u32)l1_v0 + (u32)l1_v1);
        l1_v1 = (void *)(temp_a1 & 0x7E0);
        l1_v0 = ((S_8001A044_1 *)l1_v0)->unk_00;
        l1_v1 = (void *)((u32)l1_v1 + (u32)l1_v0);
        if (((S_8001A044_2 *)l1_v1)->unk_0A != 0) {
            temp_s0 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
            goto process_record;
        }
        if (temp_a0 != 0) {
            temp_s0 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
            goto process_record;
        }
        goto block_9;
process_record:
            if (temp_s0->unk_08 != 0) {
                ((S_8001A044_10 *)(((S_8001A044_0 *)page)->unk_6000))->unk_14 = var_s1;
                temp_v0_2 = func_80019F94(temp_s0, temp_a1);
                temp_a2 = (temp_s0->unk_00 & ~0xFF) |
                           (temp_v0_2 & 0xFF);
                temp_s0->unk_00 = temp_a2;
                next_s3 = func_8001976C(current,
                      (void *)((S_8001A044_11 *)((temp_v0_2 * 0x10) +
                                    (u8 *)temp_s0->unk_10))->unk_08,
                      temp_a2, var_s1);
                if ((next_s3 - 0x14) != current) {
                    func_800196E4(D_8001DC10, temp_s0);
                    temp_s0->unk_04 = current;
                    current = next_s3;
                }
            } else {
                temp_v0_2_ptr = (void *)((u32)(var_s1 * 0x1C) +
                                         (u32)arg0);
                temp_v0_2_ptr->unk_04 = current;
                current = func_8001976C(current,
                    (void *)temp_v0_2_ptr->unk_10, 0, var_s1);
            }
block_9:
        var_s1 += 1;
        var_v0 = var_s1 * 8;
        if (*(s32 *)(((var_v0 - var_s1) * 4) + (u8 *)arg0) != 0) {
            goto loop_2;
        }
    }

    root1 = ((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20;
    (*(TownCallback *)((u8 *)root1 + 0x168))
        (D_80016094, D_800160A0,
         (u32)(current - (u8 *)arg1) / 20);
    }

    var_a0 = 0;
    var_a2 = (s32 *)((u8 *)arg2 - 4);
    var_s1 = var_a0;
    if (*arg0 != 0) {
        page2 = (u8 *)0x80010000;
loop_11:
        temp_v1 = *(s32 *)((((var_s1 * 8) - var_s1) * 4) + (u8 *)arg0);
        temp_v0 = temp_v1 >> 0x18;
        temp_a1_2 = temp_v0 & 0x3F;
        if (temp_a1_2 != var_a0) {
            temp_a0 = temp_v1 >> 0x15;
            temp_v0_3 = ((S_8001A044_13 *)(((S_8001A044_6 *)page2)->unk_6000))->unk_30;
            temp_v0 = temp_a0 & 4;
            temp_v0_4 = (void *)((u32)temp_v0 + (u32)temp_v0_3);
            temp_v1_2 = temp_a1_2 << 5;
            temp_v0_4 = ((S_8001A044_7 *)temp_v0_4)->unk_00.p;
            temp_v0_3 = (void *)((u32)temp_v1_2 + (u32)temp_v0_4);
            var_a2 += 1;
            ((S_8001A044_8 *)temp_v0_3)->unk_18 = var_a2;
            *var_a2 = 0;
            var_a0 = temp_a1_2;
        }
        temp_v0_4 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
        temp_v1_2 = ((S_8001A044_7 *)temp_v0_4)->unk_04;
        if ((temp_v1_2 != 0) &&
            !((((S_8001A044_7 *)temp_v0_4)->unk_00.i >> 0xF) & 1)) {
            *var_a2 = temp_v1_2;
            var_a2 += 1;
            *var_a2 = 0;
        }
        var_s1 += 1;
        if (*(s32 *)((var_s1 * 0x1C) + (u8 *)arg0) != 0) {
            goto loop_11;
        }
    }

    (*(TownCallback *)((u8 *)(((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x168))
        (D_80016094, D_800160CC, ((u32)var_a2 - (u32)arg2) >> 2);

    var_v1 = D_8001DC10;
    var_a2_2 = 1;
    if (((S_8001A044_9 *)var_v1)->unk_04 != 0) {
        do {
            var_v1 += 8;
            var_a2_2 += 1;
        } while (((S_8001A044_9 *)var_v1)->unk_04 != 0);
    }
    temp_callback = (*(TownCallback *)((u8 *)(((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x168));
    temp_callback(D_80016094, D_800160FC, var_a2_2);
}

#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef s32 (*TownCallback)(void *, void *, s32);

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
    void *temp_s0;
    void *temp_v0_2_ptr;
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
        l1_v1 = FIELD(FIELD(page, void *, 0x6000), void *, 0x30);
        l1_v0 = (void *)(temp_a0 * 4);
        l1_v0 = (void *)((u32)l1_v0 + (u32)l1_v1);
        l1_v1 = (void *)(temp_a1 & 0x7E0);
        l1_v0 = FIELD(l1_v0, void *, 0);
        l1_v1 = (void *)((u32)l1_v1 + (u32)l1_v0);
        if (FIELD(l1_v1, s16, 0xA) != 0) {
            temp_s0 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
            goto process_record;
        }
        if (temp_a0 != 0) {
            temp_s0 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
            goto process_record;
        }
        goto block_9;
process_record:
            if (FIELD(temp_s0, s32, 8) != 0) {
                FIELD(FIELD(page, void *, 0x6000), s32, 0x14) = var_s1;
                temp_v0_2 = func_80019F94(temp_s0, temp_a1);
                temp_a2 = (FIELD(temp_s0, s32, 0) & ~0xFF) |
                           (temp_v0_2 & 0xFF);
                FIELD(temp_s0, s32, 0) = temp_a2;
                next_s3 = func_8001976C(current,
                      (void *)FIELD((temp_v0_2 * 0x10) +
                                    (u8 *)FIELD(temp_s0, void *, 0x10),
                                    s32, 8),
                      temp_a2, var_s1);
                if ((next_s3 - 0x14) != current) {
                    func_800196E4(D_8001DC10, temp_s0);
                    FIELD(temp_s0, void *, 4) = current;
                    current = next_s3;
                }
            } else {
                temp_v0_2_ptr = (void *)((u32)(var_s1 * 0x1C) +
                                         (u32)arg0);
                FIELD(temp_v0_2_ptr, void *, 4) = current;
                current = func_8001976C(current,
                    (void *)FIELD(temp_v0_2_ptr, s32, 0x10), 0, var_s1);
            }
block_9:
        var_s1 += 1;
        var_v0 = var_s1 * 8;
        if (*(s32 *)(((var_v0 - var_s1) * 4) + (u8 *)arg0) != 0) {
            goto loop_2;
        }
    }

    root1 = FIELD(FIELD(D_80016000, void *, 0), void *, 0x20);
    FIELD(root1, TownCallback, 0x168)
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
            temp_v0_3 = FIELD(FIELD(page2, void *, 0x6000), void *, 0x30);
            temp_v0 = temp_a0 & 4;
            temp_v0_4 = (void *)((u32)temp_v0 + (u32)temp_v0_3);
            temp_v1_2 = temp_a1_2 << 5;
            temp_v0_4 = FIELD(temp_v0_4, void *, 0);
            temp_v0_3 = (void *)((u32)temp_v1_2 + (u32)temp_v0_4);
            var_a2 += 1;
            FIELD(temp_v0_3, s32 *, 0x18) = var_a2;
            *var_a2 = 0;
            var_a0 = temp_a1_2;
        }
        temp_v0_4 = (void *)((u32)(var_s1 * 0x1C) + (u32)arg0);
        temp_v1_2 = FIELD(temp_v0_4, s32, 4);
        if ((temp_v1_2 != 0) &&
            !((FIELD(temp_v0_4, s32, 0) >> 0xF) & 1)) {
            *var_a2 = temp_v1_2;
            var_a2 += 1;
            *var_a2 = 0;
        }
        var_s1 += 1;
        if (*(s32 *)((var_s1 * 0x1C) + (u8 *)arg0) != 0) {
            goto loop_11;
        }
    }

    FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20),
          TownCallback, 0x168)
        (D_80016094, D_800160CC, ((u32)var_a2 - (u32)arg2) >> 2);

    var_v1 = D_8001DC10;
    var_a2_2 = 1;
    if (FIELD(var_v1, s32, 4) != 0) {
        do {
            var_v1 += 8;
            var_a2_2 += 1;
        } while (FIELD(var_v1, s32, 4) != 0);
    }
    temp_callback = FIELD(FIELD(FIELD(D_80016000, void *, 0),
                                void *, 0x20), TownCallback, 0x168);
    temp_callback(D_80016094, D_800160FC, var_a2_2);
}

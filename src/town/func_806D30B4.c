#include "common.h"

typedef struct S_800168B4_0 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_800168B4_0;   /* D_80016000 in func_800168B4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef void (*ReportFunc)(void *, void *, u32);

typedef struct S_800168B4_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800168B4_1;   /* (temp_a1 & 0x7E0) +
                          *((s32 *)((u8 *)D_80016000->unk_30 +
                                    (temp_a3 * 4))) in func_800168B4 */

typedef struct S_800168B4_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800168B4_2;   /* D_80016000 in func_800168B4 */

typedef struct S_800168B4_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800168B4_3;   /* var_v1 in func_800168B4 */


typedef struct TownEntry {
    s32 flags;
    s32 link;
    s32 active;
    s32 pad_c;
    u8 * volatile choices;
    s32 pad_14;
    s32 pad_18;
} TownEntry;

typedef struct TownBucket {
    u8 pad_0[0x18];
    s32 *out;
    u8 pad_1c[4];
} TownBucket;

extern s32 func_80016818(void *, s32);
extern s32 func_8001643C(s32, s32, s32, s32);
extern void func_800163B8(void *, void *);

extern S_800168B4_0 *D_80016000;
extern u8 D_80016178[0x10];
extern u8 D_80016184[0x10];
extern u8 D_800161B0[0x10];
extern u8 D_800161E0[0x10];
extern u8 D_80016F88[];
extern s32 D_80016FC8;
extern s32 D_80016FCC;

void func_800168B4(s32 *arg0, s32 arg1, s32 *arg2)
{
    s32 var_s2;
    s32 var_s3;
    s32 temp_a1;
    s32 temp_a3;

    var_s3 = 0;
    var_s2 = arg1;
    if (*arg0 != 0) {
        TownEntry *var_s0 = (TownEntry *)arg0;

        do {
            s32 temp_v0 = var_s0->flags;

            temp_a1 = temp_v0 >> 19;
            temp_a3 = (temp_v0 >> 23) & 1;
            if ((((S_800168B4_1 *)((temp_a1 & 0x7E0) +
                          *((s32 *)((u8 *)D_80016000->unk_30 +
                                    (temp_a3 * 4)))))->unk_0A != 0) ||
                (temp_a3 != 0)) {
                if (var_s0->active != 0) {
                    s32 call_result = func_80016818(var_s0, temp_a1);
                    s32 temp_a2 =
                        (var_s0->flags & ~0xFF) | (call_result & 0xFF);
                    s32 result;

                    var_s0->flags = temp_a2;
                    result = func_8001643C(
                        var_s2,
                        ((s32 *)var_s0->choices)[(call_result << 2) + 2],
                        temp_a2, var_s3);
                    if ((result - 0x14) == var_s2) {
                        goto loop_join;
                    }
                    func_800163B8(&D_80016FC8, var_s0);
                    var_s0->link = var_s2;
                    var_s2 = result;
                    goto loop_join;
                } else {
                    var_s0->link = var_s2;
                    var_s2 = func_8001643C(
                        var_s2, (s32)var_s0->choices, 0, var_s3);
                }
            }
loop_join:
            var_s0++;
            var_s3++;
        } while (var_s0->flags != 0);
    }

    (*(ReportFunc *)((u8 *)(((S_800168B4_2 *)D_80016000)->unk_20) + 0x168))(
        D_80016178, D_80016184, ((u32)var_s2 - (u32)arg1) / 20U);

    {
        s32 var_t0 = 0;
        s32 *var_a2 = arg2 - 1;

        if (*arg0 != 0) {
            TownEntry *var_a0 = (TownEntry *)arg0;

            do {
                s32 temp_v1 = var_a0->flags;

                temp_a1 = (temp_v1 >> 24) & 0x3F;
                temp_a3 = temp_v1 >> 21;

                if (temp_a1 != var_t0) {
                    s32 **table;
                    s32 *base;

                    var_a2++;
                    var_t0 = temp_a1;
                    table = (s32 **)D_80016000->unk_30;
                    base = table[(temp_a3 & 4) >> 2];
                    ((TownBucket *)base)[var_t0].out = var_a2;
                    *var_a2 = 0;
                }
                temp_v1 = var_a0->link;
                if ((temp_v1 != 0) &&
                    (((var_a0->flags >> 15) & 1) == 0)) {
                    *var_a2 = temp_v1;
                    var_a2++;
                    *var_a2 = 0;
                }
                var_a0++;
            } while (var_a0->flags != 0);
        }

        (*(ReportFunc *)((u8 *)(((S_800168B4_2 *)D_80016000)->unk_20) + 0x168))(
            D_80016178, D_800161B0,
            ((u32)var_a2 - (u32)arg2) >> 2);
    }

    {
        s32 active = D_80016FCC;
        u8 *var_v1;
        s32 var_a2;

        if (active != 0) {
            var_v1 = D_80016F88 + 0x40;
            var_a2 = 1;
        } else {
            var_v1 = &D_80016F88[0x40];
            var_a2 = 1;
        }
        if (active != 0) {
            do {
                var_v1 += 8;
                var_a2++;
            } while (((S_800168B4_3 *)var_v1)->unk_04 != 0);
        }

        (*(ReportFunc *)((u8 *)(((S_800168B4_2 *)D_80016000)->unk_20) + 0x168))(
            D_80016178, D_800161E0, var_a2);
    }
}

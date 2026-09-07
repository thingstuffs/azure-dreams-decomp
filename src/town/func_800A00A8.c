#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083160[];

typedef struct S_8009D808_0 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_0;   /* arg0 in func_8009D808 */

typedef struct S_8009D808_1 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_1;   /* arg2 in func_8009D808 */

typedef struct S_8009D808_2 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_2;   /* arg1 in func_8009D808 */

typedef struct S_8009D808_3 {
    s16 unk_00;
    s16 unk_02;
} S_8009D808_3;   /* var_t0 in func_8009D808 */

void func_8009D808(void *arg0, S_8009D808_2 *arg1, S_8009D808_1 *arg2) {
    s16 temp_a3;
    s16 temp_a3_2;
    s16 temp_a3_3;
    s16 temp_a3_4;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_t1;
    u8 *base;
    u8 *temp_t2;
    void *var_t0;

    temp_v0 = ((S_8009D808_0 *)arg0)->unk_00;
    arg2->unk_00 = temp_v0;
    arg1->unk_00 = temp_v0;
    temp_v0_2 = ((S_8009D808_0 *)arg0)->unk_02;
    arg2->unk_02 = temp_v0_2;
    arg1->unk_02 = temp_v0_2;
    base = D_80083160;
    temp_t2 = base + 0x1DC;
    if ((s16) arg1->unk_00 < 0) {
        arg2->unk_00 = 0U;
        arg1->unk_00 = 0U;
    }
    if ((s16) arg1->unk_02 < 0) {
        arg2->unk_02 = 0U;
        arg1->unk_02 = 0U;
    }
    temp_t1 = 0x40;
    var_t0 = arg0;
    do {
        temp_a3 = ((S_8009D808_3 *)var_t0)->unk_00;
        if ((s16) arg1->unk_00 < temp_a3) {
            arg1->unk_00 = (u16) ((S_8009D808_3 *)var_t0)->unk_00;
            temp_v1 = (temp_t1 << ((s16 *)temp_t2)[0xA]) - 1;
            if (temp_v1 < temp_a3) {
                arg1->unk_00 = (u16) temp_v1;
            }
        }
        temp_a3_2 = ((S_8009D808_3 *)var_t0)->unk_00;
        if ((s16) arg2->unk_00 > temp_a3_2) {
            arg2->unk_00 = (u16) ((S_8009D808_3 *)var_t0)->unk_00;
            if (temp_a3_2 < 0) {
                arg2->unk_00 = 0U;
            }
        }
        temp_a3_3 = ((S_8009D808_3 *)var_t0)->unk_02;
        if ((s16) arg1->unk_02 < temp_a3_3) {
            arg1->unk_02 = (u16) ((S_8009D808_3 *)var_t0)->unk_02;
            temp_v1_2 = (temp_t1 << ((s16 *)temp_t2)[0xB]) - 1;
            if (temp_v1_2 < temp_a3_3) {
                arg1->unk_02 = (u16) temp_v1_2;
            }
        }
        temp_a3_4 = ((S_8009D808_3 *)var_t0)->unk_02;
        if ((s16) arg2->unk_02 > temp_a3_4) {
            arg2->unk_02 = (u16) ((S_8009D808_3 *)var_t0)->unk_02;
            if (temp_a3_4 < 0) {
                arg2->unk_02 = 0U;
            }
        }
        var_t0 += 8;
    } while ((s32) var_t0 < (s32) (arg0 + 0x20));
}

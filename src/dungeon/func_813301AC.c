#include "common.h"
#include "m2c_compat.h"

typedef struct S_801671AC_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_801671AC_0;   /* arg2 in func_801671AC */

typedef struct S_801671AC_1_pre {
    u16 unk_00;
} S_801671AC_1_pre;   /* the 0x2 bytes before obj in func_801671AC, addressed as obj[-1] */

typedef struct S_801671AC_1 {
    u8 pad_00[0x18];
    u16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
} S_801671AC_1;   /* obj in func_801671AC */


void func_80167354(void) __attribute__((noreturn));
extern M2C_UNK D_800814A0;

void func_801671AC(void *arg0, void *arg1, void *arg2) {
    void *obj;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 var_a1;
    s32 var_t0;
    s32 var_t1;
    u16 count;
    u16 flags;
    u16 temp_v0;

    flags = ((S_801671AC_0 *)arg2)->unk_14;
    ASM_CLOBBER("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = arg0;
    ASM_KEEP(obj);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_801671AC_0 *)arg2)->unk_14 = (u16) (flags & 0xFF7F);
    count = ((S_801671AC_1 *)obj)->unk_18;
    temp_v0 = ((S_801671AC_1 *)obj)->unk_1C;
    count--;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0++;
    ((S_801671AC_1 *)obj)->unk_1C = temp_v0;
    ((S_801671AC_1 *)obj)->unk_18 = count;
    if ((s16) temp_v0 == 3) {
        ((S_801671AC_1 *)obj)->unk_1C = 0U;
    }
    var_t1 = 0x30;
    var_t0 = var_t1;
    temp_v1 = (s16) ((S_801671AC_1 *)obj)->unk_1C;
    var_a1 = 0x30;
    if (temp_v1 == 0) {
        var_a1 = 0x54;
    }
    if (temp_v1 == 1) {
        var_t0 = 0x54;
    }
    if (temp_v1 == 2) {
        var_t1 = 0x54;
    }
    temp_v1_2 = (s16) ((S_801671AC_1 *)obj)->unk_18;
    if (temp_v1_2 < 0x14) {
        ((S_801671AC_0 *)arg2)->unk_0C = (s8) ((var_a1 * temp_v1_2) / 20);
        ((S_801671AC_0 *)arg2)->unk_0D = (s8) ((var_t0 * (s16) ((S_801671AC_1 *)obj)->unk_18) / 20);
        ((S_801671AC_0 *)arg2)->unk_0E = (s8) ((var_t1 * (s16) ((S_801671AC_1 *)obj)->unk_18) / 20);
        func_80167354();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_801671AC_0 *)arg2)->unk_0C = (s8) ((var_a1 * (0x1E - temp_v1_2)) / 10);
    ((S_801671AC_0 *)arg2)->unk_0D = (s8) ((var_t0 * (0x1E - (s16) ((S_801671AC_1 *)obj)->unk_18)) / 10);
    ((S_801671AC_0 *)arg2)->unk_0E = (s8) ((var_t1 * (0x1E - (s16) ((S_801671AC_1 *)obj)->unk_18)) / 10);
    if ((s16) ((S_801671AC_1 *)obj)->unk_18 <= 0) {
        (*(u16 *)((u8 *)obj + -2)) = (u16) (((S_801671AC_1_pre *)obj)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

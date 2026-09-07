/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_808B3620_4 {
    u8 pad_00[0x64];
    union { M2C_UNK (*s)(u8 *, u8 *, s32, s8 *); M2C_UNK (*u)(u8 *, u8 *, s32); } unk_64;   /* accessed as both */
} S_808B3620_4;   /* *(volatile void **)(D_A0700000 + 0xF58) in func_808B3620 */


typedef struct S_808B3620_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_808B3620_0;   /* var_a2 in func_808B3620 */

typedef struct S_808B3620_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_808B3620_1;   /* var_a3 in func_808B3620 */

typedef struct S_808B3620_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_808B3620_2;   /* held_arg0 in func_808B3620 */

typedef struct S_808B3620_3 {
    u8 pad_00[0x6C];
    M2C_UNK (*unk_6C)(s32);
} S_808B3620_3;   /* *(volatile void **)(D_A0700000 + 0xF58) in func_808B3620 */

extern u8 D_A0700000[];
extern u8 D_A0700150[];
extern u8 D_A0700158[];
extern u8 D_A0700168[];
extern u8 D_A070017C[];

void func_808B3620(s8 *arg0) {
    s8 *base;
    s8 *held_arg0 = arg0;
    s32 *var_a3 = (s32 *)(D_A0700000 + 0xF40);
    s32 *var_a2 = (s32 *)held_arg0;
    s32 *end = (s32 *)held_arg0 + 12;
    s32 temp_v0;
    s32 temp_v1;
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_a1;

    do {
        ASM_KEEP_NV(var_a3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v0 = ((S_808B3620_0 *)var_a2)->unk_00;
        ASM_KEEP(temp_v0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v1 = ((S_808B3620_0 *)var_a2)->unk_04;
        ASM_KEEP(temp_v1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_a0 = ((S_808B3620_0 *)var_a2)->unk_08;
        temp_a1 = ((S_808B3620_0 *)var_a2)->unk_0C;
        ((S_808B3620_1 *)var_a3)->unk_00 = temp_v0;
        ((S_808B3620_1 *)var_a3)->unk_04 = temp_v1;
        ((S_808B3620_1 *)var_a3)->unk_08 = temp_a0;
        ((S_808B3620_1 *)var_a3)->unk_0C = temp_a1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        var_a2 += 4;
        ASM_KEEP(var_a2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        var_a3 += 4;
    } while (var_a2 != end);
    ((S_808B3620_1 *)var_a3)->unk_00 = ((S_808B3620_0 *)var_a2)->unk_00;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    base = D_A0700000 + 0x144;
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.s(base, D_A0700150, ((S_808B3620_2 *)held_arg0)->unk_08, var_a3);
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.u(base, D_A0700158, *(s32 *)(D_A0700000 + 0xF48));
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.u(D_A0700168, D_A070017C, 0x30);
    ((S_808B3620_3 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_6C(0);
}

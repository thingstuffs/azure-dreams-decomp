/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C9ED0();                         /* extern */
M2C_UNK func_800C9ED4();                         /* extern */
extern void (*D_800D65D8[])(void *, void *, M2C_UNK);

typedef struct S_800C9DB8_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800C9DB8_0;   /* arg1 in func_800C9DB8 */

typedef struct S_800C9DB8_1 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x10];
    s16 unk_84;
    s16 unk_86;
    u8 pad_88[0x4];
    s16 unk_8C;
    s16 unk_8E;
} S_800C9DB8_1;   /* arg0 in func_800C9DB8 */

void func_800C9DB8(S_800C9DB8_1 *arg0, S_800C9DB8_0 *arg1, M2C_UNK arg2) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s32 temp_v0_4;
    s32 temp_v1_4;
    s32 temp_a0_4;
    s32 temp_v1;
    s32 var_s1;
    register s32 var_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 tail_value;

    var_s2 = 0x10;
    ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s2 -= 1;
loop_1:
    var_s1 = 0;
    if (var_s2 > 0) {
        var_s1 = func_800374F4(3) & 0xFFFF;
        if (var_s1 == 1) {
            temp_v1 = func_800374F4(4) & 0xFFFF;
            if (temp_v1 == 0) {
                temp_a0 = arg0->unk_8C;
                var_s2 -= 1;
                if (arg1->unk_02 < (arg0->unk_84 + temp_a0)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    tail_value = 0x400;
                    ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_800C9ED0(temp_a0);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == var_s1) {
                temp_a0_2 = arg0->unk_8E;
                var_s2 -= 1;
                if (arg1->unk_06 < (arg0->unk_86 + temp_a0_2)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    arg0->unk_72 = 0;
                    func_800C9ED4(temp_a0_2);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == 2) {
                temp_a0_3 = arg1->unk_02;
                var_s2 -= 1;
                if ((arg0->unk_84 - arg0->unk_8C) < temp_a0_3) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    tail_value = 0xC00;
                    ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_800C9ED0(temp_a0_3);
                    return;
                }
                goto loop_1;
            }
            temp_v0_4 = arg0->unk_86;
            temp_v1_4 = arg0->unk_8E;
            temp_a0_4 = arg1->unk_06;
            var_s2 -= 1;
            if ((temp_v0_4 - temp_v1_4) < temp_a0_4) {
                var_s2 += 1;
                ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                arg0->unk_72 = 0x800;
                goto block_17;
            }
            goto loop_1;
        }
        /* Duplicate return node #18. Try simplifying control flow for better match */
        goto block_17;
    }
block_17:
    {
        register void *call_arg0 ASM_REG("$4") = arg0;   /* MATCH pin: keeps a statement from moving across a call/branch */
        void (**table)(void *, void *, M2C_UNK) = D_800D65D8;

        ASM_KEEP(table);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        table[var_s1](call_arg0, arg1, arg2);
    }
}

/* MECHANISM: Retail separates the one-time preheader decrement from the loop
   target; later decrements occupy branch-back delay slots. A pinned s2 counter,
   split loads and a0/v0 dispatch bases hold its ABI; tied LEAD28 pins preserve
   the two dead v0 tail values, with the middle halfword store as its jump slot. */

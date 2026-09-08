/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800C9B44_arg0.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C9ED0();                         /* extern */
M2C_UNK func_800C9ED4();                         /* extern */
extern void (*D_800D65D8[])(void *, void *, M2C_UNK);



void func_800C9DB8(Rec_func_800C9B44_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s32 temp_v0_4;
    s32 temp_v1_4;
    s32 temp_a0_4;
    s32 temp_v1;
    s32 var_s1;
    register s32 var_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 tail_value;

    var_s2 = 0x10;
    ASM_KEEP(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
                if (arg1->unk_00.at02_s16.v < (arg0->unk_84 + temp_a0)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    tail_value = 0x400;
                    ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800C9ED0(temp_a0);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == var_s1) {
                temp_a0_2 = arg0->unk_8E;
                var_s2 -= 1;
                if (arg1->unk_04.at02_s16.v < (arg0->unk_86 + temp_a0_2)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    arg0->unk_72 = 0;
                    func_800C9ED4(temp_a0_2);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == 2) {
                temp_a0_3 = arg1->unk_00.at02_s16.v;
                var_s2 -= 1;
                if ((arg0->unk_84 - arg0->unk_8C) < temp_a0_3) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    tail_value = 0xC00;
                    ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800C9ED0(temp_a0_3);
                    return;
                }
                goto loop_1;
            }
            temp_v0_4 = arg0->unk_86;
            temp_v1_4 = arg0->unk_8E;
            temp_a0_4 = arg1->unk_04.at02_s16.v;
            var_s2 -= 1;
            if ((temp_v0_4 - temp_v1_4) < temp_a0_4) {
                var_s2 += 1;
                ASM_KEEP(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
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
        register void *call_arg0 ASM_REG("$4") = arg0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        void (**table)(void *, void *, M2C_UNK) = D_800D65D8;

        ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table[var_s1](call_arg0, arg1, arg2);
    }
}

/* MECHANISM: Retail separates the one-time preheader decrement from the loop
   target; later decrements occupy branch-back delay slots. A pinned s2 counter,
   split loads and a0/v0 dispatch bases hold its ABI; tied LEAD28 pins preserve
   the two dead v0 tail values, with the middle halfword store as its jump slot. */

#include "common.h"

typedef struct S_800C55F4_0 {
    u8 ** unk_00;
    u8 pad_04[0x4];
    u8 ** unk_08;
} S_800C55F4_0;   /* descriptor in func_800C55F4 */

typedef struct S_800C55F4_1 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x28];
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    u32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    u32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u32 unk_80;
    u16 unk_84;
    u8 pad_86[0x3A];
    union { s32 s; volatile s32 u; } unk_C0;   /* accessed as both */
    s32 unk_C4;
    union { s32 s; volatile s32 u; } unk_C8;   /* accessed as both */
    s32 unk_CC;
    u8 pad_D0[0x44];
    s32 unk_114;
} S_800C55F4_1;   /* scratch in func_800C55F4 */

typedef struct S_800C55F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C55F4_2;   /* arg2_alias in func_800C55F4 */

typedef struct S_800C55F4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C55F4_3;   /* arg1_record in func_800C55F4 */

typedef struct S_800C55F4_4 {
    u8 unk_00;
    u8 pad_01[0x315F];
    u8 * unk_3160;
} S_800C55F4_4;   /* page_record7 in func_800C55F4 */

typedef struct S_800C55F4_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C55F4_5;   /* root in func_800C55F4 */

typedef struct S_800C55F4_6 {
    u32 unk_00;
    u16 unk_04;
} S_800C55F4_6;   /* (x << 3) + (u32)table in func_800C55F4 */

typedef struct S_800C55F4_7_pre {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x8];
} S_800C55F4_7_pre;   /* the 0xA bytes before entry in func_800C55F4, addressed as entry[-1] */

typedef struct S_800C55F4_7 {
    s8 unk_00;
} S_800C55F4_7;   /* entry in func_800C55F4 */

typedef struct S_800C55F4_8 {
    u8 pad_00[0x30];
    s16 unk_30;
    s16 unk_32;
} S_800C55F4_8;   /* arg0_pin in func_800C55F4 */

typedef struct S_800C55F4_9 {
    u8 * unk_00;
} S_800C55F4_9;   /* global_base in func_800C55F4 */

typedef struct S_800C55F4_10 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C55F4_10;   /* ((S_800C55F4_9 *)global_base)->unk_00 in func_800C55F4 */



extern s32 func_8004CECC();
extern s32 func_80064840();
extern s32 func_800649A0();
extern s32 func_80064A40();
extern s32 func_80064AE0();
extern s32 func_80064BC0();
extern s32 func_80064CF0();
extern s32 func_80064D80();
extern s32 func_80065420();
extern s32 func_80065480();
extern s32 func_80065820();
extern s32 func_8006658C();
extern s32 func_800666B8();
extern s32 func_80067F20();
extern s32 func_800C5750();
extern s32 func_800C58BC();
extern s32 func_800C5914();
extern s32 func_800C596C();

extern u8 D_80083160[];

void func_800C55F4(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 sp18[0x20];
    register u8 *arg0_pin ASM_REG("$23") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *arg1_record = arg1;
    void *arg2_alias = arg2;
    register s16 arg3_pin ASM_REG("$17") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *scratch ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 stack_arg ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *first_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *first_a1;
    void *volatile sp38;
    void *volatile sp3C;
    u8 *descriptor;
    register u8 *table ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *entry ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *scan ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *page_record7;
    u8 *root;
    u8 *old_record;
    register u8 *global_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 page_flag;
    s32 result;
    s32 entry_flag;
    u32 x;
    u32 position;
    void *call_a0;
    void *call_a2;
    void *call_a3;

    ASM_KEEP4_NV(arg0_pin, arg1_record, arg2_alias, page_record7);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg3_pin);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    stack_arg = 0x1F800000;
    stack_arg |= 0x90;
    sp38 = (void *)stack_arg;
    stack_arg = 0x1F800000;

    descriptor = (*(u8 ** *)((u8 *)arg2_alias + 8));
    stack_arg |= 0x94;
    sp3C = (void *)stack_arg;
    ASM_CLOBBER("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    table = ((S_800C55F4_0 *)descriptor)->unk_00;
    scan = ((S_800C55F4_0 *)descriptor)->unk_08;

    func_800649A0();

    page_record7 = (u8 *)0x80080000;
    first_a0 = (u8 *)0x1F800028;
    first_a1 = (u8 *)0x1F800000;
    ASM_KEEP_NV(first_a1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scratch = (u8 *)0x1F800000;

    ((S_800C55F4_1 *)scratch)->unk_30 = ((S_800C55F4_2 *)arg2_alias)->unk_1C;
    {
        u32 coord;

        coord = ((S_800C55F4_2 *)arg2_alias)->unk_1E;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        first_a1 = (u8 *)((u32)first_a1 | 0xF0);
        ASM_USE2_NV(first_a0, first_a1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ((S_800C55F4_1 *)scratch)->unk_34 = coord;
    }
    ((S_800C55F4_1 *)scratch)->unk_38 = ((S_800C55F4_2 *)arg2_alias)->unk_20;

    {
        s32 initial_value;

        initial_value = ((S_800C55F4_3 *)arg1_record)->unk_02;
        ((S_800C55F4_1 *)scratch)->unk_64 = initial_value;
        ((S_800C55F4_1 *)scratch)->unk_28 = initial_value;
        initial_value = ((S_800C55F4_3 *)arg1_record)->unk_06;
        ((S_800C55F4_1 *)scratch)->unk_68 = initial_value;
        ((S_800C55F4_1 *)scratch)->unk_2A = initial_value;
        initial_value = ((S_800C55F4_3 *)arg1_record)->unk_0A;
        ((S_800C55F4_1 *)scratch)->unk_6C = initial_value;
        ((S_800C55F4_1 *)scratch)->unk_2C = initial_value;
    }

    ((S_800C55F4_1 *)scratch)->unk_CC =
        func_80065420(first_a0, first_a1,
                     (void *)0x1F800090, (void *)0x1F800094) - arg3_pin;
    func_80064AE0(sp18);
    func_80065820((u8 *)arg2_alias + 0x16, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064840(sp18, scratch + 0x50, scratch + 0xD0);
    func_80064D80(scratch + 0xD0);
    func_80064CF0(scratch + 0xD0);
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    root = ((S_800C55F4_4 *)page_record7)->unk_3160;
    entry = scan + 0xB;
    ((S_800C55F4_1 *)scratch)->unk_20 = root + 0xB0;
    arg1_record = ((S_800C55F4_5 *)root)->unk_8D0;
    page_record7 = arg1_record + 7;
    ((S_800C55F4_2 *)arg2_alias)->unk_14 |= 0x8000;
    ASM_KEEP(page_record7);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    x = *scan;
    ((S_800C55F4_1 *)scratch)->unk_70 = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_00;
    x = ((S_800C55F4_7_pre *)entry)[-1].unk_00;
    ((S_800C55F4_1 *)scratch)->unk_78 = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_00;
    x = ((S_800C55F4_7_pre *)entry)[-1].unk_01;
    ((S_800C55F4_1 *)scratch)->unk_80 = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_00;
    x = *scan;
    ((S_800C55F4_1 *)scratch)->unk_74 = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_04;
    x = ((S_800C55F4_7_pre *)entry)[-1].unk_00;
    call_a0 = scratch + 0x70;
    ((S_800C55F4_1 *)scratch)->unk_7C = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_04;
    x = *(volatile u8 *)(entry - 9);
    call_a2 = sp38;
    call_a3 = sp3C;
    ((S_800C55F4_1 *)scratch)->unk_84 = ((S_800C55F4_6 *)((x << 3) + (u32)table))->unk_04;

    {
        s32 call_result;

        call_result = func_80065420(call_a0, arg1_record + 8,
                                    call_a2, call_a3);
        call_a0 = scratch + 0x78;
        call_a2 = sp38;
        call_a3 = sp3C;
        ((S_800C55F4_1 *)scratch)->unk_C0.s = call_result;
        call_result = func_80065420(call_a0, arg1_record + 0x10,
                                    call_a2, call_a3);
        call_a0 = scratch + 0x80;
        call_a2 = sp38;
        call_a3 = sp3C;
        ((S_800C55F4_1 *)scratch)->unk_C4 = call_result;
        call_result = func_80065420(call_a0, arg1_record + 0x18,
                                    call_a2, call_a3);
        ((S_800C55F4_1 *)scratch)->unk_C8.s = call_result;
    }

    result = func_80065480((*(s32 *)((u8 *)page_record7 + 1)),
                           (*(s32 *)((u8 *)page_record7 + 9)),
                           (*(s32 *)((u8 *)page_record7 + 0x11)));
    ((S_800C55F4_1 *)scratch)->unk_114 = result;

    if (result > 0) {
        s32 c8_value;

        ((S_800C55F4_1 *)scratch)->unk_C0.u -= arg3_pin;
        c8_value = ((S_800C55F4_1 *)scratch)->unk_C8.u;
        ((S_800C55F4_1 *)scratch)->unk_C4 -= arg3_pin;
        position = *(volatile u32 *)(scratch + 0xC0);
        ((S_800C55F4_1 *)scratch)->unk_C8.s = c8_value - arg3_pin;
        if (position < 0x1E0) {
            {
                s32 first_shade;

                first_shade = 0x100;
                first_shade -= ((S_800C55F4_8 *)arg0_pin)->unk_32;
                first_shade -=
                    (((S_800C55F4_1 *)scratch)->unk_CC - position) << 5;
                if (first_shade < 0x20) {
                    first_shade = 0x20;
                    ASM_TAILSLOT_PIN(first_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800C58BC(((S_800C55F4_8 *)arg0_pin)->unk_32, position);
                    return;
                }
                if (first_shade >= 0x100) {
                    first_shade = 0xFF;
                }
                {
                    s32 shade_arg;

                    shade_arg = (s32)(s16)first_shade;
                    ASM_KEEP_DEP_NV(shade_arg, first_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_8004CECC(((S_800C55F4_8 *)arg0_pin)->unk_30,
                                  shade_arg, 0xFF, arg1_record + 4);
                }
            }

            {
                s32 second_value;
                s32 second_shade;
                s32 second_delta;
                s32 second_height;

                second_value = 0x100;
                second_height = ((S_800C55F4_8 *)arg0_pin)->unk_32;
                ASM_KEEP_DEP_NV(scratch, second_height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                second_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                second_shade = ((S_800C55F4_1 *)scratch)->unk_C4;
                second_value -= second_height;
                second_delta -= second_shade;
                second_delta <<= 5;
                second_shade = second_value - second_delta;
                if (second_shade < 0x20) {
                    second_shade = 0x20;
                    ASM_TAILSLOT_PIN(second_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800C5914(second_value,
                                  ((S_800C55F4_8 *)arg0_pin)->unk_32);
                    return;
                }
                if (second_shade >= 0x100) {
                    second_shade = 0xFF;
                }
                {
                    s32 shade_arg;

                    shade_arg = (s32)(s16)second_shade;
                    ASM_KEEP_DEP_NV(shade_arg, second_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_8004CECC(((S_800C55F4_8 *)arg0_pin)->unk_30,
                                  shade_arg, 0xFF,
                                  arg1_record + 0xC);
                }
            }

            {
                s32 third_value;
                s32 third_shade;
                s32 third_delta;
                s32 third_height;

                third_value = 0x100;
                third_height = ((S_800C55F4_8 *)arg0_pin)->unk_32;
                ASM_KEEP_DEP_NV(scratch, third_height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                third_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                third_shade = ((S_800C55F4_1 *)scratch)->unk_C8.s;
                third_value -= third_height;
                third_delta -= third_shade;
                third_delta <<= 5;
                third_shade = third_value - third_delta;
                if (third_shade < 0x20) {
                    third_shade = 0x20;
                    ASM_TAILSLOT_PIN(third_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800C596C(third_value,
                                  ((S_800C55F4_8 *)arg0_pin)->unk_32);
                    return;
                }
                if (third_shade >= 0x100) {
                    third_shade = 0xFF;
                }
                {
                    s32 shade_arg;

                    shade_arg = (s32)(s16)third_shade;
                    ASM_KEEP_DEP_NV(shade_arg, third_shade);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_8004CECC(((S_800C55F4_8 *)arg0_pin)->unk_30,
                                  shade_arg, 0xFF,
                                  arg1_record + 0x14);
                }
            }

            func_800666B8(arg1_record);
            old_record = arg1_record;
            page_flag = ((S_800C55F4_4 *)page_record7)->unk_00;
            arg1_record += 0x1C;
            ((S_800C55F4_4 *)page_record7)->unk_00 = page_flag | 2;
            page_record7 += 0x1C;
            ASM_KEEP(page_record7);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            page_record7 += 0xC;
            ASM_KEEP(page_record7);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            func_8006658C(((S_800C55F4_1 *)scratch)->unk_20 +
                          (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), old_record);

            ((S_800C55F4_2 *)arg2_alias)->unk_14 &= 0x7FFF;
            func_80067F20(arg1_record, 0, 0, 0, 0);
            old_record = arg1_record;
            arg1_record += 0xC;
            func_8006658C(((S_800C55F4_1 *)scratch)->unk_20 +
                          (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), old_record);
        }
    }

    entry_flag = ((S_800C55F4_7 *)entry)->unk_00;
    if (entry_flag >= 0) {
        entry += 0xC;
        ASM_USE_NV(entry);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        scan += 0xC;
        ASM_TAILSLOT_PIN(scan);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800C5750();
        return;
    }
    func_80064A40();
    global_base = D_80083160;
    ASM_KEEP(global_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ((S_800C55F4_10 *)(((S_800C55F4_9 *)global_base)->unk_00))->unk_8D0 = arg1_record;
}

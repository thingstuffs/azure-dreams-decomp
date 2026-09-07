#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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
    register u8 *arg0_pin ASM_REG("$23") = arg0;
    register u8 *arg1_record ASM_REG("$16") = arg1;
    void *arg2_alias = arg2;
    register s16 arg3_pin ASM_REG("$17") = arg3;
    register u8 *scratch ASM_REG("$19");
    register u32 stack_arg ASM_REG("$8");
    register u8 *first_a0 ASM_REG("$4");
    register u8 *first_a1 ASM_REG("$5");
    void *volatile sp38;
    void *volatile sp3C;
    u8 *descriptor;
    register u8 *table ASM_REG("$21");
    register u8 *entry ASM_REG("$20");
    register u8 *scan ASM_REG("$22");
    register u8 *page_record7 ASM_REG("$18");
    u8 *root;
    register u8 *old_record ASM_REG("$5");
    register u8 *global_base ASM_REG("$8");
    u8 page_flag;
    s32 result;
    s32 entry_flag;
    u32 x;
    register u32 position ASM_REG("$5");
    void *call_a0;
    void *call_a2;
    void *call_a3;

    ASM_KEEP4_NV(arg0_pin, arg1_record, arg2_alias, page_record7);
    ASM_KEEP_NV(arg3_pin);
    stack_arg = 0x1F800000;
    stack_arg |= 0x90;
    sp38 = (void *)stack_arg;
    stack_arg = 0x1F800000;

    descriptor = FIELD(arg2_alias, u8 **, 8);
    stack_arg |= 0x94;
    sp3C = (void *)stack_arg;
    ASM_CLOBBER("$18");
    table = FIELD(descriptor, u8 **, 0);
    scan = FIELD(descriptor, u8 **, 8);

    func_800649A0();

    page_record7 = (u8 *)0x80080000;
    ASM_KEEP(page_record7);
    first_a0 = (u8 *)0x1F800028;
    first_a1 = (u8 *)0x1F800000;
    ASM_KEEP_NV(first_a1);
    scratch = (u8 *)0x1F800000;

    FIELD(scratch, u32, 0x30) = FIELD(arg2_alias, u16, 0x1C);
    {
        register u32 coord ASM_REG("$2");

        coord = FIELD(arg2_alias, u16, 0x1E);
        ASM_SCHED_BARRIER();
        first_a1 = (u8 *)((u32)first_a1 | 0xF0);
        ASM_USE2_NV(first_a0, first_a1);
        FIELD(scratch, u32, 0x34) = coord;
    }
    FIELD(scratch, u32, 0x38) = FIELD(arg2_alias, u16, 0x20);

    {
        register s32 initial_value ASM_REG("$2");

        initial_value = FIELD(arg1_record, s16, 2);
        FIELD(scratch, s32, 0x64) = initial_value;
        FIELD(scratch, s16, 0x28) = initial_value;
        initial_value = FIELD(arg1_record, s16, 6);
        FIELD(scratch, s32, 0x68) = initial_value;
        FIELD(scratch, s16, 0x2A) = initial_value;
        initial_value = FIELD(arg1_record, s16, 0xA);
        FIELD(scratch, s32, 0x6C) = initial_value;
        FIELD(scratch, s16, 0x2C) = initial_value;
    }

    FIELD(scratch, s32, 0xCC) =
        func_80065420(first_a0, first_a1,
                     (void *)0x1F800090, (void *)0x1F800094) - arg3_pin;
    func_80064AE0(sp18);
    func_80065820((u8 *)arg2_alias + 0x16, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064840(sp18, scratch + 0x50, scratch + 0xD0);
    func_80064D80(scratch + 0xD0);
    func_80064CF0(scratch + 0xD0);
    ASM_KEEP(scratch);

    root = FIELD(page_record7, u8 *, 0x3160);
    entry = scan + 0xB;
    FIELD(scratch, u8 *, 0x20) = root + 0xB0;
    arg1_record = FIELD(root, u8 *, 0x8D0);
    page_record7 = arg1_record + 7;
    FIELD(arg2_alias, u16, 0x14) |= 0x8000;
    ASM_KEEP(page_record7);

    x = *scan;
    FIELD(scratch, u32, 0x70) = FIELD((x << 3) + (u32)table, u32, 0);
    x = FIELD(entry, u8, -0xA);
    FIELD(scratch, u32, 0x78) = FIELD((x << 3) + (u32)table, u32, 0);
    x = FIELD(entry, u8, -9);
    FIELD(scratch, u32, 0x80) = FIELD((x << 3) + (u32)table, u32, 0);
    x = *scan;
    FIELD(scratch, u16, 0x74) = FIELD((x << 3) + (u32)table, u16, 4);
    x = FIELD(entry, u8, -0xA);
    call_a0 = scratch + 0x70;
    FIELD(scratch, u16, 0x7C) = FIELD((x << 3) + (u32)table, u16, 4);
    x = *(volatile u8 *)(entry - 9);
    call_a2 = sp38;
    call_a3 = sp3C;
    FIELD(scratch, u16, 0x84) = FIELD((x << 3) + (u32)table, u16, 4);

    {
        s32 call_result;

        call_result = func_80065420(call_a0, arg1_record + 8,
                                    call_a2, call_a3);
        call_a0 = scratch + 0x78;
        call_a2 = sp38;
        call_a3 = sp3C;
        FIELD(scratch, s32, 0xC0) = call_result;
        call_result = func_80065420(call_a0, arg1_record + 0x10,
                                    call_a2, call_a3);
        call_a0 = scratch + 0x80;
        call_a2 = sp38;
        call_a3 = sp3C;
        FIELD(scratch, s32, 0xC4) = call_result;
        call_result = func_80065420(call_a0, arg1_record + 0x18,
                                    call_a2, call_a3);
        FIELD(scratch, s32, 0xC8) = call_result;
    }
    ASM_KEEP(table);

    result = func_80065480(FIELD(page_record7, s32, 1),
                           FIELD(page_record7, s32, 9),
                           FIELD(page_record7, s32, 0x11));
    FIELD(scratch, s32, 0x114) = result;

    if (result > 0) {
        register s32 c8_value ASM_REG("$2");

        FIELD(scratch, volatile s32, 0xC0) -= arg3_pin;
        c8_value = FIELD(scratch, volatile s32, 0xC8);
        FIELD(scratch, s32, 0xC4) -= arg3_pin;
        position = *(volatile u32 *)(scratch + 0xC0);
        FIELD(scratch, s32, 0xC8) = c8_value - arg3_pin;
        if (position < 0x1E0) {
            {
                register s32 first_shade ASM_REG("$3");

                first_shade = 0x100;
                first_shade -= FIELD(arg0_pin, s16, 0x32);
                first_shade -=
                    (FIELD(scratch, s32, 0xCC) - position) << 5;
                if (first_shade < 0x20) {
                    first_shade = 0x20;
                    ASM_TAILSLOT_PIN(first_shade);
                    func_800C58BC(FIELD(arg0_pin, s16, 0x32), position);
                    return;
                }
                if (first_shade >= 0x100) {
                    first_shade = 0xFF;
                }
                {
                    register s32 shade_arg ASM_REG("$5");

                    shade_arg = (s32)(s16)first_shade;
                    ASM_KEEP_DEP_NV(shade_arg, first_shade);
                    func_8004CECC(FIELD(arg0_pin, s16, 0x30),
                                  shade_arg, 0xFF, arg1_record + 4);
                }
            }

            {
                register s32 second_value ASM_REG("$4");
                register s32 second_shade ASM_REG("$3");
                register s32 second_delta ASM_REG("$2");
                s32 second_height;

                second_value = 0x100;
                ASM_KEEP(second_value);
                second_height = FIELD(arg0_pin, s16, 0x32);
                ASM_KEEP_DEP_NV(scratch, second_height);
                second_delta = FIELD(scratch, s32, 0xCC);
                second_shade = FIELD(scratch, s32, 0xC4);
                second_value -= second_height;
                second_delta -= second_shade;
                second_delta <<= 5;
                second_shade = second_value - second_delta;
                if (second_shade < 0x20) {
                    second_shade = 0x20;
                    ASM_TAILSLOT_PIN(second_shade);
                    func_800C5914(second_value,
                                  FIELD(arg0_pin, s16, 0x32));
                    return;
                }
                if (second_shade >= 0x100) {
                    second_shade = 0xFF;
                }
                {
                    register s32 shade_arg ASM_REG("$5");

                    shade_arg = (s32)(s16)second_shade;
                    ASM_KEEP_DEP_NV(shade_arg, second_shade);
                    func_8004CECC(FIELD(arg0_pin, s16, 0x30),
                                  shade_arg, 0xFF,
                                  arg1_record + 0xC);
                }
            }

            {
                register s32 third_value ASM_REG("$4");
                register s32 third_shade ASM_REG("$3");
                register s32 third_delta ASM_REG("$2");
                s32 third_height;

                third_value = 0x100;
                ASM_KEEP(third_value);
                third_height = FIELD(arg0_pin, s16, 0x32);
                ASM_KEEP_DEP_NV(scratch, third_height);
                third_delta = FIELD(scratch, s32, 0xCC);
                third_shade = FIELD(scratch, s32, 0xC8);
                third_value -= third_height;
                third_delta -= third_shade;
                third_delta <<= 5;
                third_shade = third_value - third_delta;
                if (third_shade < 0x20) {
                    third_shade = 0x20;
                    ASM_TAILSLOT_PIN(third_shade);
                    func_800C596C(third_value,
                                  FIELD(arg0_pin, s16, 0x32));
                    return;
                }
                if (third_shade >= 0x100) {
                    third_shade = 0xFF;
                }
                {
                    register s32 shade_arg ASM_REG("$5");

                    shade_arg = (s32)(s16)third_shade;
                    ASM_KEEP_DEP_NV(shade_arg, third_shade);
                    func_8004CECC(FIELD(arg0_pin, s16, 0x30),
                                  shade_arg, 0xFF,
                                  arg1_record + 0x14);
                }
            }

            func_800666B8(arg1_record);
            old_record = arg1_record;
            page_flag = FIELD(page_record7, u8, 0);
            arg1_record += 0x1C;
            FIELD(page_record7, u8, 0) = page_flag | 2;
            page_record7 += 0x1C;
            ASM_KEEP(page_record7);
            page_record7 += 0xC;
            ASM_KEEP(page_record7);
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                          (FIELD(scratch, s32, 0xC0) << 2), old_record);

            FIELD(arg2_alias, u16, 0x14) &= 0x7FFF;
            func_80067F20(arg1_record, 0, 0, 0, 0);
            old_record = arg1_record;
            arg1_record += 0xC;
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                          (FIELD(scratch, s32, 0xC0) << 2), old_record);
        }
    }

    entry_flag = FIELD(entry, s8, 0);
    if (entry_flag >= 0) {
        entry += 0xC;
        ASM_USE_NV(entry);
        scan += 0xC;
        ASM_TAILSLOT_PIN(scan);
        func_800C5750();
        return;
    }
    func_80064A40();
    global_base = D_80083160;
    ASM_KEEP(global_base);
    FIELD(FIELD(global_base, u8 *, 0), u8 *, 0x8D0) = arg1_record;
}

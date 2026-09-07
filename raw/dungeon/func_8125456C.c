#include "common.h"

extern s32 func_80047784();
extern void func_800A9A0C();
extern void func_80171BE0();
extern void func_80173E6C() __attribute__((noreturn));
extern void func_80173E78(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u8 D_80173E94[];
extern u8 *D_80174714;
extern u16 D_80174718;

s32 func_8125456C(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *arg2_hold ASM_REG("$9") = arg2;
    register u8 *arg0_hold ASM_REG("$16");
    register u8 *entry ASM_REG("$6");
    register s32 command ASM_REG("$7");
    register s32 command_u8 ASM_REG("$8");
    register u8 *final_arg ASM_REG("$4");
    register s32 tail_zero ASM_REG("$2");
    u8 entry_count;
    s16 index;
    s32 type;
    s32 type_8_value;

    entry = D_80174714;
    command = entry[1];
    ASM_KEEP_NV(command);
    command_u8 = command & 0xFF;
    ASM_KEEP_NV(command_u8);
    if (command_u8 == 0) {
        arg0_hold = arg0;
        ASM_KEEP(arg0_hold);
        arg0_hold[0xBA] = 0;
        func_80173E6C();
    }
    arg0_hold = arg0;
    ASM_SCHED_BARRIER();
    ASM_KEEP_NV(arg0_hold);

    index = D_80174718 + 1;
    entry_count = entry[0];
    D_80174718 = index;
    if (entry_count < index) {
        D_80174714 = entry + 2;
        D_80174718 = 0;
        arg0_hold[0x9B] = 0;
    }
    ASM_KEEP(entry);

    type_8_value = 8;
    *(s16 *)(arg0_hold + 0x2A) = (command & 7) << 9;
    *(u16 *)(arg0_hold + 0x46) |= 0x8000;

    type = command_u8 & 0xF8;
    ASM_KEEP(command_u8);
    if (type == type_8_value) {
        goto type_8;
    }
    if (type == 0x10) {
        goto type_10;
    }
    final_arg = arg0_hold;
    ASM_KEEP(final_arg);
    func_80173E6C();

type_8:
    func_80171BE0(arg0_hold, arg1, arg2_hold, arg0_hold);
    tail_zero = 0;
    ASM_TAILSLOT_PIN_TIED(tail_zero);
    func_80173E78();

type_10:
    ASM_SCHED_BARRIER();
    if (*(u8 **)(arg2_hold + 0x2C) != D_80173E94) {
        *(u8 **)(arg2_hold + 0x2C) = D_80173E94;
        func_80047784(arg2_hold,
                      D_80173E94[((D_80083228 +
                                   *(s16 *)(arg0_hold + 0x2A) + 0x100) >> 9) & 7],
                      *(s8 *)(arg2_hold + 4), command);
        ASM_KEEP(command);
        ASM_KEEP(arg2_hold);
    }
    final_arg = arg0_hold;
    ASM_KEEP(final_arg);
    func_800A9A0C(final_arg);
    return 0;
}

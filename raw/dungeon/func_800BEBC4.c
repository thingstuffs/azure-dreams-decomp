#include "common.h"

extern void func_80042B68();
extern void func_8008D330();
extern void func_80098B38();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800C4474();
extern void func_800C4AFC();

extern u8 D_80082E80[12];
extern u8 D_80083460[12];
extern u8 D_80083780[12];
extern u16 D_800DDE84[];
extern u8 D_800E188B[];
extern void *D_800E3D7C[];

s32 func_800C4324(void *arg0, s32 arg1, s16 arg2)
{
    register void *entry_arg ASM_REG("$4") = arg0;
    register void *entity ASM_REG("$17") = arg0;
    register s32 amount ASM_REG("$18") = arg1;
    s32 temp;
    s32 selected;
    u8 *counter_base;

    if (entity == D_800E3D7C[0]) {
        *(s32 *)((u8 *)entity + 0x110) = amount;
        ASM_KEEP(entry_arg);
        func_8008D330(entry_arg, D_80083780, D_80082E80, entry_arg);
        func_800C4474();
        return 0;
    }

    ASM_KEEP(entity);
    ASM_KEEP(amount);
    if ((u32)entity <= 0x9FFFFFFF) {
        register void *lookup_arg ASM_REG("$4");
        register u16 *table ASM_REG("$3");
        s32 table_index;

        func_800A63B8(entity, amount, arg2);
        lookup_arg = entity;
        ASM_KEEP(lookup_arg);
        table = (u16 *)0x800E0000;
        ASM_KEEP(table);
        table_index = *((u8 *)entity + 0x13);
        ASM_KEEP(table_index);
        table = (u16 *)((u8 *)table - 0x217C);
        ASM_KEEP(table);
        if (func_800AD6FC(lookup_arg,
                         (table[table_index] >> 6) & 3,
                         0) == 0) {
            func_800A5F38(entity, amount);
            func_800C4474();
            return 1;
        }
    }

    func_800C4AFC(*(s32 *)((u8 *)entity - 0x18), 0xC02020, entity);
    if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
        temp = func_800990FC();
        selected = temp;
        if (!(*(s32 *)((u8 *)entity + 0x1C) & 0x10)) {
            selected = func_80099194(D_800E188B, temp);
        }
        func_80099290(selected);
        func_800A5720(temp);
    }
    func_80042B68(entity, 3);
    func_80098B38(amount);
    counter_base = D_80083460;
    ASM_KEEP(counter_base);
    *(u16 *)(counter_base + 0xA) = *(u16 *)(counter_base + 0xA) - 1;
    return 1;
}

/* MECHANISM: Fixed-register locals hold entity/amount in s1/s2 and preserve the call ABI.
   Fenced page/index live ranges split 0x800E0000/-0x217C around the lbu load-delay slot.
   The zero-arg func_800990FC contract and held counter base remove the final dead/address words. */

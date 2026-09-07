#include "common.h"

extern s32 func_800422A8(void *, void *, s32, s32);
extern void *func_80098194(void);
extern void *func_800981C8(void);
extern s32 func_80098FB0(void);
extern s32 func_80098FF8(void);
extern void *func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099368(void *, s32);
extern s32 func_8009955C(void *, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);

extern u8 D_80081470[];
extern void *D_80081484;
extern void *D_800814A8;
extern u8 D_800E07EF[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern u8 *D_800E3D7C;

void *func_80097F84(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    void *held_arg0 = arg0;
    register void *held_arg1 ASM_REG("$20") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *held_arg2 = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 held_arg3 = arg3;
    register s32 first ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 second ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 index;
    void *object;
    s32 found;
    register s32 narrowed ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 flags;
    u8 *entry;
    u8 *entry_base;
    void *global_object;

       /* MATCH pin: retail schedule: same instructions, different order without it */
    if (held_arg0 != (void *)&D_80081484 &&
        held_arg0 != (void *)D_80081470 &&
        held_arg0 != *(void **)((u8 *)D_800814A8 + 0xF0)) {
        return held_arg0;
    }

    first = func_80098FB0();
    second = func_80098FF8();
    narrowed = first << 16;
    index = narrowed >> 16;

    if (index < 0) {
        goto invalid_index;
    }
    narrowed = second << 16;
    if (narrowed >= 0) {
        goto valid_index;
    }

invalid_index:
    {
        object = func_800990FC();
        func_80099290(func_80099194(held_arg2,
            func_8009955C(held_arg0,
                func_80099194(held_arg1, func_8009929C(8, object)))));
        func_800A5720(object);
        func_800981C8();
        return 0;
    }

valid_index:
    object = func_800990FC();
    func_80099290(func_80099194(D_800E07EF,
        func_80099368(held_arg0, object)));
    if (held_arg3 != 0) {
        func_800A5720(object);
    }
    func_800A56E0(0x508);

    if (held_arg0 == (void *)&D_80081484) {
        do { ((void **)0x80010248)[index] = D_80081484; } while (0);
        global_object = D_800814A8;
        flags = *(u32 *)((u8 *)global_object + 0x1C);
        D_80081484 = 0;
        *(s32 *)((u8 *)global_object + 0x124) = 0;
        *(u32 *)((u8 *)global_object + 0x1C) = flags & 0xFFEFFFFF;
        return func_80098194();
    }

    narrowed = func_800422A8(*(void **)(D_800E3D7C + 0xF0),
                              D_800E3548, 4, 0x40);
    narrowed <<= 16;
    found = narrowed >> 16;
    ASM_KEEP4(first, second, found, narrowed);   /* MATCH pin: retail delay-slot fill depends on it */
    entry_base = (u8 *)0x800E0000;
    if (found >= 0) {
        ASM_KEEP_NV(entry_base);   /* MATCH pin: keeps a constant in a register as retail does */
        entry_base += 0x36C8;
        ASM_KEEP(entry_base);   /* MATCH pin: keeps a constant in a register as retail does */
        entry = (u8 *)(found * 12);
        entry += (s32)entry_base;
        func_8009A3D0(entry[0], entry[1], 0x800);
    }

    ((void **)0x80010248)[index] = *(void **)D_80081470;
    ASM_KEEP(index);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    narrowed = (s32)D_800814A8;
    narrowed = *(s32 *)(narrowed + 0xF0);
    *(s32 *)narrowed = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    entry_base = (u8 *)0x80010248;
    ASM_KEEP(entry_base);   /* MATCH pin: keeps a constant in a register as retail does */
    narrowed = first << 16;
    narrowed >>= 14;
    narrowed += (s32)entry_base;
    ASM_KEEP(narrowed);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    *(s32 *)held_arg0 = 0;
    held_arg0 = (void *)narrowed;
    entry_base = (u8 *)0x80010000;
    ASM_KEEP(entry_base);   /* MATCH pin: keeps a constant in a register as retail does */
    narrowed = second << 16;
    narrowed >>= 14;
    narrowed += (s32)entry_base;
    *(void **)(narrowed + 0x29c) = held_arg0;
    return held_arg0;
}

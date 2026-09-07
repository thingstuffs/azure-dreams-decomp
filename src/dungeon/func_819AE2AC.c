#include "common.h"

typedef struct Entry {
    s32 field_0;
    s8 field_4;
    u8 pad_5;
    s16 field_6;
    void *field_8;
} Entry;

extern u8 D_800274C0[];
extern void func_8002590C(Entry *, s32);
extern void func_800257D0(void *, s32);
extern void func_800C9088(void *, s32, Entry *, s32);
extern void func_80025AE4(void) __attribute__((noreturn));

#ifndef NON_MATCHING
register s32 volatile v0_carrier ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

s32 func_80025AAC(void *arg0, s32 arg1, Entry *arg2)
{
    void *state = arg0;
    register s32 value ASM_REG("$20") = arg1;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    Entry *entry = arg2;
    u8 *base;
    s32 i;
    u8 *ptr;
    void *call_arg;

#ifndef NON_MATCHING
    v0_carrier = (s32)0x80020000;
    base = (u8 *)v0_carrier + 0x74C0;
#else
    base = D_800274C0;
#endif
    ASM_KEEP(base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    i = 0;
    ptr = base;
    call_arg = entry;
    do {
        entry->field_8 = ptr;
        ptr += 0x10;
        ASM_KEEP(ptr);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        func_8002590C((Entry *)call_arg, entry->field_4);
        i++;
        func_800257D0(state, entry->field_0);
        func_800C9088(state, value, entry, entry->field_6);
        call_arg = entry;
#ifndef NON_MATCHING
    } while ((v0_carrier = (i < 12)) != 0);
#else
    } while (i < 12);
#endif

    call_arg = *(void **)((u8 *)state - 8);
    if (call_arg != 0) {
        state = (u8 *)call_arg + 0x20;
        value = *(s32 *)((u8 *)call_arg + 8);
        entry = *(Entry **)((u8 *)call_arg + 0xC);
        ASM_KEEP(state);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ASM_KEEP(value);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_KEEP(entry);   /* MATCH pin: retail basic-block layout depends on it */
        i = 0;
        ASM_TAILSLOT_PIN_TIED(i);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        func_80025AE4();
    }
    ASM_KEEP(base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return 0;
}

/* MECHANISM: A guarded volatile $v0 carrier splits the held $s5 base across lui/save/addiu
   and is reused for the loop test; the $a0 lifetime plus pointer fence fixes both loop slots.
   Zero-arg noreturn plus the tied $s2 tail pin emits retail's j/move continuation contract. */

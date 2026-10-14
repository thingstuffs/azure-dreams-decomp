#include "common.h"
#include "m2c_compat.h"

s32 func_800007E8();                             /* extern */
M2C_UNK func_80000858();                /* extern */
void func_800009FC(void) __attribute__((noreturn));  /* extern */
void func_80000A24(void) __attribute__((noreturn));  /* extern */
M2C_UNK func_80000A38();                            /* extern */
M2C_UNK func_80000BC8();                         /* extern */
M2C_UNK func_80000C18();                         /* extern */
s32 func_80000C6C();                             /* extern */
typedef struct TownFlagEntry {
    u16 value;
    u16 pad;
} TownFlagEntry;

typedef struct TownFlagTable {
    u8 pad_00[0xF12];
    u16 flag_F12;
    u8 pad_F14[0xF28 - 0xF14];
    TownFlagEntry entry[5];
} TownFlagTable;

extern TownFlagTable D_00000000;

/* Runs a chain of state checks on index and its flags, taking one of two noreturn exits along the way, then always finalises and returns index unchanged. */
s32 func_808BB138(s32 index) {
    if ((func_80000C6C(D_00000000.flag_F12) == 0) && (func_80000C6C(0x278U) != 0)
        && (func_800007E8(index) != 0)) {
        if (func_80000C6C(0x281U) != 0) {
            func_80000C18(D_00000000.entry[2].value);
            func_80000C18(D_00000000.entry[3].value);
            func_80000C18(D_00000000.entry[4].value);
            func_80000C18(0x281U);
            func_80000C18(0x280U);
            func_800009FC();
        }
        if (func_80000C6C(0x288U) != 0) {
            func_80000BC8(D_00000000.entry[index].value);
            func_80000C18(0x278U);
            func_80000A38();
            func_80000A24();
        }
                        /* Duplicate return node #10. Try simplifying control flow for better match */
        func_80000858(index, 0);
        return index;
    }
    func_80000858(index, 0);
    return index;
}

/* MECHANISM: index stays live in s0, yielding the retail 0x18 frame and sole s0 save.
   A same-symbol indexed alias scope-splits D_00000000, preventing a held s1 page base.
   Noreturn zero-arg tails let maspsx emit the two retail bare j instructions. */

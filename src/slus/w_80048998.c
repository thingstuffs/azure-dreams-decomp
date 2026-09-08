#include "common.h"

typedef struct S_80083110 {
    u8 pad0[8];
    s32 field_8;
    u8 pad1[0x28 - 0xC];
    s32 field_28;
} S_80083110;

extern S_80083110 *D_80083110[4];
extern void func_800488F0(s32, s32, s32);

/* Registers the entry in a nonzero one-based slot and dispatches in mode 2, or mode 3 for slot zero. */
void func_80048998(S_80083110 *entry, s32 index) {
    if (index != 0) {
        index = index - 1;
        D_80083110[index] = entry;
        func_800488F0(entry->field_8, entry->field_28, 2);
    } else {
        func_800488F0(entry->field_8, entry->field_28, 3);
    }
}

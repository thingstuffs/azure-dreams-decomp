#include "common.h"

#include "common.h"

typedef struct S_80056558_85458 {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x44];
    /* 0x58 */ s32 f58;
    /* 0x5C */ u8 pad5c[0x10];
    /* 0x6C */ s16 f6c;
    /* 0x6E */ u8 pad6e[0x0A];
} S_80056558_85458;

extern s32 D_80073734[4];
extern S_80056558_85458 D_80085458[64];

extern s32 func_800563B0();

/* Updates entries with offset-adjusted values when their offsets differ. */
void func_80056558(void) {
    s32 entry_index;
    S_80056558_85458 *entry;
    s32 offset;
    s32 reference_offset;

    for (entry_index = 0; entry_index < D_80073734[0]; entry_index++) {
        entry = &D_80085458[entry_index];
        reference_offset = entry->f6c;
        __asm__ volatile("" : : "r"(reference_offset));
        offset = entry->f58;
        if (reference_offset != offset) {
            func_800563B0(entry_index, entry->f10 + offset, entry->f12 + offset);
        }
    }
}

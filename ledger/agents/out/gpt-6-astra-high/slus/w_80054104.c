#include "common.h"

typedef struct {
    s16 v[4];
} S_80032E0C;

extern S_80032E0C D_80032E0C;
extern s32 func_8005405C(s16 n);
extern void func_80055730();

/* Sends packed codes and region offsets for available lookup entries across 48 slots. */
void func_80054104(void) {
    S_80032E0C lookup;
    s32 slot, entry_index;
    s32 slot_group, region_offset;
    s16 entry;
    s32 code;

    lookup = D_80032E0C;
    slot = 0;
    do {
        entry_index = 0;
        slot_group = (u32)(slot & 0xFF) >> 4;
        region_offset = ((slot & 0xF) << 10) + 0x1C00;
    inner:
        entry = lookup.v[entry_index];
        code = ((entry << 8) & 0xFF00) | slot_group;
        if (entry == 0) {
            code += 0x10;
        }
        if ((func_8005405C(entry) << 16) != 0) {
            func_80055730(code, region_offset);
        }
        entry_index++;
        if (entry_index < 3) {
            goto inner;
        }
        slot++;
    } while (slot < 0x30);
}

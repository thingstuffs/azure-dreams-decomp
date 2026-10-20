#include "common.h"

extern void clear_object_status_and_dispatch_target(void *object, int target, int value, s16 flags);
extern s32 quantize_heading_to_sector(s16 referenceAngle, s16 sectorCount);

typedef struct {
    /* 0x64 */ char pad0[0x64];
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char pad1[0x0C];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ char pad2[0x02];
    /* 0x78 */ s32 *unk78;
} Struct800C5724;

/* Store and count a zero-terminated entry list, then initialize the output with a selected entry. */
void initialize_object_entries(Struct800C5724 *state, s8 *output, s32 *entries) {
    s32 *entry_end;
    s16 entry_count;

    entry_end = entries;
    state->unk78 = entry_end;
    entry_count = 0;
    if (*entry_end != 0) {
        do {
            entry_end += 1;
            entry_count++;
        } while (*entry_end != 0);
    }
    state->unk64 = entry_count;
    clear_object_status_and_dispatch_target(state, output, state->unk78[quantize_heading_to_sector(state->unk72, entry_count)], 0);
    output[5] = 0;
}

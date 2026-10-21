#include "common.h"
#include "engine/graphics.h"

/* D_80082E6A: standalone byte global (siblings in this wave access it directly
 * via hi/lo, distinct symbol from D_80082E60 even though numerically adjacent).
 * Declared >8B to force %hi/%lo addressing (matches target's lui/lbu form). */
struct S_80082E6A {
    u8 field_0;
    u8 pad[11];
};
extern struct S_80082E6A runtime_dispatch_mode_alias;

/* Entry-array element type shared with upload_entry_textures_narrow/upload_eligible_entries_by_mode (stride 0xC,
 * only flags byte at offset 0 read by those callees). */
struct S_8004761C_Entry {
    u8 flags;
    u8 pad[0xB];
};
struct S_800482C8_Entry {
    u8 flags;
    u8 pad[0xB];
};

/* S_80047694: caller-side view of an entity/state struct.
 *   field_8  (0x08): pointer to the 0xC-byte entry array (passed on to callees)
 *   field_14 (0x14): u16 flags; bit 0x400 selects the upload_eligible_entries_by_mode path
 *   field_28 (0x28): pointer to an s32 cursor/arg passed on to callees
 */
struct S_80047694 {
    u8 pad_0[0x8];
    struct S_8004761C_Entry *field_8;
    u8 pad_C[0x8];
    u16 field_14;
    u8 pad_16[0x28 - 0x16];
    s32 *field_28;
};

/* Dispatch entries and cursor to a handler selected by state flags and global mode. */
void upload_entry_textures(struct S_80047694 *state)
{
    if (state->field_14 & 0x400) {
        upload_eligible_entries_by_mode((struct S_800482C8_Entry *)state->field_8, state->field_28);
    } else if (runtime_dispatch_mode_alias.field_0 == 1) {
        upload_entry_textures_narrow(state->field_8, state->field_28);
    } else {
        upload_entry_textures_wide(state->field_8, state->field_28);
    }
}

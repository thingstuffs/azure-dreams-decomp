#include "common.h"

struct S_800475A4_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void pack_texture_into_vram_wide(struct S_800475A4_Entry *a0, s32 a1, u16 a2);

/* Packs and uploads entries with flags 0x60 clear using data offsets stored before the array. */
void upload_entry_textures_wide(struct S_800475A4_Entry *entries, s32 *source_record_ptr)
{
    struct S_800475A4_Entry *entry = entries;
    s32 *source_record = source_record_ptr;
    u16 *data_offsets = (u16 *)entries;

    do {
        if (!(entry->flags & 0x60)) {
            data_offsets--;
            pack_texture_into_vram_wide(entry, *source_record, *data_offsets);
        }
    } while (!((entry++)->flags & 0x80));
}

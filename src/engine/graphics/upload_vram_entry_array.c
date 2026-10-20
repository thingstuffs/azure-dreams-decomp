#include "common.h"

/* struct describing one draw-entry: word handle/flag at 0, two halfword coords at 4/6, pad to 0xC */
typedef struct S_8003F9E0 {
    s32 f0;
    u16 f4;
    u16 f6;
    s32 f8;
} S_8003F9E0;

extern s32 upload_vram_row_and_cache(s32 a0, s32 a1, s32 a2, s32 a3);

/* Uploads and caches VRAM strips until an entry with a zero source address is reached. */
void upload_vram_entry_array(S_8003F9E0 *entries) {
    while (entries->f0) {
        upload_vram_row_and_cache(entries->f0, entries->f4, entries->f6, 0);
        entries++;
    }
}

#include "common.h"

/* struct describing one draw-entry: word handle/flag at 0, two halfword coords at 4/6, pad to 0xC */
typedef struct S_8003F9E0 {
    s32 f0;
    u16 f4;
    u16 f6;
    s32 f8;
} S_8003F9E0;

extern s32 uploadVramRowAndCache(s32 a0, s32 a1, s32 a2, s32 a3);

/* Uploads and caches VRAM strips until an entry with a zero source address is reached. */
void uploadVramEntryArray(S_8003F9E0 *entries) {
    while (entries->f0) {
        uploadVramRowAndCache(entries->f0, entries->f4, entries->f6, 0);
        entries++;
    }
}

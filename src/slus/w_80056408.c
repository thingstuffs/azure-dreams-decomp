#include "common.h"

/* D_80085458: struct array, stride 0x78 (120) bytes; only fields touched here. */
typedef struct S_80085458 {
    /* 0x00 */ u8 pad00[6];
    /* 0x06 */ u16 f06;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x78 - 0x14];
} S_80085458;

/* D_80084960: shared struct array touched by siblings this wave; stride 0x9C
 * (156) bytes matches the already-established Entry80084960/S_80084960 size
 * used elsewhere in the codebase. This function only takes the ADDRESS of an
 * element (indexed by S_80085458.f06); it does not touch any field, so no
 * field layout is asserted here beyond the element size. */
typedef struct S_80084960 {
    /* 0x00 */ u8 pad[0x9C];
} S_80084960;

extern s32 D_80073734[4];
extern S_80085458 D_80085458[64];
extern S_80084960 D_80084960[16];

extern void audio_compute_voice_stereo_volumes(S_80085458 *a0, S_80084960 *a1);
extern s32 sound_set_indexed_voice_volumes(s32 a0, u16 a1, u16 a2);

/* Dispatch each active entry with its matching slot, then its field pair with its index. */
void audio_refresh_all_voice_volumes(void)
{
    s32 entry_index;

    for (entry_index = 0; entry_index < D_80073734[0]; entry_index++) {
        S_80085458 *entry = &D_80085458[entry_index];
        audio_compute_voice_stereo_volumes(entry, &D_80084960[entry->f06]);
        sound_set_indexed_voice_volumes(entry_index, entry->f10, entry->f12);
    }
}

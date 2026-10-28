#include "common.h"
#include "engine/audio/sequence.h"

typedef struct {
    /* 0x00 */ unsigned char pad00[4];   /* includes an s16 slot-marker (see sibling free_sound_slot) */
    /* 0x04 */ u8 *unk04;                /* data-buffer base pointer, used here as a raw address */
    /* 0x08 */ unsigned char pad08[0x14];
} S_80057A50_D80086A40; /* size 0x1C (28) -- confirmed by index-scaling in this and sibling asm */

extern S_80057A50_D80086A40 audio_bank_slots[16];
extern s16 audio_current_bank_slot[8]; /* forced hi/lo access via size > 8 (see gp-vs-hilo-extern-size) */

/* Returns the tile address for the given row and column in the selected map slot. */
void *audio_get_current_bank_tone_record(void *row_data, s32 column) {
    s32 *row = row_data;
    u8 *data_address = audio_bank_slots[audio_current_bank_slot[0]].unk04;
    s32 tile_offset = (((*row << 4) + (column & 0xFFFF)) << 5) + 0x820;
    return data_address + tile_offset;
}

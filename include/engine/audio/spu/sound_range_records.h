#ifndef SLUS_SOUND_RANGE_RECORDS_H
#define SLUS_SOUND_RANGE_RECORDS_H

#include "common.h"

typedef struct S_800799BC {
    u32 flags;
    u32 size;
} S_800799BC;

extern s32 spu_address_unit_shift;
extern s32 spu_ram_block_record_count;
extern s32 D_800799B8;
extern S_800799BC *spu_ram_block_records;

s32 initialize_sound_transfer_range(s32 count, S_800799BC *record);
s32 audio_get_whether_non_skipped_block_contains_address_starts_beyond(u32 address);
s32 func_8005D9DC(u32 value);

#endif

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

s32 SpuInitMalloc(s32 count, S_800799BC *record);
s32 _SpuIsInAllocateArea(u32 address);
s32 _SpuIsInAllocateArea_(u32 value);

#endif

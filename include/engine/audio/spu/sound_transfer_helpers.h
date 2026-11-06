#ifndef SLUS_SOUND_TRANSFER_HELPERS_H
#define SLUS_SOUND_TRANSFER_HELPERS_H
#include "sdk/libspu.h"

#include "common.h"

extern s32 spu_address_unit_shift;
extern s32 spu_transfer_complete;
extern s32 spu_transfer_callback;
extern s32 spu_transfer_completion_override;
extern s32 spu_transfer_event_handle;
extern u16 spu_transfer_address_units;

s32 write_spu_transfer_data(s32 data, u32 size);

#endif

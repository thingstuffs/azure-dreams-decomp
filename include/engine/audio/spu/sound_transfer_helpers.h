#ifndef SLUS_SOUND_TRANSFER_HELPERS_H
#define SLUS_SOUND_TRANSFER_HELPERS_H

#include "common.h"

extern s32 spu_address_unit_shift;
extern s32 spu_transfer_complete;
extern s32 spu_transfer_callback;
extern s32 spu_transfer_completion_override;
extern s32 spu_transfer_event_handle;
extern u16 spu_transfer_address_units;

s32 _spu_Fw(s32 channel, s32 playback_param);
s32 _spu_FsetRXXa(s32 index, u32 value);
s32 TestEvent(s32 event);
s32 write_spu_transfer_data(s32 data, u32 size);
s32 SpuSetTransferStartAddr(s32 address);
s32 SpuIsTransferCompleted(s32 wait_for_completion);

#endif

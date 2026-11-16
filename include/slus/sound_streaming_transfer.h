#ifndef SLUS_SOUND_STREAMING_TRANSFER_H
#define SLUS_SOUND_STREAMING_TRANSFER_H

#include "common.h"

extern s32 spu_reverb_start_addresses[10];
extern s32 spu_transfer_uses_fifo;
extern s32 spu_address_unit_shift;
extern void (* volatile spu_transfer_callback)(u32);
extern s32 spu_address_alignment_mask;
extern s32 spu_transfer_complete;
extern u8 spu_reverb_clear_buffer[];
extern s32 spu_transfer_event_handle;

extern s32 _spu_t(s32 mode, ...);
extern s32 WaitEvent(s32 event);

#endif

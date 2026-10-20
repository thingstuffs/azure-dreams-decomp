#ifndef SLUS_SOUND_STREAMING_TRANSFER_H
#define SLUS_SOUND_STREAMING_TRANSFER_H

#include "common.h"

extern s32 spu_reverb_start_addresses[10];
extern s32 spu_transfer_uses_fifo;
extern s32 spu_transfer_address_units[4];
extern s32 spu_address_unit_shift;
extern s32 spu_transfer_callback[3];
extern s32 spu_address_alignment_mask[3];
extern volatile s32 spu_transfer_complete[3];
extern u8 spu_reverb_clear_buffer[];
extern s32 spu_transfer_event_handle;

extern s32 func_8005D9DC(u32 value);
extern s32 dispatch_spu_dma_transfer_command(s32 mode, ...);
extern s32 WaitEvent(s32 event);

s32 func_8005E7E0(s32 voice);

#endif

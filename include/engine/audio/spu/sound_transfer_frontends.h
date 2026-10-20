#ifndef SLUS_SOUND_TRANSFER_FRONTENDS_H
#define SLUS_SOUND_TRANSFER_FRONTENDS_H

#include "common.h"

extern u16 spu_transfer_address_units;
extern s32 spu_transfer_uses_fifo;
extern s32 spu_address_unit_shift;

s32 dispatch_spu_dma_transfer_command(s32 command, ...);
void write_spu_transfer_fifo_in_chunks(u16 *src, u32 bytes_left);
s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param);
s32 submit_driver_transfer_mode_zero(s32 buffer_addr, s32 size);

#endif

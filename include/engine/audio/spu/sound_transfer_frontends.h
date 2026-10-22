#ifndef SLUS_SOUND_TRANSFER_FRONTENDS_H
#define SLUS_SOUND_TRANSFER_FRONTENDS_H

#include "common.h"

extern u16 spu_transfer_address_units;
extern s32 spu_transfer_uses_fifo;
extern s32 spu_address_unit_shift;

s32 _spu_t(s32 command, ...);
void _spu_FwriteByIO(u16 *src, u32 bytes_left);
s32 _spu_Fw(s32 channel, s32 playback_param);
s32 _spu_Fr(s32 buffer_addr, s32 size);

#endif

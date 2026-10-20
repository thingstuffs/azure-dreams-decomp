#ifndef SLUS_SOUND_TRANSFER_HELPERS_H
#define SLUS_SOUND_TRANSFER_HELPERS_H

#include "common.h"

extern s32 spu_address_unit_shift;
extern s32 spu_transfer_complete;
extern s32 spu_transfer_callback;
extern s32 spu_transfer_completion_override;
extern s32 spu_transfer_event_handle;
extern u16 spu_transfer_address_units;

s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param);
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 index, u32 value);
s32 TestEvent(s32 event);
s32 clamp_and_submit_driver_parameter(s32 voice, u32 rate);
s32 lookup_and_scale_driver_address(s32 address);
s32 poll_driver_completion_event(s32 wait_for_completion);

#endif

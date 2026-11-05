#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/utility_hooks.h"
#include "slus.h"

/* The shared audio channel control stores this seven-bit value at +0x1C. */

extern AudioChannelControl audio_channel_controls[];


/* Stores value masked to seven bits at index and calls the notifier with the low byte of value. */
void sound_set_seven_bit_channel_value_and_notify(u8 index, s32 unused, s32 value) {
    audio_channel_controls[index].f1C = value & 0x7F;
    noop_channel_control_notification(1, index, value & 0xFF);
}

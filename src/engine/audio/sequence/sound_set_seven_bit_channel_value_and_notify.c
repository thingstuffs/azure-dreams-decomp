#include "common.h"
#include "engine/audio/sequence.h"

/* Element of the shared D_80084960 stat/entity table (stride 0x9C = 156 bytes);
 * only the field at offset 0x1C is touched here. */
typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[0x9C - 0x1C - 4];
} S_80084960; /* size 0x9C */

extern S_80084960 audio_channel_controls[];

extern void noop_channel_control_notification();

/* Stores value masked to seven bits at index and calls the notifier with the low byte of value. */
void sound_set_seven_bit_channel_value_and_notify(u8 index, s32 unused, s32 value) {
    audio_channel_controls[index].unk1C = value & 0x7F;
    noop_channel_control_notification(1, index, value & 0xFF);
}

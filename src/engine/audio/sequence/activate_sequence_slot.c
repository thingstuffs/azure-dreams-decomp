#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"

typedef struct {
    s16 field_0;
    s16 field_2;
    s32 field_4;
    u16 field_8;
    u16 field_A;
} S_80086C00;

typedef struct {
    s32 field_0;
    s32 field_4;
    u16 field_8;
    u16 field_A;
    u8 pad0C[0x40 - 0x0C];
} S_8005B16C_req;

extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[64];
extern s32 audio_sequence_active[4];
extern u8 audio_voice_records[0x78 * 64];
extern s32 audio_update_guard[4];
extern S_80086C00 audio_sequence_slots[8];

/* Dispatches type-3 requests for active channels and marks the selected slot active. */
void activate_sequence_slot(s16 slot_index)
{
    S_8005B16C_req request;
    u8 *channel;
    s32 channel_index;
    s32 *channel_flags;
    S_80086C00 *slots;

    channel_index = 0;
    audio_update_guard[0] = 1;
    if (audio_voice_count[0] > 0) {
        channel_flags = audio_voice_masks;
        channel = audio_voice_records;
loop:
        if (*(u16 *)(channel + 6) < 0x10U) {
            if (*(u16 *)(channel + 0x1A) != 0) {
                s32 request_type;
                request_type = 3;
                request.field_4 = request_type;
                request.field_0 = *channel_flags;
                request.field_8 = *(u16 *)(channel + 0x10);
                request.field_A = *(u16 *)(channel + 0x12);
                func_8005F134(&request);
            }
        }
        channel_flags++;
        channel += 0x78;
        {
            s32 channel_count = audio_voice_count[0];
            do {
                channel_index++;
            } while (0);
            if (channel_index < channel_count)
                goto loop;
        }
    }
    slots = audio_sequence_slots;
    slots[slot_index].field_2 = 1;
    audio_sequence_active[0] = 1;
    audio_update_guard[0] = 0;
}

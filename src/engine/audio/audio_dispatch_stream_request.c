#include "shared/sound_state.h"
#include "common.h"
typedef struct CueRecord {
    u16 value;
    u8 pad_02[0x2];
    u32 base;
    u32 first;
    u32 second;
} CueRecord;

extern CueRecord *func_8003F534(void);
extern int func_80054AF0(int);
extern void activate_pending_playback(void);
extern void sound_begin_cd_playback_setup(void);
extern void audio_handle_stream_control_event(s32);

/* Loads pending CD cue fields from the current record or dispatches a countdown message. */
void audio_dispatch_stream_request(s32 message)
{
    s32 message_type = message & 0xF000;
    switch (message_type) {
    case 0:
    {
        SoundPlaybackState *status;
        u16 record_value;
        CueRecord *record;
        u32 offset_base;
        u32 flags;
        record = func_8003F534();
        record_value = record->value;
        status = &D_800847D0;
        status->unk_1C = record_value;
        offset_base = record->base;
        status->unk_10 = record->first;
        status->unk_14 = record->second;
        status->unk_31 = status->unk_10 >> 24;
        status->unk_33 = status->unk_14 >> 24;
        status->unk_10 &= 0xFFFFFF;
        status->unk_14 &= 0xFFFFFF;
        status->unk_10 -= 0x20;
        status->unk_10 += offset_base;
        status->unk_14 += 0x20;
        status->unk_14 += offset_base;
        status->unk_18 = 0;
        flags = status->flags00;
        if (flags & 0x400) {
            status->flags00 = flags | 0x4000;
            D_80084864[0] = 2;
            break;
        }
        if (status->flags04 & 0x200) {
            break;
        }
        {
            SoundTask *update_state = &D_80084858;
            s16 signed_value;
            int initial_value;
            update_state->unk_04 = 0;
            signed_value = (s16)record_value;
            initial_value = func_80054AF0(signed_value);
            update_state->unk_08 = initial_value;
            update_state->unk_0A = initial_value;
        }
        activate_pending_playback();
        sound_begin_cd_playback_setup();
        break;
    }

    case 0x1000:
        audio_handle_stream_control_event(0x74);
        break;

    case 0x2000:
        audio_handle_stream_control_event(0xE4);
        break;

    case 0x4000:
        audio_handle_stream_control_event(0xF4);
        break;

    }

}

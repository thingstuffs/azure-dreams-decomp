#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"
typedef struct CueRecord {
    u16 value;
    u8 pad_02[0x2];
    u32 base;
    u32 first;
    u32 second;
} CueRecord;

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
        record = read_sound_stream_cue_pointer();
        record_value = record->value;
        status = &sound_playback_state;
        status->stream_attenuation_mode = record_value;
        offset_base = record->base;
        status->pending_start_sector = record->first;
        status->pending_end_sector = record->second;
        status->pending_xa_channel = status->pending_start_sector >> 24;
        status->pending_xa_file = status->pending_end_sector >> 24;
        status->pending_start_sector &= 0xFFFFFF;
        status->pending_end_sector &= 0xFFFFFF;
        status->pending_start_sector -= 0x20;
        status->pending_start_sector += offset_base;
        status->pending_end_sector += 0x20;
        status->pending_end_sector += offset_base;
        status->paused_sector = 0;
        flags = status->flags00;
        if (flags & 0x400) {
            status->flags00 = flags | 0x4000;
            sound_stream_task_word[0] = 2;
            break;
        }
        if (status->flags04 & 0x200) {
            break;
        }
        {
            SoundTask *update_state = &sound_stream_task;
            s16 signed_value;
            int initial_value;
            update_state->fade_mode = 0;
            signed_value = (s16)record_value;
            initial_value = select_audio_mode_attenuation(signed_value);
            update_state->fade_level = initial_value;
            update_state->fade_target = initial_value;
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

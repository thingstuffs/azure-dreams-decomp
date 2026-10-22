/* Double-buffered sound stream selection and loading of sound-set resources from CD. */
#include "slus/gp_af3_pair.h"
#include "common.h"


s8 sound_stream_state_index = -1;

static s16 sound_stream_buffer_index;
/* Selects a buffered sound stream, loading it and its sound set from CD when needed, then starts playback. */
s32 select_sound_stream(s16 entry_index, s16 mode)
{
    if (sound_stream_resource_entries[entry_index] == sound_stream_buffer_entries[sound_stream_buffer_index]) {
        return 1;
    }

    sound_stream_buffer_index = (u16) sound_stream_buffer_index ^ 1;

    if (sound_stream_resource_entries[entry_index] != sound_stream_buffer_entries[sound_stream_buffer_index]) {
        drain_audio_commands_and_service_channels();

        if (sound_stream_state_index != mode) {
            wait_until_sound_idle();
        }

        sound_stream_resource_entries[entry_index]->field_0 &= ~0x7FFFFF;
        sound_stream_resource_entries[entry_index]->field_0 |=
            ((sound_stream_buffer_index != 0) ? (s32) sound_stream_secondary_marker_address : (s32) sound_stream_primary_marker_address) & 0x7FFFFF;

        Control_CD(6, sound_stream_resource_entries[entry_index], 0);
        sound_stream_buffer_entries[sound_stream_buffer_index] = sound_stream_resource_entries[entry_index];
        drain_cd_command_queue();
    }

    load_sound_set(mode);

    SD_Call((sound_stream_buffer_index != 0) ? 0x22 : 0x21);

    return 0;
}

/* Loads a changed sound set and its payload from CD, submits it to the driver and waits for readiness. */
s32 load_sound_set(s16 state_index)
{
    if (sound_stream_state_index != state_index) {
        S_8006E6F4 *state_table = sound_set_resources;
        S_8006E6F4 *state_entry = state_table + state_index;

        Control_CD(6, (void *)state_entry->field4, 0);
        DrawSync(0);
        {
            void *state_callback = state_entry->field0;
            gpu_scratch_write_pointer = gpu_scratch_buffer_base;
            Control_CD(6, state_callback, 0);
        }
        sound_stream_state_index = (s8)state_index;
        drain_cd_command_queue();
        set_sound_payload_slot(gpu_scratch_buffer_base);
        SD_Call(0x11);
        drain_audio_commands_and_service_channels();
        while (test_sound_channel_availability(0) != 1) {
        }
        return 0;
    }
    return 1;
}

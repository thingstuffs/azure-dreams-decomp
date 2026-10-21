#include "engine/audio/spu/sound_reset_state.h"
#include "engine/audio/spu.h"



/* Resets SPU playback state and initializes voice sentinels for the master channel. */
void reset_spu_runtime_and_start_event_service(s32 channel)
{
    s32 saved_channel = channel;
    s32 channel_value;
    s32 voice_index;

    ResetCallback(channel);
    initialize_spu_registers_and_voices(saved_channel);

    if (saved_channel == 0) {
        u16 sentinel = 0xC000;
        for (voice_index = 23; voice_index >= 0; voice_index--) {
            spu_voice_sample_notes[voice_index] = sentinel;
        }
    }

    start_spu_dma_event_service();

    channel_value = spu_reverb_start_addresses[0];

    spu_reverb_enabled = 0;
    spu_reverb_range_override = 0;
    spu_reverb_mode = 0;
    spu_reverb_depth_left = 0;
    spu_reverb_depth_right = 0;
    spu_reverb_delay = 0;
    spu_reverb_feedback = 0;
    spu_reverb_start_address = (u32)channel_value;

    store_u16_table_entry(0xD1, channel_value, 0);

    spu_ram_block_record_count = 0;
    D_800799B8 = 0;
    spu_ram_block_records = 0;
    spu_transfer_completion_override = 0;
    spu_transfer_uses_fifo = 0;
    spu_active_voice_mask = 0;
    spu_register_dirty_flags = 0;
    spu_buffered_voice_mask = 0;
    spu_register_buffer_flags = 0;
}

/* Records and returns whether enabled and the stored pointer has no matching entry. */
s32 set_reverb_address_available(s32 enabled) {
    s32 check_result;

    if (enabled != 0) {
        check_result = test_spu_blocks_beyond_address(spu_reverb_start_address);
        if (check_result == 0) {
            spu_reverb_range_override = 1;
            return 1;
        }
    }
    spu_reverb_range_override = 0;
    return 0;
}

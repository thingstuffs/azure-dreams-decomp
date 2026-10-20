#include "shared/sound_state.h"
#include "common.h"

/* S_8006E61C: 12-byte record array indexed by a signed 16-bit id.
 * field0 (u16) is a counter/state value; field4 and field8 are pointers
 * forwarded to Control_CD (callback registration). */
typedef struct {
    u16 field0;
    s16 pad2;
    void *field4;
    void *field8;
} S_8006E61C;
extern S_8006E61C sound_effect_bank_descriptors[];

/* Per-id "last processed" byte counter, indexed by field0-1. */
extern u8 sound_effect_loaded_record_ids[];

extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* switch dispatcher on pad events; takes no arguments (matched, gcc 2.7.2, code.c) */
extern void drain_audio_commands_and_service_channels(void);

extern void DrawSync(s32 a0);

/* registers a callback (kind, callback-ptr, arg) (matched, code.c) */
extern s32 Control_CD(s32 a0, void *a1, void *a2);

/* runs one step of the main loop while a condition holds (matched, code.c) */
extern void drain_cd_command_queue(void);

/* setter for D_800814C8 (matched, gcc 2.7.2, code.c) */
extern void set_sound_payload_slot(s32 a0);

/* masks a0 to 16 bits and forwards to func_80055778, sign-extends result (matched, code.c) */
extern short SD_Call(s32 a0);

/* tests availability bit n of D_800847D0 (matched, gcc 2.8.1, w_8005405C.c) */
extern s32 test_sound_channel_availability(s16 n);

/* Activates an unprocessed record, registers its callbacks, and waits for availability. */
void audio_load_sound_effect_bank(s16 record_id)
{
    S_8006E61C *record;
    s16 slot;
    u8 *processed_id;
    s32 ready_value;
    s32 available;

    {
        s32 record_offset = (s32)record_id * sizeof(S_8006E61C);
        record = (S_8006E61C *)((char *)sound_effect_bank_descriptors + record_offset);
    }
    slot = (s16)((u16)record->field0 - 1);
    processed_id = &sound_effect_loaded_record_ids[slot];
    if (*processed_id != record_id + 1) {
        drain_audio_commands_and_service_channels();
        *processed_id = (u8)(record_id + 1);
        DrawSync(0);
        {
            void *callback = record->field8;
            gpu_scratch_write_pointer = gpu_scratch_buffer_base;
            Control_CD(6, callback, 0);
        }
        Control_CD(6, record->field4, 0);
        drain_cd_command_queue();
        ready_value = 1;
        set_sound_payload_slot(gpu_scratch_buffer_base);
        SD_Call(((2 << slot) | 0x10) & 0xFFFF);
        drain_audio_commands_and_service_channels();
        do {
            available = (s16)test_sound_channel_availability(record->field0);
        } while (available != ready_value);
    }
}

#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c / w_80054E00.c). This function only reads
   flags1 (offset 0x0). */

/* Canonical task/timer object struct (established in w_800559B4.c /
   w_800540A8.c / w_80054C58.c / w_80054E00.c). Only its address is taken by
   this function, no fields accessed here. */

/* Canonical task/event object struct (established in w_8005440C.c). Only its
   address is taken by this function, no fields accessed here. */


extern void assign_sound_payload_and_release_channel(u16 a0);
extern void select_marker_table(u16 a0);
extern void handle_audio_status_code(u8 a0);
extern void func_80054104(void);
extern void audio_handle_stream_control_event(s32 a0);
extern void dispatch_audio_mix_action(u8 a0);
extern void set_sound_task_priority(u32 a0, void *a1);

/* Dispatches packed events by status nibble and enabled event flags. */
void dispatch_audio_event(s32 event) {
    s32 event_bits = event;
    register s16 packed_event = event_bits;

    switch (event_bits & 0xF0) {
    case 0x10:
        assign_sound_payload_and_release_channel((u16)packed_event);
        break;
    case 0x20:
        select_marker_table((u16)packed_event);
        break;
    case 0x70:
        if (event_bits & 1) {
            handle_audio_status_code(0x71);
        }
        if (event_bits & 2) {
            func_80054104();
        }
        if (event_bits & 4) {
            audio_handle_stream_control_event(0x74);
        }
        break;
    case 0xE0:
        if (event_bits & 1) {
            handle_audio_status_code(0xE1);
        }
        if (event_bits & 4) {
            audio_handle_stream_control_event(0xE4);
        }
        break;
    case 0xF0:
        if (event_bits & 1) {
            handle_audio_status_code(0xF1);
        }
        if (event_bits & 4) {
            audio_handle_stream_control_event(0xF4);
        }
        break;
    case 0xB0:
    case 0xC0:
    case 0xD0:
        if (packed_event & 1) {
            if (sound_playback_state.flags00 & 0x100) {
                if (!(sound_playback_state.flags00 & 0x1000)) {
                    set_sound_task_priority(packed_event & 0xFFF1, &sound_sequence_task);
                }
            }
        }
        if (packed_event & 4) {
            if (sound_playback_state.flags00 & 0x400) {
                if (!(sound_playback_state.flags00 & 0x4000)) {
                    set_sound_task_priority(packed_event & 0xFFF4, &sound_stream_task);
                }
            }
        }
        break;
    default:
        dispatch_audio_mix_action(packed_event & 0xFF);
        break;
    }
}

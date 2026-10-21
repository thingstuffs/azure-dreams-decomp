#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/entity.h"
#include "engine/resource.h"
#include "slus.h"

struct S_8006CE80
{
    u16 field_0;
    u16 field_2;
    void *field_4;
    u32 field_8;
};
extern struct S_8006CE80 dispatch_resource_records[];

extern s8 scene_music_hold[12];
/* Updates the requested state and triggers transition handling when needed. */
void request_scene_dispatch_state(s16 requested_state)
{
    u16 state_index = ((u16) requested_state) & 0xFFFF;
    struct S_8006CE80 *state_entry = &dispatch_resource_records[state_index];
    s32 current_state;
    if (runtime_dispatch_state.unk_08 == 3) {
        return;
    }
    if ((state_index == 6) && (runtime_dispatch_state.mode == 2)) {
        reset_tagged_entry_states();
    }
    runtime_dispatch_state.unk_0E = 1;
    current_state = runtime_dispatch_state.mode;
    runtime_dispatch_state.unk_08 = requested_state;
    if (current_state != state_entry->field_0) {
        if ((((u16) requested_state) & 0xFFFF) == 5) {
            SD_Call(0x72);
        }
        *(s8 *)0x80080A88 = 0;
    }
    if (scene_music_hold[0] == 0) {
        SD_Call(0xCF);
        drain_audio_commands_and_service_channels();
    }
}

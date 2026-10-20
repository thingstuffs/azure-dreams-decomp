#include "common.h"

extern void reset_audio_command_state(void);
extern void reinit_audio_voices(void);
extern void set_cd_audio_mix_mode(s32 a0);

/* Dispatches an audio action by its low byte, preserving the low 16 bits for volume updates. */
void func_80054A7C(s32 action) {
    u16 action_value = action;
    action = action & 0xFF;
    if (action != 3) {
        if (action >= 4) {
            if (action != 4) {
                return;
            }
        } else {
            if (action == 0) {
                return;
            }
            set_cd_audio_mix_mode(action_value & 0xFFFF);
            return;
        }
    } else {
        reset_audio_command_state();
        return;
    }
    reinit_audio_voices();
    return;
}

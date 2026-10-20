#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_80054C58.c, etc.) */

/* Canonical "task/timer object" struct (see src/w_800552C8.c). */


extern void sound_reset_sequence_slot_to_idle(s16 a0);
extern void sound_free_sequence_slot(s16 a0);
extern void start_pending_selection(void);
extern void suspend_sequence_slot(s16 a0);
extern void activate_sequence_slot(s16 a0);

/* Clears, activates, or deactivates a status effect according to the supplied code. */
void handle_audio_status_code(u8 code) {
    switch (code) {
    case 0x71:
        if (D_800847D0.flags00 & 0x1100) {
            D_800848F8.unk_08 = 0;
            func_800552C8();
            sound_reset_sequence_slot_to_idle(D_800847D0.unk_22);
            sound_free_sequence_slot(D_800847D0.unk_22);
        }
        D_800848F8.unk_04 = 0;
        D_800847D0.flags00 &= ~0x100;
        D_800847D0.flags00 &= ~0x1000;
        D_800847D0.flags04 &= ~2;
        if (D_800847D0.unk_26 != -1) {
            start_pending_selection();
        }
        break;
    case 0xE1:
        if (D_800847D0.flags00 & 0x100) {
            suspend_sequence_slot(D_800847D0.unk_22);
            D_800847D0.flags00 = (D_800847D0.flags00 & ~0x100) | 0x1000;
        }
        break;
    case 0xF1:
        if (D_800847D0.flags00 & 0x1000) {
            activate_sequence_slot(D_800847D0.unk_22);
            D_800847D0.flags00 = (D_800847D0.flags00 & ~0x1000) | 0x100;
        }
        break;
    }
}

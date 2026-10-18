#include "common.h"

/* Slot-table element (see sibling audio_get_current_bank_tone_record for the confirmed 0x1C-byte
 * stride layout of D_80086A40). Only the fields this function touches are
 * named; the rest is padding. */
typedef struct {
    /* 0x00 */ s16 unk00;      /* slot-marker; negative == unused */
    /* 0x02 */ u8 pad02[0xE];
    /* 0x10 */ s32 unk10;      /* value passed to func_8005A1D0 */
    /* 0x14 */ u8 pad14[0x8];
} S_8005A428_D80086A40; /* size 0x1C (28) */

extern int D_80086D4C[3]; /* forced hi/lo via size > 8 */
extern S_8005A428_D80086A40 D_80086A40[16];

extern void audio_reset_all_voices(void);
extern void close_timer_2_update_event(void);
extern void func_8005A1D0(s32 addr);
extern void func_8005A26C(void);

/* Runs frame updates, processes active slots among the first eight, and resets the slot table. */
void audio_reset_and_release_sequence_banks(void)
{
    s32 slot_index;
    S_8005A428_D80086A40 *slot;

    audio_reset_all_voices();

    if (D_80086D4C[0] > 0) {
        if (D_80086D4C[0] < 4) {
            close_timer_2_update_event();
        }
    }
    slot_index = 0;

    slot = D_80086A40;
    for (; slot_index < 8; slot_index++, slot++) {
        if (slot->unk00 >= 0) {
            func_8005A1D0(slot->unk10);
        }
    }

    func_8005A26C();
}

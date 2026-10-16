#include "common.h"

/* S_80086C00: 12-byte-stride entry table (8 entries), indexed by the
 * slot index arg0. field_0/field_2 are s16, field_4 is a s32 data
 * pointer, field_8/field_A are u16 (accessed here). */
typedef struct S_80086C00 {
    /* 0x00 */ s16 field_0;
    /* 0x02 */ s16 field_2;
    /* 0x04 */ s32 field_4;
    /* 0x08 */ u16 field_8;
    /* 0x0A */ u16 field_A;
} S_80086C00; /* size 0xC (12) */

extern S_80086C00 D_80086C00[8];
extern s32 D_800737A4[4]; /* forced hi/lo access via size > 8 */
extern s32 D_80085F98[4]; /* forced hi/lo access via size > 8 */

extern void slusActivateEntriesAndClearState(void);
extern void audioResetSequenceTracksAndChannels(void);

/* Resets sound driver state and restores the selected sequence slot to idle defaults. */
void soundResetSequenceSlotToIdle(s16 slot_index)
{
    S_80086C00 *slots;
    int zero;

    D_80085F98[0] = 1;
    zero = 0;
    D_800737A4[0] = zero;
    slusActivateEntriesAndClearState();
    audioResetSequenceTracksAndChannels();
    slots = D_80086C00;
    slots[slot_index].field_A = 0x7F;
    slots[slot_index].field_8 = 0x7F;
    slots[slot_index].field_2 = 2;
    D_80085F98[zero] = 0;
}

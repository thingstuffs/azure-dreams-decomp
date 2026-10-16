#include "shared/sound_state.h"
#include "common.h"

/* Canonical status block shared across the D_800847D0 family (see w_8005405C.c etc). */

extern void *D_80084538[];
extern void *D_800847C0[];
extern void *D_80084758[];

extern s32 func_8005A778(void *a0, s16 a1, void *a2);
extern s32 func_8005AAA8(void *a0, s32 a1);
extern void releaseEnabledSoundChannel(s32 a0);
extern void identityInt(s32 a0);
extern void soundCheckOrWaitForSpuTransfer(s32 a0);

/* Initializes an entry, marking it available on success or reporting an error on failure. */
void soundLoadPendingBankSlot(s16 entry_id) {
    s32 entry_index = entry_id;
    s32 index_or_error;
    index_or_error = entry_index;
    if ((s16)func_8005A778(D_80084538[index_or_error], index_or_error, D_800847C0[index_or_error]) == -1) {
        index_or_error = 0x01010000;
        identityInt(((entry_index << 8) & 0xFF00) | index_or_error);
    } else if ((s16)func_8005AAA8(D_80084758[index_or_error], entry_index) == -1) {
        releaseEnabledSoundChannel(index_or_error);
        index_or_error = 0x01020000;
        identityInt(((entry_index << 8) & 0xFF00) | index_or_error);
    } else {
        soundCheckOrWaitForSpuTransfer(1);
        D_800847D0.flags00 |= (0x10000 << entry_index);
    }
}

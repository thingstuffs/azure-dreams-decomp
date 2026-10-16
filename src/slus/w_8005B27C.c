#include "common.h"

typedef struct {
    s16 field_0;
    char pad4[6];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 D_80086C00[8];

extern void audioRefreshSequenceVoiceVolumes(void);

/* Stores two 7-bit values in the selected entry, then calls audioRefreshSequenceVoiceVolumes for it. */
void setSoundSlotBytePair(s16 index, s32 value_8, s32 value_a)
{
    S_80086C00 *entries = D_80086C00;
    S_80086C00 *entry = entries + index;
    entry->field_8 = value_8 & 0x7F;
    entry->field_A = value_a & 0x7F;
    audioRefreshSequenceVoiceVolumes();
}

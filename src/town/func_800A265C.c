#include "common.h"

extern u32 func_800B28A0(void);
extern void townLoadASharedBufferProcessWriteBack(void *record_ref);
extern void setResidentBitmapBit(s32 bit_id);
extern s32 D_800D0728[];
extern s16 D_800D253C[];

/* Processes entries in state 19 and triggers their associated sounds. */
void townProcessEntriesInStateN19TriggersAssociatedSounds(void) {
    s32 entry_count;
    s32 entry_index;
    s16 *sound_id;
    u8 *entry;
    u8 state;

    entry_count = D_800D0728[func_800B28A0()];
    do {
        entry_index = 0;
    } while (0);
    if (entry_count > 0) {
        sound_id = D_800D253C;
        entry = (u8 *)0x80010000;
loop:
        state = entry[0x981];
        if (state != 0) {
            if (state == 19) {
                townLoadASharedBufferProcessWriteBack((void *)(0x80010A80 + ((entry[0x983] & 0x3F) * 84)));
                setResidentBitmapBit(*sound_id);
            }
        }
        sound_id++;
        entry_index++;
        entry += 4;
        if (entry_index < entry_count) {
            goto loop;
        }
    }
}

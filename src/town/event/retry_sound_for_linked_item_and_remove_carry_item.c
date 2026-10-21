#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A9D00_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_800A9D00_0;

typedef struct S_800A9D00_1 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800A9D00_1;   /* base in retry_sound_for_linked_item_and_remove_carry_item */

typedef struct S_800A9D00_2 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_800A9D00_2;   /* ((S_800A9D00_1 *)base)->unk_2C in retry_sound_for_linked_item_and_remove_carry_item */


extern s32 get_linked_carry_item_data();
extern s32 plt_carry_item_del_ext();
extern s32 retry_sound_sequence_when_ready();
extern s8 scene_object_payload_alias[0x30];

/* Invokes retry_sound_sequence_when_ready for an eligible linked object with code 0xD04, then calls plt_carry_item_del_ext. */
void retry_sound_for_linked_item_and_remove_carry_item(void) {
    s8 *stateBase;
    S_800A9D00_0 *precedingState;

    stateBase = scene_object_payload_alias;
    precedingState = stateBase - 0x20;
    if ((get_linked_carry_item_data(stateBase, precedingState->unk_08,
                       precedingState->unk_0C) != 0) &&
        (((S_800A9D00_1 *)stateBase)->unk_2C != NULL) &&
        (((S_800A9D00_2 *)(((S_800A9D00_1 *)stateBase)->unk_2C))->unk_4C == 0xD04)) {
        retry_sound_sequence_when_ready();
    }
    plt_carry_item_del_ext();
}

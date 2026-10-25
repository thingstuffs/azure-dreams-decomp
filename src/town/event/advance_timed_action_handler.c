#include "common.h"
typedef struct {
    s32 unk0;
    void **unk4;
    u16 unk8;
    u16 unkA;
} Struct8009D814;
void advance_player_state_table(Struct8009D814 *state, s32 update_arg, s32 shared_arg);

typedef struct S_8009B0EC_0 {
    u8 pad_00[0x4];
    void (*unk_04)(Struct8009D814 *, s32,  s32);
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009B0EC_0;   /* arg0 in advance_timed_action_handler */

/* Decrement the countdown, then reset it and switch handlers when it expires. */
void advance_timed_action_handler(S_8009B0EC_0 *object) {
    u16 countdown;

    countdown = object->unk_0A - 1;
    object->unk_0A = countdown;
    if ((countdown << 0x10) <= 0) {
        object->unk_0A = 3U;
        object->unk_04 = &advance_player_state_table;
    }
}

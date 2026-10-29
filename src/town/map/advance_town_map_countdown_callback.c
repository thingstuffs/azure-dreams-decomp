#include "common.h"
#include "m2c_compat.h"
#include "town/map.h"

typedef struct S_8008BA00_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    u8 pad_66[0x2];
    void (*unk_68)(struct S_8008BA00_0 *state, void *position, void *sprite);
    void (*unk_6C)(struct S_8008BA00_0 *state, void *position, void *sprite);
} S_8008BA00_0;   /* arg0 in advance_town_map_countdown_callback */


/* Decrement the countdown and activate the next callback when it becomes negative. */
void advance_town_map_countdown_callback(S_8008BA00_0 *state, void *position, void *sprite) {
    void (*next_callback)(S_8008BA00_0 *, void *, void *);
    u16 countdown;

    countdown = state->unk_64 - 1;
    state->unk_64 = countdown;
    if ((s16) countdown < 0) {
        next_callback = state->unk_6C;
        state->unk_68 = next_callback;
        next_callback(state, position, sprite);
    }
}

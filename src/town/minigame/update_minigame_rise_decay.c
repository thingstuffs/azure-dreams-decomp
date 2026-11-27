#include "common.h"
#include "town/minigame.h"
#include "shared/sprite_frame_state.h"

typedef struct Town215E0Inner {
    u8 pad0[0x5C];
    s16 mode;
} Town215E0Inner;

typedef struct Town215E0State {
    Town215E0Inner *inner;
    s16 state;
    s16 timer;
} Town215E0State;

/* Raise the mesh angle when the reels start, then lower it back to zero. */
void update_minigame_rise_decay(Town215E0State *cycle, ObjectPosition *unused_position, LitMeshSprite *sprite) {
    u16 reduced_value;

    cycle->timer--;
    switch (cycle->state) {
    case 0:
        if (cycle->inner->mode == 4) {
            cycle->timer = 10;
            cycle->state++;
        }
        break;

    case 1:
        sprite->rotation[0] += 64;
        if (cycle->timer <= 0) {
            cycle->state++;
        }
        break;

    case 2:
        reduced_value = sprite->rotation[0] - 24;
        sprite->rotation[0] = reduced_value;
        if (reduced_value < 24) {
            sprite->rotation[0] = 0;
            cycle->state = 0;
        }
        break;

    default:
        break;
    }
}

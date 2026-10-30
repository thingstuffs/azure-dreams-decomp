#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/position.h"


typedef struct S_80020260_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0xA];
    s16 unk_36;
} S_80020260_1;   /* object in fade_scene_tile_across_terminal_phase */


/* Fades an effect in and out around an object event, then marks completion. */
void fade_scene_tile_across_terminal_phase(SceneTileObject *effect) {
    s16 state;
    s32 color;
    s32 faded_color;
    S_80020260_1 *object;

    state = effect->state.s;
    object = effect->linked;

    switch (state) {
    case 0:
        if (object->unk_36 != 0xFF) {
            break;
        }
        effect->flags &= 0xFFFD;
        effect->state.u++;
        break;
    case 1:
        color = effect->color;
        if (color <= 0x40403F) {
            effect->color = color + 0x80808;
        }
        if ((object->unk_2A & 1) == 0) {
            break;
        }
        effect->state.u++;
        break;
    case 2:
        faded_color = effect->color + (s32)0xFFF7F7F8;
        effect->color = faded_color;
        if (faded_color <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}

/* MECHANISM: Retail is a frameless leaf; 0x80020358 is its local epilogue.
   State labels preserve block order and the jump delay-slot stores.
   Split state-1/state-2 values free $a0 for the object and yield $v1/$v0 roles. */

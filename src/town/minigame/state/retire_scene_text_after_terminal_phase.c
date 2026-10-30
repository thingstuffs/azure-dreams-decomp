#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/state.h"

typedef struct S_80020488_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0xA];
    s16 unk_36;
} S_80020488_1;   /* entity in retire_scene_text_after_terminal_phase */


/* Advances the context state and sets completion flags in response to entity fields. */
void retire_scene_text_after_terminal_phase(TerminalSceneTextObject *context) {
    s16 state;
    S_80020488_1 *entity;

    state = context->state.s;
    entity = context->owner;
    switch (state) {
    case 0:
        if (entity->unk_36 == 0xFF) {
            context->flags &= 0xFFFD;
            context->state.u++;
        }
        break;
    case 1:
        if (entity->unk_2A & 1) {
            (*(u16 *)((u8 *)context + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}

/* MECHANISM: Frameless leaf with an explicit dispatch, state 0 before state 1, and a shared return.
   Width-accurate fields keep RMW order. */

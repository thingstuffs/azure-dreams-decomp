#include "town/minigame/keima.h"
#include "shared/object_flags.h"
#include "town/minigame.h"

typedef union KeimaFadeNode {
    KeimaFadeState *body;
    ObjectNodeHeader *node;
} KeimaFadeNode;

void fade_completed_keima_color(KeimaFadeState *effect) {
    s32 phase;
    u16 phase_value;
    s32 color;
    KeimaState *owner;
    KeimaFadeNode view;

    owner = effect->owner;
    phase = effect->phase.s;
    phase_value = effect->phase.u;
    switch (phase) {
    case 0:
        if (owner->flags & NODE_REMOVE) {
            effect->phase.u = phase_value + 1;
        }
        break;
    case 1:
        color = effect->color + 0xFFF7F7F8;
        effect->color = color;
        if (color <= 0x80808) {
            view.body = effect;
            view.node[-1].flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}

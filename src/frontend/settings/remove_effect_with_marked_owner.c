#include "frontend/settings.h"
#include "shared/object_flags.h"

typedef struct MenuOwner {
    u8 pad_00[0x16];
    s16 flags;
} MenuOwner;

typedef struct MenuEffect {
    u8 pad_00[0xC];
    MenuOwner *owner;
} MenuEffect;

void remove_effect_with_marked_owner(void *body) {
    MenuEffect *effect = body;
    /* The object-node flag halfword precedes its callback body. */
    u16 *body_words = body;
    if (effect->owner->flags & NODE_REMOVE) {
        body_words[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

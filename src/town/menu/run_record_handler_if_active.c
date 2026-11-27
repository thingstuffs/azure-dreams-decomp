#include "common.h"
#include "slus/imports.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/menu.h"

/* Call the record handler and update its data if the record remains active. */
void run_record_handler_if_active(TownObjectRecord *record, ObjectPosition *position, SpriteFrameState *sprite) {
    void (*handler)(TownObjectRecord *, ObjectPosition *, SpriteFrameState *);

    handler = record->state_callback.as_pm;
    if (handler != 0) {
        handler(record, position, sprite);
        if (!(NODE_HEADER(record)->flags & NODE_REMOVE)) {
            advance_sprite_animation_and_textures(sprite);
        }
    }
}

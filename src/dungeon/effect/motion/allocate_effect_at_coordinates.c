#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/spell_effect.h"
#include "slus.h"

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800DE8E8[];

/* Create the positioned sprite that advances the controller's counter. */
ObjectNodeHeader *allocate_effect_at_coordinates(struct OrbitBurstSpell *owner, SpellMotion *source_coords) {
    SpriteFrameState *sprite;
    ObjectNodeHeader *object;
    LinkedCounterSpriteBody *body;
    ObjectPosition *coords;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->update_callback = advance_linked_object_counter;
        sprite = object->sprite;
        body = NODE_BODY(object);
        body->owner = owner;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, &D_800DE8E8, 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        register_node(object, project_sprite_chain);
        coords = object->position;
        coords->x.w.i = source_coords->x.w.i;
        coords->y.w.i = source_coords->y.w.i;
        coords->z.w.i = source_coords->z.w.i;
        return object;
    } else {
        return NULL;
    }
}

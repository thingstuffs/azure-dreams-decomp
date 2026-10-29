#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "dungeon/effect/motion.h"
#include "slus.h"

typedef s32 M2C_UNK;

   /* arg0 in create_type_212_effect_object */

extern s32 D_80024374;

/* Creates a type 0x212 object, initializes its appearance, and copies the supplied components. */
void *create_type_212_effect_object(MovingPosition *source) {
    SpriteFrameState *appearance;
    ObjectNodeHeader *object;
    ObjectPosition *components;
    void *result; /* MATCH: Keep the merged return value in v0 for the shared epilogue. */

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->update_callback = &D_80024374;
        appearance = object->sprite;
        appearance->color.c.b = 0x80;
        appearance->color.c.g = 0x80;
        appearance->color.c.r = 0x80;
        select_record_entry_and_value(appearance, effect_sprite_sources, 0);
        appearance->scale_y = 0x2000;
        appearance->scale_x = 0x2000;
        register_node(object, project_sprite_chain);
        components = object->position;
        components->x.w.i = source->x;
        components->y.w.i = source->y;
        components->z.w.i = source->z;
        result = object;
        return result;
    } else {
        result = 0;
        return result;
    }
}

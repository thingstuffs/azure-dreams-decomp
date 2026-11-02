#include "shared/sprite_frame_state.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;


extern Copy12 D_80173B1C;



/* Allocate a type 0x12 object, clear its state, and attach a copy of the default data. */
void create_encounter_view_darkener(void)
{
    ObjectNodeHeader * object;
    ObjectPosition *axis_state;
    SpriteFrameState *data_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = darken_encounter_view_color;
        register_node(object, draw_linked_sprites);

        axis_state = object->position;
        axis_state->z.w.i = 0;
        axis_state->y.w.i = 0;
        axis_state->x.w.i = 0;

        data_state = object->sprite;
        data_state->scale_y = 0;
        data_state->scale_x = 0;
        data_state->color.c.b = 0;
        data_state->color.c.g = 0;
        data_state->color.c.r = 0;

        (*(Copy12 *)((u8 *)object + 0x48)) = D_80173B1C;
        data_state->source = (u8 *)object + 0x48;
    }
}

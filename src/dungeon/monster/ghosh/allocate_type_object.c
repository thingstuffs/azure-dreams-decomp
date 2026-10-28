#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"






typedef struct S_8016AD00_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016AD00_0;   /* part1 in allocate_type_12_object */

typedef struct S_8016AD00_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016AD00_1;   /* part2 in allocate_type_12_object */

/* Allocate a type 0x12 object and initialize its state and default data. */
/* Creates a zero-sized black sprite at the origin with a copied 12-byte entry from D_80077818 and its
 * update callbacks. */
void allocate_type_12_object(void)
{
    ObjectNodeHeader * object;
    ObjectPosition *primary_state;
    SpriteFrameState *secondary_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = advance_three_state_bytes;
        register_node(object, draw_linked_sprites);

        primary_state = object->position;
        primary_state->z.w.i = 0;
        primary_state->y.w.i = 0;
        primary_state->x.w.i = 0;

        secondary_state = object->sprite;
        secondary_state->scale_y = 0;
        secondary_state->scale_x = 0;
        secondary_state->color.c.b = 0;
        secondary_state->color.c.g = 0;
        secondary_state->color.c.r = 0;

        (*(GhoshSpriteTemplate *)((u8 *)object + 0x4C)) = ghosh_sprite_payload_template;
        secondary_state->source = (u8 *)object + 0x4C;
    }
}

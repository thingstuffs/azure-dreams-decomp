#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"






typedef struct S_8016AC30_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016AC30_0;   /* position in allocate_and_initialize_object */

typedef struct S_8016AC30_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016AC30_1;   /* primitive in allocate_and_initialize_object */

/* Allocate and initialize a dungeon object, then increment the object count. */
void allocate_and_initialize_object(void) {
    ObjectNodeHeader * object;
    ObjectPosition *position;
    SpriteFrameState *primitive;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = animate_timed_fade_effect;
        register_node(object, draw_linked_sprites);

        position = object->position;
        position->z.w.i = 0;
        position->y.w.i = 0;
        position->x.w.i = 0;

        primitive = object->sprite;
        primitive->scale_y = 0;
        primitive->scale_x = 0;
        primitive->color.c.b = 0;
        primitive->color.c.g = 0;
        primitive->color.c.r = 0;

        (*(GhoshSpriteTemplate *)((u8 *)object + 0x4C)) = ghosh_sprite_payload_template;
        primitive->source = (u8 *)object + 0x4C;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}

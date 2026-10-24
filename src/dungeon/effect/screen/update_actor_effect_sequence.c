#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024578_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80024578_0;   /* object in update_actor_effect_sequence */

   /* part in update_actor_effect_sequence */

   /* arg0 in update_actor_effect_sequence */

extern s32 draw_textured_ellipse();
extern u8 D_800243C4[9];
extern u8 D_80028208[9];
extern u8 D_800DF334[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *update_actor_effect_sequence(MovingPosition *source_part, s32 offset_base) {
    s32 init_data[2];
    ObjectNodeHeader *object;
    ObjectPosition *part;
    SpriteFrameState *effect;
    void *result;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        init_data[0] = 0x01000340;
        init_data[1] = 0x00200020;
        draw_textured_ellipse(D_800DF334, init_data, 1, 0);

        part = object->position;
        object->update_callback = D_800243C4;
        part->x.w.i = source_part->x;
        part->y.w.i = source_part->y;
        part->z.w.i = source_part->z;

        effect = object->sprite;
        effect->source = D_80028208;
        effect->scale_y = 0xC00;
        effect->scale_x = 0xC00;
        ((S_80024578_0 *)object)->unk_28 = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = (u8 *)object + 0x20;
    }
    return result;
}

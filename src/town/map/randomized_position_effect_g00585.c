#include "shared/entity.h"
/* Randomized position effect (G00585).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AAD70.
 */
#include "town/map/randomized_position_effect_g00585.h"
#include "shared/object_node.h"

/* Creates an effect at the supplied position and initializes its sprite and random state. */
void *create_randomized_position_effect(MovingPosition *source_position) {

    s32 random_offset;
    SpriteFrameState *sprite;
    ObjectPosition *position;
    ObjectNodeHeader *object;
    S_800A84D0_4 *effect_state;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        position = object->position;
        sprite = object->sprite;
        object->update_callback = &fade_timed_primitive;
        register_node(object, project_sprite_chain);
        position->x.w.i = (u16) source_position->x;
        position->y.w.i = (u16) source_position->y;
        position->z.w.i = (u16) source_position->z;
        select_record_entry_and_value(sprite, &radial_sprite_entries, 0);
        sprite->color.c.b = 0xFF;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags = (u16) (sprite->flags | 0xC);
        random_offset = scale_random_to_unsigned_halfword_limit(7);
        effect_state = ((void *)object) + 0x20;
        effect_state->unk_02 = (s16) (random_offset + scale_random_to_unsigned_halfword_limit(7));
    }
    return object;
}

/* Builds and submits records at randomized offsets from the origin. */
void build_randomized_offset_records(void *origin, void *spread, s32 count) {

    LocalRecord record;
    s32 index;
    s32 z;

    if (count != 0) {
        index = 0;
        rand();
        record.z = *(u16 *)((u8 *)origin + 0xA);
        record.unk16 = -4;
        while (index < count) {
            index++;
            record.x = (*(u16 *)((u8 *)origin + 2) +
                        scale_random_to_unsigned_halfword_limit(*(u16 *)spread)) -
                      (*(s32 *)spread / 2);
            record.y = (*(u16 *)((u8 *)origin + 6) +
                        scale_random_to_unsigned_halfword_limit(*(u16 *)((u8 *)spread + 4))) -
                      (*(s32 *)((u8 *)spread + 4) / 2);
            z = (*(u16 *)((u8 *)origin + 0xA) -
                 scale_random_to_unsigned_halfword_limit(*(u16 *)((u8 *)spread + 8))) -
                    (*(s32 *)((u8 *)spread + 8) / 2);
            record.z = z;
            create_randomized_position_effect((MovingPosition *)&record);
        }
    }
}

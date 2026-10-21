/* Randomized position effect (G00585).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AAD70.
 */
#include "town/map/randomized_position_effect_g00585.h"

/* Creates an effect at the supplied position and initializes its sprite and random state. */
void *create_randomized_position_effect(MovingPosition *source_position) {

    s32 random_offset;
    SpriteFrameState *sprite;
    MovingPosition *position;
    void *object;
    S_800A84D0_4 *effect_state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        position = ((S_800A84D0_0 *)object)->unk_08;
        sprite = ((S_800A84D0_0 *)object)->unk_0C;
        ((S_800A84D0_0 *)object)->unk_10 = &fade_timed_primitive;
        register_node(object, project_sprite_chain);
        position->unk_02 = (u16) source_position->unk_02;
        position->unk_06 = (u16) source_position->unk_06;
        position->unk_0A = (u16) source_position->unk_0A;
        func_8003DB94(sprite, &D_800D1464, 0);
        sprite->color.c.b = 0xFF;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags = (u16) (sprite->flags | 0xC);
        random_offset = scale_random_to_unsigned_halfword_limit(7);
        effect_state = object + 0x20;
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

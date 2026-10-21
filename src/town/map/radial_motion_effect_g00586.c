/* Radial motion effect (G00586).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AB02C.
 */
#include "town/map/radial_motion_effect_g00586.h"

/* Creates an effect behind the source with randomized reverse motion and launch speed. */
void *create_reverse_motion_effect(S_800A878C_2 *source_motion, u32 flags) {
    s16 *direction_y;
    s16 launch_speed;
    s16 stored_speed;
    s32 direction_index;
    s32 speed_roll;
    s32 velocity_x;
    s32 velocity_y;
    u32 direction;
    SpriteFrameState *sprite;
    S_800A878C_1 *motion;
    S_800A878C_4 *launch;
    void *effect;

    direction = (flags >> 9) & 7;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        motion = ((S_800A878C_0 *)effect)->unk_08;
        sprite = ((S_800A878C_0 *)effect)->unk_0C;
        ((S_800A878C_0 *)effect)->unk_10 = &D_800A86BC;
        register_node(effect, project_sprite_chain);
        direction_index = direction;
        motion->unk_02 = (s16) (source_motion->unk_02 - (dir_step_x[direction_index] * 0x10));
        direction_y = &dir_step_y[direction_index];
        motion->unk_06 = (s16) (source_motion->unk_06 - (*direction_y * 0x10));
        motion->unk_0A = (u16) source_motion->unk_0A;
        velocity_x = 0 - (source_motion->unk_0C * ((rand() & 1) + 2));
        launch = effect + 0x20;
        motion->unk_0C = (s32) (velocity_x / 16);
        velocity_y = 0 - (source_motion->unk_10 * ((rand() & 1) + 2));
        motion->unk_10 = (s32) (velocity_y / 16);
        motion->unk_14 = (s32) ((~rand() & 1) << 0xF);
        func_8003DB94(sprite, &D_800F15AC, 0);
        sprite->color.c.b = 0xFF;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags = (u16) (sprite->flags | 0xC);
        speed_roll = scale_random_to_unsigned_halfword_limit(7);
        launch_speed = speed_roll + scale_random_to_unsigned_halfword_limit(7);
        launch->unk_02 = launch_speed;
        motion->unk_14 = (s32) (0 - (launch_speed << 0x10));
        stored_speed = launch->unk_02;
        launch->unk_04 = (s32) ((s32) (stored_speed * stored_speed) / 2);
    }
    return effect;
}

/* Spawns objects at randomized positions around a center with evenly spaced angles. */
void spawn_radial_effect_objects(MovingPosition *center, S_800A895C_1 *spread, s32 count) {


    StackRecord record;
    s32 angle;
    s32 angle_step;
    s32 first_trig_value;
    s32 spawn_index;
    s32 angle_value;
    s32 y;
    u16 initial_y;
    ObjectPayloadView *object;

    if (count != 0) {
        angle_step = 0x1000 / count;
        angle = rand();
        initial_y = center->unk_0A;
        record.field16 = -4;
        record.y = initial_y;
        for (spawn_index = 0; spawn_index < count; spawn_index++) {
            record.x = (center->unk_02 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_00.u16)) -
                       (spread->unk_00.s32 / 2);
            record.z = (center->unk_06 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_04.u16)) -
                       (spread->unk_04.s32 / 2);
            y = (center->unk_0A +
                 scale_random_to_unsigned_halfword_limit(spread->unk_08.u16)) -
                (spread->unk_08.s32 / 2);
            record.y = y;
            record.fieldC = func_80064584(angle) << 5;
            first_trig_value = func_800644B8(angle);
            {
                void *record_ptr = &record;
                first_trig_value <<= 5;
                record.field10 = first_trig_value;
                object = create_reverse_motion_effect((S_800A878C_2 *)record_ptr, (s16)angle);
            }
            if (object != 0) {
                angle_value = func_800644B8(angle) << 5;
                if (angle_value < 0) {
                    angle_value = -angle_value;
                }
                ((S_800A895C_3 *)(object->unk_08))->unk_14 = -angle_value;
            }
            angle += angle_step;
        }
    }
}

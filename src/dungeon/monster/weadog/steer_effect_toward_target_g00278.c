/* Steer effect toward target.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00278 - CL:dungeon/func_80EDF8B8@dungeon/bank_eff000, CL:dungeon/func_80EDF8B8@dungeon/bank_f05000, CL:dungeon/func_80EDF8B8@dungeon/bank_f0b000, CL:dungeon/func_80EDF8B8@dungeon/bank_f11000, CL:dungeon/func_80EDF8B8@dungeon/bank_f17000, CL:dungeon/func_80EDF8B8@dungeon/bank_f1d000.
 */
#include "dungeon/monster/weadog/steer_effect_toward_target_g00278.h"
#include "shared/object_flags.h"

/* Advance position, clamp velocity, and steer acceleration toward the target. */
/* Clamps the effect's speed on all three axes and steers it toward stored coordinates, reducing
 * acceleration near the target. */
void steer_effect_toward_target(SteeringEffectWork *motion, ObjectPosition *position, void *unused)
{
    s32 target_delta;
    position->x.v += motion->velocity_x;
    position->y.v += motion->velocity_y;
    position->z.v += motion->velocity_z;

    motion->velocity_x += motion->accel_x;
    motion->velocity_y += motion->accel_y;
    motion->velocity_z += motion->accel_z;

    if (motion->velocity_x > 0x40000) {
        motion->velocity_x = 0x40000;
    }
    if (motion->velocity_x < -0x40000) {
        motion->velocity_x = -0x40000;
    }
    if (motion->velocity_y > 0x40000) {
        motion->velocity_y = 0x40000;
    }
    if (motion->velocity_y < -0x40000) {
        motion->velocity_y = -0x40000;
    }
    if (motion->velocity_z > 0x40000) {
        motion->velocity_z = 0x40000;
    }
    if (motion->velocity_z < -0x40000) {
        motion->velocity_z = -0x40000;
    }

    if (motion->target_x.w.i > position->x.w.i) {
        target_delta = motion->target_x.w.i - position->x.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        motion->accel_x = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = motion->target_x.w.i - position->x.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        motion->accel_x = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (motion->target_y.w.i > position->y.w.i) {
        target_delta = motion->target_y.w.i - position->y.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        motion->accel_y = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = motion->target_y.w.i - position->y.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        motion->accel_y = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (motion->target_z.w.i > position->z.w.i) {
        target_delta = motion->target_z.w.i - position->z.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            motion->accel_z = 0x10000;
        } else {
            motion->accel_z = 0x1000;
        }
    } else {
        target_delta = motion->target_z.w.i - position->z.w.i;
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            motion->accel_z = -0x10000;
        } else {
            motion->accel_z = -0x1000;
        }
    }

}

/* Advance the effect, then move and fade it until its timer expires. */
void initialize_shared_state_active_entries(SteeringEffectWork *effect, ObjectPosition *position, s32 update_param)
{
    s32 state;

    state = effect->state;
    effect->timer.u = effect->timer.u - 1;
    switch (state) {
    case 0:
        steer_effect_toward_target(effect, position, update_param);
        steer_effect_toward_target(effect, position, update_param);
        if (effect->timer.s == 0) {
            effect->timer.u = 0x10;
            effect->fade_length = 0x10;
            effect->state++;
        }
        effect->draw_color = effect->color.at00.v;
        break;
    case 1:
        position->x.v += effect->velocity_x;
        position->y.v += effect->velocity_y;
        position->z.v += effect->velocity_z;
        position->x.v += effect->velocity_x;
        position->y.v += effect->velocity_y;
        position->z.v += effect->velocity_z;

        effect->fade_color.at00.v =
            (effect->color.at00u.v * effect->timer.s) /
            effect->fade_length;
        effect->fade_color.at01.v =
            (effect->color.at01.v * effect->timer.s) /
            effect->fade_length;
        effect->fade_color.at02.v =
            (effect->color.at02.v * effect->timer.s) /
            effect->fade_length;
        effect->draw_color = effect->fade_color.at00u.v;

        if (effect->timer.s <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}

/* Creates an offset effect, advances it ten steps, and assigns a random color. */
void create_random_color_offset_effect(
    void *parent, s16 initial_14, s32 unused, s16 initial_32,
    s16 offset_x, s16 offset_y, s16 offset_z)
{
    s16 held_offset_x = offset_x;
    s16 held_offset_y = offset_y;
    s16 held_offset_z = offset_z;
    struct { u16 x; u16 y; u16 z; } source_offset;
    s16 step;
    s32 color_high;
    s32 color_mid;
    DelayMotionZ *source_data;
    void *effect;
    SteeringEffectWork *effect_data;

    effect = allocate_list_node(0x211, parent);
    if (effect != NULL) {
        ((ProjectileObject *)effect)->update_callback = D_801712C4;

        ((SignedPositionView *)(((ProjectileObject *)effect)->position))->x =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->x + held_offset_x;
        ((SignedPositionView *)(((ProjectileObject *)effect)->position))->y =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->y + held_offset_y;
        ((SignedPositionView *)(((ProjectileObject *)effect)->position))->z =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->z + held_offset_z;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (resolve_record_orientation_or_fallback(source_data->unk_08, source_data, &source_offset, 0) != 0) {
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->x += source_offset.x;
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->y += source_offset.y;
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->z += source_offset.z;
        }

        effect_data = (u8 *)effect + 0x20;
        effect_data->target_x.w.i = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->x;
        effect_data->target_y.w.i = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->y;
        effect_data->target_z.w.i = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->z;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (resolve_record_orientation_or_fallback(source_data->unk_08, source_data, &source_offset, 0) != 0) {
            effect_data->target_x.w.i += source_offset.x;
            effect_data->target_y.w.i += source_offset.y;
            effect_data->target_z.w.i += source_offset.z;
        }

        effect_data->origin_x = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->x;
        effect_data->origin_y = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->y;
        effect_data->origin_z = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->z;

        step = 0;
        do {
            steer_effect_toward_target(effect_data, ((ProjectileObject *)effect)->position, ((ProjectileObject *)effect)->sprite);
            step++;
        } while (step < 10);

        effect_data->param_14 = initial_14;
        effect_data->timer.s = initial_32;
        register_node(effect, D_80170ED8);

        color_high = rand();
        color_mid = rand();
        effect_data->color.at00.v =
            ((color_high & 0xFF) << 16) |
            ((color_mid & 0xFF) << 8) |
            (rand() & 0xFF);
        effect_data->draw_color = effect_data->color.at00.v;
    }
}

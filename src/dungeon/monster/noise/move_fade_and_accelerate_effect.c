#include "dungeon/monster/noise/move_fade_and_accelerate_effect.h"

/* Move and fade the effect, apply vertical acceleration, and flag it when its lifetime ends. */
void move_fade_and_accelerate_effect(T_80170F0C_S_func_80D1170C_1 *effect, IntVector3 *position)
{
    s16 life_left;
    s32 red;
    s32 green;
    s32 blue;
    s32 color_product;
    s32 *flag_page;

    position->x += effect->unk_40;
    position->y += effect->unk_44;
    position->z += effect->unk_48;

    color_product = effect->unk_00 * effect->unk_32.unk_32;
    red = color_product / effect->unk_34;
    effect->unk_04.bytes.unk_04 = red;
    color_product = effect->unk_01 * effect->unk_32.unk_32;
    green = color_product / effect->unk_34;
    effect->unk_04.bytes.unk_05 = green;
    color_product = effect->unk_02 * effect->unk_32.unk_32;
    blue = color_product / effect->unk_34;

    effect->unk_48 += effect->unk_54;
    life_left = effect->unk_32.unk_32_u;
    life_left -= 1;
    effect->unk_32.unk_32_u = life_left;
    effect->unk_04.bytes.unk_06 = blue;
    effect->unk_08 = effect->unk_04.unk_04;

    if ((life_left << 16) <= 0) {
        ((ObjectRetirementFlags *)((u8 *)effect - 2))->unk_00 |= 0x8000;
        flag_page = (s32 *)0x80080000;
        flag_page[0x14A0 / sizeof(s32)] =
            flag_page[0x14A0 / sizeof(s32)] | 0x8000;
    }
}

/* MECHANISM: Storing red and green immediately after their divisions invalidates
   the shared scale/divisor loads before scheduling; the stores then schedule late. */

/* Spawns an effect at an offset from its parent with randomized velocity. */
void spawn_random_velocity_offset_effect(EntityRec *parent, s16 effect_id, s32 effect_param, s32 unused, s16 x_offset,
    s16 y_offset, s16 z_offset) {
    register s16 saved_effect_id = effect_id;
    register s32 saved_effect_param = effect_param;
    T_80171020_S_80171020_2 *position_x;
    T_80171020_S_80171020_3 *position_y;
    T_80171020_S_80171020_1 *effect_state;
    void *effect;

    effect = allocate_list_node(0x211, parent);
    if (effect == NULL) {
        return;
    }
    ((T_80171020_S_80171020_0 *)effect)->unk_10 = &move_fade_and_accelerate_effect;
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_02 =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_02 + x_offset);
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_06 =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_06 + y_offset);
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_0A =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_0A + z_offset);
    effect_state = effect + 0x20;
    effect_state->unk_40 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_44 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_48 = (s32) (((rand() & 0x3FFF) - 0x6000) * 0x10);
    position_x = ((T_80171020_S_80171020_0 *)effect)->unk_08;
    position_x->unk_00 = (s32) (position_x->unk_00 + (effect_state->unk_40 * 2));
    position_y = ((T_80171020_S_80171020_0 *)effect)->unk_08;
    position_y->unk_04 = (s32) (position_y->unk_04 + (effect_state->unk_44 * 2));
    effect_state->unk_54 = 0x8000;
    effect_state->unk_14 = saved_effect_id;
    effect_state->unk_32 = 0x14;
    effect_state->unk_34 = 0x14;
    register_node(effect, &create_timed_offset_motion_effect);
    ((T_80171020_S_80171020_0 *)effect)->unk_20 = saved_effect_param;
    effect_state->unk_08 = saved_effect_param;
}

/* Spawn the overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_80171190(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    T_80171190_Work *work;
    ProjectileObject *obj;
    SignedHeightView *part_a;
    T_80171190_S_80171190_2 *part_b;
    void *resource;
    T_80171190_Work *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (T_80171190_Work *)((u8 *)obj + 0x20);
        obj->unk_10 = D_80171358;
        work->byte13 = 0x17;
        register_node(obj, project_sprite_chain);

        resource = D_80174E88;
        part_a = obj->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = obj->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = resource;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            work->flags14 = left;
            work->flags1c = right;
        } else if (kind >= 2) {
            left = work->flags14 | 0x2000;
            right = work->flags1c | 0x2000;
            work->flags14 = left;
            work->flags1c = right;
        } else {
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0) {
                if (!(work->flags14 & 0x200)) {
                    call_a1 = part_a;
                    left = generate_random_value();
                    call_a1 = obj;
                    if (left & 1) {
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->unk_2C = D_80174EF0;
                    }
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = &update_actor_behavior_and_direction;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

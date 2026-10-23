/* Steer effect toward target.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00278 - CL:dungeon/func_80EDF8B8@dungeon/bank_eff000, CL:dungeon/func_80EDF8B8@dungeon/bank_f05000, CL:dungeon/func_80EDF8B8@dungeon/bank_f0b000, CL:dungeon/func_80EDF8B8@dungeon/bank_f11000, CL:dungeon/func_80EDF8B8@dungeon/bank_f17000, CL:dungeon/func_80EDF8B8@dungeon/bank_f1d000.
 */
#include "dungeon/monster/weadog/steer_effect_toward_target_g00278.h"
#include "shared/object_flags.h"

/* Advance position, clamp velocity, and steer acceleration toward the target. */
/* Clamps the effect's speed on all three axes and steers it toward stored coordinates, reducing
 * acceleration near the target. */
void steer_effect_toward_target(void *motion, void *position, void *unused)
{
    s32 target_delta;
    S32_AT(position, 0x0) += S32_AT(motion, 0x40);
    S32_AT(position, 0x4) += S32_AT(motion, 0x44);
    S32_AT(position, 0x8) += S32_AT(motion, 0x48);

    S32_AT(motion, 0x40) += S32_AT(motion, 0x4c);
    S32_AT(motion, 0x44) += S32_AT(motion, 0x50);
    S32_AT(motion, 0x48) += S32_AT(motion, 0x54);

    if (S32_AT(motion, 0x40) > 0x40000) {
        S32_AT(motion, 0x40) = 0x40000;
    }
    if (S32_AT(motion, 0x40) < -0x40000) {
        S32_AT(motion, 0x40) = -0x40000;
    }
    if (S32_AT(motion, 0x44) > 0x40000) {
        S32_AT(motion, 0x44) = 0x40000;
    }
    if (S32_AT(motion, 0x44) < -0x40000) {
        S32_AT(motion, 0x44) = -0x40000;
    }
    if (S32_AT(motion, 0x48) > 0x40000) {
        S32_AT(motion, 0x48) = 0x40000;
    }
    if (S32_AT(motion, 0x48) < -0x40000) {
        S32_AT(motion, 0x48) = -0x40000;
    }

    if (S16_AT(motion, 0x5a) > S16_AT(position, 0x2)) {
        target_delta = S16_AT(motion, 0x5a) - S16_AT(position, 0x2);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x4c) = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = S16_AT(motion, 0x5a) - S16_AT(position, 0x2);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x4c) = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(motion, 0x5e) > S16_AT(position, 0x6)) {
        target_delta = S16_AT(motion, 0x5e) - S16_AT(position, 0x6);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x50) = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = S16_AT(motion, 0x5e) - S16_AT(position, 0x6);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x50) = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(motion, 0x62) > S16_AT(position, 0xa)) {
        target_delta = S16_AT(motion, 0x62) - S16_AT(position, 0xa);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            S32_AT(motion, 0x54) = 0x10000;
        } else {
            S32_AT(motion, 0x54) = 0x1000;
        }
    } else {
        target_delta = S16_AT(motion, 0x62) - S16_AT(position, 0xa);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            S32_AT(motion, 0x54) = -0x10000;
        } else {
            S32_AT(motion, 0x54) = -0x1000;
        }
    }

}

/* Advance the effect, then move and fade it until its timer expires. */
void initialize_shared_state_active_entries(void *effect, void *position, s32 update_param)
{
    s32 state;

    state = ((S_801712C4_0 *)effect)->unk_17;
    ((S_801712C4_0 *)effect)->unk_32.u = ((S_801712C4_0 *)effect)->unk_32.u - 1;
    switch (state) {
    case 0:
        steer_effect_toward_target(effect, position, update_param);
        steer_effect_toward_target(effect, position, update_param);
        if (((S_801712C4_0 *)effect)->unk_32.s == 0) {
            ((S_801712C4_0 *)effect)->unk_32.u = 0x10;
            ((S_801712C4_0 *)effect)->unk_34 = 0x10;
            ((S_801712C4_0 *)effect)->unk_17++;
        }
        ((S_801712C4_0 *)effect)->unk_08 = ((S_801712C4_0 *)effect)->unk_00.at00.v;
        break;
    case 1:
        ((IntVector3 *)position)->x += ((S_801712C4_0 *)effect)->unk_40;
        ((IntVector3 *)position)->y += ((S_801712C4_0 *)effect)->unk_44;
        ((IntVector3 *)position)->z += ((S_801712C4_0 *)effect)->unk_48;
        ((IntVector3 *)position)->x += ((S_801712C4_0 *)effect)->unk_40;
        ((IntVector3 *)position)->y += ((S_801712C4_0 *)effect)->unk_44;
        ((IntVector3 *)position)->z += ((S_801712C4_0 *)effect)->unk_48;

        ((S_801712C4_0 *)effect)->unk_04.at00.v =
            (((S_801712C4_0 *)effect)->unk_00.at00u.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_04.at01.v =
            (((S_801712C4_0 *)effect)->unk_00.at01.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_04.at02.v =
            (((S_801712C4_0 *)effect)->unk_00.at02.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_08 = ((S_801712C4_0 *)effect)->unk_04.at00u.v;

        if (((S_801712C4_0 *)effect)->unk_32.s <= 0) {
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
    void *source_data;
    void *effect;
    void *effect_data;

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
        if (resolve_record_orientation_or_fallback(((DelayMotionZ *)source_data)->unk_08, source_data, &source_offset, 0) != 0) {
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->x += source_offset.x;
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->y += source_offset.y;
            ((SignedPositionView *)(((ProjectileObject *)effect)->position))->z += source_offset.z;
        }

        effect_data = (u8 *)effect + 0x20;
        ((S_80171498_3 *)effect_data)->unk_5A = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->x;
        ((S_80171498_3 *)effect_data)->unk_5E = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->y;
        ((S_80171498_3 *)effect_data)->unk_62 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->z;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (resolve_record_orientation_or_fallback(((DelayMotionZ *)source_data)->unk_08, source_data, &source_offset, 0) != 0) {
            (*(s16 *)((u8 *)effect_data + 0x5A)) += source_offset.x;
            (*(s16 *)((u8 *)effect_data + 0x5E)) += source_offset.y;
            ((S_80171498_3 *)effect_data)->unk_62 += source_offset.z;
        }

        ((S_80171498_3 *)effect_data)->unk_36 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->x;
        ((S_80171498_3 *)effect_data)->unk_38 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->y;
        ((S_80171498_3 *)effect_data)->unk_3A = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->z;

        step = 0;
        do {
            steer_effect_toward_target(effect_data, ((ProjectileObject *)effect)->position, ((ProjectileObject *)effect)->sprite);
            step++;
        } while (step < 10);

        ((S_80171498_3 *)effect_data)->unk_14 = initial_14;
        ((S_80171498_3 *)effect_data)->unk_32 = initial_32;
        register_node(effect, D_80170ED8);

        color_high = rand();
        color_mid = rand();
        ((S_80171498_3 *)effect_data)->unk_00 =
            ((color_high & 0xFF) << 16) |
            ((color_mid & 0xFF) << 8) |
            (rand() & 0xFF);
        ((S_80171498_3 *)effect_data)->unk_08 = ((S_80171498_3 *)effect_data)->unk_00;
    }
}

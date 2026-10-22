/* Expiring sprite effect (G00370). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D1374. */
#include "dungeon/effect/expiring_sprite_effect_g00370.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* Creates an object at an offset from its parent and initializes its motion and state. */
void create_offset_sprite_effect(EntityRec *parent, s32 state_value, s16 x_offset, s16 y_offset, s32 z_offset,
                   s32 motion_scale) {
    s32 *z_argument = &z_offset;
    s32 *motion_argument = &motion_scale;
    s32 saved_z_offset = *z_argument;
    s32 saved_motion_scale = *motion_argument;
    s32 scaled_motion;
    S_800D6AD4_5 *object_state;
    ObjectNodeHeader *object;
    S_800D6AD4_4 *motion;
    S_800D6AD4_1 *x_position;
    S_800D6AD4_2 *y_position;
    S_800D6AD4_3 *z_position;

    object = allocate_list_node(0x211, parent);
    if (object != 0) {
        object->unk_10 = D_800D6804;
        (object->position)->x.w.i =
            (u16)((MovingPosition *)((*(void * *)&parent->z)))->unk_02;
        (object->position)->y.w.i =
            (u16)((MovingPosition *)((*(void * *)&parent->z)))->unk_06;
        (object->position)->z.w.i =
            (u16)((MovingPosition *)((*(void * *)&parent->z)))->unk_0A;
        x_position = object->position;
        x_position->unk_02 =
            (u16)(x_position->unk_02 + x_offset);
        y_position = object->position;
        y_position->unk_06 =
            (u16)(y_position->unk_06 + y_offset);
        z_position = object->position;
        scaled_motion = saved_motion_scale << 0x12;
        z_position->unk_0A =
            (u16)(z_position->unk_0A + saved_z_offset);
        motion = object->position;
        object_state = ((void *)object) + 0x20;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        (object->position)->velocity_z =
            (s32)(0xFFFA0000 - scaled_motion);
        object_state->unk_32 = 0x14;
        object_state->unk_34 = 0x14;
        register_node(object, D_800D68F4);
        ((S_800D6AD4_0 *)object)->unk_20 = state_value;
        object_state->unk_08 = state_value;
    }
}

/* Updates effect size and offsets, emits a sequence, and flags expiration. */
void update_expiring_sprite_effect(void *effect, S_800D6C18_2 *size_state) {
    s16 display_size;
    s16 ticks_left;
    s32 index;
    s32 emit_offset;
    u32 size_step;
    S_800D6C18_1 *size_source;
    s32 *global_base;

    size_source = ((S_800D6C18_0 *)effect)->unk_14;
    if (((S_800D6C18_0 *)effect)->unk_0C >= 0xF) {
        size_step = size_source->unk_14;
        size_state->unk_14.at00.v = (s32) (size_state->unk_14.at00.v + ((s32) (size_step + (size_step >> 0x1F)) >> 1));
    }
    display_size = size_state->unk_14.at02.v + 0x10;
    ((S_800D6C18_0 *)effect)->unk_56 = display_size;
    ((S_800D6C18_0 *)effect)->unk_54 = display_size;
    if ((((S_800D6C18_0 *)effect)->unk_0C < 0x13) && !((u16) ((S_800D6C18_0 *)effect)->unk_0C & 1)) {
        index = 0;
        do {
            if (((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 < 0) {
                ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 + 1);
            }
            if (((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 > 0) {
                ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_44 - 1);
            }
            if (((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C < 0) {
                ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C + 1);
            }
            if (((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C > 0) {
                ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)((u8 *)effect + index * 2))->unk_4C - 1);
            }
            index += 1;
        } while (index < 4);
    }
    if ((((S_800D6C18_0 *)effect)->unk_0C == 0xF) && (((S_800D6C18_0 *)effect)->unk_10 == 0)) {
        index = 0;
        emit_offset = 0;
        do {
            s32 delta;

            delta = 0xE0E0E0;
                        /*A*/
            create_offset_sprite_effect((void *)((s8 *)effect - 0x20), delta, 0, 0, emit_offset >> 0x10, (s16) index);
            delta = -0x40000;
            emit_offset += delta;
            index += 1;
        } while (index < 0x51);
    }
    ticks_left = (u16) ((S_800D6C18_0 *)effect)->unk_0C - 1;
    ((S_800D6C18_0 *)effect)->unk_0C = ticks_left;
    global_base = (s32 *) 0x80080000;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800D6C18_0_pre *)effect)[-1].unk_00 = (u16) (((S_800D6C18_0_pre *)effect)[-1].unk_00 | 0x8000);
        global_base[0x14A0 / 4] |= 0x8000;
    }
}

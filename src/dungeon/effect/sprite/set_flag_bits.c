#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
typedef struct S_8092192C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_8092192C_0;

typedef struct S_8092192C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8092192C_2;   /* arg0 in func_8092192C */

typedef struct S_8092192C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8092192C_3;

typedef struct S_8092192C_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8092192C_4;

extern u8 D_800DEC70[];
s32 register_node();
void select_record_entry_and_value();
void func_800F68AC(s16 *state, s32 *position, u16 *object);

static __inline__ u32 set_flag_bits(u32 flags, u32 mask)
{
    return flags | mask;
}

/* Creates and initializes an object at the supplied position plus coordinate offsets. */
void create_offset_half_scale_sprite(S_8092192C_2 *base_pos, s32 offset_x, s32 offset_y, s32 offset_z) {
    u16 flags;
    s32 render_value;
    SpriteFrameState *render_state;
    S_8092192C_4 *sprite;
    S_8092192C_0 *object;
    S_8092192C_3 *position;
    u32 sprite_data_addr;
    s32 base_x;
    s32 base_y;
    s32 base_z;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->unk_10 = &func_800F68AC;
        register_node(object, project_sprite_chain);
        render_state = object->unk_0C;
        flags = render_state->flags;
        render_value = 0x20;
        render_state->tpage_abr = render_value;
        flags = set_flag_bits(flags, 0xC);
        render_state->flags = flags;
        render_value = 6;
        render_state->unk_06 = render_value;
        flags = set_flag_bits(flags, 2);
        render_state->flags = flags;
        position = object->unk_08;
        base_x = (s32) base_pos->unk_00;
        sprite_data_addr = 0x800E0000;
        position->unk_00.at00.v = base_x;
        base_y = (s32) base_pos->unk_04;
        sprite_data_addr = (u32)D_800DEC70;
        position->unk_04.at00.v = base_y;
        base_z = (s32) base_pos->unk_08;
        position->unk_00.at02.v = (u16) (position->unk_00.at02.v + offset_x);
        position->unk_08.at00.v = base_z;
        position->unk_04.at02.v = (u16) (position->unk_04.at02.v + offset_y);
        position->unk_08.at02.v = (u16) (position->unk_08.at02.v + offset_z);
        render_state = object->unk_0C;
        render_state->scale_y = 0x800;
        render_state->scale_x = 0x800;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        select_record_entry_and_value(render_state, (void *) sprite_data_addr, 0);
    }
}

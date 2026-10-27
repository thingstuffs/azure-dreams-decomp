/* Creation of half-scale sprites at offsets from a supplied position. */
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct S_8092192C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8092192C_2;   /* arg0 in func_8092192C */

typedef struct S_8092192C_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8092192C_4;

extern u8 shared_sprite_entries[];
void select_record_entry_and_value(void *state, void *entries, short index);
void func_800F68AC(s16 *state, s32 *position, u16 *object);

/* Returns the union of the supplied flag word and mask. */
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
    ObjectNodeHeader *object;
    ObjectPosition *position;
    u32 sprite_data_addr;
    s32 base_x;
    s32 base_y;
    s32 base_z;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->update_callback = &func_800F68AC;
        register_node(object, project_sprite_chain);
        render_state = object->sprite;
        flags = render_state->flags;
        render_value = 0x20;
        render_state->tpage_abr = render_value;
        flags = set_flag_bits(flags, 0xC);
        render_state->flags = flags;
        render_value = 6;
        render_state->depth_bias = render_value;
        flags = set_flag_bits(flags, 2);
        render_state->flags = flags;
        position = object->position;
        base_x = (s32) base_pos->unk_00;
        sprite_data_addr = 0x800E0000;
        position->x.v = base_x;
        base_y = (s32) base_pos->unk_04;
        sprite_data_addr = (u32)shared_sprite_entries;
        position->y.v = base_y;
        base_z = (s32) base_pos->unk_08;
        position->x.w.i = (u16) (*(u16 *)&position->x.w.i + offset_x);
        position->z.v = base_z;
        position->y.w.i = (u16) (*(u16 *)&position->y.w.i + offset_y);
        position->z.w.i = (u16) (*(u16 *)&position->z.w.i + offset_z);
        render_state = object->sprite;
        render_state->scale_y = 0x800;
        render_state->scale_x = 0x800;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        select_record_entry_and_value(render_state, (void *) sprite_data_addr, 0);
    }
}

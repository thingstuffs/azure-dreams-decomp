#include "shared/entity.h"
#include "dungeon/monster/beldo_large.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "engine/node/allocation.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81339A5C_1 {
    u8 pad_00[2];
    union { u16 u; s16 s; } unk_02;
    u8 pad_04[2];
    union { u16 u; s16 s; } unk_06;
    u8 pad_08[2];
    u16 unk_0A;
    u8 pad_0C[10];
    u16 unk_16;
} S_func_81339A5C_1;

typedef struct S_func_81339A5C_2 {
    u8 pad_00[0x24];
    void *unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} S_func_81339A5C_2;

extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 item_effect_descriptor;

extern void *beldo_actor_nodes;
extern void *D_80175D68;

/* Creates a linked object and initializes its position and rendering state. */
void create_linked_object_position(void)
{
    s32 object_z;
    u16 source_z;
    u16 object_y;
    ObjectPosition *source_pos;
    S_func_81339A5C_2 *object_data;
    void *source_data;
    ObjectNodeHeader *object;
    SpriteFrameState *render_flags;
    S_func_81339A5C_1 *object_pos;
    SpriteFrameState *render_state;

    source_pos = ((ObjectNodeHeader *)beldo_actor_nodes)->position;
    source_data = beldo_actor_nodes + 0x20;
    object = allocate_list_node(0x12, beldo_actor_nodes);
    if (object != NULL) {
        object->update_callback = update_vertical_motion_and_effect;
        object_data = (S_func_81339A5C_2 *)((u8 *)object + 0x20);
        register_node(object, project_sprite_chain);
        render_flags = object->sprite;
        render_flags->flags =
            (u16)(render_flags->flags & 0xFFF3);
        object_data->unk_24 = source_data;
        object_pos = object->position;
        object_pos->unk_02.u = (u16)source_pos->x.w.i;
        object_pos->unk_06.u = (u16)source_pos->y.w.i;
        object_pos->unk_0A =
            ((S_func_81339A5C_1 *)source_pos)->unk_0A;
        source_z = ((S_func_81339A5C_1 *)source_pos)->unk_0A;
        object_y = ((S_func_81339A5C_1 *)object_pos)->unk_06.u;
        object_z = ((S_func_81339A5C_1 *)object_pos)->unk_0A;
        object_pos->unk_06.u = (u16)(object_y - 0x140);
        object_pos->unk_16 = source_z;
        object_pos->unk_0A = (u16)(object_z - 0x20);
        render_state = object->sprite;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->depth_bias = 6;
        object_data->unk_58 =
            (source_pos->x.w.i - 0x20) / 0x40;
        object_data->unk_59 =
            (source_pos->y.w.i - 0x20) / 0x40;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        render_state->source = &item_effect_descriptor;
        D_80175D68 = object;
    }
}

/* MECHANISM: Computing object_data before the callback makes its natural live range cross the call;
   the scheduler sinks the addiu back after the call while allocation retains the retail s2/s3 frame. */

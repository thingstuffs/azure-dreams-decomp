#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/monster/beldo_large.h"

typedef struct S_80170D2C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x3A];
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
} S_80170D2C_0;   /* work in create_timed_offset_motion_effect */



extern u8 D_80170BB0[];
extern u8 D_80173B88[];

/* Create an offset object and initialize its motion and render data. */
void create_timed_offset_motion_effect(u8 *unused, s16 duration, s32 offset_x, s32 offset_y, s32 offset_z) {
    s32 fixed_value;
    ObjectNodeHeader *obj;
    S_80170D2C_0 *work;
    ObjectPosition *prim;
    SpriteFrameState *packet;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        work = NODE_BODY(obj);
        work->unk_18 = duration;
        obj->update_callback = D_80170BB0;
        register_node(obj, project_sprite_chain);
        packet = obj->sprite;
        packet->tpage_abr = 0x20;
        packet->depth_bias = 0;
        packet->flags |= 0xC;
        prim = obj->position;
        prim->x.v = view_reference_entity.x.v;
        prim->y.v = view_reference_entity.y.v;
        prim->z.v = view_reference_entity.z.v;
        (prim->x).unsigned_parts.integer += (offset_x);
        (prim->y).unsigned_parts.integer += (offset_y);
        (prim->z).unsigned_parts.integer += (offset_z);
        work->unk_1C = view_reference_entity.x.unsigned_parts.integer;
        fixed_value = view_reference_entity.y.unsigned_parts.integer;
        work->unk_1E = fixed_value;
        work->unk_20 = view_reference_entity.z.unsigned_parts.integer;
        work->unk_5C = (-(offset_x << 16) / (duration / 8)) / 2;
        work->unk_60 = (-(offset_y << 16) / (duration / 8)) / 2;
        work->unk_64 = (-(offset_z << 16) / (duration / 8)) / 2;
        work->unk_68 = (-(offset_x << 16) / (duration / 8)) / 4;
        work->unk_6C = (-(offset_y << 16) / (duration / 8)) / 4;
        work->unk_70 = (-(offset_z << 16) / (duration / 8)) / 4;
        packet = obj->sprite;
        packet->scale_y = 0x1000;
        packet->scale_x = 0x1000;
        packet->color.c.b = 0;
        packet->color.c.g = 0;
        packet->color.c.r = 0;
        __builtin_memcpy(((u8 *)obj) + 0x48, D_80173B88, 12);
        packet->source = ((u8 *)obj) + 0x48;
    }
}

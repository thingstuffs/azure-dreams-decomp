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

typedef struct S_80170D2C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170D2C_2;   /* packet in create_timed_offset_motion_effect */

typedef struct S_80170D2C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80170D2C_4;   /* D_80083780 in create_timed_offset_motion_effect */

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
        work = (S_80170D2C_0 *)(((u8 *)obj) + 0x20);
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
        *(u16 *)&prim->x.w.i += offset_x;
        *(u16 *)&prim->y.w.i += offset_y;
        *(u16 *)&prim->z.w.i += offset_z;
        work->unk_1C = ((S_80170D2C_4 *)((u8 *)(&view_reference_entity)))->unk_00.at02.v;
        fixed_value = ((S_80170D2C_4 *)((u8 *)(&view_reference_entity)))->unk_04.at02.v;
        work->unk_1E = fixed_value;
        work->unk_20 = ((S_80170D2C_4 *)((u8 *)(&view_reference_entity)))->unk_08.at02.v;
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

#ifndef DUNGEON_OVL_BC9094_H
#define DUNGEON_OVL_BC9094_H

#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"

typedef struct ChildA {
    u8 pad_00[10];
    s16 field_0A;
} ChildA;

typedef struct ChildB {
    u8 pad_00[36];
    u8 field_24;
    u8 field_25;
    u8 pad_26[6];
    void *field_2C;
} ChildB;

typedef struct Body {
    u8 pad_00[19];
    u8 field_13;
    u32 flags_14;
    u8 pad_18[4];
    u32 flags_1C;
    u8 pad_20[108];
    void *callback_8C;
    u8 pad_90[10];
    u8 field_9A;
    u8 pad_9B;
    s8 field_9C;
} Body;

typedef struct Object {
    ObjectNodeHeader header;
    Body body_20;
} Object;

extern u8 nyuel_slot_d_action_callback[9];
extern u8 nyuel_frame_set_7[9];
extern u8 D_80162F00[9];
extern u8 D_8015EA98[9];

extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 func_8004491C(ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(Body *, s32, s32);
extern void try_move_actor_to_valid_position(void *,void *,void *,void *);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */

Body *allocate_actor_parts(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c);
#endif

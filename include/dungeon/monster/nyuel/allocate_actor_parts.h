#ifndef DUNGEON_OVL_BC9094_H
#define DUNGEON_OVL_BC9094_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

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
    u8 pad_00[8];
    ChildA *child_a_08;
    ChildB *child_b_0C;
    void *field_10;
    u8 pad_14[12];
    Body body_20;
} Object;

extern u8 D_8015EE9C[9];
extern u8 D_80162ED8[9];
extern u8 D_80162F00[9];
extern u8 D_8015EA98[9];

extern Object *allocate_list_node(s32, void *);
extern Object *func_8003FD64(s32, void *);
extern void register_node(Object *, void *);
extern void func_8004491C(Object *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(Body *, s32, s32);
extern void initialize_actor_sprite_and_animation(Object *, ChildA *, ChildB *, s16);
extern void try_move_actor_to_valid_position(Body *, ChildA *, ChildB *, Body *);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */

Body *allocate_actor_parts(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c);
#endif

#ifndef DUNGEON_OVL_BDB094_H
#define DUNGEON_OVL_BDB094_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct {
    u8 pad0[10];
    s16 unkA;
} Func80BBB094PartA;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;
    u8 unk25;
    u8 pad26[6];
    void *unk2C;
} Func80BBB094PartB;

typedef struct {
    u8 pad0[0x13];
    u8 unk13;
    u32 unk14;
    u8 pad18[4];
    u32 unk1C;
    u8 pad20[0x6C];
    void *unk8C;
    u8 pad90[10];
    u8 unk9A;
    u8 unk9B;
    s8 unk9C;
} Func80BBB094PartC;

typedef struct {
    u8 pad0[8];
    Func80BBB094PartA *unk8;
    Func80BBB094PartB *unkC;
    void *unk10;
    u8 pad14[12];
    Func80BBB094PartC unk20;
} Func80BBB094Object;

extern u8 nyuel_slot_a_action_callback[];
extern u8 nyuel_frame_set_5[];
extern u8 D_80150F00[];
extern u8 D_8014CA98[];

extern Func80BBB094Object *allocate_list_node(s32, void *);
extern Func80BBB094Object *func_8003FD64(s32, void *);
extern void register_node(Func80BBB094Object *, void *);
extern void func_8004491C(Func80BBB094Object *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(Func80BBB094PartC *, s32, s32);
extern void initialize_actor_sprite_and_animation(Func80BBB094Object *, Func80BBB094PartA *,
                          Func80BBB094PartB *, s32);
extern void try_move_actor_to_valid_position(Func80BBB094PartC *, Func80BBB094PartA *,
                          Func80BBB094PartB *, Func80BBB094PartC *);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */

Func80BBB094PartC *func_8014C894(s32 spawn_flags, s16 attr_a, s32 attr_b, s32 attr_c);
#endif

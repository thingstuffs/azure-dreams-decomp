#ifndef DUNGEON_OVL_EF906C_H
#define DUNGEON_OVL_EF906C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "engine/node/allocation.h"
struct ObjectNodeHeader;

   /* part_a in func_8014C86C */

typedef struct S_8014C86C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8014C86C_6;   /* child in func_8014C86C */

   /* elem in func_8014C86C */

typedef struct S_8014C86C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8014C86C_8;   /* base in func_8014C86C */

extern s32 generate_random_value(void);
extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();

extern void func_8014CB64(void *actor, void *motion, void *sprite_arg);
extern void func_8014D1A4(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status);
extern u8 D_8015018C[];
extern u8 D_801501CC[];

void * spawn_configured_overlay_effect(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
#endif

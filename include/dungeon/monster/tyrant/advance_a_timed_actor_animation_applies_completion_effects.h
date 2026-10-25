#ifndef DUNGEON_OVL_7F0F7800_P05_H
#define DUNGEON_OVL_7F0F7800_P05_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 pad0[0x8C];
    void (*field8C)();
    u8 pad90[6];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 field9B;
} T_801727CC_Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 field14;
    u8 pad16[0x0E];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    u8 *field2C;
} T_801727CC_Obj2;

typedef struct {
    u8 pad0[0x2A];
    s16 field2A;
    u8 pad2C[0x1A];
    u16 field46;
    u8 pad48[0x25];
    s8 field6D;
} T_801727CC_Obj3;


struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);
extern void func_80047784(T_801727CC_Obj2 *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(T_801727CC_Obj3 *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(T_801727CC_Obj3 *, s32);
extern void * actor_update_node_cursor[];
extern u8 D_80173FE8[];
extern u8 D_80174010[];
void advance_a_timed_actor_animation_applies_completion_effects(T_801727CC_Obj0 *action, s32 context, SpriteFrameState *sprite, T_801727CC_Obj3 *actor);
extern void update_dungeon_actor_behavior();
#endif

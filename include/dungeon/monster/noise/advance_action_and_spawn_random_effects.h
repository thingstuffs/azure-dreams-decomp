#ifndef DUNGEON_OVL_7F43F800_P06_H
#define DUNGEON_OVL_7F43F800_P06_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct T_80172FFC_S_80172FFC_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} T_80172FFC_S_80172FFC_0;   /* arg0 in func_80172FFC */


typedef struct T_80172FFC_S_80172FFC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} T_80172FFC_S_80172FFC_3;   /* arg1 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_4 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x8];
    void * unk_A8;
    u8 pad_AC[0x8];
    s32 unk_B4;
} T_80172FFC_S_80172FFC_4;   /* temp_s2 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} T_80172FFC_S_80172FFC_5;   /* temp_v0_3 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} T_80172FFC_S_80172FFC_6;   /* temp_s1 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} T_80172FFC_S_80172FFC_7;   /* temp_s0 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} T_80172FFC_S_80172FFC_8;   /* sp50 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} T_80172FFC_S_80172FFC_9;   /* temp_a1_2 in func_80172FFC */

typedef struct T_80172FFC_S_80172FFC_10 {
    s16 unk_00;
    u16 unk_02;
} T_80172FFC_S_80172FFC_10;   /* &sp60[((u16) ((T_80172FFC_S_80172FFC_4 *)temp_s2)->unk_94 >> 7) & 0x1C] in func_80172FFC */


typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Packed32;

typedef struct {
    long long out18;
    Packed32 copy;
} T_80172FFC_WorkMid;

s32 rand();                                /* extern */

extern s32 resolve_record_orientation_or_fallback();
extern void * allocate_list_node();
extern void * func_8003FD64();
extern s32 register_node();
extern s32 func_8004491C();
extern void select_sprite_entry();
extern void func_80047784();
extern s32 func_80065420();
extern void * resolve_attack_damage_and_effects();
extern s32 advance_status_timers();
extern s32 play_sound_if_enabled();
extern void reduce_actor_food_meter(void *, s32);
extern s8 D_800DCECC[];
extern Packed32 D_80170838;
extern u8 D_80174E90[];
extern u8 D_80174EB8[];
extern u8 D_80174EC0;
void advance_action_and_spawn_random_effects(void *action, void *motion, void *sprite, EntityRec *actor);
extern void update_actor_behavior_and_direction();
extern void project_sprite_entries_to_quads();
#endif

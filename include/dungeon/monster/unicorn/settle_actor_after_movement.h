#ifndef DUNGEON_OVL_7F511800_P01_H
#define DUNGEON_OVL_7F511800_P01_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"

typedef struct T_80172664_S_80172664_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} T_80172664_S_80172664_0;   /* arg3 in func_80172664 */

typedef struct T_80172664_S_80172664_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } timer;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 phase;
} T_80172664_S_80172664_1;   /* arg0 in func_80172664 */

typedef struct T_80172664_S_80172664_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} T_80172664_S_80172664_2;   /* arg2 in func_80172664 */

typedef struct T_80172664_S_80172664_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} T_80172664_S_80172664_3;   /* arg1 in func_80172664 */



extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void * actor_update_node_cursor;
extern u8 unicorn_action_continuation_address;
extern u8 D_80174D7C;
extern u8 D_80174D84;
extern u8 D_80174D8C;
void settle_actor_after_movement(void *animation, void *motion, SpriteFrameState *sprite, void *actor);
#endif

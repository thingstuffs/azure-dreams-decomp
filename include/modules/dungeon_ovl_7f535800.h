#ifndef DUNGEON_OVL_7F535800_H
#define DUNGEON_OVL_7F535800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/position_views.h"


extern s32 D_80158A58;
extern s32 D_80159014;
extern s32 D_8015C20C;
extern s32 D_8015C25C;

extern void *allocate_list_node();
extern void *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();


typedef struct S_80158878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80158878_0;   /* temp_v0 in func_80158878 */

typedef struct S_80158878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158878_1;   /* var_s0 in func_80158878 */

   /* temp_s4 in func_80158878 */

typedef struct S_80158878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    s32 * unk_2C;
} S_80158878_3;   /* temp_s2 in func_80158878 */

typedef struct S_80158878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158878_4;   /* temp_s5 in func_80158878 */

/* Allocates an object and initializes its state and attached data. */

void *spawn_clown_slot_c(s16 init_flags, s16 pos_x, s16 pos_y, s16 init_value);
void *func_80158878(s16 init_flags, s16 pos_x, s16 pos_y, s16 init_value);
#endif

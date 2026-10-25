#ifndef DUNGEON_OVL_7F559800_H
#define DUNGEON_OVL_7F559800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/position_views.h"
struct RegistrationNode;

extern u8 clown_object_callback_4[];
extern s32 D_8016B014;
extern s32 D_8016E20C;
extern s32 D_8016E25C;

extern void *allocate_list_node();
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

typedef struct S_8016A878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A878_1;   /* var_s0 in func_8016A878 */

   /* temp_s4 in func_8016A878 */

typedef struct S_8016A878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A878_4;   /* temp_s5 in func_8016A878 */

/* Allocate and initialize an object with its placement, flags, and runtime state. */

void *create_flagged_actor_object(s16 init_flags, s16 tile_x, s16 tile_y, s16 object_id);
#endif

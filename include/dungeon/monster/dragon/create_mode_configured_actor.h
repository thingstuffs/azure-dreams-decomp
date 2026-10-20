#ifndef DUNGEON_OVL_9EF054_H
#define DUNGEON_OVL_9EF054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"


typedef s32 M2C_UNK;

   /* obj in func_8016A854 */

typedef struct S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A854_1;   /* work in func_8016A854 */

   /* part_a in func_8016A854 */

typedef struct S_8016A854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A854_3;   /* part_b in func_8016A854 */

typedef struct S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A854_4;   /* actor in func_8016A854 */


extern void *allocate_list_node();
extern void *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8016AA28[];
extern u8 D_8016AE54;
extern u8 D_8016DC7C[];
extern u8 D_8016DCDC[];

/* Allocates an actor object and initializes its parts and flags for the requested kind. */

void *create_mode_configured_actor_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
#endif

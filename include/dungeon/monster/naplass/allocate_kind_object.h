#ifndef DUNGEON_OVL_F8F070_H
#define DUNGEON_OVL_F8F070_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
struct R03_80170A28_S_80170A28_2;
struct RegistrationNode;

typedef s32 M2C_UNK;

typedef struct S_8015E870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E870_1;   /* work in func_8015E870 */

typedef struct S_8015E870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E870_2;   /* part_a in func_8015E870 */

typedef struct S_8015E870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015E870_4;   /* actor in func_8015E870 */

extern void *allocate_list_node();
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern void func_8015EA3C(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void func_8015EE68(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);
extern u8 D_80162194[];
extern u8 D_801621DC[];

void * allocate_kind_object(s16 spawn_flags, s16 value_24, s16 value_25, s16 value_0a);
#endif

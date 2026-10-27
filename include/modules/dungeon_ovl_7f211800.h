#ifndef DUNGEON_OVL_7F211800_H
#define DUNGEON_OVL_7F211800_H
#include "common.h"
#include "engine/node.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
struct R03_80170A28_S_80170A28_2;
struct ObjectNodeHeader;


typedef struct S_8016A894_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A894_1;   /* work in func_8016A894 */

typedef struct S_8016A894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A894_2;   /* part_a in func_8016A894 */

typedef struct S_8016A894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A894_4;   /* actor in func_8016A894 */

extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern void func_8016AA68(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void func_8016AE94(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);
extern u8 D_8016EA7C[];
extern u8 viper_frame_set_9[];

void * func_8016A894(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif

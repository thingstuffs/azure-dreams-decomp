#ifndef DUNGEON_OVL_7F223800_H
#define DUNGEON_OVL_7F223800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
struct ObjectNodeHeader;
struct ObjectNodeHeader;

typedef s32 M2C_UNK;

typedef struct S_8015E854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E854_1;   /* result in func_8015E854 */

typedef struct S_8015E854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E854_2;   /* data08 in func_8015E854 */

typedef struct S_8015E854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E854_3;   /* data0C in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8015E854_4;   /* objectState in func_8015E854 */

extern void func_8015EA8C(void *entity_state, void *entity_motion, SpriteFrameState *entity_part);
extern u8 D_80161D30[];
extern u8 D_80161D78[];
extern void func_8015EF74(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);

extern void *allocate_list_node();
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern s16 set_or_clear_actor_status_slot();
extern void unlink_node(struct ObjectNodeHeader *node);
extern void func_80044A50(struct ObjectNodeHeader *node);
extern void retire_tracked_effect_by_id();

void * create_tracked_effect_object(s16 mode, s16 value24, s16 value25, s16 value0A);
#endif

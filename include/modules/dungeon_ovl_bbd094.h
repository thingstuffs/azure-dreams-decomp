#ifndef DUNGEON_OVL_BBD094_H
#define DUNGEON_OVL_BBD094_H
#include "common.h"
#include "engine/node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
struct ObjectNodeHeader;


extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();

extern void func_8016AE9C(void);
extern void func_8016EED8(void);
extern void func_8016EF00(void);
extern void func_8016AA98(void);

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */

u8 *func_8016A894(s16 flags, s16 kind_id, u16 variant, s16 spawn_value);
#endif

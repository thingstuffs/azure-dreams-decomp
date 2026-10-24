#ifndef DUNGEON_OVL_BBD094_H
#define DUNGEON_OVL_BBD094_H
#include "common.h"
#include "shared/object_node.h"


extern void *allocate_list_node();
extern u8 *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern void project_sprite_chain(void);
extern void func_80045340(void);
extern u32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern void func_8016AE9C(void);
extern void func_8016EED8(void);
extern void func_8016EF00(void);
extern void func_8016AA98(void);

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */

u8 *func_8016A894(s16 flags, s16 kind_id, u16 variant, s16 spawn_value);
#endif

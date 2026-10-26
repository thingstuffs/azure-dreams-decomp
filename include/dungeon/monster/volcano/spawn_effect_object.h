#ifndef DUNGEON_OVL_E27054_H
#define DUNGEON_OVL_E27054_H
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"

typedef void (*Callback)(void);


extern void *allocate_list_node(s32 kind, void *data);
extern u8 *func_8003FD64(s32 kind, void *data);
extern s32 register_node(void *object, void *callback);
extern s32 func_8004491C(void *object, void *callback);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *object, s32 attr_a, s16 attr_b);
extern void initialize_actor_sprite_and_animation(void *object, void *attr_a, void *attr_b, s32 attr_c);
extern void try_move_actor_to_valid_position(void *object, void *attr_a, void *attr_b, void *attr_c);

extern void func_8014CE5C(void);
extern u8 volcano_frame_set[];
extern u8 D_80150538[];
extern void func_8014CA58(void);

void * spawn_effect_object(s32 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
#endif

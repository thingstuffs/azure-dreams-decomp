#ifndef DUNGEON_OVL_E09000_CODE_H
#define DUNGEON_OVL_E09000_CODE_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016A800_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_8016A800_0;   /* result in func_8016A854 */

typedef struct S_8016A800_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A800_1;   /* root in func_8016A854 */

typedef struct S_8016A800_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A800_2;   /* position in func_8016A854 */

typedef struct S_8016A800_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A800_3;   /* arg3_part in func_8016A854 */

typedef struct S_8016A800_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A800_4;   /* (void *)arg2_work in func_8016A854 */


extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern void func_8016AA58();
extern void func_8016AE5C();
extern u8 D_8016E510[];
extern u8 D_8016E538[];



/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
#endif

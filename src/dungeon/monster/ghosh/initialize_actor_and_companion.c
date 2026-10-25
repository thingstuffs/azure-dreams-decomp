#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8016AEDC_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    u8 * unk_10;
} S_8016AEDC_0;   /* object in initialize_actor_and_companion */

typedef struct S_8016AEDC_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x28];
    s8 unk_48;
    s8 unk_49;
    s8 unk_4A;
    s8 unk_4B;
} S_8016AEDC_1;   /* work in initialize_actor_and_companion */

typedef struct S_8016AEDC_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016AEDC_2;   /* part_a in initialize_actor_and_companion */

typedef struct S_8016AEDC_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016AEDC_3;   /* part_b in initialize_actor_and_companion */

typedef struct S_8016AEDC_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
    s8 unk_B0;
    u8 pad_B1[0x3];
    s8 unk_B4;
} S_8016AEDC_4;   /* a0_copy in initialize_actor_and_companion */

typedef struct S_8016AEDC_5 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016AEDC_5;   /* a2_copy in initialize_actor_and_companion */

typedef struct S_8016AEDC_6 {
    u8 pad_00[0x12];
    s8 unk_12;
    u8 unk_13;
    u8 pad_14[0x2F];
    u8 unk_43;
} S_8016AEDC_6;   /* spawned in initialize_actor_and_companion */


struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
void func_80042640(void *, s16);
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 retain_spawn_resource(s16, s16);
extern s8 random_dungeon_range_16();
void initialize_actor_sprite_and_animation(void *, void *, void *, s32);
s32 try_move_actor_to_valid_position(void *, void *, void *, void *);
void * allocate_boss_actor(s16, s16, s16, s16);

extern u8 D_8016B0E8[];
extern s32 ghosh_action_resume_address;
extern u8 ghosh_frame_set_3[];
extern u8 *ghosh_actor_node;

/*
 * Creates Ghosh and its companion one tile to the right, stores both nodes, and retains the
 * companion's resources.
 */
void *initialize_actor_and_companion(s16 mode_flags, s32 config_24, s32 config_25, s32 config_0a)
{
    u8 *work_copy;
    u16 spawn_config_0a;
    s32 saved_config_24;
    s16 saved_config_25;
    u8 *object;
    u8 *work;
    u8 *part_a;
    u8 *part_b;
    u8 *callback;
    u8 *spawned;
    s32 mode_kind;
    u16 saved_config_0a;

    work = 0;
    saved_config_24 = config_24;
    saved_config_25 = config_25;
    object = allocate_list_node(0x112, (struct ObjectNodeHeader * *)(((u8 *)(&scene_object_list_anchor))));
    saved_config_0a = config_0a;
    if (object != 0) {
        work = object + 0x20;
        ghosh_actor_node = object;
        ((S_8016AEDC_0 *)object)->unk_10 = D_8016B0E8;
        ((S_8016AEDC_1 *)work)->unk_13 = MONSTER_GHOSH;
        register_node(object, project_sprite_chain);

        callback = ghosh_frame_set_3;
        part_a = ((S_8016AEDC_0 *)object)->unk_08;
        work_copy = work;
        ((S_8016AEDC_2 *)part_a)->unk_0A = config_0a;
        part_b = ((S_8016AEDC_0 *)object)->unk_0C;
        mode_kind = mode_flags & 3;
        ((S_8016AEDC_3 *)part_b)->unk_2C = callback;
        ((S_8016AEDC_3 *)part_b)->unk_24 = saved_config_24;

        ((S_8016AEDC_3 *)part_b)->unk_25 = saved_config_25;
        if (mode_kind == 1) {
            ((S_8016AEDC_1 *)work)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((S_8016AEDC_1 *)work)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (mode_kind >= 2) {
            ((S_8016AEDC_1 *)work)->unk_14 |= ACTOR_CLASS_ENABLED;
            ((S_8016AEDC_1 *)work)->unk_1C |= ACTOR_PLAYER_SIDE;
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, (s16)mode_flags);
        {

            ((S_8016AEDC_4 *)work_copy)->unk_9A = 0xFF;
            ((S_8016AEDC_4 *)work_copy)->unk_9C = -1;
            ((S_8016AEDC_4 *)work_copy)->unk_8C = &ghosh_action_resume_address;
            ((S_8016AEDC_4 *)work_copy)->unk_AE = 0;
            ((S_8016AEDC_4 *)work_copy)->unk_B4 = 0;
            ((S_8016AEDC_4 *)work_copy)->unk_B0 = 0;
            ((S_8016AEDC_5 *)part_b)->unk_14 |= 0x80;
            try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
        }
        ((S_8016AEDC_1 *)work)->unk_49 = 0xE;
        ((S_8016AEDC_1 *)work)->unk_48 = 3;
        ((S_8016AEDC_1 *)work)->unk_4A = random_dungeon_range_16(0x10, 0x18);
        ((S_8016AEDC_1 *)work)->unk_4B = 1;
    }

    {
        s32 spawn_mode;
        s32 spawn_config_24;
        s32 spawn_config_25;

        spawn_mode = (s16)mode_flags;
        spawn_config_24 = (s16)(saved_config_24 + 1);
        config_25 = (s32)((u32)saved_config_25 << 16);
        spawn_config_0a = saved_config_0a;
        spawn_config_25 = config_25 >> 16;
        spawned = allocate_boss_actor(spawn_mode, spawn_config_24, spawn_config_25, (s16)spawn_config_0a);
    }
    retain_spawn_resource(((S_8016AEDC_6 *)spawned)->unk_13, 1);
    func_80042640(spawned, ((S_8016AEDC_6 *)spawned)->unk_13);
    ((S_8016AEDC_6 *)spawned)->unk_43 = 0xFF;
    ((S_8016AEDC_6 *)spawned)->unk_12 = 0;
    return work;
}

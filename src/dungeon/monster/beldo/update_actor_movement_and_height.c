#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef s32 M2C_UNK;
extern int abs(int);

typedef void (*Callback)();

typedef union {
    long long value;
    struct { s32 high; u32 low; } word;
} DivProduct;

extern void enqueue_runtime_pool_script();
extern void select_indirect_table_entry();
extern void advance_sprite_animation_and_textures();
extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern void update_object_animation(void *obj, void *motion, SpriteFrameState *part, void *state);
extern Callback beldo_callbacks[];
extern M2C_UNK D_80173FC8[];

typedef struct S_8017112C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { u8 n; s8 n2; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
    u8 pad_8A[0x11];
    u8 unk_9B;
    u8 pad_9C[0x1F];
    u8 unk_BB;
} S_8017112C_0;   /* actor in update_actor_movement_and_height */

typedef struct S_8017112C_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8017112C_1;   /* slot in update_actor_movement_and_height */

typedef struct S_8017112C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017112C_2_pre;   /* the 0x14 bytes before node in update_actor_movement_and_height, addressed as node[-1] */

typedef struct S_8017112C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8017112C_3;   /* record in update_actor_movement_and_height */

typedef struct S_8017112C_4 {
    s32 unk_00;
    u8 pad_04[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_8017112C_4;   /* motion in update_actor_movement_and_height */

/* Updates actor behavior, movement, facing, and height. */
void update_actor_movement_and_height(void *entity_arg, void *motion_arg, SpriteFrameState *monster_arg)
{
    void *actor = entity_arg;
    u16 state_direction;
    void *call_entity;
    void *call_motion;
    void *call_monster;
    s32 saved_state;
    s32 current_state;
    s32 view_angle;
    Callback callback;
    Callback active_callback;
    s16 floor_height;
    s32 target_height;
    s32 height;
    s32 height_gap;
    u16 global_flags;
    u16 *flag_word;
    s32 height_delta;
    s32 height_fixed;
    s32 divisor_magic;
    s32 height_step;
    DivProduct product;
    u8 *slot;
    void *node;
    void *record;

    if (((S_8017112C_0 *)actor)->unk_BB == 0 && g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
        ((S_8017112C_0 *)actor)->unk_BB = 1;
        enqueue_runtime_pool_script(D_80173FC8);
        ((S_8017112C_0 *)actor)->unk_6D.n = 0;
        ((S_8017112C_0 *)actor)->unk_9B = 0;
    }

    flag_word = &(*(u16 *)0x80013714);
    global_flags = *flag_word;
    if (global_flags & 8) {
        s32 slot_index = 1;
        slot = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            node = ((S_8017112C_1 *)slot)->unk_AC;
            if (node != 0) {
                record = ((S_8017112C_2_pre *)node)[-1].unk_00;
                ((S_8017112C_3 *)record)->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot -= 4;
        } while (slot_index >= 0);
    }

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(Callback *)((u8 *)entity_arg + (0x8C)));
        if (callback == (Callback)&update_object_animation) {
            callback(entity_arg, motion_arg, monster_arg, actor);
            return;
        }
        ((S_8017112C_0 *)actor)->unk_71 &= 0x7F;
        return;
    }

    call_entity = entity_arg;
    call_motion = motion_arg;
    call_monster = monster_arg;
    state_direction = ((S_8017112C_0 *)actor)->unk_6D.n2;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_monster, actor) != 0) {
        return;
    }

    active_callback = (*(Callback *)((u8 *)entity_arg + (0x8C)));
    if (active_callback != 0) {
        active_callback(entity_arg, motion_arg, monster_arg, actor);
    }
    beldo_callbacks[(*(u8 *)((u8 *)entity_arg + (0x9A)))](entity_arg, motion_arg, monster_arg, actor);

    saved_state = (s32)state_direction << 16;
    current_state = ((S_8017112C_0 *)actor)->unk_6D.n2;
    saved_state >>= 16;
    if (saved_state != current_state) {
        try_move_actor_to_valid_position(entity_arg, motion_arg, monster_arg, actor);
    }

    ((S_8017112C_4 *)motion_arg)->unk_00 += ((S_8017112C_4 *)motion_arg)->unk_0C;
    (*(s32 *)((u8 *)motion_arg + (4))) += ((S_8017112C_4 *)motion_arg)->unk_10;

    view_angle = g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017112C_0 *)actor)->unk_2A + 0x100;
    state_direction = (view_angle >> 9) & 7;
    if ((*(s16 *)((u8 *)entity_arg + (0x94))) != state_direction) {
        select_indirect_table_entry(monster_arg,
                      *((u8 *)monster_arg->frameTable + state_direction),
                      monster_arg->unk_04);
        (*(s16 *)((u8 *)entity_arg + (0x94))) = state_direction;
    }

    monster_arg->flags &= 0xFFFE;
    apply_monster_koyaw_data(((S_8017112C_0 *)actor)->unk_1C, (u8 *)monster_arg + 0xC);

    if (!(((S_8017112C_0 *)actor)->unk_1C & 0x20)) {
        if (!(monster_arg->flags & 0x40)) {
            advance_sprite_animation_and_textures(monster_arg);
        }
    } else {
        monster_arg->flags |= 0x7000;
        ((S_8017112C_0 *)actor)->unk_1C &= 0xFFFBFFFF;
    }

    if ((*(s16 *)((u8 *)entity_arg + (0xB8))) == 1) {
        target_height = ((S_8017112C_4 *)motion_arg)->unk_14.at02.v;
        height = ((S_8017112C_4 *)motion_arg)->unk_08.at02.v;
        height_fixed = ((S_8017112C_4 *)motion_arg)->unk_08.at02u.v;
        if (target_height > height) {
            height_gap = target_height - height;
            height_gap = abs(height_gap);
            divisor_magic = 0x66660000;
            if (height_gap >= 0x65) {
                height_gap = height_fixed + 8;
                ((S_8017112C_4 *)motion_arg)->unk_08.at02.v = height_gap;
            } else {
                height_delta = ((S_8017112C_4 *)motion_arg)->unk_14.at00.v;
                height_fixed = ((S_8017112C_4 *)motion_arg)->unk_08.at00.v;
                divisor_magic |= 0x6667;
                height_delta -= height_fixed;
                height_delta = abs(height_delta);
                product.value = (long long)height_delta * divisor_magic;
                height_step = (product.word.high >> 2) - (height_delta >> 31);
                height_fixed += height_step;
                ((S_8017112C_4 *)motion_arg)->unk_08.at00.v = height_fixed;
            }
        }
    }

    if ((*(s16 *)((u8 *)entity_arg + (0xB8))) == 2 && ((S_8017112C_4 *)motion_arg)->unk_08.at02.v >= -0x3EF) {
        ((S_8017112C_4 *)motion_arg)->unk_08.at02.v = ((S_8017112C_4 *)motion_arg)->unk_08.at02u.v - 4;
    }

    if (((S_8017112C_0 *)actor)->unk_1C & 0x40000000) {
        ((S_8017112C_0 *)actor)->unk_1C &= 0xBFFFFFFF;
        floor_height = sample_terrain_surface_height((monster_arg->tile_x << 6) | 0x20,
                              (monster_arg->tile_y << 6) | 0x20,
                              (s16)(((S_8017112C_0 *)actor)->unk_88 - 0x20));
        if (floor_height < 0x200) {
            (*(u16 *)((u8 *)entity_arg + (0x92))) += ((S_8017112C_0 *)actor)->unk_88 - floor_height;
            ((S_8017112C_0 *)actor)->unk_88 = floor_height;
        }
    }

    monster_arg->flags |= 0x40;
}

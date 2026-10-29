#include "shared/audio_commands.h"
/* Targeted effect movement, particle spawning, sprite growth, and fading. */
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_18fa800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor/effect.h"
#include "dungeon/effect/particle.h"
#include "dungeon/effect/screen.h"
#include "dungeon/item.h"

typedef struct S_func_818DA800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[2];
    union { s16 as_s16; u16 as_u16; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 as_s16; u16 as_u16; } unk_50;
    union { s16 as_s16; u16 as_u16; } unk_52;
} S_func_818DA800_1;

typedef struct S_func_818DA800_2 {
    union {
        s32 as_s32;
        struct {
            u8 pad_00[2];
            union { s16 as_s16; u16 as_u16; } unk_02;
        } half;
    } unk_00;
    union {
        s32 as_s32;
        struct {
            u8 pad_04[2];
            union { s16 as_s16; u16 as_u16; } unk_06;
        } half;
    } unk_04;
    union {
        s32 as_s32;
        struct {
            u8 pad_08[2];
            union { s16 as_s16; u16 as_u16; } unk_0A;
        } half;
    } unk_08;
    union {
        s32 as_s32;
        struct {
            u8 pad_0C[2];
            s16 unk_0E;
        } half;
    } unk_0C;
    union {
        s32 as_s32;
        struct {
            u8 pad_10[2];
            s16 unk_12;
        } half;
    } unk_10;
    union {
        s32 as_s32;
        struct {
            u8 pad_14[2];
            s16 unk_16;
        } half;
    } unk_14;
} S_func_818DA800_2;

typedef struct S_func_818DA800_3 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    union { s8 as_s8; u8 as_u8; } unk_72;
    union { s8 as_s8; u8 as_u8; } unk_73;
} S_func_818DA800_3;

typedef struct S_func_818DA800_5 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_818DA800_5;

typedef struct S_func_818DA800_7 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818DA800_7;

typedef struct S_func_818DA800_8 {
    void *unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[2];
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x34];
    u16 unk_48;
    u8 pad_4A[2];
    u16 unk_4C;
} S_func_818DA800_8;

typedef struct S_func_818DA800_9 {
    u8 pad_00[4];
    void *unk_04;
} S_func_818DA800_9;

typedef struct S_func_818DA800_10 {
    u8 unk_00;
} S_func_818DA800_10;

typedef struct S_func_818DA800_11 {
    u8 pad_00[2];
    u16 unk_02;
} S_func_818DA800_11;

extern s32 get_definition_entry_byte_13(s16 entry_index);

#define D_80024538 ((u8 *)advance_target_growth_and_fade)
extern u8 ribbon_sprite_entries[];
#define D_80024684 ((u8 *)create_coordinate_sprite_object)

extern u8 current_spell_effect_variant[];

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18fa800_entry)(S_func_818DA800_1 *, S_func_818DA800_2 *) = run_growing_target_effect;

/* Advances a targeted effect through movement, particle spawning, target interaction, and cleanup. */
void run_growing_target_effect(S_func_818DA800_1 *effect_state, S_func_818DA800_2 *motion)
{
    ActorRecord *actor;
    MovingTile *actor_data;
    void *image_base;
    void *resource_base;
    s32 actor_or_corner;
    SpriteFrameState *prim;
    u8 * actor_header;
    S_func_818DA800_8 *child_state;
    s16 timer;
    s32 phase;
    s32 tile_coord;

    actor = effect_state->unk_00;
    timer = (u16)effect_state->unk_50.as_u16;
    timer -= 1;
    phase = effect_state->unk_0A.as_s16;
    actor_data = ((S_func_818DA800_5 *)((u8 *)actor - 0x20))->unk_0C;
    effect_state->unk_50.as_u16 = timer;

    actor_header = ((u8 *)actor - 0x20);
    switch (phase) {
    case 0:
    if ((((u16 *)effect_state->unk_04)[0] & 0x80) == 0) {
        break;
    }
    {
        S_func_818DA800_3 *target_actor;
        s16 height;

        height = (s16)get_definition_entry_byte_13(0x22);
        target_actor = scan_actor_along_heading(actor,
            actor_data->tile_x,
            actor_data->tile_y,
            actor->facing, height);
        actor->target = target_actor;
        if (target_actor == 0) {
            actor->target_tile_x = actor_data->tile_x;
            actor->target_tile_y = actor_data->tile_y;
        } else {
            prim = ((S_func_818DA800_5 *)((u8 *)target_actor - 0x20))->unk_0C;
            actor->target_tile_x = prim->tile_x;
            actor->target_tile_y = prim->tile_y;
        }
    }

    motion->unk_00.half.unk_02.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_00.half.unk_02.as_u16;
    motion->unk_04.half.unk_06.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_04.half.unk_06.as_u16;
    motion->unk_08.half.unk_0A.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_08.half.unk_0A.as_u16;
    effect_state->unk_50.as_u16 = 8;
    tile_coord = actor->target_tile_x;
    motion->unk_0C.half.unk_0E =
        (tile_coord << 6) - (motion->unk_00.half.unk_02.as_u16 - 0x20);
    motion->unk_0C.as_s32 = motion->unk_0C.as_s32 /
        effect_state->unk_50.as_s16;
    tile_coord = actor->target_tile_y;
    motion->unk_10.half.unk_12 =
        (tile_coord << 6) - (motion->unk_04.half.unk_06.as_u16 - 0x20);
    motion->unk_10.as_s32 = motion->unk_10.as_s32 /
        effect_state->unk_50.as_s16;
    motion->unk_14.half.unk_16 = sample_terrain_surface_height(
        motion->unk_00.half.unk_02.as_u16, motion->unk_04.half.unk_06.as_u16,
        (s16)(((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_08.half.unk_0A.as_u16 -
              0x30)) - motion->unk_08.half.unk_0A.as_s16;
    motion->unk_14.as_s32 = motion->unk_14.as_s32 /
        effect_state->unk_50.as_s16;
    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
    effect_state->unk_0A.as_u16++;
    break;

    case 1:
    motion->unk_00.as_s32 += motion->unk_0C.as_s32;
    motion->unk_04.as_s32 += motion->unk_10.as_s32;
    motion->unk_08.as_s32 += motion->unk_14.as_s32;
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    {
        actor_or_corner = 3;
        image_base = D_80024538;
        resource_base = ribbon_sprite_entries;
        do {
            ObjectNodeHeader *burst_obj;
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            s32 prim_color;

            burst_obj = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (burst_obj != 0) {
                register_node(burst_obj, project_sprite_chain);
                prim = burst_obj->sprite;
                position_or_z_offset = (s32)burst_obj->position;
                burst_obj->update_callback = image_base;
                center_coord = motion->unk_00.half.unk_02.as_s16;
                child_state = (S_func_818DA800_8 *)((u8 *)burst_obj + 0x20);
                if (actor_or_corner >> 1) {
                    corner_coord = center_coord - 16;
                } else {
                    corner_coord = center_coord + 16;
                }
                ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_00.half.unk_02.as_s16 = corner_coord;
                position_or_z_offset = (s32)burst_obj->position;
                center_coord = motion->unk_04.half.unk_06.as_s16;
                if ((actor_or_corner & 1) == 0) {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord + 16;
                    prim_color = 0xC00000;
                } else {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord - 16;
                    prim_color = 0xC00000;
                }
                position_or_z_offset = -0x100000;
                burst_obj->position->z.v =
                    motion->unk_08.as_s32 + position_or_z_offset;
                prim->scale_y = 0xC00;
                prim->tpage_abr = 0x60;
                {
                    u16 prim_flags;

                    prim_flags = prim->flags;
                    prim_color |= 0xC000;
                    prim_color |= 0xC0;
                    position_or_z_offset = resource_base;
                    prim->unk_00 = position_or_z_offset;
                    prim->scale_x = 0;
                    prim->color.word = prim_color;
                    prim_flags |= 0xC;
                    prim->flags = prim_flags;
                }
                prim->source = ((S_func_818DA800_9 *)prim->unk_00)->unk_04;
                prim->unk_04 = 0;
                prim->frame_ticks = 0;
                child_state->unk_00 = effect_state;
                child_state->unk_48 =
                    actor->target ? 0x20 : 0xA;
                child_state->unk_4C = 0;
            }
            actor_or_corner--;
        } while (actor_or_corner >= 0);
    }
    if (actor->target != 0) {
        S_func_818DA800_5 *impact_obj;
        impact_obj = allocate_list_node(0x201, &scene_object_list_anchor.next);
        if (impact_obj != 0) {
            u16 effect_y;
            u16 effect_z;
            s32 duration;
            register_node(impact_obj, func_80024714);
            impact_obj->unk_10 = D_80024684;
            child_state = (S_func_818DA800_8 *)((u8 *)impact_obj + 0x20);
            child_state->unk_04 = motion->unk_00.half.unk_02.as_u16;
            effect_y = motion->unk_04.half.unk_06.as_u16;
            child_state->unk_06 = effect_y;
            effect_z = motion->unk_08.half.unk_0A.as_u16;
            child_state->unk_12 = 1;
            child_state->unk_0C = -64;
            duration = 40;
            child_state->unk_08 = effect_z;
            impact_obj->unk_20 = effect_state;
            child_state->unk_10 = duration;
        }
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    break;

    case 2:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    if (actor->target == 0) {
        effect_state->unk_50.as_u16 = 8;
        effect_state->unk_0A.as_u16 = 5;
        break;
    }
    effect_state->unk_50.as_u16 = 20;
    effect_state->unk_0A.as_u16++;
    break;

    case 3:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    if (actor->target != 0 &&
        try_trigger_target_record_effect(actor->target, 1, actor) == 0 &&
        (((S_func_818DA800_3 *)actor->target)->unk_14 & 4) != 0) {
        try_apply_effect_four_by_chance(
            actor->target,
            ((S_func_818DA800_10 *)current_spell_effect_variant)->unk_00 == 0xFF ? 0xFF : 0x10,
            2);
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    break;

    case 4:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    effect_state->unk_50.as_u16 = 4;
    effect_state->unk_0A.as_u16++;
    break;

    case 5:
    if (effect_state->unk_52.as_s16 & (u16)0x8000) {
        effect_state->unk_52.as_u16 &= 0x7FFF;
    } else {
        if (effect_state->unk_50.as_s16 <= 0) {
            g_dungeon_status.active_actor = 0;
            ((S_func_818DA800_11 *)((u8 *)effect_state - 4))->unk_02 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            break;
        }
    }
    }
}
#include "modules/dungeon_ovl_18fa800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct Unk818DAD38Owner {
    void *unk0;
    u8 pad4[0x44];
    u16 timer;
    s16 unk4A;
    u16 state;
} Unk818DAD38Owner;

typedef struct Unk818DAD38Target {
    u8 pad0[4];
    s8 unk4;
    s8 unk5;
    u8 pad6[6];
    u32 unkC;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 unk1C;
    u16 unk1E;
} Unk818DAD38Target;

/* Advance the target's growth animation, then fade its color and mark completion. */
void advance_target_growth_and_fade(Unk818DAD38Owner *owner, s32 unused,
                   SpriteFrameState *target) {
    s16 state;
    u16 next_scale;
    u16 *owner_flags;

    owner_flags = (u16 *)((u8 *)owner->unk0 + 0x52);
    *owner_flags |= 0x8000;
    owner->timer--;
    advance_sprite_animation_and_textures(target);

    if (target->flags & 0x6000) {
        target->unk_04 = 0;
        target->frame_ticks = 0;
    }

    state = owner->state;
    switch (state) {
    case 0:
        target->scale_x += 0x200;
        next_scale = target->scale_y + 0x200;
        target->scale_y = next_scale;
        if (next_scale >= 0x1C00) {
            target->scale_x = 0xC00;
            target->scale_y = 0x1800;
            owner->unk4A = 0;
            target->color.word = 0x808080;
        }
        if ((s16)owner->timer <= 0) {
            owner->state++;
        }
        break;
    case 1:
        if ((u8)*(u32 *)&target->color.word < 9) {
            target->color.word = 0;
            ((u16 *)owner)[-1] |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        } else {
            *(u32 *)&target->color.word += 0xFFEFEFF0;
        }
        break;
    }
}

/* MECHANISM: Updating unk1C before unk1E selects retail's v1/v0 load-add order while held s1/s0
   preserve the 0x20 frame. The state ladder is a switch; the fade arm needs no barrier here. */
#include "modules/dungeon_ovl_18fa800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_818DAE84_0 {
    void * unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    s16 unk_10;
} S_818DAE84_0;   /* arg0 in create_coordinate_sprite_object */

typedef struct S_818DAE84_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818DAE84_1;   /* inner in create_coordinate_sprite_object */

/* Updates progress from a countdown and sets completion flags when it expires. */
void create_coordinate_sprite_object(void *state) {
    s32 remaining;
    s16 next_remaining;
    s32 progress;
    S_818DAE84_1 *linked_object;

    linked_object = ((S_818DAE84_0 *)state)->unk_00;
    linked_object->unk_52 = (u16)(linked_object->unk_52 | 0x8000);

    progress = ((S_818DAE84_0 *)state)->unk_0C;
    if (progress < 0x50) {
        progress += 8;
    }

    remaining = ((S_818DAE84_0 *)state)->unk_10;
    ((S_818DAE84_0 *)state)->unk_0C = progress;
    if (remaining < 9) {
        ((S_818DAE84_0 *)state)->unk_0C = remaining * 8;
    }

    next_remaining = (u16)((S_818DAE84_0 *)state)->unk_10 - 1;
    ((S_818DAE84_0 *)state)->unk_10 = next_remaining;
    if ((next_remaining << 16) <= 0) {
        ((u16 *)state)[-1] = (u16)(((u16 *)state)[-1] | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

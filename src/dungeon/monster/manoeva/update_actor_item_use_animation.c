#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
extern int abs(int);

typedef __SIZE_TYPE__ uptr;

typedef struct S_801728E4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801728E4_0;   /* arg0 in update_actor_item_use_animation */

typedef struct S_801728E4_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_801728E4_1;   /* arg3 in update_actor_item_use_animation */

typedef struct S_801728E4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728E4_3;   /* entry in update_actor_item_use_animation */

typedef struct S_801728E4_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728E4_5;   /* global in update_actor_item_use_animation */

typedef struct {
    u8 pad00[0x12];
    u8 field12;
    u8 field13;
} ItemInfo;

extern u8 manoeva_action_resume_address[8];
extern u8 manoeva_frame_set_1[8];
extern u8 D_80176648[8];
extern u8 manoeva_frame_set_2[8];

extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void * create_actor_spell_effect(void *, void *, s32, void *);
extern void create_actor_linked_effect(void *);

/* Advances an actor's item action through source selection, animation, and cleanup. */
void update_actor_item_use_animation(void *action, void *item, SpriteFrameState *sprite, void *actor)
{
    void *act = actor;
    u8 state;
    s32 use_global_source;
    u16 action_flags;
    s32 item_kind;
    ObjectNodeHeader *source_sprite;

    state = ((S_801728E4_0 *)action)->unk_9B;
    use_global_source = 0;
    switch (state) {
    case 0:
        {
            void *source_entity;

            item = 0;
            if (((S_801728E4_1 *)act)->unk_1C & ACTOR_PLAYER_SIDE) {
                switch (((S_801728E4_1 *)act)->unk_46 & 0x3FFF) {
                case 7:
                    use_global_source = 1;
                    /* fallthrough */
                case 3:
                    item = (u8 *)act + 0xE;
                    break;
                case 6:
                    use_global_source = 1;
                    /* fallthrough */
                case 2:
                    item = (u8 *)act + 0xB;
                    break;
                case 5:
                    use_global_source = 1;
                    /* fallthrough */
                case 1:
                    item = (u8 *)act + 8;
                    break;
                default:
                    break;
                }
            } else {
                item_kind = ((S_801728E4_1 *)act)->unk_46 & 0x3FFF;
                switch (item_kind) {
                case 3:
                    item = (u8 *)act + 0xE;
                    break;
                case 2:
                    item = (u8 *)act + 0xB;
                    break;
                case 1:
                    item = (u8 *)act + 8;
                    break;
                default:
                    break;
                }
            }
            if ((*(u8 *)&((EntityRec *)item)->x) == 0) {
                return;
            }

            {
                s16 global_source_test;

                ((S_801728E4_0 *)action)->unk_98 &= 0xFF7F;
                global_source_test = use_global_source;
                if (global_source_test) {
                    source_entity = primary_actor_record;
                    ((S_801728E4_1 *)act)->unk_60 = source_entity;
                    source_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)source_entity - 0x20))->sprite;
                    ((S_801728E4_1 *)act)->unk_72.s = ((S_801728E4_3 *)source_sprite)->unk_24;
                    ((S_801728E4_1 *)act)->unk_73.s = ((S_801728E4_3 *)source_sprite)->unk_25;
                } else if (item_action_definitions[(*(u8 *)&((EntityRec *)item)->x)].kind == 2) {
                    source_entity = ((S_801728E4_1 *)act)->unk_60;
                    if (source_entity != 0) {
                        source_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)source_entity - 0x20))->sprite;
                        ((S_801728E4_1 *)act)->unk_72.s = ((S_801728E4_3 *)source_sprite)->unk_24;
                        ((S_801728E4_1 *)act)->unk_73.s = ((S_801728E4_3 *)source_sprite)->unk_25;
                    }
                } else {
                    ((S_801728E4_1 *)act)->unk_60 =
                        scan_actor_along_heading(act,
                                      sprite->tile_x,
                                      sprite->tile_y,
                                      ((S_801728E4_1 *)act)->unk_2A,
                                      0x10);
                    ((S_801728E4_1 *)act)->unk_72.u = abs(((S_801728E4_1 *)act)->unk_72.u);
                    ((S_801728E4_1 *)act)->unk_73.u = abs(((S_801728E4_1 *)act)->unk_73.u);
                }
            }
        }

        if (!create_actor_spell_effect(act, item, use_global_source, (u16 *)((u8 *)action + 0x98))) {
            return;
        }
        create_actor_linked_effect(act);
        ((S_801728E4_0 *)action)->unk_9B++;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_801728E4_0 *)action)->unk_9B++;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = D_80176648;
        select_sprite_entry(sprite,
            *(u8 *)((uptr)(((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728E4_1 *)act)->unk_2A + 0x100) >> 9) & 7) +
                    (uptr)D_80176648),
            0);
        ((S_801728E4_0 *)action)->unk_9B++;
        return;

    case 3:
        if (sprite->unk_04 == 6 && (sprite->flags & 0x1000)) {
            ((S_801728E4_0 *)action)->unk_98 |= 0x80;
        } else if (sprite->flags & 0xE000) {
            ((S_801728E4_0 *)action)->unk_98 |= 0x80;
        }
        if (!(((S_801728E4_0 *)action)->unk_98 & 0x80)) {
            return;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        (sprite->frameTable) = manoeva_frame_set_2;
        select_sprite_entry(sprite,
            *(u8 *)((uptr)(((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728E4_1 *)act)->unk_2A + 0x100) >> 9) & 7) +
                    (uptr)manoeva_frame_set_2),
            0);
        ((S_801728E4_0 *)action)->unk_9B++;
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            (sprite->frameTable) = manoeva_frame_set_1;
            select_sprite_entry(sprite,
                manoeva_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728E4_1 *)act)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        ((EntityRec *)item)->flags14 = 0;
        ((EntityRec *)item)->unk_10 = 0;
        ((EntityRec *)item)->unk_0C = 0;
        set_record_integer_tile_center(item, sprite->tile_x, sprite->tile_y);
        source_sprite = ((u8 *)(&g_dungeon_status));
        if (source_sprite->sprite != 0) {
            return;
        }
        ((S_801728E4_5 *)source_sprite)->unk_0A--;
        ((S_801728E4_0 *)action)->unk_8C = manoeva_action_resume_address;
        advance_status_timers(act);
        ((S_801728E4_1 *)act)->unk_73.s = 0;
        ((S_801728E4_1 *)act)->unk_72.s = 0;
        ((S_801728E4_1 *)act)->unk_6D--;
        ((S_801728E4_1 *)act)->unk_46 &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}

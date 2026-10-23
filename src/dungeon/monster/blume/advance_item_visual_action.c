#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/cd.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_80170FD8[];
extern u8 D_80171284[];
extern u8 blume_action_resume_address[];
#include "dungeon/monster/blume.h"
extern u8 D_80175424[12];

typedef struct S_801737C8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737C8_0;   /* arg0 in advance_item_visual_action */

typedef struct S_801737C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737C8_2;   /* linked in advance_item_visual_action */


   /* coords in advance_item_visual_action */

/* Process item use, spawn its visual effect, and finish the action when ready. */
/* Starts a targeted spell, emits randomly colored sprite particles during casting, then restores movement
 * and status. */
void advance_item_visual_action(void *controller, ObjectPosition *motion, SpriteFrameState *actor, void *object)
{
    u8 *item_slot;
    s16 use_player;
    u8 state;
    void *target;

    use_player = 0;
    state = ((S_801737C8_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)object + 0x1C)) & ACTOR_PLAYER_SIDE) {
            switch ((*(u16 *)((u8 *)object + 0x46)) & 0x3FFF) {
            case 7:
                use_player = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)object + 0xE;
                break;
            case 6:
                use_player = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)object + 0xB;
                break;
            case 5:
                use_player = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch ((*(u16 *)((u8 *)object + 0x46)) & 0x3FFF) {
            case 3:
                item_slot = (u8 *)object + 0xE;
                break;
            case 2:
                item_slot = (u8 *)object + 0xB;
                break;
            case 1:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_801737C8_0 *)controller)->unk_98 &= 0xFF7F;
            {
                s32 target_player;

                target_player = use_player;
                if (target_player != 0) {
                    u32 item_data;

                    target = primary_actor_record;
                    (*(void * *)((u8 *)object + 0x60)) = target;
                    item_data = (u32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    (*(u8 *)((u8 *)object + 0x72)) = ((S_801737C8_2 *)item_data)->unk_24;
                    (*(u8 *)((u8 *)object + 0x73)) = ((S_801737C8_2 *)item_data)->unk_25;
                } else {
                    u8 *item_table;
                    u8 item_id;
                    u32 item_data;

                    item_table = item_action_definitions;
                    item_id = *item_slot;
                    item_data = (item_id * 20 + item_table)[0x12];
                    if (item_data == 2) {
                        target = (*(void * *)((u8 *)object + 0x60));
                        if (target != 0) {
                            item_data = (u32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                            (*(u8 *)((u8 *)object + 0x72)) = ((S_801737C8_2 *)item_data)->unk_24;
                            (*(u8 *)((u8 *)object + 0x73)) = ((S_801737C8_2 *)item_data)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_actor_along_heading(
                            object, actor->tile_x, actor->tile_y,
                            (*(s16 *)((u8 *)object + 0x2A)), 0x10);
                        (*(void * *)((u8 *)object + 0x60)) = (void *)dx;
                        dx = abs(*(s8 *)((u8 *)object + 0x72));
                        dy = abs(*(s8 *)((u8 *)object + 0x73));
                        (*(u8 *)((u8 *)object + 0x72)) = dx;
                        (*(u8 *)((u8 *)object + 0x73)) = dy;
                    }
                }
            }

            if (create_actor_spell_effect(object, item_slot, use_player, (u8 *)controller + 0x98) == 0) {
                return;
            }
            ((S_801737C8_0 *)controller)->unk_9B = ((S_801737C8_0 *)controller)->unk_9B + 1;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(object);
        (*(u8 *)((u8 *)object + 0x6D))--;
        ((S_801737C8_0 *)controller)->unk_8C = blume_action_resume_address;
        (*(u8 *)((u8 *)object + 0x73)) = 0;
        (*(u8 *)((u8 *)object + 0x72)) = 0;
        (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        ((S_801737C8_0 *)controller)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 effect_count;
            s32 dim_channel;

            effect_count = 0;
            dim_channel = 0x20;
            for (; effect_count < 1; effect_count++) {
                object = allocate_flagged_object_node(0x212);
                if (object != 0) {
                    u8 *effect_data;
                    SpriteFrameState *sprite;
                    MovingPosition *effect_pos;
                    s32 dx;
                    s32 dy;
                    s32 color_bits;

                    effect_data = (u8 *)object + 0x20;
                    (*(u16 *)((u8 *)effect_data + 0x24)) = 0x13;
                    (*(u16 *)((u8 *)object + 0x20)) = 0;
                    (*(void * *)((u8 *)object + 0x10)) = D_80171284;
                    register_node(object, D_80170FD8);

                    sprite = (*(void * *)((u8 *)object + 0x0C));
                    sprite->tpage_abr = dim_channel;
                    sprite->flags |= 0x0C;
                    effect_pos = (*(void * *)((u8 *)object + 8));
                    effect_pos->x = ((u16)motion->x.w.i);
                    effect_pos->y = ((u16)motion->y.w.i);
                    effect_pos->z = ((u16)motion->z.w.i);

                    dx = (rand() & 0x3F) - 0x20;
                    dy = (rand() & 0x3F) - 0x20;
                    effect_pos->x += dx;
                    effect_pos->y += dy;
                    sprite->scale_x = 0x1000;
                    sprite->scale_y = 0x1000;

                    color_bits = rand() & 7;
                    if (color_bits & 1) {
                        sprite->color.c.r = 0x80;
                    } else {
                        sprite->color.c.r = dim_channel;
                    }
                    if (color_bits & 2) {
                        sprite->color.c.g = 0x80;
                    } else {
                        sprite->color.c.g = dim_channel;
                    }
                    if (color_bits & 4) {
                        sprite->color.c.b = 0x80;
                    } else {
                        sprite->color.c.b = dim_channel;
                    }
                    (*(u8 *)((u8 *)effect_data + 2)) = sprite->color.c.r;
                    (*(u8 *)((u8 *)effect_data + 3)) = sprite->color.c.g;
                    (*(u8 *)((u8 *)effect_data + 4)) = sprite->color.c.b;
                    sprite->clut = 0x7DCF;
                    sprite->flags |= 0x100;
                    (*(Copy12 *)((u8 *)effect_data + 0x34)) = *(Copy12 *)D_80175424;
                    sprite->source = effect_data + 0x34;
                    (*(u16 *)((u8 *)effect_data + 0x50)) = 8;
                    (*(u16 *)((u8 *)effect_data + 0x4E)) = 4;
                }
            }
        }

        if ((actor->unk_04 == 6 &&
             (actor->flags & 0x1000)) ||
            (actor->flags & 0xE000)) {
            ((S_801737C8_0 *)controller)->unk_98 |= 0x80;
        }
        if ((actor->unk_04 == 9 &&
             (actor->flags & 0x1000)) ||
            (actor->flags & 0xE000)) {
            actor->flags |= 0x800;
            ((S_801737C8_0 *)controller)->unk_96 = 0x14;
            ((S_801737C8_0 *)controller)->unk_9B = ((S_801737C8_0 *)controller)->unk_9B + 1;
            return;
        }
        return;

    case 3:
        {
            s16 timer;

            if (((s32)g_dungeon_status.active_actor) == 0) {
                ((S_801737C8_0 *)controller)->unk_96 = 0;
            }
            timer = ((S_801737C8_0 *)controller)->unk_96 - 1;
            ((S_801737C8_0 *)controller)->unk_96 = timer;
            if (timer <= 0) {
                ((S_801737C8_0 *)controller)->unk_96 = 0;
                actor->flags &= 0xF7FF;
            }
            if (!(actor->flags & 0xE000)) {
                return;
            }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
            if (*(u8 * *)&actor->frameTable != blume_direction_frames) {
                u8 *facing_frames;
                s32 facing_index;

                facing_frames = blume_direction_frames;
                actor->frameTable = facing_frames;
                facing_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 9) & 7;
                select_sprite_entry(actor, facing_frames[facing_index], 0);
                actor->flags &= 0xF7FF;
            }
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_801737C8_0 *)controller)->unk_8C = blume_action_resume_address;
            advance_status_timers(object);
            (*(u8 *)((u8 *)object + 0x73)) = 0;
            (*(u8 *)((u8 *)object + 0x72)) = 0;
            (*(u8 *)((u8 *)object + 0x6D))--;
            (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

        return;
    default:
        return;
    }
}

#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
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

extern s32 get_cd_command_queue_depth(void);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_80170FD8[];
extern u8 D_80171284[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
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

typedef struct S_801737C8_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801737C8_1_pre;   /* the 0x14 bytes before active in advance_item_visual_action, addressed as active[-1] */

typedef struct S_801737C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737C8_2;   /* linked in advance_item_visual_action */

typedef struct S_801737C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801737C8_5;   /* child in advance_item_visual_action */

   /* coords in advance_item_visual_action */

/* Process item use, spawn its visual effect, and finish the action when ready. */
/* Starts a targeted spell, emits randomly colored sprite particles during casting, then restores movement
 * and status. */
void advance_item_visual_action(void *controller, ObjectPosition *motion, void *actor, void *object)
{
    u8 *item_slot;
    s16 use_player;
    u8 state;
    void *target;

    use_player = 0;
    state = ((S_801737C8_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)object + 0x1C)) & 0x2000) {
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
                    item_data = (u32)((S_801737C8_1_pre *)target)[-1].unk_00;
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
                            item_data = (u32)((S_801737C8_1_pre *)target)[-1].unk_00;
                            (*(u8 *)((u8 *)object + 0x72)) = ((S_801737C8_2 *)item_data)->unk_24;
                            (*(u8 *)((u8 *)object + 0x73)) = ((S_801737C8_2 *)item_data)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_monster_along_heading(
                            object, ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25,
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
        set_record_integer_tile_center(motion, ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(object);
        (*(u8 *)((u8 *)object + 0x6D))--;
        ((S_801737C8_0 *)controller)->unk_8C = D_80171E20;
        (*(u8 *)((u8 *)object + 0x73)) = 0;
        (*(u8 *)((u8 *)object + 0x72)) = 0;
        (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteFrameState *)actor)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)actor)->flags &= 0xF7FF;
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
                    void *sprite;
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
                    ((S_801737C8_5 *)sprite)->unk_10 = dim_channel;
                    ((S_801737C8_5 *)sprite)->unk_14 |= 0x0C;
                    effect_pos = (*(void * *)((u8 *)object + 8));
                    effect_pos->unk_02 = ((u16)motion->x.w.i);
                    effect_pos->unk_06 = ((u16)motion->y.w.i);
                    effect_pos->unk_0A = ((u16)motion->z.w.i);

                    dx = (rand() & 0x3F) - 0x20;
                    dy = (rand() & 0x3F) - 0x20;
                    effect_pos->unk_02 += dx;
                    effect_pos->unk_06 += dy;
                    ((S_801737C8_5 *)sprite)->unk_1C = 0x1000;
                    ((S_801737C8_5 *)sprite)->unk_1E = 0x1000;

                    color_bits = rand() & 7;
                    if (color_bits & 1) {
                        ((S_801737C8_5 *)sprite)->unk_0C = 0x80;
                    } else {
                        ((S_801737C8_5 *)sprite)->unk_0C = dim_channel;
                    }
                    if (color_bits & 2) {
                        ((S_801737C8_5 *)sprite)->unk_0D = 0x80;
                    } else {
                        ((S_801737C8_5 *)sprite)->unk_0D = dim_channel;
                    }
                    if (color_bits & 4) {
                        ((S_801737C8_5 *)sprite)->unk_0E = 0x80;
                    } else {
                        ((S_801737C8_5 *)sprite)->unk_0E = dim_channel;
                    }
                    (*(u8 *)((u8 *)effect_data + 2)) = ((S_801737C8_5 *)sprite)->unk_0C;
                    (*(u8 *)((u8 *)effect_data + 3)) = ((S_801737C8_5 *)sprite)->unk_0D;
                    (*(u8 *)((u8 *)effect_data + 4)) = ((S_801737C8_5 *)sprite)->unk_0E;
                    ((S_801737C8_5 *)sprite)->unk_12 = 0x7DCF;
                    ((S_801737C8_5 *)sprite)->unk_14 |= 0x100;
                    (*(Copy12 *)((u8 *)effect_data + 0x34)) = *(Copy12 *)D_80175424;
                    ((S_801737C8_5 *)sprite)->unk_08 = effect_data + 0x34;
                    (*(u16 *)((u8 *)effect_data + 0x50)) = 8;
                    (*(u16 *)((u8 *)effect_data + 0x4E)) = 4;
                }
            }
        }

        if ((((SpriteFrameState *)actor)->unk_04 == 6 &&
             (((SpriteFrameState *)actor)->flags & 0x1000)) ||
            (((SpriteFrameState *)actor)->flags & 0xE000)) {
            ((S_801737C8_0 *)controller)->unk_98 |= 0x80;
        }
        if ((((SpriteFrameState *)actor)->unk_04 == 9 &&
             (((SpriteFrameState *)actor)->flags & 0x1000)) ||
            (((SpriteFrameState *)actor)->flags & 0xE000)) {
            ((SpriteFrameState *)actor)->flags |= 0x800;
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
                ((SpriteFrameState *)actor)->flags &= 0xF7FF;
            }
            if (!(((SpriteFrameState *)actor)->flags & 0xE000)) {
                return;
            }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25);
            if (*(u8 * *)&((SpriteFrameState *)actor)->frameTable != D_801753BC) {
                u8 *facing_frames;
                s32 facing_index;

                facing_frames = D_801753BC;
                ((SpriteFrameState *)actor)->frameTable = facing_frames;
                facing_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 9) & 7;
                select_sprite_entry(actor, facing_frames[facing_index], 0);
                ((SpriteFrameState *)actor)->flags &= 0xF7FF;
            }
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_801737C8_0 *)controller)->unk_8C = D_80171E20;
            advance_status_timers(object);
            (*(u8 *)((u8 *)object + 0x73)) = 0;
            (*(u8 *)((u8 *)object + 0x72)) = 0;
            (*(u8 *)((u8 *)object + 0x6D))--;
            (*(u16 *)((u8 *)object + 0x46)) &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }

        return;
    default:
        return;
    }
}

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void spawn_angled_random_velocity_effect(void *, s32, s32);
extern void spawn_directional_random_velocity_effect(void *, s32);

extern u8 D_800E2348[];
extern u8 D_800E2388[8];
extern u8 D_800E2398[8];
extern s32 D_80171F1C;

typedef struct S_80173B08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173B08_0;   /* arg0 in update_actor_item_use */

typedef struct S_80173B08_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173B08_1_pre;   /* the 0x14 bytes before active in update_actor_item_use, addressed as active[-1] */

typedef struct S_80173B08_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173B08_2;   /* linked in update_actor_item_use */

/* Updates the actor's item-use state, animation, and effects. */
void update_actor_item_use(void *action, EntityRec *motion, void *sprite, void *actor)
{
    u8 *item_slot;
    u32 stage;
    s32 flag;
    s16 effect_count;
    u32 state;
    void *target;

    flag = 0;
    state = ((S_80173B08_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                flag = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                flag = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                flag = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind;

            action_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_80173B08_0 *)action)->unk_98 &= 0xFF7F;
            {
                u8 is_special;
                void *item_id;

                is_special = flag;
                if (is_special != 0) {
                    target = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = target;
                    item_id = ((S_80173B08_1_pre *)target)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173B08_2 *)item_id)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173B08_2 *)item_id)->unk_25;
                } else {
                    item_id = (void *)(*item_slot);
                    if (D_8006DE24[((u8)item_id)].kind == 2) {
                        target = (*(void * *)((u8 *)actor + 0x60));
                        if (target != 0) {
                            item_id = ((S_80173B08_1_pre *)target)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173B08_2 *)item_id)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173B08_2 *)item_id)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_monster_along_heading(
                            actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                            (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                        (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
                        dx = (*(s8 *)((u8 *)actor + 0x72));
                        dy = (*(s8 *)((u8 *)actor + 0x73));
                        if (dx < 0) {
                            dx = -dx;
                        }
                        if (dy < 0) {
                            dy = -dy;
                        }
                        (*(u8 *)((u8 *)actor + 0x72)) = dx;
                        (*(u8 *)((u8 *)actor + 0x73)) = dy;
                    }
                }
            }

            if (create_actor_spell_effect(actor, item_slot, flag,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_80173B08_0 *)action)->unk_9B++;
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            g_dungeon_status.unk_0C = 0;
            (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_80173B08_0 *)action)->unk_8C = &D_80171F1C;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            return;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_80173B08_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        ((S_80173B08_0 *)action)->unk_9B++;
        ((S_80173B08_0 *)action)->unk_98 &= 0xFFF7;
        (*(u32 *)((u8 *)actor + 0x1C)) &= 0xFFFBFFFF;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((SpriteFrameState *)sprite)->tpage_abr = 0x20;
        ((SpriteFrameState *)sprite)->flags |= 0xC;

    case 3:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80173B08_0 *)action)->unk_9B = 7;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            ((S_80173B08_0 *)action)->unk_98 |= 0x80;
            return;
        }
        {
            s16 floor_height;

            floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                  ((u16)motion->y.w.i),
                                  (s16)((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
            if ((((S_80173B08_0 *)action)->unk_92.s -
                 (s16)(floor_height - (*(u16 *)((u8 *)actor + 0x88)))) != 0) {
                return;
            }
        }
        ((S_80173B08_0 *)action)->unk_96.u = 0;
        stage = ((S_80173B08_0 *)action)->unk_9B;
        stage++;
        ((S_80173B08_0 *)action)->unk_9B = stage;
        ((SpriteFrameState *)sprite)->frameTable = D_800E2398;
        select_sprite_entry(sprite, D_800E2398[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
        return;

    case 4:
    {
        s16 timer;

        timer = ((S_80173B08_0 *)action)->unk_96.u;
        ((S_80173B08_0 *)action)->unk_96.u = timer + 1;
        if (timer < 12 && !(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
    }
        ((S_80173B08_0 *)action)->unk_98 |= 0x80;
        ((SpriteFrameState *)sprite)->flags |= 0x800;
        ((S_80173B08_0 *)action)->unk_96.u = 0x12;
        ((S_80173B08_0 *)action)->unk_9B++;
        effect_count = 0;
        do {
            spawn_angled_random_velocity_effect((u8 *)action - 0x20,
                          (*(s16 *)((u8 *)actor + 0x2A)), 0xE0E0E0);
            effect_count++;
        } while ((s16)effect_count < 3);
        return;

    case 5:
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            ((S_80173B08_0 *)action)->unk_96.u = 0;
        }
        if (((S_80173B08_0 *)action)->unk_96.s >= 10) {
            effect_count = 0;
            do {
                spawn_angled_random_velocity_effect((u8 *)action - 0x20,
                              (*(s16 *)((u8 *)actor + 0x2A)), 0xE0E0E0);
                effect_count++;
            } while ((s16)effect_count < 3);
        }
        if ((u32)(((S_80173B08_0 *)action)->unk_96.u - 10) < 7) {
            s16 angle;

            for (angle = 0; angle < 0x1000; angle += 0x200) {
                if (angle != (*(s16 *)((u8 *)actor + 0x2A))) {
                    effect_count = 0;
                    do {
                        spawn_directional_random_velocity_effect((u8 *)action - 0x20, angle);
                        effect_count++;
                    } while ((s16)effect_count <= 0);
                }
            }
        }
        {
            s16 timer;

            timer = ((S_80173B08_0 *)action)->unk_96.u - 1;
            ((S_80173B08_0 *)action)->unk_96.u = timer;
            if (timer > 0 && !(((SpriteFrameState *)sprite)->flags & 0xE000)) {
                return;
            }
        }
        ((S_80173B08_0 *)action)->unk_96.u = 0;
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        state = ((S_80173B08_0 *)action)->unk_98;
        stage = ((S_80173B08_0 *)action)->unk_9B;
        stage++;
        state |= 8;
        ((S_80173B08_0 *)action)->unk_9B = stage;
        ((S_80173B08_0 *)action)->unk_98 = state;
        ((SpriteFrameState *)sprite)->frameTable = D_800E2388;
        select_sprite_entry(sprite, D_800E2388[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
        return;

    case 6:
        if (((S_80173B08_0 *)action)->unk_92.s >= -0x1F) {
            ((S_80173B08_0 *)action)->unk_92.u -= 4;
            return;
        }
        ((S_80173B08_0 *)action)->unk_9B++;

    case 7:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_800E2348) {
            ((SpriteFrameState *)sprite)->frameTable = D_800E2348;
            select_sprite_entry(
                sprite,
                D_800E2348[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
            ((S_80173B08_0 *)action)->unk_9E = 0;
            ((S_80173B08_0 *)action)->unk_98 |= 8;
            (*(u32 *)((u8 *)actor + 0x1C)) |= 0x40000;
            ((S_80173B08_0 *)action)->unk_92.s = -0x20;
            ((SpriteFrameState *)sprite)->flags &= 0xFFF3;
        }
        {

            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
            ((S_80173B08_0 *)action)->unk_8C = &D_80171F1C;
            advance_status_timers(actor);
        }
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    }
}

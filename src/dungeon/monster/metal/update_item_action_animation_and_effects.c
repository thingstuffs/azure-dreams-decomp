#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_parent_return_effect(void *, s32, s32, s32, s32, s32, s32);
extern void spawn_parent_offset_random_motion_effect(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_80171650[];
extern u8 D_801742C8[];


typedef struct S_80173078_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173078_0;   /* arg0 in update_item_action_animation_and_effects */

typedef struct S_80173078_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173078_1_pre;   /* the 0x14 bytes before active in update_item_action_animation_and_effects, addressed as active[-1] */

typedef struct S_80173078_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173078_2;   /* linked in update_item_action_animation_and_effects */


/* Updates an item action, its animation, particle effects, and completion state. */
void update_item_action_animation_and_effects(void *action, EntityRec *movement, void *sprite, void *actor)
{
    u8 *item_slot;
    s16 special;
    s32 count;
    s32 next_state;
    u8 state;
    void *target;

    special = 0;
    state = ((S_80173078_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
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
            u8 *item_id;

            ((S_80173078_0 *)action)->unk_98 &= 0xFF7F;
            if (special != 0) {
                target = D_800814A8;
                (*(void * *)((u8 *)actor + 0x60)) = target;
                item_id = ((S_80173078_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173078_2 *)item_id)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173078_2 *)item_id)->unk_25;
            } else {
                item_id = (u8 *)(*item_slot);
                if (D_8006DE24[((u8)item_id)].kind == 2) {
                    target = (*(void * *)((u8 *)actor + 0x60));
                    if (target != 0) {
                        item_id = ((S_80173078_1_pre *)target)[-1].unk_00;
                        (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173078_2 *)item_id)->unk_24;
                        (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173078_2 *)item_id)->unk_25;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)scan_monster_along_heading(
                        actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
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

                if (create_actor_spell_effect(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
                return;
        }
        next_state = ((S_80173078_0 *)action)->unk_9B + 1;
        ((S_80173078_0 *)action)->unk_9B = next_state;
        return;
        }

        movement->flags14 = 0;
        movement->unk_10 = 0;
        movement->unk_0C = 0;
        set_record_integer_tile_center(movement, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_80173078_0 *)action)->unk_8C = D_80171650;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80173078_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            u16 flags;
            s16 timer;

            flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            if (flags & 0x8000) {
                next_state = ((S_80173078_0 *)action)->unk_9B + 1;
                ((S_80173078_0 *)action)->unk_96.u = 0;
                ((S_80173078_0 *)action)->unk_9B = next_state;
                return;
            }
            if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2 && (flags & 0x1000)) {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = flags | 0x800;
                ((S_80173078_0 *)action)->unk_96.u = 0x16;
            }
            if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
                return;
            }
            timer = ((S_80173078_0 *)action)->unk_96.u - 1;
            ((S_80173078_0 *)action)->unk_96.u = timer;
            if (timer <= 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
                ((S_80173078_0 *)action)->unk_9B++;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
            if (((S_80173078_0 *)action)->unk_96.s < 7) {
                return;
            }
        }

        count = 0;
        do {
            register s32 x;
            register s32 y;
            s16 z;

            count++;
            sprite = (void *)(rand() & 0xFF);
            sprite = (void *)((u32)sprite | 0x80);
            x = rand();
            x &= 0x7F;
            x -= 0x40;
            x <<= 16;
            x >>= 16;
            y = rand();
            y &= 0x7F;
            y -= 0x40;
            y <<= 16;
            y >>= 16;
            z = (rand() & 0x7F) - 0x40;
            create_parent_return_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                          (s32)sprite, x, y, z);
        } while ((u16)count < 5);
        return;

    case 3:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80173078_0 *)action)->unk_96.u = 0x20;
            ((S_80173078_0 *)action)->unk_98 |= 0x80;
            ((S_80173078_0 *)action)->unk_9B++;
            count = 0;
            do {
                s32 brightness;

                count++;
                brightness = (rand() & 0xFF) | 0x80;
                spawn_parent_offset_random_motion_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                              brightness, 0, 0, 0);
            } while ((u16)count < 20);
        }
    case 4:
        {
            s16 timer;

            if (((s32)g_dungeon_status.unk_0C) == 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
            }
            timer = ((S_80173078_0 *)action)->unk_96.u - 1;
            ((S_80173078_0 *)action)->unk_96.u = timer;
            if (timer <= 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
            movement->flags14 = 0;
            movement->unk_10 = 0;
            movement->unk_0C = 0;
            set_record_integer_tile_center(movement, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801742C8) {
                u8 *animation_table;
                s32 direction;

                animation_table = D_801742C8;
                (*(u8 * *)((u8 *)sprite + 0x2C)) = animation_table;
                direction = ((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animation_table[direction], 0);
            }
            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
            ((S_80173078_0 *)action)->unk_8C = D_80171650;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }
    }
}

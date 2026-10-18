#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern int abs(int);
extern s32 get_cd_command_queue_depth(void);
extern void func_80047784(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, void *);
extern void create_actor_linked_effect(void *);

extern u8 D_80170F20[];
extern u8 D_801762C0[];


typedef struct S_80172798_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172798_0;   /* arg0 in advance_selected_item_action */

typedef struct S_80172798_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172798_1_pre;   /* the 0x14 bytes before active in advance_selected_item_action, addressed as active[-1] */

typedef struct S_80172798_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172798_2;   /* linked in advance_selected_item_action */


typedef struct S_80172798_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172798_5;   /* global in advance_selected_item_action */

/* Advances the selected item action and resets movement when it ends. */
void advance_selected_item_action(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 special;
    u8 *selection;
    void *active;
    u8 *scratch_pointer;

    special = 0;
    selection = (u8 *)(((S_80172798_0 *)action)->unk_9B);
    switch ((u8)selection) {
    case 0:
        if ((((u32)actor->flags1C)) & 0x2000) {
            switch (((actor->unk_46) & 0x3FFF)) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        } else {
            switch ((actor->unk_46) & 0x3FFF) {
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        }

        if (*selection != 0) {
            ((S_80172798_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 special_test;

                special_test = special;
                if (special_test != 0) {
                    active = D_800814A8;
                    (actor->target) = active;
                    scratch_pointer = ((S_80172798_1_pre *)active)[-1].unk_00;
                    (((u8)actor->unk_72)) = ((S_80172798_2 *)scratch_pointer)->unk_24;
                    (((u8)actor->unk_73)) = ((S_80172798_2 *)scratch_pointer)->unk_25;
                } else {
                    u8 item_id;

                    item_id = *selection;
                    if (D_8006DE24[item_id].kind == 2) {
                        active = (actor->target);
                        if (active != 0) {
                            scratch_pointer = ((S_80172798_1_pre *)active)[-1].unk_00;
                            (((u8)actor->unk_72)) = ((S_80172798_2 *)scratch_pointer)->unk_24;
                            (((u8)actor->unk_73)) = ((S_80172798_2 *)scratch_pointer)->unk_25;
                        }
                    } else {



                        (actor->target) = scan_monster_along_heading(
                            actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                            (actor->facing), 0x10);
                        actor->unk_72 = abs(actor->unk_72);
                        actor->unk_73 = abs(actor->unk_73);
                    }
                }
            }

            if (create_actor_spell_effect(actor, selection, special,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            ((S_80172798_0 *)action)->unk_9B++;
            return;
        }
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            g_dungeon_status.unk_0C = 0;
            (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
            advance_status_timers(actor);
            (((u8)actor->unk_6D))--;
            ((S_80172798_0 *)action)->unk_8C = D_80170F20;
            (((u8)actor->unk_73)) = 0;
            (((u8)actor->unk_72)) = 0;
            (actor->unk_46) &= 0x7FFF;
            return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172798_0 *)action)->unk_9B++;

    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 7 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172798_0 *)action)->unk_96 = 1;
            ((S_80172798_0 *)action)->unk_98 |= 0x80;
        }
        {
            s16 timer;

            timer = ((S_80172798_0 *)action)->unk_96 - 1;
            ((S_80172798_0 *)action)->unk_96 = timer;
            if (timer <= 0) {
                ((S_80172798_0 *)action)->unk_96 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801762C0) {
            u8 *anim_table;
            s32 direction;

            anim_table = D_801762C0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            direction = ((g_game_work.view.viewAngle + (actor->facing) + 0x100) >> 9) & 7;
            func_80047784(sprite, anim_table[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&g_dungeon_status.unk_00;
            if (((S_80172798_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_80172798_5 *)scratch_pointer)->unk_0A--;
            ((S_80172798_0 *)action)->unk_8C = D_80170F20;
            advance_status_timers(actor);
            (((u8)actor->unk_73)) = 0;
            (((u8)actor->unk_72)) = 0;
            (((u8)actor->unk_6D))--;
            (actor->unk_46) &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }

        return;
    default:
        return;
    }
}

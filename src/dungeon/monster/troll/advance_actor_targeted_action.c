#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_8017472C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_8017472C_0;   /* arg0 in advance_actor_targeted_action */

typedef struct S_8017472C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017472C_2_pre;   /* the 0x14 bytes before object in advance_actor_targeted_action, addressed as object[-1] */

typedef struct S_8017472C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017472C_3;   /* record in advance_actor_targeted_action */

typedef struct S_8017472C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017472C_4;   /* arg2 in advance_actor_targeted_action */


typedef struct S_8017472C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017472C_6;   /* control in advance_actor_targeted_action */


extern s32 get_cd_command_queue_depth();
extern int abs(int);
extern void select_sprite_entry();
extern void *scan_monster_along_heading();
extern void set_record_integer_tile_center();
extern void advance_status_timers();
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern void spawn_random_color_burst_particle();
extern void spawn_growing_rotating_flash();

extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];

/* Updates an actor's action state, target coordinates, animation, and completion. */
void advance_actor_targeted_action(void *action, EntityRec *transform, void *sprite, EntityRec *actor)
{
    s32 state;
    register s32 use_player_target;
    s32 kind;
    u8 *move;
    void *target;
    s32 target_x;
    s32 target_y;
    u16 ticks_left;
    s32 step;
    u8 *anim_table;
    void *current_anim;
    s32 delay_slot;
    u8 *control;

    state = ((S_8017472C_0 *)action)->unk_9B;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            kind = (actor->unk_46 & 0x3FFF) - 1;
            switch (kind) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                move = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                move = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                move = (u8 *)actor + 8;
                break;
            default:
                move = 0;
                break;
            }
        } else {
            kind = actor->unk_46 & 0x3FFF;
            switch (kind) {
            case 3:
                move = (u8 *)actor + 0xE;
                break;
            case 2:
                move = (u8 *)actor + 0xB;
                break;
            case 1:
                move = (u8 *)actor + 8;
                break;
            default:
                move = 0;
                break;
            }
        }
        if (*move != 0) {
            ((S_8017472C_0 *)action)->unk_98 &= 0xFF7F;
            if (use_player_target != 0) {
                target = D_800814A8;
                actor->target = target;
                state = ((S_8017472C_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_8017472C_3 *)state)->unk_24;
                actor->unk_73 = ((S_8017472C_3 *)state)->unk_25;
            } else if (D_8006DE24[*move].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    state = ((S_8017472C_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((S_8017472C_3 *)state)->unk_24;
                    actor->unk_73 = ((S_8017472C_3 *)state)->unk_25;
                }
            } else {
                target = scan_monster_along_heading(
                    actor,
                    ((S_8017472C_4 *)sprite)->unk_24,
                    ((S_8017472C_4 *)sprite)->unk_25,
                    actor->facing,
                    0x10);
                actor->target = target;
                actor->unk_72 =
                abs(actor->unk_72);
                actor->unk_73 =
                abs(actor->unk_73);

            }

            if (create_actor_spell_effect(actor, move, use_player_target,
                (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_8017472C_0 *)action)->unk_96.s = 0x16;
            ((S_8017472C_0 *)action)->unk_AE.s = 0xE;
            ((S_8017472C_0 *)action)->unk_9B++;
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_8017472C_0 *)action)->unk_8C = D_801724BC;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((S_8017472C_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_8017472C_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_8017472C_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        step = 0;
        if (!(((S_8017472C_0 *)action)->unk_96.s & 1) &&
            ((S_8017472C_0 *)action)->unk_AE.s != 0) {
            ((S_8017472C_0 *)action)->unk_AE.u--;
        }
        for (step = 0; step < 10; step++) {
            spawn_random_color_burst_particle(action, transform, sprite, actor);
        }

        if (((S_8017472C_0 *)action)->unk_96.u == 0x16) {
            spawn_growing_rotating_flash(action, transform, sprite);
        }
        ticks_left = ((S_8017472C_0 *)action)->unk_96.s - 1;
        ((S_8017472C_0 *)action)->unk_96.s = ticks_left;
        if ((s32)(ticks_left << 16) > 0 &&
            !(((S_8017472C_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_8017472C_0 *)action)->unk_98 |= 0x80;
        ((S_8017472C_0 *)action)->unk_9B++;
        return;

    case 3:
        if (D_8008346C == 0) {
            ((S_8017472C_0 *)action)->unk_96.s = 0;
        }
        if (!(((S_8017472C_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);

        kind = actor->unk_48;
        switch (kind) {
        case 0xD:
            current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
            anim_table = D_80175E24;
            if (current_anim != anim_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (u8 *)&D_80083460;
            break;
        case 0xE:
            current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
            anim_table = D_80175E2C;
            if (current_anim != anim_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (u8 *)&D_80083460;
            break;
        case 0xF:
            current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
            anim_table = D_80175E34;
            if (current_anim != anim_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (u8 *)&D_80083460;
            break;
        default:
            current_anim = (u8 *)&D_80083460;
            control = current_anim;
            break;
        }
        if (((S_8017472C_6 *)control)->unk_0C != 0) {
            return;
        }
        ((S_8017472C_6 *)control)->unk_0A--;
        ((S_8017472C_0 *)action)->unk_8C = D_801724BC;
        advance_status_timers(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        (*(u8 *)&actor->unk_6D)--;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    default:
        break;
    }
}

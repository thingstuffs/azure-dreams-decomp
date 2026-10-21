/* Relink of matched dungeon/func_80F89D7C; every changed retail word is a paired relocation. */
#define D_80174AD4 D_80156AD4
#define D_80174AFC D_80156AFC
#define D_80174B04 D_80156B04
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
extern void func_80153138(void *, void *, void *, void *);
extern void func_80155D38(void *, s32, void *, void *);

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    u16 unk_A0;
} S_8017357C_0;   /* arg0 in func_8015557C */


typedef struct S_8017357C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_3;   /* counter_base in func_8015557C */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern s32 func_8009FD40(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern u8 D_80156AFC[];
extern u8 D_80156B04[];

/* Updates actor state, animation, and transition counters. */
void func_8015557C(void *controller, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 actor_flags;
    s32 state;

    state = ((S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80156AFC;
        func_80047784(sprite,
            D_80156AFC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A = ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A
        - 1;
        ((S_8017357C_0 *)controller)->unk_9B++;
        return;
    case 1:
        if ((func_80042900(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80156B04;
            func_80047784(sprite,
                D_80156B04[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                ((S_8017357C_0 *)controller)->unk_8C = func_80153138;
            } else {
                ((S_8017357C_0 *)controller)->unk_96.s = 3;

                ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A =
                    ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A + 1;
                ((S_8017357C_0 *)controller)->unk_9B++;
            }
            return;
        }
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->unk_64 != 0) {
            if (func_800AA6B4(controller, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (actor->tileY == 0) {
            if (g_dungeon_status.flags & 0x2008) {
                return;
            }
            func_800AA79C(controller, motion, sprite, actor);
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            func_800AA258(controller, motion, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, motion, sprite, actor);
            ((S_8017357C_0 *)controller)->unk_A0 = 0;
            func_80155D38(controller, motion, sprite, actor);
            return;
        }
        if (actor->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            EntityRec *owner = primary_actor_record;

            if ((func_8009A180(actor,
                    (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_food(actor);
        func_800A9A04(actor);
        if ((func_80042900(actor, 1) << 16) != 0) {
            TileObject *origin = &reference_tile_object;
            s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

            if (((tile == origin->room_index) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, sprite) < 2)) {
                if (!(generate_random_value() & 7)) {
                    func_80042B68(actor, 1);
                }
            }
        }
        if ((func_80042900(actor, 1) << 16) != 0) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80156B04;
        func_80047784(sprite,
            D_80156B04[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor_flags = actor->flags1C | 0x40000;
        actor->flags1C = actor_flags;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            actor->flags1C = actor_flags & ~0x200;
            ((S_8017357C_0 *)controller)->unk_8C = func_80153138;
        } else {
            ((S_8017357C_0 *)controller)->unk_96.s = 3;

            ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A =
                ((S_8017357C_3 *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A + 1;
            ((S_8017357C_0 *)controller)->unk_9B++;
        }
        return;
    case 2:
        ((S_8017357C_0 *)controller)->unk_96.s--;
        if (((S_8017357C_0 *)controller)->unk_96.u <= 0) {
            motion->flags14 = 0xFFF00000;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        ((S_8017357C_0 *)controller)->unk_A0 = 0;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80156AD4;
        func_80047784(sprite,
            D_80156AD4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags1C &= ~0x200;
        ((S_8017357C_0 *)controller)->unk_8C = func_80153138;
    }
}


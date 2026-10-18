/* Relink of matched dungeon/func_80D8D7C8; every changed retail word is a paired relocation. */
#define D_800E23A8 D_8016DEC4
#define D_800E23B0 D_8016DECC
#define D_8014DF1C D_8016B514
/* Relink of matched dungeon/func_809782AC; every changed retail word is a paired relocation. */
#define D_801714D4 D_8016B514
#define D_80174158 D_8016DEC4
#define D_80174160 D_8016DECC
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_8016D6B8(void *, s32, void *, void *);

extern s32 D_8016B514;
extern u8 D_8016DEC4[];
extern u8 D_8016DECC[];

/* Advance actor states, select directional animations, and process entity actions. */
void func_8016D364(void *actor, void *context, void *animation, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.unk_0A--;
        direction_anims = D_8016DEC4;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047784(animation,
            direction_anims[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = D_8016DECC;
            func_80047784(animation,
                D_8016DECC[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.unk_0A++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            func_8016D6B8(actor, context, animation, entity);
            return;
        }

        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        func_800A9A04(entity);
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = D_8016DECC;
        func_80047784(animation,
            D_8016DECC[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.unk_0A++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            g_dungeon_status.unk_0A--;
            entity->flags1C &= ~8;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = &D_8016B514;
        }

        return;
    }
}

#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017360C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_8017360C_0;   /* arg0 in func_8017360C */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30();
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173E00(void *, void *, void *, void *);

extern u8 D_801714D4[];
extern u8 D_801740F0[];
extern u8 D_801740F8[];
extern u8 D_80174150[];
extern u8 D_80174158[];
extern u8 D_80174160[];


/* Advances the actor state sequence and selects effects for its facing direction. */
void func_8017360C(void *action, void *context, void *entity, EntityRec *actor)
{
    s32 effect_entry;
    s32 next_state;
    u8 state;

    state = ((S_8017360C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *local_table_0;
    {
        DungeonGlobalStatus *dungeon_state;
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        local_table_0 = D_801740F8;
        
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_0;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_0;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        dungeon_state = &dungeonStatus;
        (*(u16 *)&dungeon_state->unk_0A)--;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        goto store_state;
    }

    }

    case 1:
    {
        u8 *local_table_1;
        if (((S_8017360C_0 *)action)->unk_92.s != 0) {
            return;
        }
        local_table_1 = D_80174150;
        
                (*(void * *)((u8 *)entity + 0x2C)) = local_table_1;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_1;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        goto store_state;

    }

    case 2:
    {
        u8 *local_table_2;
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 2) {
            return;
        }
        local_table_2 = D_80174158;
        
                (*(void * *)((u8 *)entity + 0x2C)) = local_table_2;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_2;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        goto store_state;

    }

    case 3:
    {
        u8 *local_table_3;
        if ((func_80042900(actor, 1) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &dungeonStatus;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                func_800AA6B4(action, context, entity, 0)) {
                return;
            }

            if (actor->tileY == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                func_800AA79C(action, context, entity, actor);
                return;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                func_800AA258(action, context, entity, actor);
                return;
            }

            {
            u32 adjustment_flag = 0x80000;
            if ((actor_flags & adjustment_flag) != 0) {
                u16 remaining_amount;

                func_800AA888(action, context, entity, actor);
                remaining_amount = ((S_8017360C_0 *)action)->unk_92.u;
                remaining_amount -= ((S_8017360C_0 *)action)->unk_A2;
                ((S_8017360C_0 *)action)->unk_A2 = 0;
                ((S_8017360C_0 *)action)->unk_9E = 0;
                ((S_8017360C_0 *)action)->unk_92.u = remaining_amount;
                func_80173E00(action, context, entity, actor);
                return;
            }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                EntityRec *owner = D_800814A8;

                if ((s16)func_8009A180(actor,
                        (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *room_base = &D_80082E80;
                s8 room_id = ((Rec_D_80082E80 *)entity)->unk_26.as_s8;

                if ((room_id != room_base->unk_026) || (room_id < 0)) {
                    if ((s16)func_8009FD40(room_base, entity) >= 2) {
                        goto final_check;
                    }
                }

                if ((func_800A6D30() & 7) != 0) {
                    goto final_check;
                }
                func_80042B68(actor, 1);
            }
final_check:
            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
        }

        local_table_3 = D_80174160;
        
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_3;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_3;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000) != 0) {
            goto finished;
        }
        ((S_8017360C_0 *)action)->unk_9B++;
        {
            DungeonGlobalStatus *dungeon_state = &dungeonStatus;
            (*(u16 *)&dungeon_state->unk_0A)++;
        }
        return;

    }

    case 4:
        {
        u8 *local_table_4;
        u32 phase_flag = 0x40000;
        u32 phase_flags;

        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        local_table_4 = D_801740F8;
        phase_flags = ((u32)actor->flags1C);
        
        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
effect_common:
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_4;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_4;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
store_state:
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        return;
        }

    case 5:
    {
        u8 *local_table_5;
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 4) {
            return;
        }

        local_table_5 = D_801740F0;
        
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_5;
        effect_entry = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_5;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        {
            DungeonGlobalStatus *dungeon_state = &dungeonStatus;
            (*(u16 *)&dungeon_state->unk_0A)--;
        }
        break;

    }
    default:
        return;
    }

finished:
        ((S_8017360C_0 *)action)->unk_8C = D_801714D4;
        return;
}

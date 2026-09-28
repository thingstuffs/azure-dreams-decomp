#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8016B0EC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_8016B0EC_0;   /* arg0 in func_8016B0EC */


typedef struct S_8016B0EC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_8016B0EC_2;   /* arg2 in func_8016B0EC */





extern s32 func_80042900(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_8016B69C(void *, void *, void *, void *);
extern void func_8016B854(void *, void *, void *, void *);
extern s32 func_8016BF9C(void *, void *, void *, void *);
extern void func_8016C234(void *, void *, void *, void *);
extern void func_8016C358(void *, void *, void *, void *);
extern s32 func_8016C66C(void *, void *, void *, s32);
extern void func_8016E574(void *, void *, void *, void *);

extern u8 D_8016FE40[];
extern u8 D_8016FE48[];
extern u8 D_8016FE98[];
extern u8 D_8016FEA0[];
extern u8 D_8016FEB0[];
extern u8 D_8016FEB8[];

/* Updates creature behavior, animation, and facing according to its current state. */
void func_8016B0EC(void *actor, void *context, void *sprite, void *creature)
{
    s32 distance;
    s8 room_id;
    u16 action_flags;

    if (dungeonStatus.flags & 0x1000) {
        ((S_8016B0EC_0 *)actor)->unk_9A = 0xE;
        func_8016B69C(actor, context, sprite, creature);
        return;
    }

    if (((EntityRec *)creature)->tileY == 0) {
        u8 *anim_table;

        func_800AA79C(actor, context, sprite, creature);
        if (((S_8016B0EC_2 *)sprite)->unk_2C == D_8016FEA0) {
            return;
        }
        anim_table = D_8016FEB0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((gameWork.view.viewAngle + ((EntityRec *)creature)->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)((EntityRec *)creature)->flags1C) & 0x200) {
        if (((S_8016B0EC_2 *)sprite)->unk_2C == D_8016FEA0) {
            ((S_8016B0EC_0 *)actor)->unk_9A = 0xD;
            ((S_8016B0EC_0 *)actor)->unk_9B = 1;
            ((S_8016B0EC_0 *)actor)->unk_8C = 0;
            ((EntityRec *)creature)->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_8016FEB0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)((EntityRec *)creature)->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, creature);
            return;
        }

        {
            void *current_anims;
            u8 *anim_table;

            if (((S_8016B0EC_0 *)actor)->unk_9A != 0xE) {
                ((S_8016B0EC_0 *)actor)->unk_9A = 0xE;
                ((S_8016B0EC_0 *)actor)->unk_B2 = 0;
            }

            current_anims = ((S_8016B0EC_2 *)sprite)->unk_2C;
            if (current_anims == D_8016FEB8) {
                if (((S_8016B0EC_2 *)sprite)->unk_14 & 0xE000) {
                    u8 *reset_anims = D_8016FE40;

                    (*(void * *)((u8 *)sprite + 0x2C)) = reset_anims;
                    func_80047784(sprite,
                        reset_anims[((gameWork.view.viewAngle + ((EntityRec *)creature)->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_8016B0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8016B0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8016B0EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_8016FE40;
                if (current_anims != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((gameWork.view.viewAngle + ((EntityRec *)creature)->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_8016B0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8016B0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8016B0EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        ((EntityRec *)creature)->flags1C |= 0x40000;
        ((S_8016B0EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (((EntityRec *)creature)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_8016FE48) != 0) {
                return;
            }
        }

        if (((u32)((EntityRec *)creature)->flags1C) & 0x80000) {
            s16 base_offset;

            func_800AA888(actor, context, sprite, creature);
            base_offset = ((S_8016B0EC_0 *)actor)->unk_92.u - ((S_8016B0EC_0 *)actor)->unk_A2.u;
            ((S_8016B0EC_0 *)actor)->unk_A2.s = 0;
            ((S_8016B0EC_0 *)actor)->unk_9E = 0;
            ((S_8016B0EC_0 *)actor)->unk_92.s = base_offset;
            func_8016E574(actor, context, sprite, creature);
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            func_800AAB10(actor, context, sprite, creature);
        }
    }

    room_id = func_8009FB34(((S_8016B0EC_2 *)sprite)->unk_24.at00.v, ((S_8016B0EC_2 *)sprite)->unk_24.at01.v);
    ((S_8016B0EC_2 *)sprite)->unk_26 = room_id;

    if (((EntityRec *)creature)->unk_6D > 0) {
        if (((u32)((EntityRec *)creature)->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_8016B0EC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto generic;
        }
        if (!(((EntityRec *)creature)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016C66C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = ((EntityRec *)creature)->unk_46 | 0x4000;
            ((EntityRec *)creature)->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const action_labels[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            extern void *const D_8016A808[];
            u32 action_index = (u32)((((EntityRec *)creature)->unk_46 & 0x3FFF) - 1);

            if (action_index >= 12) {
                goto generic;
            }
            (void)action_labels;
            goto *D_8016A808[action_index];
        }
sw_case89:
            if ((func_8016BF9C(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_8016C234(actor, context, sprite, creature);
            return;

sw_case567:
        {
            EntityRec *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_8016B0EC_2 *)sprite)->unk_24.at00.v, ((S_8016B0EC_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &distance);
            player = D_800814A8;
            ((EntityRec *)creature)->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                goto case_123;
            }
        }
            /* fallthrough */

case_12:
            func_800A9A0C(creature);
            return;

case_123:
            func_800AAF00(actor, context, sprite, D_8016FE98, func_8016B0EC);
            return;

generic:
            func_8016B854(actor, context, sprite, creature);
            return;
    }

    if (!(((u32)((EntityRec *)creature)->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)((EntityRec *)creature)->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_8016B0EC_2 *)sprite)->unk_24.at00.v, ((S_8016B0EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    ((EntityRec *)creature)->facing = func_800A0818(
                        ((S_8016B0EC_2 *)sprite)->unk_24.at00.v, ((S_8016B0EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                    return;
                }
            }
        }
    } else if ((func_80042900(creature, 4) << 16) == 0) {
        if (D_800814A8->unk_9A == 0x17) {
            func_8016C358(actor, context, sprite, creature);
        }
    }
}

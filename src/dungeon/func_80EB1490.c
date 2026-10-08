#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
extern int abs(int);

typedef struct S_80172C90_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
} S_80172C90_1;   /* arg0 in func_8014EC90 */

typedef struct S_80172C90_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172C90_3_pre;   /* the 0x14 bytes before localOwner in func_8014EC90, addressed as localOwner[-1] */

typedef struct S_80172C90_3 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172C90_3;   /* localOwner in func_8014EC90 */

typedef struct S_80172C90_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172C90_4;   /* localLinked in func_8014EC90 */


extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800A56E0(s32);
extern void func_800DB2DC(void *, void *, void *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);

extern u8 D_8014D0F4[];
extern u8 D_80150EF8[];
extern u8 D_80150F00[];

/* Updates the actor action sequence, including movement, landing, and recovery. */
void func_8014EC90(void *action, EntityRec *motion, Rec_D_80082E80 *sprite, EntityRec *actor)
{
    u32 dir_offset;
    u16 angle;
    u32 action_index;
    s16 *dir_x_table;
    s32 dir_x;
    s32 dir_y;
    u16 timer;
    u32 state;
    u8 *selector;
    s32 special;
    s32 tail_state; /* MATCH: the shared state store receives its value in v0. */
    u16 position[3];

    dir_x_table = dirStepX;
    angle = ((u16)actor->facing);
    dir_offset = angle >> 8;
    dir_offset &= 0xE;
    dir_x = *(s16 *)((u8 *)dir_x_table + dir_offset);
    dir_offset += (u32)dirStepY;
    dir_y = *(s16 *)dir_offset;
    timer = ((S_80172C90_1 *)action)->unk_96.s;
    state = ((S_80172C90_1 *)action)->unk_9B;
    ((S_80172C90_1 *)action)->unk_96.s = timer - 1;
    special = 0;
    switch (state) {

    case 0:
        ((S_80172C90_1 *)action)->unk_AC.s = ((u16)motion->z.w.i);
        if (((u32)actor->flags1C) & 0x2000) {
            u16 action_kind;

            action_kind = actor->unk_46 & 0x3FFF;
            action_index = action_kind - 1;
            switch (action_index) {
            case 6:
                special = 1;
            case 2:
                selector = (u8 *)actor + 0xE;
                break;
            case 5:
                special = 1;
            case 1:
                selector = (u8 *)actor + 0xB;
                break;
            case 4:
                special = 1;
            case 0:
                selector = (u8 *)actor + 8;
                break;
            case 3:
            default:
                selector = 0;
            }
        } else {
            u16 action_kind;

            action_kind = actor->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                selector = (u8 *)actor + 0xE;
                break;
            case 2:
                selector = (u8 *)actor + 0xB;
                break;
            case 1:
                selector = (u8 *)actor + 8;
                break;
            default:
                selector = 0;
            }
        }

        if (*selector != 0) {
            void *owner;
            u16 use_owner;
            s32 move_result;

            ((S_80172C90_1 *)action)->unk_98 &= 0xFF7F;
            use_owner = special;
            if (use_owner) {
                owner = D_800814A8;
                actor->target = owner;
                move_result = ((S_80172C90_3_pre *)owner)[-1].unk_00;
                actor->unk_72 = ((S_80172C90_4 *)move_result)->unk_24;
                actor->unk_73 = ((S_80172C90_4 *)move_result)->unk_25;
            } else {
                dir_offset = *selector;
                if (D_8006DE24[dir_offset].kind == 2) {
                    owner = actor->target;
                    if (owner != 0) {
                        move_result = ((S_80172C90_3_pre *)owner)[-1].unk_00;
                        actor->unk_72 = ((S_80172C90_4 *)move_result)->unk_24;
                        actor->unk_73 = ((S_80172C90_4 *)move_result)->unk_25;
                    }
                } else {
                    actor->target = func_800A05A4(actor,
                        sprite->unk_24,
                        sprite->unk_25,
                        actor->facing, 16);
                    actor->unk_72 = abs(actor->unk_72);
                    actor->unk_73 = abs(actor->unk_73);
                }
            }

            {
                void *move_actor;

                move_actor = actor;
                position[0] = ((u16)motion->x.w.i);
                position[1] = ((u16)motion->y.w.i);
                position[2] = ((u16)motion->z.w.i);
                move_result = func_800A94A0(move_actor, selector, special,
                                            (u8 *)action + 0x98);
            }
            if (!move_result) {
                return;
            }
            sprite->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DB2DC(motion, sprite, actor, 10);
            ((S_80172C90_1 *)action)->unk_90 = 0;
            ((S_80172C90_1 *)action)->unk_96.s = 2;
            ((S_80172C90_1 *)action)->unk_98 |= 8;
            {
                s32 back_x;
                s32 back_y;

                back_x = -dir_x;
                back_y = -dir_y;
                motion->unk_0C =
                    (back_x << 18) + (back_x << 19);
                motion->unk_10 =
                    (back_y << 18) + (back_y << 19);
            }
            motion->flags14 = (s32)0xFFF30000;
            {
                tail_state = ((S_80172C90_1 *)action)->unk_9B;
                tail_state++;
                ((S_80172C90_1 *)action)->unk_9B = tail_state;
                return;
            }
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        {
            void *owner;

            owner = D_800814A8;
            dungeonStatus.unk_0C = 0;
            ((S_80172C90_3 *)owner)->unk_A6--;
        }
        func_800A4ACC(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_80172C90_1 *)action)->unk_8C = D_8014D0F4;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (sprite->unk_14.at00_u16.v & 0x8000) {
            ((S_80172C90_1 *)action)->unk_9B = 16;
            ((S_80172C90_1 *)action)->unk_98 |= 0x80;
            return;
        }
        if (((S_80172C90_1 *)action)->unk_96.u <= 0) {
            motion->unk_0C = 0;
            motion->unk_10 = 0;
            motion->flags14 = 0;
            motion->unk_0C = dir_x << 18;
            motion->unk_10 = dir_y << 18;
            motion->flags14 = (s32)0xFFF30000;
            {
                ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
                return;
            }
        }
        motion->unk_0C *= 2;
        motion->unk_10 *= 2;
        return;

    case 2:
        if (func_8003F270()) {
            sprite->unk_14.at00_u16.v |= 0x0800;
            return;
        }
        sprite->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172C90_1 *)action)->unk_9B++;

    case 3:
        motion->flags14 += 0x30000;
        if (!((sprite->unk_04.as_s8 == 4 && (sprite->unk_14.at00_u16.v & 0x1000)) ||
              (sprite->unk_14.at00_u16.v & 0xE000))) {
            return;
        }
        {
            motion->unk_0C = dir_x << 19;
            motion->unk_10 = dir_y << 19;
            ((S_80172C90_1 *)action)->unk_98 |= 0x80;
            ((S_80172C90_1 *)action)->unk_9B++;
            return;
        }

    case 4:
        motion->flags14 += 0x20000;
        if (!((((u32)actor->flags1C) & 0x08000000) && (motion->z.w.i <= ((S_80172C90_1 *)action)->unk_AC.u))) {
            if (motion->z.w.i <= ((S_80172C90_1 *)action)->unk_AC.u) {
                return;
            }
        }
        {
            u8 *effect;

            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            ((S_80172C90_1 *)action)->unk_96.s = 4;
            sprite->unk_1C.at00_u16.v = 0x1400;
            sprite->unk_1C.at02_u16.v = 0x0C00;
            effect = D_80150F00;
            sprite->unk_2C.as_pu8 = effect;
            func_80047784(sprite,
                effect[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172C90_1 *)action)->unk_98 &= 0xFFF7;
            ((S_80172C90_1 *)action)->unk_9B++;
            return;
        }

    case 5:
    {
        s32 ticks;
        s32 ticks_squared;

        ticks = ((S_80172C90_1 *)action)->unk_96.u;
        ticks_squared = ticks * ticks;
        ticks = 0x1000 + ticks_squared * 300;
        sprite->unk_1C.at00_u16.v = ticks;
        sprite->unk_1C.at02_u16.v = 0x1000 - ticks_squared * 200;
    }
        if (((S_80172C90_1 *)action)->unk_96.u > 0) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_80150EF8;
        func_80047784(sprite,
            D_80150EF8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172C90_1 *)action)->unk_96.s = 10;
        ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
        return;

    case 6:
    {
        s32 current_coord;
        {
            s32 tile_coord;

            tile_coord = sprite->unk_24;
            current_coord = motion->x.w.i;
            tile_coord = tile_coord << 6;
            current_coord -= 0x20;
            motion->unk_0C =
                (tile_coord - current_coord) << 14;
        }
        {
            s32 tile_coord;
            s32 target_coord;

            tile_coord = sprite->unk_25;
            current_coord = motion->y.w.i;
            tile_coord <<= 6;
            target_coord = tile_coord;
            current_coord -= 0x20;
            motion->unk_10 =
                (target_coord - current_coord) << 14;
        }
    }
        if (((S_80172C90_1 *)action)->unk_96.u > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        sprite->unk_14.at00_u16.v |= 0x6000;
        ((S_80172C90_1 *)action)->unk_9B = 16;
        return;

    case 16:
    {

        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        if (sprite->unk_2C.as_pu8 != D_80150F00) {
            sprite->unk_2C.as_pu8 = D_80150F00;
            func_80047784(sprite,
                D_80150F00[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
        sprite->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172C90_1 *)action)->unk_8C = D_8014D0F4;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }
    default:
        return;
    }
}

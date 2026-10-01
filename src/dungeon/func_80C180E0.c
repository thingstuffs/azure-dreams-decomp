#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_801738E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_801738E0_0;   /* arg0 in func_801738E0 */

typedef struct S_801738E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801738E0_1;   /* arg2 in func_801738E0 */

typedef struct S_801738E0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801738E0_2;   /* arg3 in func_801738E0 */

typedef struct S_801738E0_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_801738E0_3;   /* arg1 in func_801738E0 */


struct GlobalStruct {
    u16 unk0;
    u16 flags;
    u8 unk4[6];
    u16 counter;
};

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174250(void *, void *, void *, void *);

extern u8 D_801713A8[];
extern u8 D_8017449C[];
extern u8 D_801744EC[];
extern u8 D_801744F4[];
extern u8 D_801744FC[];

/* Updates actor states, directional animations, and activity flags. */
void func_801738E0(void *actor_arg, void *motion_arg, void *sprite_arg, void *entity_arg)
{
    void *actor = actor_arg;
    void *motion = motion_arg;
    void *sprite = sprite_arg;
    void *entity = entity_arg;
    DungeonGlobalStatus *global_state;
    u8 *anim_table;
    u32 clear_mask;
    u32 entity_flags;
    u8 state;

    state = ((S_801738E0_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (((S_801738E0_1 *)sprite)->unk_14 & 0x8000) {
            ((S_801738E0_0 *)actor)->unk_90 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_801744FC;
            func_80047784(
                sprite,
                D_801744FC[
                    ((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
                0);
            dungeonStatus.unk_0A--;
            ((S_801738E0_0 *)actor)->unk_9B = 2;
            return;
        }
        ((S_801738E0_0 *)actor)->unk_98 |= 8;
        ((S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((S_801738E0_2 *)entity)->unk_1C &= 0xFFFBFFFF;
        if (!(((S_801738E0_1 *)sprite)->unk_14 & 0x6000)) {
            return;
        }
        {
            s32 initial_speed = 0xFFF80000;
            anim_table = D_801744F4;
            ((S_801738E0_3 *)motion)->unk_14 = initial_speed;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(
            sprite,
            *(u8 *)((((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7)
                    + (u32)anim_table),
            0);
        ((S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 1:
        if (((S_801738E0_3 *)motion)->unk_14 <= 0xFFFFF) {
            ((S_801738E0_3 *)motion)->unk_14 += 0x20000;
        }
        if (((S_801738E0_0 *)actor)->unk_90 < 0) {
            return;
        }
        ((S_801738E0_0 *)actor)->unk_90 = 0;
        ((S_801738E0_3 *)motion)->unk_14 = 0;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_801744FC;
        func_80047784(
            sprite,
            D_801744FC[
                ((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800A9A0C(entity);

        {
            struct GlobalStruct *globals = ((struct GlobalStruct *)&dungeonStatus);
            globals->counter--;
        }
        ((S_801738E0_0 *)actor)->unk_9B = 2;
        return;

    case 2:
        ((S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        if ((func_80042900(entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_801744F4;
            func_80047784(
                sprite,
                D_801744F4[
                    ((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
                0);
            entity_flags = ((S_801738E0_2 *)entity)->unk_1C | 0x40000;
            ((S_801738E0_2 *)entity)->unk_1C = entity_flags;
            if (((S_801738E0_1 *)sprite)->unk_14 & 0x8000) {
                clear_mask = ~0x200U;
                goto clear_200;
            }
            {
                register struct GlobalStruct *globals;
                globals = ((struct GlobalStruct *)&dungeonStatus);
                entity_flags = globals->counter + 1;
                globals->counter = entity_flags;
            }
            ((S_801738E0_0 *)actor)->unk_9B++;
            return;
        } else {
            global_state = &dungeonStatus;
        }

        if (global_state->flags & 0x1000) {
            return;
        }
        if (((S_801738E0_2 *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (((S_801738E0_2 *)entity)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                return;
            }
            func_800AA79C(actor, motion, sprite, entity);
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }
        entity_flags = ((S_801738E0_2 *)entity)->unk_1C;
        if (entity_flags & 0x100) {
            func_800AA258(actor, motion, sprite, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            func_800AA888(actor, motion, sprite, entity);
            ((S_801738E0_0 *)actor)->unk_A8 = 0;
            func_80174250(actor, motion, sprite, entity);
            return;
        }
        if (((S_801738E0_2 *)entity)->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(
                     entity, (u8 *)D_800814A8->unk_58 + 0x20)
                 << 16) != 0) {
                return;
            }
        }
        func_800A9A0C(entity);
        func_800A9A04(entity);
        if ((func_80042900(entity, 1) << 16) != 0) {
            TileObject *origin = &D_80082E80;
            s8 coordinate = ((S_801738E0_1 *)sprite)->unk_26;

            if ((((coordinate == origin->unk_026) && (coordinate >= 0)) ||
                 (func_8009FD40(origin, sprite) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(entity, 1);
            }
        }
        if ((func_80042900(entity, 1) << 16) != 0) {
            goto done;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_801744F4;
        func_80047784(
            sprite,
            D_801744F4[
                ((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        entity_flags = ((S_801738E0_2 *)entity)->unk_1C | 0x40000;
        ((S_801738E0_2 *)entity)->unk_1C = entity_flags;
        if (((S_801738E0_1 *)sprite)->unk_14 & 0x8000) {
            clear_mask = ~0x200U;
            goto clear_200;
        }
        {
            struct GlobalStruct *globals = ((struct GlobalStruct *)&dungeonStatus);
            globals->counter++;
        }
        ((S_801738E0_0 *)actor)->unk_9B++;
        goto done;

    case 3:
        if (!(((S_801738E0_1 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        } else {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_801744EC;
        }

        func_80047784(
            sprite,
            D_801744EC[((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);

advance_state:
        ((S_801738E0_0 *)actor)->unk_9B++;
        goto done;

    case 4:
        if (!(((S_801738E0_1 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        }
        ((S_801738E0_3 *)motion)->unk_14 = 0xFFF80000;
        ((S_801738E0_0 *)actor)->unk_A8 = 8;
        ((S_801738E0_0 *)actor)->unk_98 &= 0xBFFF;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_8017449C;
        func_80047784(
            sprite,
            D_8017449C[
                ((gameWork.view.viewAngle + ((S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801738E0_0 *)actor)->unk_98 |= 8;
        ((S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((S_801738E0_0 *)actor)->unk_9B = 0x10;
        goto done;

    case 16:
        if (!(((S_801738E0_1 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        }
        ((S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        ((S_801738E0_0 *)actor)->unk_98 |= 0x4000;
        ((S_801738E0_3 *)motion)->unk_14 = 0;
        {
            struct GlobalStruct *globals = ((struct GlobalStruct *)&dungeonStatus);
            globals->counter--;
        }
        ((S_801738E0_2 *)entity)->unk_1C &= ~0x200;
        ((S_801738E0_0 *)actor)->unk_8C = D_801713A8;
        goto done;
    default:
        goto done;
    }

clear_200:
    ((S_801738E0_2 *)entity)->unk_1C = clear_mask & entity_flags;
    ((S_801738E0_0 *)actor)->unk_8C = D_801713A8;

done:
    return;
}

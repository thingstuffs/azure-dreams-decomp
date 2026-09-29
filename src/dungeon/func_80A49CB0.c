#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801734B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801734B0_0;   /* arg0 in func_801734B0 */

typedef struct S_801734B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801734B0_1;   /* arg2 in func_801734B0 */

typedef struct S_801734B0_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801734B0_2;   /* arg3 in func_801734B0 */

typedef struct S_801734B0_5 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
    u16 unk_B8;
} S_801734B0_5;   /* copy_arg0 in func_801734B0 */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173C34(void *, void *, void *, void *);

extern u8 D_8017140C[];
extern u8 D_80175894[];
extern u8 D_80175894[];

/* Updates actor state, animation, and callbacks according to entity and dungeon flags. */
void func_801734B0(void *in_actor, void *in_context, void *in_sprite, void *in_entity)
{
    void *context = in_context;
    s32 entity_flags;
    u16 stat_value;
    u16 stat_delta;
    u8 *page_base;
    s32 state;

    state = ((S_801734B0_0 *)in_actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
        func_80047784(in_sprite,
            D_80175894[((gameWork.view.viewAngle + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801734B0_0 *)in_actor)->unk_96 = 0;
        {
            u16 counter_value;

            counter_value = ((u16)dungeonStatus.unk_0A);
            counter_value--;
            dungeonStatus.unk_0A = counter_value;
        }
        ((S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(in_entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
            func_80047784(in_sprite,
                D_80175894[((gameWork.view.viewAngle + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801734B0_2 *)in_entity)->unk_1C.s |= 0x40000;
            if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0x8000)) {

                state = ((u16)dungeonStatus.unk_0A);
                state++;
                dungeonStatus.unk_0A = state;
                ((S_801734B0_0 *)in_actor)->unk_9B++;
                return;
            }
            ((S_801734B0_2 *)in_entity)->unk_1C.s &= ~0x200;
            ((S_801734B0_0 *)in_actor)->unk_8C = D_8017140C;
            return;
        }
        page_base = (u8 *)0x80080000;

        {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if (((S_801734B0_2 *)in_entity)->unk_64 != 0) {
                if (func_800AA6B4(in_actor, context, in_sprite, 0) != 0) {
                    return;
                }
            }
            if (((S_801734B0_2 *)in_entity)->unk_25 == 0) {
                if (dungeonStatus.flags & 0x2008) {
                    return;
                }
                func_800AA79C(in_actor, context, in_sprite, in_entity);
                return;
            }
            if ((func_800A2C34(in_entity) << 16) != 0) {
                return;
            }
            entity_flags = ((S_801734B0_2 *)in_entity)->unk_1C.u;
            if (entity_flags & 0x100) {
                func_800AA258(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (entity_flags & 0x80000) {

                func_800AA888(in_actor, context, in_sprite, in_entity);
                stat_value = ((S_801734B0_5 *)in_actor)->unk_92;
                stat_delta = ((S_801734B0_5 *)in_actor)->unk_B6;
                ((S_801734B0_5 *)in_actor)->unk_B6 = 0;
                ((S_801734B0_5 *)in_actor)->unk_B8 = 0;
                ((S_801734B0_5 *)in_actor)->unk_92 = stat_value - stat_delta;
                func_80173C34(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (((S_801734B0_2 *)in_entity)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(in_entity) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((func_8009A180(in_entity,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(in_entity);
            func_800A9A04(in_entity);
            if ((func_80042900(in_entity, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((S_801734B0_1 *)in_sprite)->unk_26;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)func_8009FD40(origin, in_sprite) < 2)) {
                    if (!(func_800A6D30() & 7)) {
                        func_80042B68(in_entity, 1);
                    }
                }
            }
            if ((func_80042900(in_entity, 1) << 16) != 0) {
                return;
            }
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
        func_80047784(in_sprite,
            D_80175894[((gameWork.view.viewAngle + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            u32 updated_flags;

            updated_flags = ((S_801734B0_2 *)in_entity)->unk_1C.s;
            updated_flags |= 0x40000;
            ((S_801734B0_2 *)in_entity)->unk_1C.s = updated_flags;
        }
        if (((S_801734B0_1 *)in_sprite)->unk_14 & 0x8000) {
            ((S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;
            ((S_801734B0_0 *)in_actor)->unk_8C = D_8017140C;
            return;
        }

        {

            state = ((u16)dungeonStatus.unk_0A);
            state++;
            dungeonStatus.unk_0A = state;
        }

        ((S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 2:
        if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            dungeonStatus.unk_0A--;
        }

        ((S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;

        ((S_801734B0_0 *)in_actor)->unk_8C = D_8017140C;

        return;
    }
}

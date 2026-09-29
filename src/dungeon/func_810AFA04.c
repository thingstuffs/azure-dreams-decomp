#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_80173204_arg0.h"


typedef struct S_80173204_1 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80173204_1;   /* arg2 in func_80173204 */



typedef struct S_80173204_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_7;   /* counter in func_80173204 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA79C(void *, s32, void *, void *);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_80173A20(void *, s32, void *, void *);

extern u8 D_80170E54;
extern u8 D_80173C9C[];
extern u8 D_80173CA4[];

/* Updates entity state, directional animation, and color fading. */
void func_80173204(Rec_func_80173204_arg0 *controller, s32 update_mode, S_80173204_1 *sprite, EntityRec *entity)
{
    s32 state;
    s32 flags;
    s8 floor;
    DungeonGlobalStatus *counter_base;
    TileObject *floor_base;

    if (controller->unk_9B < 2U) {
        if (sprite->unk_0C.u8 < 0x33U) {
            goto dispatch;
        }
        sprite->unk_0C.s32 += -0x30303;
    } else if (sprite->unk_0C.u8 < 0x80U) {
        sprite->unk_0C.s32 += 0x30303;
    }

dispatch:
    state = controller->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    entity->flags1C |= 0x10000000;
    if (!(sprite->unk_14 & 0xE000)) {
        return;
    }
    sprite->unk_2C = D_80173C9C;
    func_80047784(
        sprite,
        D_80173C9C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
    counter_base = &dungeonStatus;
    counter_base->unk_0A =
        ((u16)counter_base->unk_0A) - 1;
    controller->unk_9B++;
    return;

state_1:
    if ((func_80042900(entity, 1) << 16) == 0) {
        sprite->unk_2C = D_80173CA4;
        func_80047784(
            sprite,
            D_80173CA4[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        if (sprite->unk_14 & 0x8000) {
            entity->flags1C &= ~0x200;
            entity->flags1C &= 0xEFFFFFFF;
            sprite->unk_0C.s32 = 0x808080;
            controller->unk_8C.as_pu8 = &D_80170E54;
            return;
        }
        dungeonStatus.unk_0A++;
        controller->unk_9B++;
        return;
    }

    if (dungeonStatus.flags & 0x1000) {
        return;
    }
    if (entity->unk_64 != 0) {
        if (func_800AA6B4(controller, update_mode, sprite, 0) != 0) {
            return;
        }
    }
    if (entity->tileY == 0) {
        if (dungeonStatus.flags & 0x2008) {
            return;
        }
        func_800AA79C(controller, update_mode, sprite, entity);
        return;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        return;
    }

    flags = entity->flags1C;
    if (flags & 0x100) {
        func_800AA258(controller, update_mode, sprite, entity);
        return;
    }
    if (flags & 0x80000) {
        func_800AA888(controller, update_mode, sprite, entity);
        func_80173A20(controller, update_mode, sprite, entity);
        return;
    }
    if (entity->unk_6D == 0) {
        return;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        if ((func_8009A180(
                 entity,
                 ((s32)D_800814A8->unk_58) + 0x20) << 16) != 0) {
            return;
        }
    }
    func_800A9A0C(entity);
    func_800A9A04(entity);
    if ((func_80042900(entity, 1) << 16) != 0) {
        floor_base = &D_80082E80;
        floor = sprite->unk_26;
        if (!((floor == floor_base->unk_026) && (floor >= 0))) {
            if (func_8009FD40(floor_base, sprite) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(entity, 1);
        }
    }

second_check:
    if ((func_80042900(entity, 1) << 16) != 0) {
        return;
    }
    sprite->unk_2C = D_80173CA4;
    func_80047784(
        sprite,
        D_80173CA4[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
    if (sprite->unk_14 & 0x8000) {
        entity->flags1C &= ~0x200;
        entity->flags1C &= 0xEFFFFFFF;
        sprite->unk_0C.s32 = 0x808080;
        controller->unk_8C.as_pu8 = &D_80170E54;
        return;
    }
    {
        u8 *counter;

        counter = ((u8 *)(&dungeonStatus));
        ((S_80173204_7 *)counter)->unk_0A++;
    }

increment_state:
    controller->unk_9B++;
    return;

state_2:
    if (!(sprite->unk_14 & 0x8000)) {
        if (sprite->unk_0C.u8 < 0x80U) {
            return;
        }
    }
    {
        u8 *counter = ((u8 *)(&dungeonStatus));
        ((S_80173204_7 *)counter)->unk_0A--;
    }
    entity->flags1C &= 0xEFFFFFFF;
    sprite->unk_0C.s32 = 0x808080;
    entity->flags1C &= ~0x200;
    controller->unk_8C.as_pu8 = &D_80170E54;

    return;
}

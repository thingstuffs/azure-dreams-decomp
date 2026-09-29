#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173D38(void *, void *, void *, void *);

extern u8 D_80171138[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];


typedef struct S_801739F8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_801739F8_0;   /* arg0 in func_801739F8 */


typedef struct S_801739F8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801739F8_4;   /* global in func_801739F8 */

/* Advances entity animation states and updates the shared activity count. */
void func_801739F8(void *controller, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define controller controller
#define context saved_context
#define sprite sprite

    state = ((S_801739F8_0 *)controller)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &dungeonStatus;
        (*(u16 *)&activity_counts->unk_0A)--;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AFC;
        direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite, D_80174AFC[direction & 7], 0);
        ((S_801739F8_0 *)controller)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register DungeonGlobalStatus *activity_counts;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
            direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            func_80047784(sprite, D_80174AF4[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            activity_counts = &dungeonStatus;
            (*(u16 *)&activity_counts->unk_0A)++;
            ((S_801739F8_0 *)controller)->unk_9B++;
            return;
        }

        dungeon_state = &dungeonStatus.unk_00;
        if (((S_801739F8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            func_800AA6B4(controller, context, sprite, 0)) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            func_800AA888(controller, context, sprite, entity);
            ((S_801739F8_0 *)controller)->unk_A0 = 0;
            func_80173D38(controller, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            EntityRec *owner = D_800814A8;

            if ((func_8009A180(entity,
                    (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
        direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite, D_80174AF4[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((S_801739F8_4 *)dungeon_state)->unk_0A++;

        ((S_801739F8_0 *)controller)->unk_9B++;
        return;

    case 2:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &dungeonStatus;
        (*(u16 *)&activity_counts->unk_0A)--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((S_801739F8_0 *)controller)->unk_8C = D_80171138;
        return;
    }

    default:
        return;
    }
}

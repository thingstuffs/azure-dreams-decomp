#include "modules/dungeon_resource17_slot0.h"

void func_80173F10(void *action, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&dungeonStatus.unk_00;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
        direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite,(u8)(((u8 *)D_801744F4)[direction & 7]), 0);
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
            direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            func_80047784(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&dungeonStatus.unk_00;
            ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A++;
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
            return;
        }

        dungeon_state = &dungeonStatus.unk_00;
        if (((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            dungeonBeginReadyActorDirectionalAction(action, context, sprite, 0)) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            func_800AA888(action, context, sprite, entity);
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174250(action, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((dungeonCheckEntityRelation(entity,
                    (u8 *)((R17_80173F10_S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        direction = (gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_0A++;

        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&dungeonStatus.unk_00;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_8C = ((u8 *)func_801713A8);
        return;
    }

    default:
        return;
    }
}

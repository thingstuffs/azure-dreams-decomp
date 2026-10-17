/* Relink of matched dungeon/func_80AF3B98; every changed retail word is a paired relocation. */
#define dungeonAdvanceActorTransitionAndRestoreFacing func_80151398
#define D_801759F8 D_801519F8
#define D_80175A00 D_80151A00
#define D_80175A18 D_80151A18
#define D_80175A80 D_80151A80
#define D_80175A81 D_80151A81
#define D_80175A84 D_80151A84
#include "modules/dungeon_resource10_slot0.h"
extern void func_8015126C(void *, void *, void *);
extern s32 func_80150BE4(void *, s32, void *, s32);
extern void func_80150F24(s32, void *, void *, void *);
extern s32 func_80069EF8(void);

void func_80151398(void *transition, void *position, Rec_D_80082E80 *record, void *actor) {
    u8 *object_data = ((u8 *)(&gameWork));
    u8 state;
    u32 next_state;

    state = ((R10_80175398_S_80175398_0 *)transition)->unk_9B;
    switch (state) {

    case 0:
        next_state = ((R10_80175398_S_80175398_0 *)transition)->unk_9B + 1;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B = next_state;
        return;

    case 1:
        func_80041588(((u8 *)D_801519F8), ((u8 *)D_80151A80), 0);
        ((R10_80175398_S_80175398_0 *)transition)->unk_AC = 0;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
        ((R10_80175398_S_80175398_1 *)actor)->unk_8A = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;

    case 2:
    {
        s32 direction;
        u16 angle;

        direction = ((gameWork.view.viewAngle + ((R10_80175398_S_80175398_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        angle = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;
        if (((u8 *)D_80151A80)[0] == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        func_80041588(((u8 *)D_801519F8), ((u8 *)D_80151A80), 1);
        soundSetCdCueParameters(0, ((s32 *)D_8006CD58)[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), 0);
        (*(u8 *)D_80151A81) = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_80151A81));
        dungeonSelectNearbyTargetAndInitializeSlot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
    }

    case 3:
    {
        u16 old_timer = ((R10_80175398_S_80175398_0 *)transition)->unk_96.u;
        u16 timer = old_timer - 1;
        u8 *target_color;

        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 cd_finished = (*(u8 *)D_80151A81);
            ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = old_timer;
            if (cd_finished == 0) {
                return;
            }
            ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }

        target_color = ((u8 * *)D_800DCEEC)[lookupMaskedByteTable(actor)];
        ((R10_80175398_S_80175398_2 *)object_data)->unk_A8 +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_00 - ((R10_80175398_S_80175398_2 *)object_data)->unk_A8) /
            ((R10_80175398_S_80175398_0 *)transition)->unk_96.s;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_A9 +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_01 - ((R10_80175398_S_80175398_2 *)object_data)->unk_A9) /
            ((R10_80175398_S_80175398_0 *)transition)->unk_96.s;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_AA +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_02 - ((R10_80175398_S_80175398_2 *)object_data)->unk_AA) /
            ((R10_80175398_S_80175398_0 *)transition)->unk_96.s;
        return;
    }

    case 4:
        object_data = func_8003FC64(0x12);
        if (object_data == NULL) {
            return;
        }
        {
            R10_80175398_DungeonEffect *effect = (R10_80175398_DungeonEffect *)object_data;

            effect->resource = ((u8 *)func_8015126C);
            func_8004491C(effect, ((u8 *)func_80150BE4));
            ((R10_80175398_S_80175398_0 *)transition)->unk_A8.p = effect;
            effect->child->x = ((R10_80175398_DungeonCopy3 *)position)->x;
            effect->child->y = ((R10_80175398_DungeonCopy3 *)position)->y;
            (*(s16 *)D_80151A18) = -2;
            effect->child->z = ((R10_80175398_DungeonCopy3 *)position)->z;
            object_data = (u8 *)effect->tail;
            ((R10_80175398_DungeonTail *)object_data)->value1e = 0x1000;
            ((R10_80175398_DungeonTail *)object_data)->value1c = 0x1000;
            ((R10_80175398_DungeonTail *)object_data)->color = 0x00808080;
        }
        {
            s16 resource_index = lookupMaskedByteTable(actor) - 1;

            if (resource_index < 0) {
                s32 random_value = func_80069EF8();

                resource_index = random_value % 3;
            }
            func_8003DB94(object_data, ((u8 *)D_8014A000) + ((s32 *)D_80151A00)[resource_index], 0);
        }
        record->unk_14.at00_u16.v |= 0x80;
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = 0;
        next_state = ((R10_80175398_S_80175398_0 *)transition)->unk_9B + 1;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B = next_state;
        return;

    case 5:
    {
        u16 old_timer = ((R10_80175398_S_80175398_0 *)transition)->unk_96.u;
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = old_timer + 1;
        if ((s16)old_timer < 30) {
            s16 update_count = 0;
            do {
                func_80150F24(transition, position, record, actor);
                update_count++;
            } while (update_count < 8);
        }
    }
        object_data = ((R10_80175398_S_80175398_0 *)transition)->unk_A8.p2;
        object_data = ((R10_80175398_S_80175398_2 *)object_data)->unk_0C;
        if (((R10_80175398_S_80175398_2 *)object_data)->unk_14 & 0xE000) {
            ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
        }

    case 6:
        if (((R10_80175398_S_80175398_0 *)transition)->unk_9B != 6) {
            return;
        }
        if (dungeonCreateStatusLinkedRenderEffect(position, (*(void * *)D_80151A84), (*(s16 *)D_80151A18), ((u8 *)D_800DCF5C)) == 0) {
            return;
        }
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
        dungeonDecrementMonsterEntryCount(((R10_80175398_S_80175398_1 *)actor)->unk_13, 3);
        func_8009A3D0(record->unk_24, record->unk_25, 0x300);
        func_8009A028(actor);
        object_data = (u8 *)actor - 0x20;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_10 |= 0x80000000;
        return;

    case 7:
    {
        u8 *linked_actor = dungeonAdvanceStagedEntityLoad(record, actor);
        ((R10_80175398_S_80175398_1 *)actor)->unk_60 = linked_actor;
        if (linked_actor == NULL) {
            return;
        }
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->unk_9B++;
        ((R10_80175398_S_80175398_7 *)(((R10_80175398_S_80175398_1 *)actor)->unk_60))->unk_2A = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;
        {
            u8 *linked_state = ((R10_80175398_S_80175398_1 *)actor)->unk_60;
            s32 direction;
            u8 *direction_frames;

            object_data = ((R10_80175398_S_80175398_5_pre *)linked_state)[-1].unk_00;
            direction = ((gameWork.view.viewAngle + ((R10_80175398_S_80175398_5 *)linked_state)->unk_2A + 0x100) >> 9) & 7;
            direction_frames = ((R10_80175398_S_80175398_2 *)object_data)->unk_2C;
            selectIndirectTableEntry(object_data, direction_frames[direction], ((R10_80175398_S_80175398_2 *)object_data)->unk_04);
        }
        ((R10_80175398_S_80175398_2 *)object_data)->unk_14 &= 0xFFFE;
    }

    case 8:
    {
        u16 timer = ((R10_80175398_S_80175398_0 *)transition)->unk_96.u - 1;
        ((R10_80175398_S_80175398_0 *)transition)->unk_96.u = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        {

            ((R10_80175398_S_80175398_7 *)(((R10_80175398_S_80175398_1 *)actor)->unk_60))->unk_2A = ((R10_80175398_S_80175398_1 *)actor)->unk_8A;
            ((R10_80175398_S_80175398_0_pre *)transition)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            dungeonStatus.unk_0A--;
        }
    }
        ((R10_80175398_S_80175398_1 *)actor)->unk_6D = 0;

        return;
    default:
        return;
    }
}

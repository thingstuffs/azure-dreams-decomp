/* Relink of matched dungeon/func_80A9D4E8; every changed retail word is a paired relocation. */
#define D_80170E7C D_80158E7C
#define D_80174C3C D_8015CC3C
#define D_80174C7C D_8015CC7C
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"



extern int abs(int);
extern u8 D_80158E7C;
extern u8 D_8015CC3C[8];
extern u8 D_8015CC7C[8];

extern s32 getCdCommandQueueDepth();
extern void func_80047784();
extern void *dungeonScanMonsterAlongHeading();
extern void dungeonSetRecordIntegerTileCenter();
extern void dungeonAdvanceStatusTimers();
extern void func_800A56E0();
extern s32 dungeonCreateActorSpellEffect();
extern void dungeonCreateTwoRowObjectGroup();


typedef struct S_80172CE8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172CE8_0;   /* arg0 in func_8015ACE8 */

typedef struct S_80172CE8_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80172CE8_1_pre;   /* the 0x14 bytes before node in func_8015ACE8, addressed as node[-1] */

typedef struct S_80172CE8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172CE8_2;   /* owner in func_8015ACE8 */

typedef struct S_80172CE8_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80172CE8_3;   /* arg2 in func_8015ACE8 */


/* Updates item activation, actor animation, and action cleanup. */
void func_8015ACE8(void *action, EntityRec *motion, void *actor, EntityRec *object) {
    u16 position[3];
    s16 is_special;
    u8 *item_slot;
    void *node;
    u8 state;

    is_special = 0;
    state = ((S_80172CE8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((((u32)object->flags1C)) & 0x2000) {
            u32 kind = ((object->unk_46) & 0x3FFF) - 1;
            switch (kind) {
            case 6: is_special = 1;
            case 2: item_slot = (u8 *)object + 0xE; break;
            case 5: is_special = 1;
            case 1: item_slot = (u8 *)object + 0xB; break;
            case 4: is_special = 1;
            case 0: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        } else {
            s32 kind = (object->unk_46) & 0x3FFF;
            switch (kind) {
            case 3: item_slot = (u8 *)object + 0xE; break;
            case 2: item_slot = (u8 *)object + 0xB; break;
            case 1: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        }

        if (*item_slot != 0) {

            ((S_80172CE8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_existing;
                u32 item_def;

                use_existing = is_special;
                if (use_existing) {
                    node = D_800814A8;
                    (object->target) = node;
                    {
                        item_def = (u32)((S_80172CE8_1_pre *)node)[-1].unk_00;
                        (((u8)object->unk_72)) = ((S_80172CE8_2 *)item_def)->unk_24;
                        (((u8)object->unk_73)) = ((S_80172CE8_2 *)item_def)->unk_25;
                    }
                } else {
                    u8 *item_defs = D_8006DE24;
                    u8 item_id = *item_slot;
                    item_def = (item_id * 20 + item_defs)[0x12];
                    if (item_def == 2) {
                        node = (object->target);
                        if (node != 0) {
                            {
                                item_def = (u32)((S_80172CE8_1_pre *)node)[-1].unk_00;
                                (((u8)object->unk_72)) = ((S_80172CE8_2 *)item_def)->unk_24;
                                (((u8)object->unk_73)) = ((S_80172CE8_2 *)item_def)->unk_25;
                            }

                        }
                    } else {



                        (object->target) = dungeonScanMonsterAlongHeading(
                            object,
                            ((S_80172CE8_3 *)actor)->unk_24,
                            ((S_80172CE8_3 *)actor)->unk_25,
                            (object->facing),
                            0x10);
                        object->unk_72 = abs(object->unk_72);
                        object->unk_73 = abs(object->unk_73);
                    }
                }

            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (dungeonCreateActorSpellEffect(object, item_slot, is_special, (u8 *)action + 0x98)) {
                ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
                func_800A56E0(0x703);
                dungeonCreateTwoRowObjectGroup(position, (s16)((*item_slot - 1) % 3));
                ((S_80172CE8_0 *)action)->unk_9B++;
                return;
            }
            return;

        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((S_80172CE8_3 *)actor)->unk_24, ((S_80172CE8_3 *)actor)->unk_25);
        dungeonStatus.unk_0C = 0;
        {
            u8 *active_object = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
        }
        dungeonAdvanceStatusTimers(object);
        (((u8)object->unk_6D))--;
        ((S_80172CE8_0 *)action)->unk_8C = &D_80158E7C;
        (((u8)object->unk_73)) = 0;
        (((u8)object->unk_72)) = 0;
        (object->unk_46) &= 0x7FFF;
        return;

    case 1:
        if (!(((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)actor + 0x2C)) = D_8015CC7C;
        func_80047784(
            actor,
            D_8015CC7C[((gameWork.view.viewAngle + (object->facing) + 0x100) >> 9) & 7],
            0);
        ((S_80172CE8_0 *)action)->unk_9B++;
        return;

    case 2:
        if (getCdCommandQueueDepth()) {
            ((S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            return;
        }
        ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172CE8_0 *)action)->unk_9B++;
                        /* fall through */

    case 3:
        if ((((S_80172CE8_3 *)actor)->unk_04 == 5 &&
            (((S_80172CE8_3 *)actor)->unk_14 & 0x1000)) ||
            (((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            ((S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            ((S_80172CE8_0 *)action)->unk_96 = 0x10;
            ((S_80172CE8_0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 timer = ((S_80172CE8_0 *)action)->unk_96 - 1;
            ((S_80172CE8_0 *)action)->unk_96 = timer;
            if ((s16)timer <= 0) {
                ((S_80172CE8_0 *)action)->unk_96 = 0;
                ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
            }
        }

        if (!(((S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((S_80172CE8_3 *)actor)->unk_24, ((S_80172CE8_3 *)actor)->unk_25);

        if (((S_80172CE8_3 *)actor)->unk_2C != D_8015CC3C) {
            (*(void * *)((u8 *)actor + 0x2C)) = D_8015CC3C;
            func_80047784(
                actor,
                D_8015CC3C[((gameWork.view.viewAngle + (object->facing) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172CE8_0 *)action)->unk_8C = &D_80158E7C;
        dungeonAdvanceStatusTimers(object);
        if ((object->unk_6D) > 0) {
            (((u8)object->unk_6D))--;
        }
        (((u8)object->unk_73)) = 0;
        (((u8)object->unk_72)) = 0;
        (object->unk_46) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;

    default:
        break;
    }

    return;
}

#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern s32 D_800835E8[];
extern u8 D_800E131C[];

extern s32 func_80042900(void *, s32);
extern void dungeonBeginModeSelectedItemAction(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 dungeonProcessRecordAndUpdateLinkedState(s32, s32);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern void func_800997FC(void *);
extern void raiseEntityLevel(void *, s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);
extern void createActorValuePopup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void dungeonCreateViewColorFlash(s32, s16);


typedef struct S_800BF9EC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BF9EC_2_pre;   /* the 0x14 bytes before node in dungeonUseItemToLevelUpEligibleActors, addressed as node[-1] */

typedef struct S_800BF9EC_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800BF9EC_2;   /* node in dungeonUseItemToLevelUpEligibleActors */

typedef struct S_800BF9EC_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BF9EC_3;   /* ((S_800BF9EC_2_pre *)node)[-1].unk_00 in dungeonUseItemToLevelUpEligibleActors */

/* Applies an action to the target or eligible list nodes and updates action state. */
s32 dungeonUseItemToLevelUpEligibleActors(EntityRec *target, s32 action_id, s16 action_type, s32 action_param)
{
    EntityRec *head;
    void *node;

    if (action_type == 13) {
        return dungeonProcessRecordAndUpdateLinkedState(action_id, action_param);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = action_id;
        dungeonBeginModeSelectedItemAction(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, action_id, action_type);
        if (dungeonApplyActorFoodPreference(target, D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3, action_id) == 0) {
            func_800A5F38(target, action_id);
            return 1;
        }
    } else {
        dungeonCreateViewColorFlash(0x2020C0, 1);
        func_800997FC(D_800E131C);

        head = D_800814A8;
        node = (u8 *)((void *)head->unk_5C) + 0x20;
        if (node != head) {
            do {
                if (((((S_800BF9EC_2 *)node)->unk_1C & 0x2400) != 0x2000 ||
                     (func_80042900(node, 12) << 16) != 0) &&
                    (*(u8 *)((u8 *)&target->unk_10 + 1)) < 99) {
                    ((S_800BF9EC_2 *)node)->unk_18 = D_800835E8[((S_800BF9EC_2 *)node)->unk_11];
                    raiseEntityLevel(node, 0);
                    if ((((S_800BF9EC_3 *)(((S_800BF9EC_2_pre *)node)[-1].unk_00))->unk_14 & 0x8000) == 0) {
                        s32 effect_id = 0x8003;
                        if (((S_800BF9EC_2 *)node)->unk_14 & 0x2000) {
                            effect_id = 0x8002;
                        }
                        createActorValuePopup(effect_id, node, -2, 1);
                    }
                }
                node = (u8 *)((S_800BF9EC_2 *)node)->unk_5C + 0x20;
            } while (node != head);
        }
    }

    dungeonClearSlotAndUpdateLinkedState(action_id);
    dungeonStatus.unk_0A--;
    return 1;
}

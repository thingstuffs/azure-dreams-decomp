#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_800C13C8_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C13C8_0;   /* arg0 in dungeonUseItemToDrawFlameCircle; pointer addresses record offset 0x14 */

typedef struct S_800C13C8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C13C8_1;   /* state in dungeonUseItemToDrawFlameCircle */

typedef struct S_800C13C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C13C8_2;   /* temp_v0 in dungeonUseItemToDrawFlameCircle */


void dungeonBeginModeSelectedItemAction(); /* extern */
s32 dungeonProcessRecordAndUpdateLinkedState(s32, s32);           /* extern */
void dungeonClearSlotAndUpdateLinkedState();                         /* extern */
void func_800997FC();                   /* extern */
void func_800A5F38();                 /* extern */
void func_800A6480();            /* extern */
s32 dungeonApplyActorFoodPreference();                /* extern */
s32 dungeonCreateFivePointEffect(); /* extern */
extern M2C_UNK D_800C135C;
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_800E1482;

/* Handles an object operation and updates its state or triggers its effect. */
s32 dungeonUseItemToDrawFlameCircle(void *object, s32 value, s16 operation, s32 context) {
    S_800C13C8_2 *object_data;
    s32 result;

    if (operation == 0xD) {
        return dungeonProcessRecordAndUpdateLinkedState(value, context);
    }
    if (object == D_800E3D7C) {
        ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_124 = value;
        dungeonBeginModeSelectedItemAction(object, &D_80083780.x.v, &D_80082E80.unk_000, 0);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        func_800A6480(object, value, operation);
        if (dungeonApplyActorFoodPreference(object, D_800DDE84[((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_27] & 3, value) == 0) {
            func_800A5F38(object, value);
            return 1;
        }

        dungeonStatus.unk_0A--;
    } else {
        object_data = ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_00;
        if (dungeonCreateFivePointEffect(object_data->unk_24, object_data->unk_25, ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_9C,
            &D_800DEAE0, 0x5000, 0x202080, &D_800C135C) == 0) {
            result = 0;
            return result;
        }
        func_800997FC(&D_800E1482);
    }
    dungeonClearSlotAndUpdateLinkedState(value);
    result = 1;
    return result;
}

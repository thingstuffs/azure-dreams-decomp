#include "common.h"
#include "shared/record_ptrs.h"

extern u8 D_80081471;
extern u8 D_80081485;
extern u8 D_800E04BA[];
extern u8 D_800E04E6[];

extern void func_800997FC(void *data_ptr);
extern void dungeonAdjustSourceValueAndFinalize(s32 value, void *data_ptr);
extern void dungeonSelectNearbyTargetAndInitializeSlot(s32 slot_id, void *target, s32 target_id, s16 slot_value);
extern s16 dungeonGetSpecialTableDataIndex(s32 actor_value);
extern void dungeonAppendPackedActionRecord(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);

/* Start the actor action and apply its target effect unless a blocking flag is set. */
s32 dungeonBeginTargetFlaggedAction(void *actor, s32 action_arg, s32 unused, void *target) {
    if ((D_80081485 != 0) || (D_80081471 != 0)) {
        if (D_80081471 != 0) {
            func_800997FC(D_800E04BA);
            return 0;
        }
        dungeonAdjustSourceValueAndFinalize(((s32)D_800E3D7C), D_800E04E6);
        return 0;
    }
    *(s32 *)((u8 *)target + 0x1C) |= 0x100000;
    *(s32 *)((u8 *)actor + 0x124) = 0;
    *(s8 *)((u8 *)actor + 0x9A) = 0x22;
    *(s8 *)((u8 *)actor + 0x9B) = 0;
    *(s32 *)((u8 *)actor + 0x8C) = 0;
    dungeonSelectNearbyTargetAndInitializeSlot((u8 *)actor - 0x20, action_arg, 8, 0x300);
    dungeonAppendPackedActionRecord(target, 0x48, dungeonGetSpecialTableDataIndex(*(s32 *)((u8 *)actor + 0xBC)), 0);
    return 1;
}

#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern s32 func_800A5C70(void);
extern void dungeonAppendPackedActionRecord(s32 object_ptr, s32 action_code, s32 payload, s32 extra_byte);

typedef struct ActionDispatchState {
    u8 pad_00[0x8C];
    s32 callback;
    u8 pad_90[0xA];
    s8 action;
    s8 phase;
} ActionDispatchState;

/* Sets the object action to 0x33, conditionally sets a global flag, and dispatches the target. */
void dungeonBeginAction33AndDispatch(void *object, s32 unused_1, s32 unused_2, s32 target) {
    s32 action = 0x33;
    u32 saved_target;

    ((ActionDispatchState *)object)->action = action;
    ((ActionDispatchState *)object)->phase = 0;
    ((ActionDispatchState *)object)->callback = 0;
    do {
        saved_target = target;
    } while (0);

    if ((D_80013714 & 2) || ((gameWork.buttons & 0x20) && func_800A5C70())) {
        dungeonStatus.flags |= 0x80;
    }
    dungeonAppendPackedActionRecord(saved_target, 0x10, 0, 0);
}

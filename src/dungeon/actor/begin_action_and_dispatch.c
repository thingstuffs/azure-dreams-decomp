#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/item.h"

typedef struct ActionDispatchState {
    u8 pad_00[0x8C];
    s32 callback;
    u8 pad_90[0xA];
    s8 action;
    s8 phase;
} ActionDispatchState;

/* Sets the object action to 0x33, conditionally sets a global flag, and dispatches the target. */
void begin_action_33_and_dispatch(void *object, void *unused_1, void *unused_2, void *target) {
    s32 action = 0x33;
    void *saved_target;

    ((ActionDispatchState *)object)->action = action;
    ((ActionDispatchState *)object)->phase = 0;
    ((ActionDispatchState *)object)->callback = 0;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_80091258). */
    do {
        saved_target = target;
    } while (0);

    if ((system_update_flags & 2) || ((g_game_work.buttons & 0x20) && check_action_available_without_nearby_actor())) {
        g_dungeon_status.flags |= 0x80;
    }
    append_packed_action_record(saved_target, 0x10, 0, 0);
}

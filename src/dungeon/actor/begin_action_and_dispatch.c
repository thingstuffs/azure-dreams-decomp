#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern s32 check_action_available_without_nearby_actor(void);
extern void append_packed_action_record(s32 object_ptr, s32 action_code, s32 payload, s32 extra_byte);

typedef struct ActionDispatchState {
    u8 pad_00[0x8C];
    s32 callback;
    u8 pad_90[0xA];
    s8 action;
    s8 phase;
} ActionDispatchState;

/* Sets the object action to 0x33, conditionally sets a global flag, and dispatches the target. */
void begin_action_33_and_dispatch(void *object, s32 unused_1, s32 unused_2, s32 target) {
    s32 action = 0x33;
    u32 saved_target;

    ((ActionDispatchState *)object)->action = action;
    ((ActionDispatchState *)object)->phase = 0;
    ((ActionDispatchState *)object)->callback = 0;
    do {
        saved_target = target;
    } while (0);

    if ((system_update_flags & 2) || ((g_game_work.buttons & 0x20) && check_action_available_without_nearby_actor())) {
        g_dungeon_status.flags |= 0x80;
    }
    append_packed_action_record(saved_target, 0x10, 0, 0);
}

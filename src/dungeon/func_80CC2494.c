#include "common.h"
#include "shared/dungeon_status.h"

extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8017405C(void *, s32, s32, void *);

/* Checks an object action, dispatches its update, and clears flags as needed. */
s32 func_80175C94(void *object, s32 query_x, s32 query_y, s32 action_override) {
    void *saved_object = object;
    s32 next_state;
    s32 clear_result;
    s16 action_result;
    s32 override_bits;

    action_result = func_800ADDA0(query_x, query_y, saved_object, 3, 6,
                           (u8 *)saved_object + 0x9C);
    if (action_result < 0) {
        return 0;
    }
    override_bits = action_override << 16;
    if (override_bits == 0) {
        next_state = 0xE;
        if (action_result != 0) {
            if (action_result == 2) {
                goto call_block;
            }
            goto tail_block;
        }
        *((s8 *)saved_object + 0x9A) = next_state;
        func_800A9A0C(saved_object);
        return 0;
    } else {
        func_8017405C(saved_object, query_x, query_y, saved_object);
        return 0;
    }
call_block:
    func_8017405C(saved_object, query_x, query_y, saved_object);
    return 0;

tail_block:
    *((u8 *)saved_object + 0x71) &= 0x7F;
    if (dungeonStatus.flags & 8) {
        clear_result = 0;
    } else {
        return 1;
    }
    *(u16 *)((u8 *)saved_object + 0x46) &= 0x7FFF;
    return clear_result;

    return 0;
}


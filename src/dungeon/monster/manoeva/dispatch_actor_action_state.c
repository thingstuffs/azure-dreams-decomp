#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/monster/manoeva.h"

#include "dungeon/player/object/action_state.h"
void update_actor_status_and_mp();                      /* extern */
s32 relink_entity_and_clear_high_flag(); /* extern */

typedef struct S_80172114_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172114_0;   /* held_arg0 in dispatch_actor_action_state */

/* Updates object state and flags according to the state handler result. */
s32 dispatch_actor_action_state(void *object, s32 state_input_a, s32 state_input_b) {
    s32 saved_input_a;
    s32 saved_input_b;
    void *saved_object;
    s32 call_result;
    s32 state;

    saved_input_a = state_input_a;
    saved_input_b = state_input_b;
    saved_object = object;
    call_result = relink_entity_and_clear_high_flag(saved_input_a, saved_input_b, saved_object, 2, 4, saved_object + 0x9C);
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state >= 0) {
        switch (state) {
        case 0:
            ((S_80172114_0 *)saved_object)->unk_9A = 0xE;
            update_actor_status_and_mp(saved_object);
            return 0;
        case 2:
            advance_actor_turn_path(saved_object, saved_input_a, saved_input_b, saved_object);
            return 0;
        case 1:
            ((S_80172114_0 *)saved_object)->unk_71 =
                    (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
            if ((has_pending_dungeon_activity(saved_object) << 0x10) != 0) {
                ((S_80172114_0 *)saved_object)->unk_46 =
                    (u16) (((S_80172114_0 *)saved_object)->unk_46 & 0x7FFF);
                return 0;
            }
        default:
            ((S_80172114_0 *)saved_object)->unk_71 =
                    (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
            if ((g_dungeon_status.flags & 8) == 0) {
                call_result = 1;
                break;
            }
            ((S_80172114_0 *)saved_object)->unk_46 =
                (u16) (((S_80172114_0 *)saved_object)->unk_46 & 0x7FFF);
            return 0;
        }
    }
    return call_result;
}

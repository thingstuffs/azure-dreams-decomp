#include "common.h"
#include "shared/object_index_slots.h"

extern void func_80033D08(void *actor);
extern void initialize_record_with_handler_table(void *record, s32 setup_value, s32 init_value);

/* Clean up the actor, clear its indexed flag, and complete its current action. */
void complete_player_action(void *actor, s32 motionState, s32 completionArg) {
    func_80033D08(actor);
    *(((*(s32 *)((u8 *)actor + 0x40)) * 8) + ((u8 *)D_80082660)) = 0;
    initialize_record_with_handler_table(actor, motionState, completionArg);
}

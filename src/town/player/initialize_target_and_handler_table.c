#include "town/player/position_handlers.h"
#include "common.h"
#include "town/player.h"
#include "town/player/handler_reset_data.h"
#include "town/player/object.h"

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B228;

/* Initialize the target, assign the state table, and clear the global flag. */
void initialize_target_and_handler_table(Struct8009B228 *state, ObjectPosition *target) {
    clear_object_velocity(target);
    state->unk4 = dispatch_state_callback_by_mode;
    player_handler_reset_byte = 0;
}

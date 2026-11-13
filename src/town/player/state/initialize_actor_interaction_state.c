#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"
#include "town/player/state.h"
#include "town/player.h"



typedef struct S_800946FC_0 {
    void (*unk_00)();
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800946FC_0;   /* arg0 in install_actor_interaction_handler */

/* Initializes the object's data pointer and sets its initial value to 0x13. */
void install_actor_interaction_handler(S_800946FC_0 *object) {
    object->unk_00 = update_actor_interaction_actions;
    object->unk_0A = 0x13;
}

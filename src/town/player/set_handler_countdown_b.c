#include "common.h"
#include "town/player.h"
#include "town/player/state.h"

typedef struct S_80098CD8_0 {
    u8 pad_00[0x4];
    void (*unk_04)(void *, s32);
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098CD8_0;   /* arg0 in set_handler_and_countdown_400 */

/* Initialize the object's data pointer and set its initial value to 0x400. */
void set_handler_and_countdown_400(S_80098CD8_0 *object) {
    object->unk_04 = &forward_state_value_to_handler_b;
    object->unk_10 = 0x400;
}

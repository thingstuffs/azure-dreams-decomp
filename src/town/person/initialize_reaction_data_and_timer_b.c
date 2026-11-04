#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void ease_reaction_position_to_target();

typedef struct S_800CA774_0 {
    u8 pad_00[0x54];
    void (*unk_54)();
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800CA774_0;   /* arg0 in initialize_reaction_data_and_timer_10_b */

/* Initializes the object's data pointer and sets its initial value to 10. */
void initialize_reaction_data_and_timer_10_b(S_800CA774_0 *object, void *unused_position, void *unused_context, void *unused_game) {
    object->unk_54 = &ease_reaction_position_to_target;
    object->unk_6C = 0xA;
}

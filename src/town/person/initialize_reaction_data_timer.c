#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_800CA134(void *state, void *position);

typedef struct S_800CA744_0 {
    u8 pad_00[0x54];
    void (*unk_54)();
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800CA744_0;   /* arg0 in initialize_reaction_data_and_timer_10 */

/* Initializes the object's data pointer and associated value to 10. */
void initialize_reaction_data_and_timer_10(S_800CA744_0 *object) {
    object->unk_54 = &D_800CA134;
    object->unk_6C = 0xA;
}

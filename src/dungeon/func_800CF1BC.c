#include "common.h"
#include "m2c_compat.h"

s32 resolve_actor_floor_trap_once();                                /* extern */
extern u8 D_800D4494;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D491C_0;   /* arg0 in set_actor_data_pointer */

/* Sets the object data pointer when the status check is positive. */
void set_actor_data_pointer(S_800D491C_0 *object) {
    if (resolve_actor_floor_trap_once() > 0) {
        object->unk_8C = &D_800D4494;
    }
}

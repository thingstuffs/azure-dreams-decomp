#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800A2DF0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A2DF0_0;   /* arg0 in add_entity_position_to_menu_vector */


/* Add three record increments to the corresponding 16-bit components. */
void add_entity_position_to_menu_vector(S_800A2DF0_0 *components, EntityRec *increments) {
    components->unk_00 = (u16) (components->unk_00 + ((u16)increments->x.w.i));
    components->unk_02 = (u16) (components->unk_02 + ((u16)increments->y.w.i));
    components->unk_04 = (u16) (components->unk_04 + ((u16)increments->z.w.i));
}

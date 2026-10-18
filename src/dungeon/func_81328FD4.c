#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8016F78C;

typedef struct S_801707D4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_801707D4_0;   /* arg0 in set_boss_effect_data_pointer */

typedef struct S_801707D4_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_801707D4_1;   /* arg3 in set_boss_effect_data_pointer */

/* Set the object's data pointer and clear the flag owner's high flag bit. */
void set_boss_effect_data_pointer(S_801707D4_0 *object, M2C_UNK unused_1, M2C_UNK unused_2, S_801707D4_1 *flag_owner) {
    object->unk_8C = &D_8016F78C;
    flag_owner->unk_46 = (u16) (flag_owner->unk_46 & 0x7FFF);
}

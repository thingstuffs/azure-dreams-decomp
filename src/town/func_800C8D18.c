#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C6478_0 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C6478_0;   /* arg0 in set_linked_data_pointer_variant_3 */

typedef struct S_800C6478_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C6478_1;   /* ((S_800C6478_0 *)arg0)->unk_80 in set_linked_data_pointer_variant_3 */


extern M2C_UNK D_800D5930;


/* Sets the object's linked data pointer to D_800D5930. */
void set_linked_data_pointer_variant_3(S_800C6478_0 *object) {
    ((S_800C6478_1 *)(object->unk_80))->unk_04 = &D_800D5930;
}

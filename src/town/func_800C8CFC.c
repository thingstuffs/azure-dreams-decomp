#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C645C_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C645C_1;   /* arg0 in set_linked_data_pointers_variant_2 */

typedef struct S_800C645C_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C645C_2;   /* ((S_800C645C_1 *)arg0)->unk_80 in set_linked_data_pointers_variant_2 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D58F4;

typedef struct S_800C645C_0 {
    u8 pad_00[0x7C];
    M2C_UNK ** unk_7C;
} S_800C645C_0;   /* arg0 in set_linked_data_pointers_variant_2 */

/* Set both object references to D_800D58F4. */
void set_linked_data_pointers_variant_2(S_800C645C_0 *object) {
    *object->unk_7C = &D_800D58F4;
    ((S_800C645C_2 *)(((S_800C645C_1 *)object)->unk_80))->unk_04 = &D_800D58F4;
}

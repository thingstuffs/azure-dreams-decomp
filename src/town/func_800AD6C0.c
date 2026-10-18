#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800AAD3C;

typedef struct S_800AAE20_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800AAE20_0;   /* arg0 in set_person_data_pointer */

/* Sets the object's pointer at offset 0x50 to D_800AAD3C. */
void set_person_data_pointer(S_800AAE20_0 *object) {
    object->unk_50 = &D_800AAD3C;
}

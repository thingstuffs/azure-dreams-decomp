#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "m2c_compat.h"
#include "town/person.h"


typedef struct S_800CB060_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800CB060_1;   /* ((S_800CB060_0 *)arg0)->unk_80 in set_linked_data_pointer */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D6960;


/* Set the object's linked data pointer to D_800D6960. */
void set_linked_data_pointer(Rec_func_80094268_arg0 *object) {
    ((S_800CB060_1 *)(object->unk_80))->unk_04 = &D_800D6960;
}

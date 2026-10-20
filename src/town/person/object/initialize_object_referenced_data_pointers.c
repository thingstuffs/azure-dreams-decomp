#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB028_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800CB028_1;   /* arg0 in initialize_object_referenced_data_pointers */

typedef struct S_800CB028_2 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800CB028_2;   /* ((S_800CB028_1 *)arg0)->unk_80 in initialize_object_referenced_data_pointers */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D685C;
extern M2C_UNK D_800D6870;

typedef struct S_800CB028_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
} S_800CB028_0;   /* arg0 in initialize_object_referenced_data_pointers */

/* Initialize the object's referenced data pointers. */
void initialize_object_referenced_data_pointers(S_800CB028_0 *object) {
    *object->unk_7C = &D_800D685C;
    ((S_800CB028_2 *)(((S_800CB028_1 *)object)->unk_80))->unk_04 = &D_800D6870;
}

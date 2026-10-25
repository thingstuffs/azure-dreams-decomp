#include "town/person.h"
#include "m2c_compat.h"





/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D685C;
extern M2C_UNK D_800D6870;


/* Initialize the object's referenced data pointers. */
void initialize_object_referenced_data_pointers(PersonObject *object, s32 unused_context, s8 *unused_output) {
    *object->data_7C = &D_800D685C;
    object->descriptor->entries[1] = &D_800D6870;
}

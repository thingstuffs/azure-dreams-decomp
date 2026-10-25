#include "common.h"
typedef struct Obj_800B45A0 Obj_800B45A0;
void advance_inner_value_and_complete(Obj_800B45A0 *obj);

typedef struct S_800B1DBC_0 {
    u8 pad_00[0x10];
    void (*unk_10)(Obj_800B45A0 *);
} S_800B1DBC_0;   /* arg0 in set_object_data_pointer_2 */

/* Sets the object's pointer to advance_inner_value_and_complete. */
void set_object_data_pointer_2(S_800B1DBC_0 *object) {
    object->unk_10 = &advance_inner_value_and_complete;
}

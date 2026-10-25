#include "common.h"
void update_person_global_state(void *object, s32 call_arg, s32 *values);

typedef struct S_800AAE20_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, s32,  s32 *);
} S_800AAE20_0;   /* arg0 in set_person_data_pointer */

/* Sets the object's pointer at offset 0x50 to update_person_global_state. */
void set_person_data_pointer(S_800AAE20_0 *object) {
    object->unk_50 = &update_person_global_state;
}

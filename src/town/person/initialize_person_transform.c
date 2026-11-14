#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern void *person_transform_defaults[];
extern s32 D_800C283C[];

/* Initialize the object with its indexed resource and set its flag and data pointer. */
void initialize_person_transform(void *object, s32 setup_value, SpriteFrameState *unused) {
    u8 *obj = object;

    init_secondary_list_record(object, setup_value, person_transform_defaults[obj[0x94]]);
    obj[0x14] = 1;
    *(void **)(obj + 0x50) = D_800C283C;
}

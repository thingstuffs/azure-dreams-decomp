#include "common.h"
#include "shared/town_object.h"
#include "town/person/object.h"

extern s32 D_800D6220[];
extern s32 *D_800D62D8[];
extern PersonDescriptor D_800D62E0;
extern s32 D_800D6308[];
extern TownIndexedHandler D_800D630C[];

/* Assign the object data pointers and link the shared data entry. */
void set_object_data_tables_with_link(TownObjectRecord *object) {
    object->state_handlers = D_800D6308;
    object->indexed_handlers = D_800D630C;
    object->unk_7C.as_pps32 = D_800D62D8;
    object->descriptor = &D_800D62E0;
    D_800D62E0.entries[1] = D_800D6220;
}

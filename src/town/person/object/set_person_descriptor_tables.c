#include "common.h"
#include "town/person/object.h"

#include "shared/town_object.h"

extern s32 *D_800D6330[];
extern PersonDescriptor D_800D6338;
extern s32 D_800D6360[];
extern TownIndexedHandler D_800D6364[];

/*
 * Binds object fields 0x58/0x5C to D_800D6360/D_800D6364 and fields 0x7C/0x80 to
 * D_800D6330/D_800D6338.
 */
void set_person_descriptor_tables(TownObjectRecord *object) {
    object->state_handlers = D_800D6360;
    object->indexed_handlers = D_800D6364;
    object->unk_7C.as_pps32 = D_800D6330;
    object->descriptor = &D_800D6338;
}

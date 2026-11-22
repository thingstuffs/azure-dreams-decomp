#include "town/person_callbacks_api.h"
#include "shared/object_index_slots.h"

struct TownObjectRecord;

/* Set the object's data pointer and clear its indexed table entry's flag. */
void install_object_handler_and_clear_slot_flag(struct TownObjectRecord *object) {
    unsigned char *body = (unsigned char *)object;
    int entry_index;
    *(void **)(body + 0x54) = dispatch_record_handler;
    entry_index = *(int *)(body + 0x60);
    object_index_slots[entry_index].active = 0;
}

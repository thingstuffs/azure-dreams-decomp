#include "common.h"
#include "town/person/object_setup.h"
#include "shared/object_index_slots.h"

extern u32 person_motion_tag[4];
extern u32 person_slot_flag_handler_address[4];
typedef struct {
    u8 pad0;
    s8 val;
    u8 pad2[6];
} Rec8;


/* Installs object handlers, sets its status, and clears its object and slot state bytes. */
void initialize_object_handlers(void *object, void *unused_context, void *unused_setup) {
    *(void **) ((u8 *) object + 0x50) = &person_motion_tag[0];
    *(s8 *) ((u8 *) object + 0x92) = 1;
    *(void **) ((u8 *) object + 0x54) = &person_slot_flag_handler_address[0];
    *(s8 *) ((u8 *) object + 0x15) = 0;
    object_index_slots[*(s32 *) ((u8 *) object + 0x60)].unk_01 = 0;
}

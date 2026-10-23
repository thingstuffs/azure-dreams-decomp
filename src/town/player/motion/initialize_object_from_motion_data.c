#include "common.h"
#include "shared/town_handler.h"

typedef struct {
    unsigned char pad04[0];
} Unknown;

extern void clear_entity_record_fields(void *);
extern signed char town_action_reset_byte;
extern int D_80098764;
extern int D_800D01B8[];

/* Initializes an object from the supplied data and sets its handler and state. */
void initialize_object_from_motion_data(void *object, void *initializationData, void *ptr2) {
    unsigned short secondaryValue;

    call_the_handler_selects_nonzero_entry((s32 *) D_800D01B8, object, ptr2);
    town_action_reset_byte = 0;
    *(unsigned short *)((unsigned char *)object + 0x30) =
        *(unsigned short *)((unsigned char *)initializationData + 2);
    secondaryValue = *(unsigned short *)((unsigned char *)initializationData + 6);
    *(short *)((unsigned char *)object + 0xA) = 8;
    *(int **)((unsigned char *)object + 4) = &D_80098764;
    *(unsigned short *)((unsigned char *)object + 0x32) = secondaryValue;
    clear_entity_record_fields(initializationData);
}

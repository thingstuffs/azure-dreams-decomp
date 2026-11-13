#include "common.h"
#include "town/player/action_reset_data.h"
#include "shared/town_handler.h"
#include "town/player/motion.h"
#include "town/player/object.h"
#include "town/player/position.h"

typedef struct {
    unsigned char pad04[0];
} Unknown;


extern int D_800D01B8[];

/* Initializes an object from the supplied data and sets its handler and state. */
void initialize_object_from_motion_data(void *object, ObjectPosition *initializationData, void *ptr2) {
    unsigned short secondaryValue;

    dispatch_selected_entry_if_nonzero(D_800D01B8, object, ptr2);
    town_action_reset_byte = 0;
    *(unsigned short *)((unsigned char *)object + 0x30) =
        *(unsigned short *)((unsigned char *)initializationData + 2);
    secondaryValue = initializationData->y.unsigned_parts.integer;
    *(short *)((unsigned char *)object + 0xA) = 8;
    *(int **)((unsigned char *)object + 4) = interpolate_position_by_angle_offset;
    *(unsigned short *)((unsigned char *)object + 0x32) = secondaryValue;
    clear_entity_record_fields(initializationData);
}

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "slus.h"
#include "town/person.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person_callbacks_api.h"


extern s32 D_800D6CF0[];


/* Clears the entity's indexed flag and sets its next handler and state. */
void initialize_fade_action(TownObjectRecord *entity, s32 unused, void *context) {
    sound_set_cd_cue_parameters(0, 0x2C3D, 0x02000002, 0x010000EA);
    SD_Call(0x300);
    initialize_object_entries((entity), context, (s32 *)(&D_800D6CF0));
    object_index_slots[entity->slot].unk_00 = 0;
    entity->handler = advance_fade_and_set_gray_color;
    entity->timer.as_s16 = 0x19;
}

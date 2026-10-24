#include "common.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
short SD_Call(int flags);
#include "town/person/object/initialize_object_entries_api.h"

extern M2C_UNK D_800CC4B0[3];
extern s32 D_800D6CF0[];


/* Clears the entity's indexed flag and sets its next handler and state. */
void initialize_fade_action(Rec_func_80094268_arg0 *entity, s32 unused, void *context) {
    sound_set_cd_cue_parameters(0, 0x2C3D, 0x02000002, 0x010000EA);
    SD_Call(0x300);
    initialize_object_entries((Struct800C5724 *)(entity), context, (s32 *)(&D_800D6CF0));
    object_index_slots[entity->unk_60].unk_00 = 0;
    entity->unk_54 = &D_800CC4B0;
    entity->unk_6C.as_s16 = 0x19;
}

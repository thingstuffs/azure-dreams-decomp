#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


extern M2C_UNK sound_set_cd_cue_parameters();
extern M2C_UNK SD_Call();
extern void initialize_object_entries();

extern M2C_UNK D_800CC4B0[3];
extern M2C_UNK D_800D6CF0[3];


/* Clears the entity's indexed flag and sets its next handler and state. */
void initialize_fade_action(Rec_func_80094268_arg0 *entity, M2C_UNK unused, M2C_UNK context) {
    sound_set_cd_cue_parameters(0, 0x2C3D, 0x02000002, 0x010000EA);
    SD_Call(0x300);
    initialize_object_entries(entity, context, &D_800D6CF0);
    D_80082660[entity->unk_60].unk_00 = 0;
    entity->unk_54 = &D_800CC4B0;
    entity->unk_6C.as_s16 = 0x19;
}

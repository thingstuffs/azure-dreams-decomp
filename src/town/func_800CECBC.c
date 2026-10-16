#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK soundSetCdCueParameters();
extern M2C_UNK SD_Call();
extern void townInitializeObjectEntries();

extern M2C_UNK D_800CC4B0[3];
extern M2C_UNK D_800D6CF0[3];


/* Clears the entity's indexed flag and sets its next handler and state. */
void townInitializeFadeAction(Rec_func_80094268_arg0 *entity, M2C_UNK unused, M2C_UNK context) {
    soundSetCdCueParameters(0, 0x2C3D, 0x02000002, 0x010000EA);
    SD_Call(0x300);
    townInitializeObjectEntries(entity, context, &D_800D6CF0);
    *((s8 *)((M2C_UNK *)D_80082660) + (entity->unk_60 * 8)) = 0;
    entity->unk_54 = &D_800CC4B0;
    entity->unk_6C.as_s16 = 0x19;
}

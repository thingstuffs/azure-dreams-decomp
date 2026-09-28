#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_800A4ACC();                      /* extern */



/* Reset the entity state, clear the target flag, and decrement its counter. */
void func_8016D6F8(Rec_func_800A9E70_arg0 *entity, M2C_UNK unused_1, M2C_UNK unused_2, EntityRec *target) {
    target->unk_71 = (u8) (target->unk_71 & 0x7F);
    entity->unk_8C = 0;
    entity->unk_9A.as_s8 = 0x17;
    entity->unk_9B.as_s8 = 0;
    func_800A4ACC(target);
    target->unk_6D = (u8) (((u8)target->unk_6D) - 1);
}

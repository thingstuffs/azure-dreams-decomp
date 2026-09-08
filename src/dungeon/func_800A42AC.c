#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800AA53C();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
extern u16 D_80013714;
extern u16 D_80083462;


/* Process an entity's pending updates and clear its update flags. */
void func_800A9A0C(Rec_D_800E3D7C *entity) {
    s8 updates_left;
    u8 entity_type;

    entity->unk_71.as_u8 = (u8) (entity->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2800)) {
        if (entity->unk_6D.as_s8 != 0) {
            do {
                if (!(D_80013714 & 8)) {
                    if (!(entity->unk_1C.as_s32 & 8) && ((entity_type = entity->unk_10.at03_u8.v, ((entity_type < 0x2FU) != 0)) || (entity_type == 0x39))) {
                        func_800AD594(entity, 4);
                    }
                    func_800A4ACC(entity);
                }
                updates_left = (u8) entity->unk_6D.as_s8 - 1;
                entity->unk_6D.as_s8 = updates_left;
            } while ((updates_left << 0x18) != 0);
        }
        entity->unk_44.at02_u16.v = (u16) (entity->unk_44.at02_u16.v & 0x7FFF);
        func_800AA53C(entity);
    }
}

#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800AA53C();                      /* extern */
M2C_UNK func_800AD594();             /* extern */


/* Process an entity's pending updates and clear its update flags. */
void func_800A9A0C(EntityRec *entity) {
    s8 updates_left;
    u8 entity_type;

    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2800)) {
        if (entity->unk_6D != 0) {
            do {
                if (!(*(u16 *)0x80013714 & 8)) {
                    if (!(entity->flags1C & 8) && ((entity_type = (*(u8 *)((u8 *)&entity->unk_10 + 3)), ((entity_type
                        < 0x2FU) != 0)) || (entity_type == 0x39))) {
                        func_800AD594(entity, 4);
                    }
                    func_800A4ACC(entity);
                }
                updates_left = (u8) entity->unk_6D - 1;
                entity->unk_6D = updates_left;
            } while ((updates_left << 0x18) != 0);
        }
        entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
        func_800AA53C(entity);
    }
}

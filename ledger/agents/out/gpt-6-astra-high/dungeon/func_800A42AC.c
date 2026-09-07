#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800AA53C();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
extern u16 D_80013714;
extern u16 D_80083462;

typedef struct S_800A9A0C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x26];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800A9A0C_0;   /* arg0 in func_800A9A0C */

/* Process an entity's pending updates and clear its update flags. */
void func_800A9A0C(S_800A9A0C_0 *entity) {
    s8 updates_left;
    u8 entity_type;

    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2800)) {
        if (entity->unk_6D != 0) {
            do {
                if (!(D_80013714 & 8)) {
                    if (!(entity->unk_1C & 8) && ((entity_type = entity->unk_13, ((entity_type < 0x2FU) != 0)) || (entity_type == 0x39))) {
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

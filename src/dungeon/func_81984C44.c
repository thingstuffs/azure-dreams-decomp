#include "modules/dungeon_ovl_19a332c.h"

void *func_80026444(void *source_entity)
{
    void *node;
    s16 owner_limit;
    s32 initial_limit;
    void *next_link;
    s8 entity_floor;
    ovl_19a332c_81984C44_S_81984C44_4 *owner;

    node = D_800814A8;
    initial_limit = 0x100;
    if (((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26 < 0) {
        initial_limit = 4;
    }
    next_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next_link + 0x20;
    if (node != D_800814A8) {
        do {
            void *next_link;
            if (((func_800A2CB8(D_800814A8, node) << 16) != 0) &&
                ((dungeonCheckEntityEligibility(node) << 16) != 0) &&
                !(((ovl_19a332c_81984C44_S_81984C44_2_pre *)node)[-1].unk_12 & 0x2000)) {
                entity_floor = ((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26;
                owner = ((ovl_19a332c_81984C44_S_81984C44_2_pre *)node)[-1].unk_00;
                if (entity_floor >= 0) {
                    if (entity_floor == owner->unk_26) {
                        return node;
                    }
                } else {
                    owner_limit = initial_limit;
                    if (dungeonGetTileChebyshevDistance(owner, source_entity) < owner_limit) {
                        return node;
                    }
                }
            }
            next_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)next_link + 0x20;
        } while (node != D_800814A8);
    }
    return 0;
}

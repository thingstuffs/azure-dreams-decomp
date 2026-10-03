#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800C8A3C();


/* Process an entity's item, deferring the primary entity's handling and cleaning up completed uses. */
s32 func_800C4220(EntityRec *entity, s32 item, s16 use_type) {
    if (entity == D_800E3D7C) {
        entity->unk_110 = item;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((s32)entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, use_type);
        if (func_800AD6FC(entity,
                          (D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3,
                          0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    if (func_800C8A3C(entity, 0x400, 8) != 0) {
        func_800A56E0(0x520);
    }
    func_80098B38(item);
    dungeonStatus.unk_0A--;
    return 1;
}

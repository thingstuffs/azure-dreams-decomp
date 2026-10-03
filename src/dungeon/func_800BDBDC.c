#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef s32 M2C_UNK;

typedef struct {
    u8 pad_0[0xA];
    u16 field_A;
} D_80083460_Type;

#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
M2C_UNK func_80099844();
s32 func_800A2424();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
extern M2C_UNK D_800E173A;

/* Processes an entity's item interaction and consumes the item when finished. */
s32 func_800C333C(EntityRec *entity, s32 item, s16 action) {
    if (entity == ((s32)D_800E3D7C)) {
        entity->unk_110 = item;
        func_8008D330(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, action);
        if (func_800AD6FC(
                entity,
                (D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3,
                0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    if (func_800A2424(entity, 1) == 0) {
        func_80099844(entity, &D_800E173A);
    }
    func_80098B38(item);
    {
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    }
    return 1;
}

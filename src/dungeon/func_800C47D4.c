#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9F34_arg0.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8009A180();
extern s8 func_8009FB34();
extern s32 func_800A1C58();
extern M2C_UNK func_800CA0DC();
extern M2C_UNK func_800CA93C();
extern M2C_UNK func_800CAA94();




typedef struct S_800C9F34_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800C9F34_3;   /* arg2 in func_800C9F34 */


/* Updates entity action state and dispatches the appropriate handler. */
void func_800C9F34(Rec_func_800C9F34_arg0 *actor_state, M2C_UNK context, S_800C9F34_3 *position, EntityRec *entity) {

    if (dungeonStatus.flags & 0x1000) {
        actor_state->unk_9A.as_s8 = 0xE;
        func_800CA0DC(actor_state);
        return;
    }
    if (dungeonStatus.flags & 0x2000) {
        goto update_tile;
    }
    actor_state->unk_9A.as_s8 = 0xE;
    entity->flags1C =
        entity->flags1C | 0x40000;
    actor_state->unk_98 = actor_state->unk_98 & 0xFFF7;
    if (entity->unk_28 == 0) {
        goto dispatch_action;
    }
    if (((*(u16 *)0x80013714) & 8) == 0) {
        goto check_entity;
    }
dispatch_action:
    func_800CAA94(actor_state, context, position);
    return;

check_entity:
    if ((func_800A1C58(entity) << 0x10) == 0) {
        goto update_tile;
    }
    if ((dungeonStatus.unk_0C == entity) &&
        (dungeonStatus.unk_0A == 0) &&
        !(dungeonStatus.flags & 8)) {
        entity->unk_18 = 0;
        dungeonStatus.unk_0C = 0;
        return;
    }
    return;

update_tile:
    position->unk_26 = func_8009FB34(
        position->unk_24, position->unk_25);
    if ((entity->unk_6D > 0) &&
        (!(dungeonStatus.flags & 0x2000) ||
         ((func_8009A180(entity,
            ((s32)D_800814A8->unk_58) + 0x20) << 0x10) == 0))) {
        func_800CA93C(actor_state, context, position);
    }
}

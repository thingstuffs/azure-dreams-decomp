#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_func_800C9F34_arg0.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8009A180();
extern s8 func_8009FB34();
extern s32 func_800A1C58();
extern M2C_UNK func_800CA0DC();
extern M2C_UNK func_800CA93C();
extern M2C_UNK func_800CAA94();
extern u16 D_80013714;
extern void *D_800814A8;
extern M2C_UNK D_80083460;
extern u16 D_80083462;


typedef struct S_800C9F34_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    void * unk_0C;
} S_800C9F34_0;   /* st in func_800C9F34 */



typedef struct S_800C9F34_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800C9F34_3;   /* arg2 in func_800C9F34 */


/* Updates entity action state and dispatches the appropriate handler. */
void func_800C9F34(Rec_func_800C9F34_arg0 *actor_state, M2C_UNK context, S_800C9F34_3 *position, void *entity) {
    void *action_state = &D_80083460;

    if (((S_800C9F34_0 *)action_state)->unk_02 & 0x1000) {
        actor_state->unk_9A.as_s8 = 0xE;
        func_800CA0DC(actor_state);
        return;
    }
    if (((S_800C9F34_0 *)action_state)->unk_02 & 0x2000) {
        goto update_tile;
    }
    actor_state->unk_9A.as_s8 = 0xE;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 =
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 | 0x40000;
    actor_state->unk_98 = actor_state->unk_98 & 0xFFF7;
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        goto dispatch_action;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if ((D_80013714 & 8) == 0) {
        goto check_entity;
    }
dispatch_action:
    func_800CAA94(actor_state, context, position);
    return;

check_entity:
    if ((func_800A1C58(entity) << 0x10) == 0) {
        goto update_tile;
    }
    if ((((S_800C9F34_0 *)action_state)->unk_0C == entity) &&
        (((S_800C9F34_0 *)action_state)->unk_0A == 0) &&
        !(((S_800C9F34_0 *)action_state)->unk_02 & 8)) {
        ((Rec_D_800E3D7C *)entity)->unk_18 = 0;
        ((S_800C9F34_0 *)action_state)->unk_0C = 0;
        return;
    }
    return;

update_tile:
    position->unk_26 = func_8009FB34(
        position->unk_24, position->unk_25);
    if ((((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) &&
        (!(D_80083462 & 0x2000) ||
         ((func_8009A180(entity,
            ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) == 0))) {
        func_800CA93C(actor_state, context, position);
    }
}

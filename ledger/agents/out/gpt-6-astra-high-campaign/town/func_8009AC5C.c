#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80097D54_arg0.h"

extern s32 func_80098988();
extern s16 func_800C2AE8();

/* Move the entity in its current direction until the movement countdown expires. */
void func_800983BC(Rec_func_80097D54_arg0 *move_state, Rec_D_800E3D7C *entity, s32 finish_arg) {
    s16 direction;
    u16 steps_left;

    entity->unk_08.at02_s16.v = func_800C2AE8(entity);
    steps_left = move_state->unk_0A - 1;
    move_state->unk_0A = steps_left;
    if ((s16)steps_left < 0) {
        func_80098988(move_state, entity, finish_arg);
        return;
    }
    direction = move_state->unk_10;
    switch (direction) {
    case 0x400:
        entity->unk_00.at00_s32.v += 0x120000;
        break;
    case 0xC00:
        entity->unk_00.at00_s32.v -= 0x120000;
        break;
    case 0:
        entity->unk_04.at00_s32.v += 0x120000;
        break;
    default:
        entity->unk_04.at00_s32.v -= 0x120000;
        break;
    }
}

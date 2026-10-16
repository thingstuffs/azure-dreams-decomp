#include "modules/dungeon_resource03_slot0.h"

void func_8017139C(void *controller, void *context, void *entity, void *path_state)
{
    void *state = path_state;
    s32 move_flags;
    s16 direction;
    s16 move_result;
    s16 x;
    s32 y;
    s32 control_flags;

    if (((R03_8017139C_S_8017139C_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((R03_8017139C_S_8017139C_0 *)state)->unk_71.u <= ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != ((u8 *)D_80173C74)) {
        (*(u8 * *)((u8 *)entity + (0x2C))) = ((u8 *)D_80173C74);
        func_80047784(
            entity,
            ((u8 *)D_80173C74)[((gameWork.view.viewAngle + ((R03_8017139C_S_8017139C_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (((R03_8017139C_S_8017139C_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    direction = ((s16)func_800A0818(
        x,
        y,
        ((R03_8017139C_S_8017139C_3 *)((u8 *)state + ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.s))->unk_74,
        ((R03_8017139C_S_8017139C_3 *)((u8 *)state + ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)controller + 0x98));
    move_result = ((s16)func_8009A66C(direction, entity, state, 0x20));

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((R03_8017139C_S_8017139C_3 *)((u8 *)state + ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((R03_8017139C_S_8017139C_3 *)((u8 *)state + ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.s))->unk_7C;
    ((R03_8017139C_S_8017139C_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (((R03_8017139C_S_8017139C_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    ((R03_8017139C_S_8017139C_0 *)state)->unk_2A = direction;
    if (move_result == 3) {
        if (!(dungeonStatus.flags & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            func_80171D3C(controller, context, entity, state);
        } else {
            ((R03_8017139C_S_8017139C_2 *)controller)->unk_9A = 0xF;
        }
    } else {
        control_flags = ((R03_8017139C_S_8017139C_2 *)controller)->unk_98;
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_9A = 0xF;
        control_flags &= ~8;
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_98 = control_flags;
    }
    ((R03_8017139C_S_8017139C_2 *)controller)->unk_8C = 0;
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 0;
        return;
    }

    ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 8;
    {
        s32 step_count = ((R03_8017139C_S_8017139C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 8 / step_count;
        }
    }
}

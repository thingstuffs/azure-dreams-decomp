#include "modules/dungeon_ovl_e0365c.h"

void func_80171B68(void *action, s32 action_id, void *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((E_80171B68_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((E_80171B68_S_80171570_0 *)state)->unk_71.u <= ((E_80171B68_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != D_80174518) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80174518;
        func_80047784(
            entity,
            D_80174518[((gameWork.view.viewAngle + ((E_80171B68_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((E_80171B68_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(x, y, tile_mask);

    direction = func_800A0818(
        x,
        y,
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_74,
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_7C,
        (u8 *)action + 0x98);
    move_result = func_8009A66C(direction, entity, state, 0x20);

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((E_80171B68_S_80171570_0 *)state)->unk_8A = (u16)((E_80171B68_S_80171570_0 *)state)->unk_8A + 1;

    new_x = ((Rec_D_80082E80 *)entity)->unk_24;
    new_y = ((Rec_D_80082E80 *)entity)->unk_25;
    if (((E_80171B68_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, tile_mask);
    ((E_80171B68_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(dungeonStatus.flags & 0x80)
        && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
        func_80171DAC(action, action_id, entity, state);
        ((E_80171B68_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((E_80171B68_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((E_80171B68_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((E_80171B68_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((E_80171B68_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((E_80171B68_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((E_80171B68_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}

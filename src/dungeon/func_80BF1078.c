#include "modules/dungeon_ovl_7f559800.h"

void *dungeonCreateFlaggedActorObject(s16 init_flags, s16 tile_x, s16 tile_y, s16 object_id)
{
    s32 mode;
    s32 flags_14;
    s32 flags_1c;
    S_8016A878_3 *placement;
    S_8016A878_2 *object_data;
    void *object;
    S_8016A878_4 *runtime;
    S_8016A878_1 *state;
    s8 saved_x;
    register s16 saved_id;
    s8 saved_y;

    state = 0;
    saved_x = tile_x;
    saved_id = object_id;
    saved_y = tile_y;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        state = object + 0x20;
        ((S_8016A878_0 *)object)->unk_10 = D_8016AA58;
        state->unk_13 = 0x10;
        func_8004491C(object, func_80045340);
        object_data = ((S_8016A878_0 *)object)->unk_08;
        object_data->unk_0A = saved_id;
        placement = ((S_8016A878_0 *)object)->unk_0C;
        mode = init_flags & 3;
        placement->unk_25 = saved_y;
        runtime = state;
        placement->unk_2C = &D_8016E20C;
        placement->unk_24 = saved_x;
        if (mode == 1) {
            flags_14 = state->unk_14 | 0x6000;
            flags_1c = state->unk_1C | 0x6000;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (mode >= 2) {
            flags_14 = state->unk_14 | 0x2000;
            flags_1c = state->unk_1C | 0x2000;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    func_800A48F0(state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    placement->unk_2C = &D_8016E25C;
                }
            }
        }
        func_800A9C18(object, object_data, placement, init_flags);
        runtime->unk_9A = 0xFF;
        runtime->unk_9C = -1;
        runtime->unk_8C = &D_8016B014;
        state->unk_1C = (s32)(state->unk_1C | 0x40000);
        runtime->unk_92 = -0x20;
        func_800AA36C(runtime, object_data, placement, state);
    }
    return state;
}

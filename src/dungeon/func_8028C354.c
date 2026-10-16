#include "modules/dungeon_floor_spawns.h"

void createTintedDungeonObject(s16 x, s16 y, s16 tinted, s32 render_param)
{
    u16 flags;
    floor_spawns_isolated_8028C354_S_8001F354_1 *render_state;
    void *object;
    s16 *position;
    s16 *object_data;

    object = func_8003FC64(2);
    if (object != NULL) {
        ((floor_spawns_isolated_8028C354_S_8001F354_0 *)object)->unk_10 = (s32)D_800A5AF0;
        func_8004491C(object, D_80044BB0);
        position = (s16 *)((floor_spawns_isolated_8028C354_S_8001F354_0 *)object)->unk_08;
        position[1] = x + 0x280;
        position[3] = y;
        position[5] = 1;
        render_state = ((floor_spawns_isolated_8028C354_S_8001F354_0 *)object)->unk_0C;
        render_state->unk_1C = 0x2000;
        render_state->unk_1E = 0x1000;
        render_state->unk_08 = render_param;
        if (tinted != 0) {
            render_state->unk_0C = 0x202080;
        } else {
            render_state->unk_0C = 0x808080;
        }
        flags = render_state->unk_14;
        render_state->unk_10 = 0x20;
        object_data = (s16 *)(object + 0x20);
        render_state->unk_14 = flags | 0xC;
        object_data[3] = 0x18;
        object_data[4] = x;
    }
}

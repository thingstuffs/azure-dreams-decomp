/* Relinked copy of dungeon/func_809A35A0 (func_809A35A0.c); retail differs only at relocation sites. */
#include "modules/dungeon_ovl_9c32d4.h"

/* r121_nodonor relink of dungeon/func_809A35A0: symbols this copy binds at other addresses. */
void func_801695A0(u8 *actor_data, u8 *output_data, u8 *effect_data);
void func_801695A0(u8 *actor_data, u8 *output_data, u8 *effect_data);
extern u8 D_80169D7C[12];

void func_8016986C(EntityRec *parent, s32 effect_param, u8 *effect_data)
{
    void *effect;
    ovl_9c32d4_809A35A0_S_80174DA0_2 *position;
    ovl_9c32d4_809A35A0_S_80174DA0_3 *display;
    ovl_9c32d4_809A35A0_S_80174DA0_4 *state;
    void *parent_position;
    u16 coordinate;

    effect = func_8003FD64(0x12, parent);
    if (effect != 0) {
        ((ovl_9c32d4_809A35A0_S_80174DA0_0 *)effect)->unk_10 = func_801695A0;
        position = ((ovl_9c32d4_809A35A0_S_80174DA0_0 *)effect)->unk_08;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_02;
        position->unk_0E = coordinate;
        position->unk_02 = coordinate;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_06;
        position->unk_12 = coordinate;
        position->unk_06 = coordinate;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_0A;
        position->unk_16 = coordinate;
        position->unk_0A = coordinate;

        display = ((ovl_9c32d4_809A35A0_S_80174DA0_0 *)effect)->unk_0C;
        display->unk_08 = D_80169D7C;
        display->unk_1E = 0x1000;
        display->unk_1C = 0x1000;
        display->unk_0C = 0;
        display->unk_06 = 8;

        parent_position = (*(void * *)&parent->z);
        state = (u8 *)effect + 0x20;
        state->unk_0C = effect_param;
        state->unk_10 = effect_data;
        state->unk_1C = parent_position;
        state->unk_16 = *effect_data;
        ((ovl_9c32d4_809A35A0_S_80174DA0_0 *)effect)->unk_20 = 0x40;
        state->unk_04 = 0;
    }
}

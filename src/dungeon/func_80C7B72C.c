/* Relink of matched dungeon/func_80BC172C; every changed retail word is a paired relocation. */
#define dungeonSpawnParentOffsetRandomMotionEffect func_8015EF2C
#define func_80170884 func_8015E884
#include "modules/dungeon_ovl_be1084.h"
extern void func_8015EBFC(void *, void *);
extern s32 rand(void);

void func_8015EF2C(void *parent_arg, register s16 effect_param_arg, register s32 state_value_arg,
    register s32 unused_arg, register s32 offset_x_arg, register s32 offset_y_arg, register s32 offset_z_arg) {
    register void *parent = parent_arg;
    register s16 effect_param = effect_param_arg;
    register s32 state_value = state_value_arg;
    register s32 offset_x = offset_x_arg;
    register s32 offset_y = offset_y_arg;
    register s32 offset_z = offset_z_arg;
    S_80BC172C_1 *effect_data;
    void *effect;
    u16 parent_x;

    effect = func_8003FD64(0x211, parent);
    if (effect != NULL) {
        ((S_80BC172C_0 *)effect)->unk_10 = func_8015EBFC;
        do {
            parent_x = ((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_02;
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_02 = (s16) (parent_x + offset_x);
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_06 =
                (s16) (((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_06 + offset_y);
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_0A =
                (s16) ((((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_0A + offset_z) - 0x64);
        } while (0);
        ((S_80BC172C_6 *)(((S_80BC172C_3 *)effect)->unk_0C))->unk_06 = 6;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data = effect + 0x20;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_14 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data->unk_14 = effect_param;
        effect_data->unk_32 = 5;
        effect_data->unk_34 = 5;
        func_8004491C(effect, func_8015E884);
        ((S_80BC172C_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}

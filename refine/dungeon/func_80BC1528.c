#include "common.h"

typedef struct S_80BC1528_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC1528_0;   /* obj in func_80BC1528 */

typedef struct S_80BC1528_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80BC1528_1;   /* saved_arg0 in func_80BC1528 */

typedef struct S_80BC1528_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80BC1528_2;   /* tail in func_80BC1528 */

typedef struct S_80BC1528_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80BC1528_3;   /* ((S_80BC1528_0 *)obj)->unk_08 in func_80BC1528 */

typedef struct S_80BC1528_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80BC1528_4;   /* ((S_80BC1528_1 *)saved_arg0)->unk_08 in func_80BC1528 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C();
extern u8 D_80170884[];
extern u8 D_80170A64[];

/* Creates an offset effect and initializes its motion back toward the parent. */
void func_80BC1528(
    void *parent_obj, s16 effect_param, s32 initial_value, s32 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    S_80BC1528_1 *parent = parent_obj;
    register s16 saved_param ASM_REG("$23") = effect_param;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 saved_value = initial_value;
    register s32 saved_duration ASM_REG("$22") = duration;   /* MATCH pin: load-bearing for the whole function shape */
    s32 saved_offset_x = offset_x;
    s32 saved_offset_y = offset_y;
    s32 saved_offset_z = offset_z;
    register void *effect ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_80BC1528_2 *effect_data;
    register s32 duration_s16;
    register s32 duration_eighth ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 return_delta_x;
    register s32 return_delta_y ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 step_x;
    register s32 step_y ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 step_z;
    s32 rounded_step_x;
    register s32 rounded_step_y ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 rounded_step_z;

    effect = func_8003FD64(0x211, parent);
    if (effect != 0) {
        ((S_80BC1528_0 *)effect)->unk_10 = D_80170A64;

        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_02 =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_02 + saved_offset_x;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_06 =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_06 + saved_offset_y;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_0A =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_0A + saved_offset_z - 100;

        effect_data = (u8 *)effect + 0x20;
        effect_data->unk_36 = ((S_80BC1528_4 *)(parent->unk_08))->unk_02;
        effect_data->unk_38 = ((S_80BC1528_4 *)(parent->unk_08))->unk_06;
        effect_data->unk_3A = ((S_80BC1528_4 *)(parent->unk_08))->unk_0A;

        duration_s16 = (s16)saved_duration;
        duration_eighth = duration_s16;
        return_delta_x = -(saved_offset_x << 16);
        if (duration_s16 < 0) {
            duration_eighth = duration_s16 + 7;
        }
        duration_eighth >>= 3;

        step_x = return_delta_x / duration_eighth;
        effect_data->unk_40 = step_x / 2;
        ASM_KEEP(step_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        return_delta_y = -(saved_offset_y << 16);
        step_y = return_delta_y / duration_eighth;
        effect_data->unk_44 = step_y / 2;
        ASM_KEEP(step_y);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        step_z = -(saved_offset_z << 16) / duration_eighth;
        effect_data->unk_48 = step_z / 2;

        rounded_step_x = step_x;
        ASM_KEEP(rounded_step_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (rounded_step_x < 0) {
            rounded_step_x += 3;
        }
        effect_data->unk_4C = rounded_step_x >> 2;

        rounded_step_y = step_y;
        if (rounded_step_y < 0) {
            rounded_step_y += 3;
        }
        effect_data->unk_50 = rounded_step_y >> 2;

        rounded_step_z = step_z;
        if (rounded_step_z < 0) {
            rounded_step_z += 3;
        }
        effect_data->unk_54 = rounded_step_z >> 2;

        effect_data->unk_14 = saved_param;
        effect_data->unk_32 = saved_duration;
        func_8004491C(effect, D_80170884, step_x);
        ((S_80BC1528_0 *)effect)->unk_20 = saved_value;
        effect_data->unk_08 = saved_value;
    }

    ASM_KEEP(saved_param);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(saved_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(saved_duration);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(saved_offset_x);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(saved_offset_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(saved_offset_z);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
}

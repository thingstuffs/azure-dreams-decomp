#include "common.h"


extern u8 D_80083498[];
extern u8 D_80045340[];
extern s32 D_8014CA58;
extern s32 D_8014D014;
extern s32 D_8015020C;
extern s32 D_8015025C;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();


typedef struct S_8014C878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_8014C878_0;   /* temp_v0 in func_8014C878 */

typedef struct S_8014C878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8014C878_1;   /* var_s0 in func_8014C878 */

typedef struct S_8014C878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C878_2;   /* temp_s4 in func_8014C878 */

typedef struct S_8014C878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    s32 * unk_2C;
} S_8014C878_3;   /* temp_s2 in func_8014C878 */

typedef struct S_8014C878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C878_4;   /* temp_s5 in func_8014C878 */

void *func_8014C878(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 temp_v1;
    s32 state_flags0;
    s32 state_flags1;
    S_8014C878_3 *temp_s2;
    S_8014C878_2 *temp_s4;
    void *temp_v0;
    S_8014C878_4 *temp_s5;
    S_8014C878_1 *var_s0;
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    var_s0 = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 == 0) {
        goto done;
    }
    var_s0 = temp_v0 + 0x20;
    ((S_8014C878_0 *)temp_v0)->unk_10 = &D_8014CA58;
    var_s0->unk_13 = 0x10;
    func_8004491C(temp_v0, D_80045340);
    temp_s4 = ((S_8014C878_0 *)temp_v0)->unk_08;
    temp_s4->unk_0A = saved_arg3;
    temp_s2 = ((S_8014C878_0 *)temp_v0)->unk_0C;
    temp_v1 = arg0 & 3;
    temp_s2->unk_25 = saved_arg2;
    temp_s5 = var_s0;
    temp_s2->unk_2C = &D_8015020C;
    temp_s2->unk_24 = saved_arg1;
    if (temp_v1 == 1) {
        state_flags0 = var_s0->unk_14 | 0x6000;
        state_flags1 = var_s0->unk_1C | 0x6000;
        var_s0->unk_14 = state_flags0;
        var_s0->unk_1C = state_flags1;
    } else if (temp_v1 >= 2) {
        state_flags0 = var_s0->unk_14 | 0x2000;
        state_flags1 = var_s0->unk_1C | 0x2000;
        var_s0->unk_14 = state_flags0;
        var_s0->unk_1C = state_flags1;
    } else if (((arg0 & ~3) << 0x10) == 0) {
        register void *call_a0 ASM_REG("$4") = temp_v0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        if (!(var_s0->unk_14 & 0x200)) {
            if (func_800A6D30(call_a0) & 1) {
                func_800A48F0(var_s0, 1, (func_800A6D30(call_a0) & 0x3F) | 0x20);
                temp_s2->unk_2C = &D_8015025C;
            }
        }
    }
    func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
    temp_s5->unk_9A = 0xFF;
    temp_s5->unk_9C = -1;
    temp_s5->unk_8C = &D_8014D014;
    var_s0->unk_1C = (s32)(var_s0->unk_1C | 0x40000);
    temp_s5->unk_92 = -0x20;
    func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
done:
    return var_s0;
}

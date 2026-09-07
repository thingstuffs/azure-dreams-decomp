#include "common.h"





#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80048FBC();
s32 func_80049004();
s32 func_800491CC();
extern s32 D_8002E5E8[];

typedef struct S_800B44F0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x10];
    s32 unk_5C;
} S_800B44F0_0;   /* arg0 in func_800B44F0 */

typedef struct S_800B44F0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800B44F0_1;   /* temp_v1 in func_800B44F0 */

/* Initializes state data, applies defaults, and reports initialization success. */
s32 func_800B44F0(void *state, s32 input)
{
    s32 *defaults;
    s32 state_data;
    s32 setup_result;
    s32 init_result;
    s32 success;

    success = 0;
    state_data = state + 0x60;
    setup_result = func_80049004(state_data, input, 0xC);
    ((S_800B44F0_0 *)state)->unk_5C = setup_result;
    if (setup_result != 0) {
        register s32 call_arg ASM_REG("$4") = setup_result;   /* MATCH pin: load-bearing for the whole function shape */

        ASM_KEEP(call_arg);   /* MATCH pin: load-bearing for the whole function shape */
        defaults = D_8002E5E8;
        ((S_800B44F0_0 *)state)->unk_40 = D_8002E5E8[0];
        ((S_800B44F0_0 *)state)->unk_44 = ((S_800B44F0_1 *)defaults)->unk_04;
        ((S_800B44F0_0 *)state)->unk_48 = ((S_800B44F0_1 *)defaults)->unk_08;
        func_800491CC(call_arg, state + 0x40, 0x21);
        init_result = func_80048FBC(state_data, 0xC);
        success = init_result != 0;
        ((S_800B44F0_0 *)state)->unk_20 = init_result;
    }
    return success;
}

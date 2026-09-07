#include "common.h"
#include "m2c_compat.h"

void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
void func_80175F44(void *, s32, void *, s32, s32);
extern s32 D_80083460;

typedef struct S_80172BB0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172BB0_0;   /* arg3 in func_80172BB0 */

typedef struct S_80172BB0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172BB0_1;   /* arg2 in func_80172BB0 */

typedef struct S_80172BB0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x19];
    u8 unk_B5;
} S_80172BB0_2;   /* arg0 in func_80172BB0 */

s32 func_80172BB0(S_80172BB0_2 *arg0, M2C_UNK arg1, S_80172BB0_1 *arg2, void *arg3) {
    s32 temp_v0;
    s32 var_v0;
    register u16 *global ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */

    {
        register s32 history ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        history = ((S_80172BB0_0 *)arg3)->unk_71;
        history &= 0x7F;
        ((S_80172BB0_0 *)arg3)->unk_71 = history;
    }
    {
        register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        global = (u16 *)(page + 0x3460);
    }
    var_v0 = 0;
    if (global[1] & 0x2000) {
        return -1;
    }

    temp_v0 = func_800A04F0(arg3, arg2->unk_24,
        arg2->unk_25, ((S_80172BB0_0 *)arg3)->unk_2A);
    if ((func_800A2CB8(arg3, temp_v0) << 0x10) == 0) {
        return var_v0;
    }

    if (global[1] & 0x2000) {
        return -1;
    }
    if (!(((S_80172BB0_0 *)arg3)->unk_46 & 0x8000) && (global[1] & 8)) {
        return -1;
    }
    if ((u32)(((0 - func_800A0134(temp_v0, arg3)) + 0x40) & 0xFFFF) <
            0x81U) {
        var_v0 = 1;
        if ((func_800A2B5C(arg3) << 0x10) != 0) {
            return -1;
        }
        func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) != 0) {
            return -1;
        }

        arg0->unk_9B = 0;
        if (arg0->unk_B5 == 0) {
            arg0->unk_9A = 0x11;
            arg0->unk_8C = 0;
            ((S_80172BB0_0 *)arg3)->unk_84 = 0x7C;
            ((S_80172BB0_0 *)arg3)->unk_85 = 0;
            arg0->unk_98 =
                (u16)(arg0->unk_98 | 8);
            func_8009C93C(arg3, arg2, ((S_80172BB0_0 *)arg3)->unk_2A, 1, 0);
            ((S_80172BB0_0 *)arg3)->unk_6D--;
        } else {
            register s32 one ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

            one = 1;
            func_80175F44(arg0, arg1, arg2, one, one);
        }
    }
    ASM_KEEP(var_v0);   /* MATCH pin: retail register colouring depends on it */
    return var_v0;
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"

void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
void func_80175F44(void *, s32, void *, s32, s32);
extern s32 D_80083460;




s32 func_80172BB0(Rec_func_800A9E70_arg0 *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2, void *arg3) {
    s32 temp_v0;
    s32 var_v0;
    register u16 *global ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */

    {
        register s32 history ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        history = ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8;
        history &= 0x7F;
        ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = history;
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
        arg2->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);
    if ((func_800A2CB8(arg3, temp_v0) << 0x10) == 0) {
        return var_v0;
    }

    if (global[1] & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) && (global[1] & 8)) {
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

        arg0->unk_9B.as_s8 = 0;
        if (arg0->unk_B5 == 0) {
            arg0->unk_9A.as_s8 = 0x11;
            arg0->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
            arg0->unk_98 =
                (u16)(arg0->unk_98 | 8);
            func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
        } else {
            register s32 one ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

            one = 1;
            func_80175F44(arg0, arg1, arg2, one, one);
        }
    }
    ASM_KEEP(var_v0);   /* MATCH pin: retail register colouring depends on it */
    return var_v0;
}

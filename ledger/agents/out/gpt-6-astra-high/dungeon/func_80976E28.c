#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
M2C_UNK func_80171C34(); /* extern */
extern u16 D_80083462;

typedef struct S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172628_0;   /* hold_arg0 in func_80172628 */

/* Update entity state and flags according to the state query result. */
s32 func_80172628(void *entity_arg, M2C_UNK primary_context_arg, M2C_UNK secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    register s32 result ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    M2C_UNK primary_context = primary_context_arg;
    M2C_UNK secondary_context = secondary_context_arg;
    register s32 force_state ASM_REG("$19") = force_state_arg;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *entity = entity_arg;

    result = func_800ADDA0(primary_context, secondary_context, entity, 3, 6, entity + 0x9C);
    result <<= 0x10;
    state_type = result >> 0x10;
    {
        result = 0;
        if (state_type < 0) {
            goto done;
        }
        if ((force_state << 0x10) != 0) {
            goto call_state;
        }
        ASM_KEEP(force_state);   /* MATCH pin: keeps a statement from moving across a call/branch */
        if (state_type == 1) {
            goto type_one;
        }
        if (state_type >= 2) {
            goto type_ge_two;
        }
        if (state_type == 0) {
            goto type_zero;
        }
        goto reset_state;

    type_ge_two:
        if (state_type == 2) {
            goto call_state;
        }
        goto reset_state;

    type_zero:
        ((S_80172628_0 *)entity)->unk_9A = 0xE;
        func_800A9A0C(entity);
        result = 0;
        goto done;

    call_state:
        func_80171C34(entity, primary_context, secondary_context, entity);
        ASM_KEEP(primary_context);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(secondary_context);   /* MATCH pin: retail schedule: same instructions, different order without it */
        result = 0;
        goto done;

    type_one:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((func_800A2BDC(entity) << 0x10) != 0) {
            goto clear_state;
        }
    reset_state:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((D_80083462 & 8) == 0) {
            result = 1;
            goto done;
        }
    clear_state:
        result = 0;
        ((S_80172628_0 *)entity)->unk_46 = (u16) (((S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    done:
        return result;
    }
}

/* MECHANISM: The 0x80172714/0x8017274c words are true-space local joins,
   so shared labels replace the seed's phantom calls and preserve retail block order.
   Guarded arg pins fix s1/s2/s3/s0; a v0 return local fills both zero delay slots. */

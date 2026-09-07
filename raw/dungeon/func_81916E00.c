#include "common.h"

typedef s32 M2C_UNK;
typedef struct Copy24 {
    s32 words[6];
} Copy24;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800246F4(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FD64();
M2C_UNK func_8004491C();
extern M2C_UNK D_8002457C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC50;

void *func_80024600(s32 *arg0, Copy24 *arg1) {
    s32 temp_arg0;
    void *temp_s0;
    void *temp_v0;
    Copy24 *temp_v1;

    temp_v0 = func_8003FD64(0x212, (s8 *) arg0 - 0x20);
    if (temp_v0 == NULL) {
        register s32 tail_result ASM_REG("$2") = 0;

        ASM_TAILSLOT_PIN_TIED(tail_result);
        func_800246F4();
        return NULL;
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8002457C;
    temp_arg0 = *arg0;
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, s16 *, 0x24) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = temp_arg0;
    M2C_FIELD(temp_s0, s32 *, 0xC) = 0x808080;
    M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
    M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x60);
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
    func_8003DB94(temp_s0, &D_800DEC50, 0);
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = M2C_FIELD(temp_v0, Copy24 **, 8);
    *temp_v1 = *arg1;
    return temp_v0;
}

/* MECHANISM: The seed already matched the 0x20 frame and s0/s2/s1 save order.
   A guarded tied $v0 zero stays live on the noreturn failure edge.
   LEAD 28 sinks its move into the converted j delay slot, closing word 14. */

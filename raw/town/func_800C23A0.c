#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[12];
extern u16 D_80083780[6];
extern void func_800BFB8C(void);

void func_800BFB00(s16 arg0, s16 arg1) {
    u16 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v0 = func_8003FD64(2, D_80083498);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, void (**)(void), 0x10) = func_800BFB8C;
        M2C_FIELD(temp_v0, u16 *, 0x20) = D_80083780[1];
        temp_a0 = (s8 *)temp_v0 + 0x20;
        M2C_FIELD(temp_a0, volatile u16 *, 2) = D_80083780[3];
        temp_v1 = D_80083780[5];
        M2C_FIELD(temp_a0, s16 *, 8) = arg0;
        M2C_FIELD(temp_a0, s16 *, 0xA) = arg1;
        M2C_FIELD(temp_a0, s16 *, 0xE) = 6;
        M2C_FIELD(temp_a0, volatile u16 *, 4) = temp_v1;
    }
}

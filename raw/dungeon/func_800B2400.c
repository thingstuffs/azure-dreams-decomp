#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    u8 pad[0xA];
    u16 value;
} Counter;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern M2C_UNK func_800B8024();
extern Counter D_80083460;
extern M2C_UNK D_800B7774;

void *func_800B7B60(void *arg0, s32 *arg1) {
    u16 temp_a2;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800B7774;
        M2C_FIELD(temp_v0, s32 *, 0x20) = *arg1;
        temp_a1 = M2C_FIELD(arg0, void **, -0x18);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = M2C_FIELD(temp_a1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = M2C_FIELD(temp_a1, u16 *, 6);
        temp_a2 = M2C_FIELD(temp_a1, u16 *, 0xA);
        M2C_FIELD(temp_v1, u16 *, 0xA) = temp_a2;
        func_800B8024((s16) M2C_FIELD(temp_v1, u16 *, 2), (s16) M2C_FIELD(temp_v1, u16 *, 6), (s16) temp_a2);
        D_80083460.value++;
    }
    return temp_v0;
}

#include "common.h"

typedef struct {
    u8 pad_000[0xC8];
    s16 field_C8;
} State80083160;

extern State80083160 D_80083160;
extern void func_800909A0();
extern void func_80090A54(void) __attribute__((noreturn));

void func_80090A04(void *arg0) {
    s16 value = *(s16 *)((u8 *)arg0 + 6);
    State80083160 *state = &D_80083160;

    if (value < 0x200) {
        state->field_C8 = 0;
        func_80090A54();
    }
    if (value < 0x300) {
        func_800909A0(state);
        func_800909A0();
    }
    func_800909A0();
    func_800909A0();
}

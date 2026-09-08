#include "common.h"

typedef struct {
    u8 pad_000[0xC8];
    s16 field_C8;
} State80083160;

extern State80083160 D_80083160;
extern void func_800909A0();

/* Clear the state field or invoke updates according to the record value. */
void func_80090A04(void *record) {
    s16 threshold_value = *(s16 *)((u8 *)record + 6);
    State80083160 *state = &D_80083160;

    if (threshold_value < 0x200) {
        state->field_C8 = 0;
        return;
    }
    if (threshold_value < 0x300) {
        func_800909A0(state);
        func_800909A0();
    }
    func_800909A0();
    func_800909A0();
}

#include "common.h"

#include "common.h"

typedef struct Func80037C7CState {
    s32 *field00;
    u8 pad04[0x08];
    s16 field0C;
    u8 pad0E[0x02];
    u16 field10;
    u8 pad12[0x06];
    u16 field18;
    u8 pad1A[0x0A];
    s16 field24;
    u8 pad26[0x02];
    s16 field28;
    u8 pad2A[0x02];
    u16 field2C;
    u8 pad2E[0x06];
    u16 field34;
    u8 pad36[0x0A];
    s16 field40;
} Func80037C7CState;

void func_80037C7C(Func80037C7CState *arg0, s32 arg1) {
    s16 value = (s16)arg1;
    s32 original = arg1;

    arg0->field00[4] = value;
    if (value >= 0x37) {
        arg0->field0C = -0x38;
        arg0->field10 = 0x30;
    } else {
        arg0->field0C = -original - 2;
        arg0->field10 = original - 6;
        if ((s16)arg0->field10 <= 0) {
            arg0->field10 = 1;
        }
    }

    if ((s16)original < 0x36) {
        arg0->field24 = -original + 0x36;
    } else {
        arg0->field24 = 0;
    }

    arg1 = -original;
    arg0->field18 = arg0->field10;
    arg0->field28 = arg1 - 3;
    arg0->field2C = original + 6;
    if ((s16)arg0->field2C <= 0) {
        arg0->field2C = 1;
    }
    if ((s16)original < 0x40) {
        arg0->field40 = arg1 + 0x40;
    } else {
        arg0->field40 = 0;
    }
    arg0->field34 = arg0->field2C;
}

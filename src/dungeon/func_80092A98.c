#include "common.h"

typedef struct {
    u8 pad0[0x4C];
    void *unk4C;
    u8 pad50[0x35];
    u8 unk85;
} Unk80092A98;

s16 func_800981F8(Unk80092A98 *arg0) {
    s16 value;
    u8 byte;

    value = arg0->unk85;
    if (arg0->unk4C != 0) {
        byte = *((u8 *)arg0->unk4C + 2);
        value += (s8)byte;
    }
    if (value < 0) {
        value = 0;
    }
    if (value >= 100) {
        value = 99;
    }
    return value;
}

#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x44];
    u8 *data;
    u8 pad48[2];
    s16 offset;
    u8 pad4c[0x1c];
    void (*callback)(void);
} FuncState;

typedef struct {
    u16 pad00;
    u16 value;
} FuncValue;

extern void func_80035D38(void);

void func_80035CE4(FuncState *arg0, FuncValue *arg1) {
    u16 value;

    value = arg1->value - 0x20;
    arg1->value = value;
    if ((s16)value < 2) {
        u8 *data;
        s16 offset;

        arg1->value = 2;
        arg0->callback = func_80035D38;
        data = arg0->data;
        offset = arg0->offset;
        *(data + offset + 0x50) = 1;
    }
}

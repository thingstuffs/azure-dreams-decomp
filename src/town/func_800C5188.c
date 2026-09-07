#include "common.h"

typedef struct {
    void *value;
    void *pad[2];
} PointerGlobal;

typedef struct {
    u32 value;
    s32 pad[2];
} FlagGlobal;

extern s32 func_800352FC(void);
extern void func_8008F134(void *arg0);

extern PointerGlobal D_800FE4A0;
extern PointerGlobal D_800834B8;
extern u8 D_80097D2C[12];
extern FlagGlobal D_800814A0;

void func_800C28E8(void *arg0) {
    void *object;

    if (func_800352FC() != 0) {
        object = D_800FE4A0.value;
        if (object == arg0 && D_800834B8.value == D_80097D2C) {
            func_8008F134(object);
            ((u16 *) object)[-1] |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
}

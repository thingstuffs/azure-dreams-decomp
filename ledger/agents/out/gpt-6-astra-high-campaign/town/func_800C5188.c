#include "common.h"

typedef struct {
    void *value;
    void *pad[2];
} PointerGlobal;

typedef struct {
    u32 value;
    s32 pad[2];
} FlagGlobal;

extern s32 func_800352FC(void *, s32, s32, s32);
extern void func_8008F134(void *arg0);

extern PointerGlobal D_800FE4A0;
extern PointerGlobal D_800834B8;
extern u8 D_80097D2C[12];
extern FlagGlobal D_800814A0;

/* Update the current object and set its and the global flags when the request succeeds. */
void func_800C28E8(void *object, s32 request_data, s32 request_param, s32 check_param) {
    void *current_object;

    if (func_800352FC(object, request_data, request_param, check_param) != 0) {
        current_object = D_800FE4A0.value;
        if (current_object == object && D_800834B8.value == D_80097D2C) {
            func_8008F134(current_object);
            ((u16 *) current_object)[-1] |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
}

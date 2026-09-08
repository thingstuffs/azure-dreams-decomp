#include "common.h"

typedef struct {
    u8 pad00[0x4C];
    s32 unk4C;
    u8 pad50[0x6C - 0x50];
    s32 unk6C[3];
    u8 pad78[0x88 - 0x78];
    s32 unk88;
    s32 unk8C[7];
} Unk818110CC;

extern s32 func_80049004(s32 *arg0, s32 arg1, s32 arg2);
extern s32 func_80048FBC(s32 *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, s32 *arg1, s32 arg2);
extern s32 D_8002E5E8[3];

/* Allocates object buffers and links them to the initialized three-word state. */
s32 func_80028284(Unk818110CC *object, s32 buffer_param)
{
    s32 success = 0;
    s32 *buffers = object->unk8C;
    s32 allocated_buffer;

    allocated_buffer = func_80049004(buffers, buffer_param, 8);
    object->unk88 = allocated_buffer;
    if (allocated_buffer != 0) {
        allocated_buffer = func_80048FBC(buffers, 8);
        object->unk4C = allocated_buffer;
        if (allocated_buffer != 0) {
            object->unk6C[0] = D_8002E5E8[0];
            object->unk6C[1] = D_8002E5E8[1];
            object->unk6C[2] = D_8002E5E8[2];
            func_800491CC(object->unk88, object->unk6C, 15);
            success = 1;
        }
    }
    return success;
}

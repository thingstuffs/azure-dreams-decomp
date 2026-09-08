#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void func_800C170C(s32 arg0);
extern s32 func_800C2124(void);
extern Position D_80083780;


typedef struct S_800C21F8_0 {
    void (*unk_00)(void);
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800C21F8_0;   /* arg0 in func_800C21F8 */

/* Switches the object callback when its distance from the global position exceeds either limit. */
s32 func_800C21F8(S_800C21F8_0 *object) {
    s32 y_distance;
    register s32 x_distance ASM_REG("$2");
    register s32 axis_delta ASM_REG("$3");

    x_distance = object->unk_04;
    axis_delta = D_80083780.x;
    y_distance = D_80083780.y;
    x_distance -= axis_delta;
    if (x_distance < 0) {
        x_distance = 0 - x_distance;
    }
    axis_delta = object->unk_06;
    x_distance = (s32)((u32)x_distance << 16);
    axis_delta -= y_distance;
    y_distance = axis_delta;
    if (axis_delta < 0) {
        y_distance = 0 - y_distance;
    }
    if ((object->unk_0C < (x_distance >> 16)) ||
        ((s16)y_distance > object->unk_0E)) {
        func_800C170C(y_distance);
        object->unk_00 = (void (*)(void))func_800C2124;
        
        return 1;
    }
    return 0;
}


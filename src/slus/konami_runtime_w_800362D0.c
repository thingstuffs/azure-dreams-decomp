#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void);

extern u8 D_80082040[];
extern u8 D_80082538[];

extern void func_80036ED4(void *arg0, void *arg1, s32 *arg2, s16 arg3,
                          s16 arg4, s32 arg5);
extern void func_80036350(void);

void func_800362D0(void *arg0) {
    u32 child;
    u8 field_27;
    u8 field_26;
    s16 offset;

    child = FIELD(arg0, u32, 0x74);
    field_27 = FIELD((void *)child, u8, 0x27);
    field_26 = FIELD((void *)child, u8, 0x26);
    child = FIELD((void *)child, u16, 0x22);
    offset = child - (field_26 - 1);
    FIELD(arg0, u8, 0x4D) = field_27;

    func_80036ED4(D_80082538, D_80082040, arg0, 1, offset,
                  FIELD(FIELD(arg0, void *, 0x74), s32, 0x80));
    FIELD(arg0, Callback, 0x68) = func_80036350;
}

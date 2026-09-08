#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void);

extern u8 D_80082040[];
extern u8 D_80082538[];

extern void func_80036ED4(void *arg0, void *arg1, s32 *arg2, s16 arg3,
                          s16 arg4, s32 arg5);
extern void func_80036350(void);

/* Initializes the object from its child data and sets the next callback. */
void func_800362D0(void *object) {
    u32 child_or_index;
    u8 child_byte;
    u8 index_base;
    s16 index_offset;

    child_or_index = FIELD(object, u32, 0x74);
    child_byte = FIELD((void *)child_or_index, u8, 0x27);
    index_base = FIELD((void *)child_or_index, u8, 0x26);
    child_or_index = FIELD((void *)child_or_index, u16, 0x22);
    index_offset = child_or_index - (index_base - 1);
    FIELD(object, u8, 0x4D) = child_byte;

    func_80036ED4(D_80082538, D_80082040, object, 1, index_offset,
                  FIELD(FIELD(object, void *, 0x74), s32, 0x80));
    FIELD(object, Callback, 0x68) = func_80036350;
}

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void *func_8004B404(s32);
extern void func_8004B1A4(void *);
extern void func_800B1B70(void *);
extern void *func_800B1938(void *);
extern void func_800B1B10(void *, s32, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_800B1CD8(void) __attribute__((noreturn));
extern void func_800B1890(void);

extern u8 D_8004CAA0[];
extern u32 D_800814A0;

void *func_800B1BEC(s32 arg0, s32 arg1, s32 arg2)
{
    void *object;
    void *part;
    void *second;
    u16 flags;
    u32 global_flags;

    object = func_8003FC64(0);
    if (object != 0) {
        part = (u8 *)object + 0x20;
        FIELD(part, void *, 8) = func_8004B404(0xCC);
        second = func_8004B404(0xCC);
        FIELD(part, void *, 0xC) = second;

        if (FIELD(part, void *, 8) != 0 && second != 0) {
            FIELD(object, void *, 0xC) = (u8 *)object + 0x58;
            func_800B1B70(part);
            FIELD(part, void *, 0x44) = func_800B1938((u8 *)object + 0x68);
            func_800B1B10(part, arg0, arg1, arg2);
            func_8004491C(object, D_8004CAA0);
            FIELD(object, void *, 0x10) = func_800B1890;
            func_800B1CD8();
        }

        func_8004B1A4(FIELD(part, void *, 8));
        func_8004B1A4(FIELD(part, void *, 0xC));
        flags = FIELD(object, u16, 0x1E) | 0x8000;
        global_flags = D_800814A0 | 0x8000;
        FIELD(object, u16, 0x1E) = flags;
        D_800814A0 = global_flags;
    }
    return object;
}

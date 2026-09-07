#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008D330(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80098B38(s32 arg0);
extern void func_800997FC(void *arg0);
extern void func_800A5F38(void *arg0, s32 arg1);
extern void func_800A63B8(void *arg0, s32 arg1, s16 arg2);
extern s32 func_800AD6FC(void *arg0, s32 arg1, s32 arg2);
extern void func_800BD854(void);
extern void func_800C4AFC(s32 arg0, s32 arg1, void *arg2);

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E0E9B[];
extern void *D_800E3D7C;

s32 func_800BD72C(void *arg0, s32 arg1, s16 arg2)
{
    if (arg0 == D_800E3D7C) {
        FIELD(arg0, s32, 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800BD854();
        return 0;
    }

    if ((s32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(
                arg0, (D_800DDE84[FIELD(arg0, u8, 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BD854();
            return 1;
        }
    }

    func_800C4AFC(FIELD(arg0, s32, -0x18), 0xC0C0C0, arg0);
    if ((FIELD(arg0, s32, 0x14) & 0x4000) &&
        !(FIELD(arg0, s32, 0x1C) & 0x200)) {
        func_800997FC(D_800E0E9B);
    }
    func_80042B68(arg0, 1);
    func_80098B38(arg1);
    D_80083460.fieldA--;
    return 1;
}

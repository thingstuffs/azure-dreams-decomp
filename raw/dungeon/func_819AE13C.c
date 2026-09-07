#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_80064AE0(void *);
extern void func_80064B90(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065AB0(u16, void *);
extern void func_80065C50(u16, void *);
extern void func_80065DF0(u16, void *);

void func_8002593C(void *arg0, void *arg1, void *arg2)
{
    u8 *scratch = (u8 *)0x1F800000;
    MATRIX matrix;

    FIELD(scratch, s32, 0x40) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x44) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x48) = FIELD(arg1, s16, 0xA);
    func_80064AE0(&matrix);

    FIELD(scratch, s16, 0x50) = FIELD(scratch, s16, 0x58) =
        FIELD(scratch, s16, 0x60) = 0x1000;
    FIELD(scratch, s16, 0x52) = FIELD(scratch, s16, 0x54) =
        FIELD(scratch, s16, 0x56) = FIELD(scratch, s16, 0x5A) =
        FIELD(scratch, s16, 0x5C) = FIELD(scratch, s16, 0x5E) = 0;

    func_80065AB0(FIELD(arg2, u16, 0x16), scratch + 0x50);
    func_80065DF0(FIELD(arg2, u16, 0x1A), scratch + 0x50);
    func_80065C50(FIELD(arg2, u16, 0x18), scratch + 0x50);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80064840(scratch + 0x50, arg0, scratch + 0xD0);
    func_80064D80(scratch + 0xD0);
    func_80064CF0(scratch + 0xD0);
}

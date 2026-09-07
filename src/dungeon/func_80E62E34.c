#include "common.h"

typedef struct {
    u8 pad00[0x1E];
    s16 field1E;
    u8 pad20[0x0C];
    u8 *field2C;
} Obj;

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
} Other;

typedef struct {
    u8 pad00[0x9A];
    s8 field9A;
    s8 field9B;
    u8 pad9C[2];
    s16 field9E;
} First;

extern s16 D_80083228[];
extern u8 D_8017556C[];
extern void func_80047784(Obj *, u8, s32);

void func_80172634(First *arg0, s32 arg1, Obj *arg2, Other *arg3)
{
    arg0->field9A = 0x10;
    arg0->field9B = 0;
    arg0->field9E = 2;
    arg2->field2C = D_8017556C;
    func_80047784(arg2,
                  D_8017556C[((D_80083228[0] + arg3->field2A + 0x100) >> 9) & 7],
                  0);
    arg2->field1E = 0xC00;
}

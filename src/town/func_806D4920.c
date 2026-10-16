#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
typedef struct Town654Request { u8 prefix[0x18]; s16 flag_18; } Town654Request;
extern s32 func_8001868C(s32 flag);
extern void func_80018594(s32 flag);
extern void func_800177CC(Town654Request *, s32);

void func_80016920(Town654Request *request, s32 parameter)
{
    if (func_8001868C(0x1455) != 0) func_80018594(request->flag_18);
    func_800177CC(request, parameter);
}

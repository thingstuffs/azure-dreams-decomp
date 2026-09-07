#include "common.h"

extern void func_80016ABC(const char *, const char *, s32, s32);
extern char D_80017568[];
extern char D_80017658[];

void func_806CF0C0(s32 value, s32 unused, s32 line)
{
    (void)unused;
    func_80016ABC(D_80017568, D_80017658, value, line);
}

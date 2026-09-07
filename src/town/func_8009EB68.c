#include "common.h"

extern void func_80053DA8(s32 arg0);
extern void func_8009C648(void *arg0, s32 arg1);
extern void func_8008F134(void *arg0);
extern void func_80033D08(void *arg0);
extern void func_800A0504(s32 arg0);
struct S_800814A0 {
    s32 v;
    s32 pad[2];
};
extern struct S_800814A0 D_800814A0;

void func_8009C2C8(unsigned short *arg0, s32 unused, s32 arg2)
{
    func_80053DA8(0x600);
    func_8009C648(arg0, arg2);
    func_8008F134(arg0);
    func_80033D08(arg0);
    arg0[-1] |= 0x8000;
    D_800814A0.v |= 0x8000;
    func_800A0504(arg2);
}

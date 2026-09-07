#include "common.h"

extern void func_80033C84(s32 arg0);
extern struct { s32 v; s32 pad[0x520]; } D_800814A0;

void func_8008BF0C(void *arg0) {
    s32 temp;
    func_80033C84(*(s32 *)((u8 *) arg0 + 0));
    *(u16 *)((u8 *) arg0 - 2) = (u16) (*(u16 *)((u8 *) arg0 - 2) | 0x8000);
    temp = D_800814A0.v;
    *(s32 *)((u8 *) arg0 - 0x10) = 0;
    D_800814A0.v = (s32) (temp | 0x8000);
}

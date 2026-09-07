#include "common.h"

extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
extern void func_8009539C(void *arg0);
extern void func_8008F664(void *arg0, void *arg1);
extern s32 D_800834B8;
extern void *D_8009BC44;

void func_8009C20C(void *arg0, void *arg1, void *arg2) {
    s32 *p = &D_800834B8;
    s32 temp_v0;

    *(s8 *)((u8 *)arg1 + 0x15) = 1;
    *(s32 *)((u8 *)arg2 + 0xC) = func_800644B8(*(s16 *)((u8 *)p + 0x10)) << 6;
    *(s32 *)((u8 *)arg2 + 0x10) = func_80064584(*(s16 *)((u8 *)p + 0x10)) << 6;
    *(s32 *)((u8 *)arg2 + 0x14) = 0xFFF20000;
    temp_v0 = *(s32 *)((u8 *)(*(void **)((u8 *)p - 0x18)) + 0x14);
    if (temp_v0 < 0) {
        *(s32 *)((u8 *)arg2 + 0x14) = temp_v0 + 0xFFF20000;
    }
    func_8009539C(arg2);
    func_8008F664(arg1, arg2);
    *(void **)((u8 *)arg0 + 0x50) = &D_8009BC44;
}

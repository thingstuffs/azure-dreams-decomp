#include "common.h"

extern void func_8004DDBC(void *arg0, void *arg1, void *arg2);
extern u8 D_80408A30[];

void func_800204C4(void *arg0) {
    void *temp;
    void *addr;

    addr = D_80408A30;
    temp = *(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x60)) + 8);
    *(s16 *)(*(void **)((u8 *)temp + 4) + 8) = 0x40;
    *(s16 *)(*(void **)((u8 *)temp + 4) + 0xA) = 0x20;
    func_8004DDBC((u8 *)arg0 + 4, addr, temp);

    temp = *(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x60)) + 0xC);
    *(s16 *)(*(void **)((u8 *)temp + 4) + 8) = 0xC0;
    *(s16 *)(*(void **)((u8 *)temp + 4) + 0xA) = 0x20;
    func_8004DDBC((u8 *)arg0 + 0x10, addr, temp);
}

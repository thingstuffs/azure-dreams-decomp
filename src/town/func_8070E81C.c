#include "common.h"

typedef void (*TownCallback)(s32, s32);

extern void func_80016CC4(void);
extern void func_8001A7AC(void);
extern s8 D_80016000[];
extern s8 D_8001BCB4[];

s32 func_8001781C(void) {
    func_80016CC4();
    *(void **)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x1C) + 0x40) = D_8001BCB4;
    func_8001A7AC();
    (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0xE, 0x200);
    return 0;
}

#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/sys_flags.h"


extern s16 D_8008146C;

extern void func_800B074C(void);
extern void func_80033AE8(s32 a0);
extern void func_800B8A40(void);
extern void func_800C24FC(void);

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void into_dn_door_jobs(s32 unused, s32 unused_second, s32 unused_third) {
    func_800B074C();
    func_80033AE8(0x16);
    func_800B8A40();
    func_800C24FC();
    D_8008146C = 1;
    D_80082E60.flags16 = 0;
    D_80013714 &= 0xFFF8;
}

#include "common.h"

typedef struct S_80013714 {
    u16 flags;   /* 0x0 */
    u8 pad[8];   /* keep size > 8 to force %hi/%lo addressing */
} S_80013714;

extern S_80013714 D_80013714;
extern s16 D_8008146C;
extern u16 D_80082E76;

extern void func_800B074C(void);
extern void func_80033AE8(s32 a0);
extern void func_800B8A40(void);
extern void func_800C24FC(void);

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void func_800A0EB8(void) {
    func_800B074C();
    func_80033AE8(0x16);
    func_800B8A40();
    func_800C24FC();
    D_8008146C = 1;
    D_80082E76 = 0;
    D_80013714.flags &= 0xFFF8;
}

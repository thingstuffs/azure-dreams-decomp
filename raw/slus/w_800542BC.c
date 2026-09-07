#include "common.h"

#include "common.h"

/* D_80084850 accessed via %hi/%lo (lui+lw/sw); size > 8 forces non-gp. */
extern s32 D_80084850[3];

extern s32 func_800557C8(void);
extern void func_80054788(s32 a0, s32 a1);
extern void func_80054B08(s32 a0, s32 a1);
extern void func_8005500C(s32 a0, s32 a1);
extern void func_8005552C(s32 a0, s32 a1);
extern void func_800543C8(void);
extern void func_800557BC(void);

void func_800542BC(void) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;

    D_80084850[0] += 1;
loop_1:
    temp_v0 = func_800557C8();
    temp_a0 = temp_v0 & 0xFFFF;
    temp_v1 = temp_v0 & 0xF00;
    if (temp_a0 != 0) {
        switch (temp_v1) {
        case 0x0:
            func_80054788(temp_a0, temp_v0);
            break;
        case 0x300:
            func_80054B08(temp_a0, temp_v0);
            break;
        case 0x200:
            func_8005500C(temp_a0, temp_v0);
            break;
        case 0x500:
        case 0x700:
        case 0x800:
        case 0x600:
            func_8005552C(temp_v0 & 0xFFFF, temp_v0);
            break;
        }
        goto loop_1;
    }
    /* void — do not pass temp_a0==0 (that emitted move a0,zero in delay). */
    func_800543C8();
    func_800557BC();
}

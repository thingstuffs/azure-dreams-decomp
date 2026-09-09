#include "common.h"

extern void *func_800A9B2C(s32 arg0, void *arg1);

extern u8 D_8006C894[];
extern u8 D_8006C8F7[];
extern u8 D_8006C982[];
extern u8 D_8006C9E4[];
extern u8 D_800C25C0[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern void *D_80100E38[];

void *func_800A9D74(void *arg0, void *arg1) {
    s32 temp_a0;
    register void *temp_v0 ASM_REG("$2"); /* MATCH: Both store paths use the return-value register. */
    void *temp_v1;

    if ((arg0 != 0) && (arg1 != 0)) {
        if (((*(u8 *)((u8 *)arg1 + 0x14) == 4) ||
             (*(u8 *)((u8 *)arg1 + 0x4D) != 0)) &&
            ((temp_v1 = *(void **)((u8 *)arg0 - 0x10),
              (temp_v1 == D_800C3174)) ||
             (temp_v1 == D_800C321C) ||
             ((temp_v1 == D_800C25C0) &&
              (*(s32 *)((u8 *)arg0 + 0x60) != 0)))) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x60);
            if (temp_a0 == 4) {
                return D_8006C9E4;
            }
            ASM_SCHED_BARRIER(); /* MATCH: Keep the 4/5-arm seam scheduling. */
            if (temp_a0 == 5) {
                if (*(u16 *)((u8 *)arg1 + 0x4C) == 0xB05) {
                    temp_v1 = (void *)0x80100000;
                    temp_v0 = D_8006C8F7;
                } else {
                    temp_v1 = (void *)0x80100000;
                    temp_v0 = D_8006C982;
                }
                *(void **)((u8 *)temp_v1 + 0xE38) = temp_v0;
            } else {
                temp_v0 = func_800A9B2C(temp_a0, (u8 *)arg1 + 0x4C);
                D_80100E38[0] = temp_v0;
                if (temp_v0 == 0) {
                    return 0;
                }
            }
            return D_8006C894;
        }
    }
    return 0;
}

/* MECHANISM: Keep the ra-only 0x18 frame and the three pinned v0 tail values so
   LEAD 22/28 emit retail's tail jumps. A zero-code fence at the 4/5-arm seam
   keeps li v0,5 at word 35 and lets the arm-4 page lui fill word 31. */

#include "common.h"

extern void *func_800A9B2C(s32 arg0, void *arg1);
extern void *func_800A9E2C();
extern void *func_800A9E48();
extern void *func_800A9E58();

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
    void *temp_v0;
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
                register void *result ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                result = (void *)0x80070000;
                ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
                result = (u8 *)result - 0x361C;
                ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800A9E58();
                return result;
            }
            ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
            if (temp_a0 == 5) {
                if (*(u16 *)((u8 *)arg1 + 0x4C) == 0xB05) {
                    register void *result ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                    result = (void *)0x80070000;
                    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
                    result = (u8 *)result - 0x3709;
                    ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_800A9E2C();
                    return result;
                }
                D_80100E38[0] = D_8006C982;
                return func_800A9E48();
            }
            temp_v0 = func_800A9B2C(temp_a0, (u8 *)arg1 + 0x4C);
            D_80100E38[0] = temp_v0;
            if (temp_v0 != 0) {
                register void *result ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                result = (void *)0x80070000;
                ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
                result = (u8 *)result - 0x376C;
                ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800A9E58();
                return result;
            }
        }
    }
    return 0;
}

/* MECHANISM: Keep the ra-only 0x18 frame and the three pinned v0 tail values so
   LEAD 22/28 emit retail's tail jumps. A zero-code fence at the 4/5-arm seam
   keeps li v0,5 at word 35 and lets the arm-4 page lui fill word 31. */

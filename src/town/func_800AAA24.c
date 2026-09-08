#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
s32 func_8004A658();                          /* extern */
void *func_8009C390(); /* extern */
void func_800A8200(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_800A8248();         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A8248;

typedef struct S_800A8184_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800A8184_0;   /* temp_v0 in func_800A8184 */

typedef struct S_800A8184_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
} S_800A8184_1;   /* temp_s0 in func_800A8184 */

typedef struct S_800A8184_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A8184_2;   /* temp_s1 in func_800A8184 */

void func_800A8184(s32 arg0, s32 arg1) {
    s32 temp_s3;
    S_800A8184_1 *temp_s0;
    S_800A8184_2 *temp_s1;
    void *temp_v0;
    register s32 held_arg1 ASM_REG("$18") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8009C390(0, 0, &D_800A8248, 0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        temp_s3 = ((S_800A8184_0 *)temp_v0)->unk_08;
        temp_s1 = ((S_800A8184_0 *)temp_v0)->unk_0C;
        temp_s0->unk_4C = arg0;
        temp_s0->unk_4D = held_arg1;
        if ((held_arg1 & 0xFF) == 0x12) {
            u8 *dispatch_result;

            dispatch_result = (u8 *)0x80070000;
            ASM_KEEP(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            dispatch_result -= 0x1DC0;
            ASM_TAILSLOT_PIN(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800A8200();
            return;
        }
        temp_s1->unk_08 = func_8004A658(temp_s0->unk_4D, temp_s0->unk_4C);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_80033CD8(temp_s0, &D_80045340);
        func_800A8248(temp_s0, temp_s3, temp_s1);
    }
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
}
/* MECHANISM: The 0x28 frame and held s4/s2/s3/s1/s0 roles preserve the exact prologue and ABI lifetimes.
   A zero-word scheduling fence after the result store prevents delay-slot theft, keeping sw v0,8(s1)
   before call setup and allowing the D_80045340 low half to fill the following jal delay slot. */

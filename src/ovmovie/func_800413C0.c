#include "common.h"

extern u32 *D_80178380;
extern s32 D_8017681C;
extern void func_80177D08(void);
extern void func_80177C48(void);

/* Wait for status bit 29 to clear, returning -1 on timeout or 0 on success. */
s32 func_800413C0(void) {
    volatile s32 polls_left;
    u32 *status;
    s32 poll_limit;

    asm(
        "lui $3,%%hi(D_80178380)\n\t"
        "lw $3,%%lo(D_80178380)($3)\n\t"
        "lui $2,0x10"
        : "=r"(status), "=r"(poll_limit));
    polls_left = poll_limit;
    if (*(volatile u32 *) status & 0x20000000) {
        s32 timeout_value;
        u32 *poll_status;

        timeout_value = -1;
        do {
            polls_left = polls_left - 1;
            if (polls_left == timeout_value) {
                asm volatile(
                    "lui $4,%%hi(D_8017681C)\n\t"
                    "addiu $4,$4,%%lo(D_8017681C)"
                    :
                    :
                    : "$4");
                func_80177D08();
                func_80177C48();
                return -1;
            }
            asm volatile(
                "lui $2,%%hi(D_80178380)\n\t"
                "lw $2,%%lo(D_80178380)($2)"
                : "=r"(poll_status));
        } while (*(volatile u32 *) poll_status & 0x20000000);
    }
    return 0;
}

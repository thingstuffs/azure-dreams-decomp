#include "common.h"

extern u32 *D_80178380;
extern s32 D_8017681C;
extern void func_80177D08(void);
extern void func_80177C48(void);

s32 func_800413C0(void) {
    volatile s32 sp10;
    register u32 *status ASM_REG("$3");
    register s32 init ASM_REG("$2");

    asm(
        "lui $3,%%hi(D_80178380)\n\t"
        "lw $3,%%lo(D_80178380)($3)\n\t"
        "lui $2,0x10"
        : "=r"(status), "=r"(init));
    sp10 = init;
    if (*(volatile u32 *) status & 0x20000000) {
        register s32 sentinel ASM_REG("$4");
        register u32 *status_loop ASM_REG("$2");

        sentinel = -1;
        do {
            sp10 = sp10 - 1;
            if (sp10 == sentinel) {
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
                : "=r"(status_loop));
        } while (*(volatile u32 *) status_loop & 0x20000000);
    }
    return 0;
}

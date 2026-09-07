#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8002652C(void) __attribute__((noreturn));
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2CB8(void *, void *);
extern s32 func_800A41F0(void *);
void *func_81984C44(void *arg0)
{
    register void *node ASM_REG("$16");
    register u8 *page ASM_REG("$17");
    register void *entity ASM_REG("$18");
    register s32 limit ASM_REG("$19");
    register u8 *page0 ASM_REG("$4");
    register s32 limit0 ASM_REG("$5");
    register void *next ASM_REG("$2");
    register void *tail_value ASM_REG("$2");
    s8 floor;
    void *owner;

    entity = arg0;
    page0 = (u8 *)0x80080000;
    ASM_KEEP(entity);
    ASM_KEEP(page0);
    node = FIELD(page0, void *, 0x14A8);
    limit0 = 0x100;
    if (FIELD(entity, s8, 0x26) < 0) {
        limit0 = 4;
    }
    ASM_KEEP(limit0);
    next = FIELD(node, void *, 0x5C);
    ASM_KEEP(next);
    node = (u8 *)next + 0x20;
    if (node != FIELD(page0, void *, 0x14A8)) {
        page = page0;
        limit = limit0;
        ASM_KEEP(page);
        ASM_KEEP(limit);
        do {
            if (((func_800A2CB8(FIELD(page, void *, 0x14A8), node) << 16) != 0) &&
                ((func_800A41F0(node) << 16) != 0) &&
                !(FIELD(node, u16, -2) & 0x2000)) {
                floor = FIELD(entity, s8, 0x26);
                owner = FIELD(node, void *, -0x14);
                if (floor >= 0) {
                    if (floor == FIELD(owner, s8, 0x26)) {
                        tail_value = node;
                        ASM_KEEP(tail_value);
                        func_8002652C();
                    }
                } else {
                    if (func_8009FD40(owner, entity) < limit) {
                        return node;
                    }
                }
            }
            next = FIELD(node, void *, 0x5C);
            ASM_KEEP(next);
            node = (u8 *)next + 0x20;
        } while (node != FIELD(page, void *, 0x14A8));
    }
    return 0;
}

/* MECHANISM: Split pre-call page/limit in a0/a1 from held s1/s3; pin arg/node in s2/s0.
   A v0 next temp preserves non-destructive list updates; zero-arg noreturn triggers LEAD 18.
   A guarded v0 tail value fills word 43's branch delay; the residue is byte-exact. */

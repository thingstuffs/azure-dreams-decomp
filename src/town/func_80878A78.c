#include "common.h"

typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, s32);
    u8 pad6C[8];
    void (*func74)(s32);
} CallbackTable;

typedef struct {
    u8 pad00[0x10];
    u8 *data;
} TownObject;

extern volatile s32 D_8070309C;
extern CallbackTable *volatile D_807030B8;
extern u8 D_807028F4[];
extern u8 D_8070291C[];
extern TownObject *volatile D_807030AC;
extern u8 D_80702FB8[];
extern u8 *D_8070306C[];
extern u8 **D_807030B4;
extern void func_80702A54(void);
extern void func_80702B34(void) __attribute__((noreturn));

void func_80878A78(s32 arg0, s32 arg1)
{
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    s32 sentinel;
    u8 *ptr;
    s32 first;

#ifdef NON_MATCHING
    zero = 0;
#endif
    if (D_8070309C != 0) {
        D_807030B8->func68(D_807028F4, D_8070291C, zero | 0xE2);
        D_807030B8->func74(zero | 1);
    }

    D_8070309C = zero | 1;
    func_80702A54();

    if (arg1 == (zero | 2)) {
        D_807030AC->data = D_80702FB8;
        func_80702B34();
    }

    D_807030AC->data = D_8070306C[arg0];
    do { ptr = D_807030AC->data; } while (0);
    first = ptr[1];
    sentinel = zero | 0x80;
    ASM_CLOBBER("$0");   /* MATCH pin: load-bearing for the whole function shape */
    if (first != sentinel) {
        s32 terminator;
        terminator = zero | 0x80;
        ptr++;
        do {
            u32 index = *(volatile u32 *)(ptr + 11);
            u8 **table = D_807030B4;
            do { *(volatile u32 *)(ptr + 11) = (u32)table[index]; } while (0);
            ptr += 20;
        } while (*ptr != terminator);
    }
}

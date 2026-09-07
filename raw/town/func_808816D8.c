#include "common.h"

typedef struct Func808816D8Callbacks {
    u8 pad68[0x68];
    void (*func68)(void *, void *, s32);
    u8 pad6C[8];
    void (*func74)(s32);
} Func808816D8Callbacks;

typedef struct Func808816D8Owner {
    u8 pad10[0x10];
    u8 *data;
} Func808816D8Owner;

extern s32 D_80700740[3];
extern Func808816D8Callbacks *D_8070100C[3];
extern Func808816D8Owner *D_80701000[3];
extern s32 * volatile D_80701008[];
extern u8 D_807007A8[16];
extern u8 D_807007D0[16];
extern u8 D_80700704[16];
extern void func_80700EB4(void);

#ifdef NON_MATCHING
#define READ_ZERO(value) ((value) = 0)
#else
#define READ_ZERO(value) ASM_UNDEF(value)
#endif

void func_808816D8(void) {
    u8 *var_a0;
    u8 *temp_a0;

    if (D_80700740[0] != 0) {
        register s32 zero ASM_REG("$0");
        READ_ZERO(zero);
        D_8070100C[0]->func68(D_807007A8, D_807007D0, zero | 0x4B);
        READ_ZERO(zero);
        D_8070100C[0]->func74(zero | 1);
    }
    {
        register s32 zero ASM_REG("$0");
        READ_ZERO(zero);
        *(s32 *)0x80700740 = zero | 1;
    }
    func_80700EB4();
    ASM_SCHED_BARRIER();
    D_80701000[0]->data = D_80700704;
    temp_a0 = D_80701000[0]->data;
    {
        register s32 zero ASM_REG("$0");
        register s32 limit ASM_REG("$2");
        register u8 check ASM_REG("$3");
        register s32 var_a1 ASM_REG("$5");
        READ_ZERO(zero);
        check = temp_a0[1];
        ASM_SCHED_BARRIER();
        limit = zero | 0x80;
        READ_ZERO(zero);
        if (check != limit) {
            var_a1 = zero | 0x80;
            var_a0 = temp_a0 + 1;
            do {
                *(volatile s32 *)(var_a0 + 0xB) = D_80701008[0][*(volatile s32 *)(var_a0 + 0xB)];
                var_a0 += 0x14;
            } while (*var_a0 != var_a1);
        }
    }
}

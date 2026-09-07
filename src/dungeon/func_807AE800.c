#include "common.h"
typedef s32 M2C_UNK;
#ifdef __mips__
static const u32 bank_words[] __asm__("func_807AE800") __attribute__((section(".text.func_807AE800"), aligned(4))) = {
    0x800F61D8,0x800F61D8,0x800F6218,0x800F62F8,0x800F635C,0x800F635C,0x800F635C,0x800F635C,
    0x800F635C,0x800F635C,0x800F635C,0x800F635C,0x800F635C,0x800F635C,0x800F635C,0x800F635C,
    0x800F620C,0x800F635C,0x800F635C,0x800F634C,0x00000001,0x00010001,0x00010000,0x0001FFFF,
    0x0000FFFF,0xFFFFFFFF,0xFFFF0000,0xFFFF0001,
};
__asm__(".globl func_807AE800\n.type func_807AE800,@function\n.size func_807AE800,144\n");
#define BODY_NAME func_807AE870
#else
#define BODY_NAME func_807AE800
#endif
extern void func_800478B8(M2C_UNK);
void BODY_NAME(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2)
#ifdef __mips__
    __attribute__((section(".text.func_807AE800")))
#endif
;
void BODY_NAME(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) { func_800478B8(arg2); }

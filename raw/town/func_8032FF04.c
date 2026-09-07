#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern u8 *volatile D_80016000;

void func_8001A704(s32 arg0, s32 arg1, s32 arg2)
{
    volatile u8 *root = D_80016000;
    register void *entry_ptr ASM_REG("$2");
    register void *position ASM_REG("$7");
    register s32 index ASM_REG("$3");
    register s32 value ASM_REG("$2");

    entry_ptr = FIELD(root, void *volatile, 0x30);
    ASM_KEEP(entry_ptr);
    index = FIELD(root, volatile s32, 8);
    index <<= 5;
    ASM_KEEP(index);
    entry_ptr = FIELD(entry_ptr, void *volatile, 0);
    ASM_KEEP(entry_ptr);
    index += (s32)entry_ptr;
    ASM_KEEP(index);
    position = FIELD(root, void *volatile, 0x1C);
    ASM_KEEP(position);
    arg1 <<= 5;
    ASM_KEEP(arg1);
    value = FIELD((void *)index, s16, 0xC);
    ASM_KEEP(value);
    arg1 += value;
    FIELD(position, volatile s32, 4) = arg1;
    {
        register void *position2 ASM_REG("$4");

        position2 = FIELD(root, void *volatile, 0x1C);
        ASM_KEEP(position2);
        arg2 <<= 5;
        ASM_KEEP(arg2);
        value = FIELD((void *)index, s16, 0xE);
        ASM_KEEP(value);
        arg2 += value;
        FIELD(position2, s32, 8) = arg2;
    }
}

/* MECHANISM: Frameless leaf; volatile pointer-chain reads plus zero-byte keeps
   preserve three load-delay gaps. Guarded pins encode the measured v0/v1/a3
   roles, while a block-local destination reuses the dead root in a0. */

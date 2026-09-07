#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BC26C_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC26C_0;   /* result in func_800BC26C */

typedef struct S_800BC26C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800BC26C_1;   /* fields in func_800BC26C */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800BC2E8(void);
extern u8 D_800BC388[9];
extern u8 D_800BC3E4[9];

void *func_800BC26C(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *fields;
    register s32 store_arg1 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    result = func_8003FD64(0x110, (void *)arg0);
    if (result != NULL) {
        do { store_arg1 = arg1; } while (0);
        ASM_KEEP(store_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_800BC26C_0 *)result)->unk_10 = D_800BC388;
        func_8004491C(result, D_800BC3E4);
        fields = (u8 *)result + 0x20;
        ((S_800BC26C_0 *)result)->unk_20 = arg0;
        ((S_800BC26C_1 *)fields)->unk_04 = arg2;
        if ((arg1 << 16) != 0) {
            func_800BC2E8();
            return (void *)0x7F80;
        }
        ((S_800BC26C_1 *)fields)->unk_0C = 0x7FC0;
        ((S_800BC26C_1 *)fields)->unk_0E = store_arg1;
    }
    return result;
}

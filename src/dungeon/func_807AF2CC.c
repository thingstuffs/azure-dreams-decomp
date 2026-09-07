#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_800F678C;

typedef struct S_807AF2CC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_807AF2CC_0;   /* func_8003FC64(0) in func_807AF2CC */

void func_807AF2CC(void) {
    ((S_807AF2CC_0 *)(func_8003FC64(0)))->unk_10 = &D_800F678C;
}

#include "common.h"
#include "shared/record_ptrs.h"
extern void initialize_fifteen_four_byte_records(u8 *);
extern u8 D_80019B08;
extern s32 D_80019B88;
/* Register D_80019B08 with the scene and keep the handle it returns. */
void func_805D3B14(void)
{
    initialize_fifteen_four_byte_records(&D_80019B08);
    D_80019B88 = (*((s32 (**)(s32, s32, s32, s32 *)) (((s8 *) (*((void **) (((s8 *) D_80016000)
        + 0x20)))) + 0x68)))(0, 0, 0, &D_80019B08);
}

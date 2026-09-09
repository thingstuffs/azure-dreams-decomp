#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_800ADFE8();                      /* extern */
M2C_UNK func_800AE0F4();                      /* extern */
M2C_UNK func_800AE2A4();                      /* extern */
s32 func_800B14B0(); /* extern */
s32 func_800B1BEC();        /* extern */
extern M2C_UNK D_800AE090;

typedef struct S_800AE1AC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    s32 unk_2C;
} S_800AE1AC_0;   /* temp_s0 in open_shop */

typedef struct S_800AE1AC_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800AE1AC_1;   /* var_s1 in open_shop */

/* open_shop: Allocate and initialize the shop and its resources, cleaning up if either resource fails. */
void *open_shop(M2C_UNK unused, s32 primary_param, s32 secondary_param, s32 shared_param) {
    s32 second_resource;
    S_800AE1AC_0 *shop_state;
    void *shop;

    shop = func_8003FC64(0);
    if (shop != NULL) {
        shop_state = shop + 0x20;
        shop_state->unk_20 = shared_param;
        shop_state->unk_18 = primary_param;
        shop_state->unk_1C = secondary_param;
        shop_state->unk_14 = 6;
        func_800ADFE8(shop_state);
        ((S_800AE1AC_1 *)shop)->unk_10 = &D_800AE090;
        shop_state->unk_28 = func_800B14B0(shop, shop_state->unk_04, shop_state->unk_08, shop_state->unk_0C, shop_state->unk_10, shop_state->unk_20, primary_param);
        second_resource = func_800B1BEC(shop, 0x48, -0xC);
        shop_state->unk_2C = second_resource;
        if ((shop_state->unk_28 == 0) || (second_resource == 0)) {
            func_800AE2A4(shop_state);
            shop = NULL;
        }
        func_800AE0F4(shop_state);
    }
    return shop;
}

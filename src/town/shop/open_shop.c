#include "shared/object_node.h"
#include "common.h"

void refresh_paged_selection_state();                      /* extern */
void copy_global_state_and_record_block(s32 *);                      /* extern */
struct FuncArg; void process_record_and_apply_flags(struct FuncArg *);                      /* extern */
s32 allocate_paged_shop_item_list(); /* extern */
s32 create_dual_buffer_object();        /* extern */
void advance_dispatch_when_countdown_expires(void *state_data);

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
} S_800AE1AC_0;

typedef struct S_800AE1AC_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800AE1AC_1;

/* open_shop: Allocate and initialize the shop and its resources, cleaning up if either resource fails. */
void *open_shop(s32 unused, s32 primary_param, s32 secondary_param, s32 shared_param) {
    s32 second_resource;
    S_800AE1AC_0 *shop_state;
    void *shop;

    shop = func_8003FC64(0);
    if (shop != 0) {
        shop_state = shop + 0x20;
        shop_state->unk_20 = shared_param;
        shop_state->unk_18 = primary_param;
        shop_state->unk_1C = secondary_param;
        shop_state->unk_14 = 6;
        refresh_paged_selection_state(shop_state);
        ((S_800AE1AC_1 *)shop)->unk_10 = &advance_dispatch_when_countdown_expires;
        shop_state->unk_28 = allocate_paged_shop_item_list(shop, shop_state->unk_04, shop_state->unk_08, shop_state->unk_0C,
            shop_state->unk_10, shop_state->unk_20, primary_param);
        second_resource = create_dual_buffer_object(shop, 0x48, -0xC);
        shop_state->unk_2C = second_resource;
        if ((shop_state->unk_28 == 0) || (second_resource == 0)) {
            process_record_and_apply_flags((struct FuncArg *)(shop_state));
            shop = 0;
        }
        copy_global_state_and_record_block((s32 *)(shop_state));
    }
    return shop;
}

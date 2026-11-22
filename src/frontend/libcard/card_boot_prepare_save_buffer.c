#include "frontend/card/save_image.h"
#include "common.h"

extern CardSaveHeaderPrefix D_80028064;

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Copies the initial word into the buffer and initializes state for the selected mode. */
void card_boot_prepare_save_buffer(CardSaveImage *save, s32 config, s32 mode) {
    u8 *state_base;
    s16 is_mode_two;

    save->prefix = D_80028064;
    state_base = (u8 *)0x80010000;
    is_mode_two = (mode == 2);
    *(s16 *)(state_base + 0x208) = is_mode_two;
    *(s16 *)(state_base + 0x20A) = is_mode_two;
    *(s32 *)(state_base + 0x224) = *(u32 *)(state_base + 0x2D5C);
    *(s32 *)(state_base + 0x230) = card_boot_build_resident_bit_mask();
    *(s32 *)(state_base + 0x228) = card_boot_sum_slot_lookup_values();
    card_boot_build_save_description(save, config);
    card_boot_store_save_icon_clut_and_frames(save, config);
}

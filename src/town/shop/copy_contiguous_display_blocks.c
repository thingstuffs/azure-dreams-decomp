#include "common.h"
#include "town/shop.h"
#include "town/shop/display_template_data.h"

typedef struct {
    u8 bytes[24];
} __attribute__((packed)) Packed24;

extern Packed24 D_800D16E4;

/* Copies two packed data blocks into a contiguous 36-byte destination. */
void copy_contiguous_display_blocks(void *dst) {
    void *src;

    src = &D_800D16E4;
    *(Packed24 *)dst = *(Packed24 *)src;
    src = &shop_second_display_template;
    *(ShopDisplayTemplateBlock *)((u8 *)dst + 24) = *(ShopDisplayTemplateBlock *)src;
}

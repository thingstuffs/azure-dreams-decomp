#include "common.h"
#include "town/shop.h"

typedef struct {
    u8 bytes[24];
} __attribute__((packed)) Packed24;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

extern Packed24 D_800D16E4;
extern Packed12 shop_second_display_template;

/* Copies two packed data blocks into a contiguous 36-byte destination. */
void copy_contiguous_display_blocks(void *dst) {
    void *src;

    src = &D_800D16E4;
    *(Packed24 *)dst = *(Packed24 *)src;
    src = &shop_second_display_template;
    *(Packed12 *)((u8 *)dst + 24) = *(Packed12 *)src;
}

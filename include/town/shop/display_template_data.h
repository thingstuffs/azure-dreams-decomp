#ifndef TOWN_SHOP_DISPLAY_TEMPLATE_DATA_H
#define TOWN_SHOP_DISPLAY_TEMPLATE_DATA_H

#include "common.h"

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) ShopDisplayTemplateBlock;

/* The second 12-byte display template at 0x800D16D8. */
extern ShopDisplayTemplateBlock shop_second_display_template;

#endif

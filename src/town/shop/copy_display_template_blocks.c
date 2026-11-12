#include "common.h"
#include "town/shop/display_template_data.h"

typedef struct {
    u8 bytes[0x30];
} Packed48;

typedef struct {
    Packed48 first;
    ShopDisplayTemplateBlock second;
} CopyTarget;

extern u8 D_800D16FC[0x30];

/* Copies the 48-byte and 12-byte global blocks into the target. */
void copy_display_template_blocks(CopyTarget *target)
{
    target->first = *(Packed48 *)D_800D16FC;
    target->second = shop_second_display_template;
}

#include "sdk/libc.h"
#include "common.h"
#include "town/scene.h"
#include "town/shop/object.h"


typedef struct {
    u8 pad00[0x20];
    s8 copy_source[12];
    u8 pad2C[0x34];
} TownSystemScratch;

extern TownSystemScratch town_system_scratch;

/* Pass a four-byte copy of the system scratch data to append_shop_entry. */
void copy_scratch_bytes_and_dispatch(void)
{
    s8 copied_bytes[4];

    memcpy(copied_bytes, town_system_scratch.copy_source, sizeof(copied_bytes));
    append_town_item(copied_bytes);
}

#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"

struct TownObject; void set_shop_slot_colors(struct TownObject *, s32);                 /* extern */


/* Pass the object's data at offset 0x20 and its unk_08 value to set_shop_slot_colors. */
void process_shop_object_data(s32 object_addr) {
    EffectStateWordView *data;

    data = object_addr + 0x20;
    set_shop_slot_colors((struct TownObject *)(data), data->unk_08);
}

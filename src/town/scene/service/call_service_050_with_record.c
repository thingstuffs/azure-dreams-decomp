#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Pass the square scene record to service slot 0x50. */
s32 get_item_buy_money_from_scene_record(void) {
    return town_scene_root->services->callback_050(square_scene_service_050_record);
}

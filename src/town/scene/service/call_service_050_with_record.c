#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Pass the square scene record to service slot 0x50. */
s32 call_service_050_with_record(void) {
    return town_scene_root->services->callback_050(square_scene_service_050_record);
}

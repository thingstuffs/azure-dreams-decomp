#include "common.h"

#include "slus.h"
#include "town/map/camera.h"
#include "town/map.h"

/* Apply the setting and store its current value. */
void apply_and_store_setting(IntVector3 *setting) {
    bind_view_triplet_source(setting);
    D_80100D90 = setting;
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/cd.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

/* Run initialization once and mark it complete. */
void load_shared_resource_once(void) {
    if (shared_sprite_resource_loaded == 0) {
        Control_CD(6, shared_sprite_resource_descriptor, 0);
        drain_cd_command_queue();
        shared_sprite_resource_loaded = 1;
    }
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 Control_CD(s32 event_code, void *event_data, s32 payload);
void drain_cd_command_queue(void);
extern s8 shared_sprite_resource_loaded;
extern M2C_UNK shared_sprite_resource_descriptor;

/* Run initialization once and mark it complete. */
void load_shared_resource_once(void) {
    if (shared_sprite_resource_loaded == 0) {
        Control_CD(6, &shared_sprite_resource_descriptor, 0);
        drain_cd_command_queue();
        shared_sprite_resource_loaded = 1;
    }
}

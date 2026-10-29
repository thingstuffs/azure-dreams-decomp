#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "slus.h"

extern s8 encounter_cd_ready;

/* Clears the status flag and registers the callback and status handlers. */
void register_encounter_cd_callbacks(s32 input_value) {
    void *callback;

    callback = prepare_encounter_resource_descriptor(input_value);
    encounter_cd_ready = 0;
    Control_CD(6, callback, 0);
    Control_CD(0xFF, set_byte_one, &encounter_cd_ready);
}

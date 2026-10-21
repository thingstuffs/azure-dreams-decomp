#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"

extern void *prepare_encounter_resource_descriptor(void);
extern void Control_CD(s32, void *, void *);
extern s8 encounter_cd_ready;

/* Clears the status flag and registers the callback and status handlers. */
void register_encounter_cd_callbacks(void) {
    void *callback;

    callback = prepare_encounter_resource_descriptor();
    encounter_cd_ready = 0;
    Control_CD(6, callback, 0);
    Control_CD(0xFF, set_byte_one, &encounter_cd_ready);
}

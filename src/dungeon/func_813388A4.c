#include "common.h"

extern void *prepare_encounter_resource_descriptor(void);
extern void Control_CD(s32, void *, void *);
extern s32 D_8003E140[];
extern s8 D_8017397C;

/* Clears the status flag and registers the callback and status handlers. */
void register_encounter_cd_callbacks(void) {
    void *callback;

    callback = prepare_encounter_resource_descriptor();
    D_8017397C = 0;
    Control_CD(6, callback, 0);
    Control_CD(0xFF, D_8003E140, &D_8017397C);
}

#include "common.h"

extern s32 bind_view_triplet_source(s32);
extern s32 D_80100D90;

/* Apply the setting and store its current value. */
void apply_and_store_setting(s32 setting) {
    bind_view_triplet_source(setting);
    D_80100D90 = setting;
}

#include "common.h"

extern void apply_entry_position(s32 *, s32 *, s32, s32);
extern s32 D_8001B8F8[];
extern s32 scene_dispatch_context[];

/* Dispatch the first and third arguments using the fixed data tables. */
void dispatch_first(s32 dispatch_value, s32 unused, s32 dispatch_option) {
    apply_entry_position(D_8001B8F8, scene_dispatch_context, dispatch_value, dispatch_option);
}

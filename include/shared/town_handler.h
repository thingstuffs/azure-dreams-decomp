#ifndef SHARED_TOWN_HANDLER_H
#define SHARED_TOWN_HANDLER_H

#include "common.h"
#include "shared/town_object.h"
#include "records/Rec_D_80082D58.h"

/* The third argument is the destination carried through the handler helpers. */
void dispatch_selected_entry_if_nonzero(s32 *entries, TownObjectRecord *record, void *ptr2);
void forward_selected_entry_value(s32 *values, TownObjectRecord *selector, void *ptr2);
void store_entry_and_set_frame(s32 value, Rec_D_80082D58 *record, void *ptr2);
void set_sprite_frame_by_view_angle(u8 *sourceBytes, s32 selection, u8 *destination);

#endif

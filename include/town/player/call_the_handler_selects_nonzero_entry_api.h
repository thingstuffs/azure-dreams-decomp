#ifndef TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_API_H
#define TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_API_H

#include "common.h"

struct TownObjectRecord;

void dispatch_selected_entry_if_nonzero(s32 *, struct TownObjectRecord *, void *);

#endif

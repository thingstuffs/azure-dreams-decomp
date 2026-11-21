#include "common.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"

s32 libcard_select_slot(s32 slot) { _new_card_804086CC(slot); return _card_write_804086BC(slot, 0x3F, 0); }

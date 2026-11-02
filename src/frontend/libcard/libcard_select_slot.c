#include "common.h"
#include "frontend/libcard.h"

extern void _new_card_804086CC(s32);
extern s32 _card_write_804086BC(s32, s32, s32);
s32 libcard_select_slot(s32 slot) { _new_card_804086CC(slot); return _card_write_804086BC(slot, 0x3F, 0); }

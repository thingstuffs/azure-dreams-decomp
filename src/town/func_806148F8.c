#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern u8 D_800191FC[];

void submit_scene_entry_data_b(void) { D_80016000->unk_20->callback_218(D_800191FC); }

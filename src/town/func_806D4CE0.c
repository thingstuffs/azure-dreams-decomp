#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern u8 D_80018B44[];

void submit_scene_entry_data_d(void) { D_80016000->unk_20->callback_218(D_80018B44); }

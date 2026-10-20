#include "engine/scene/cd_cohort_types.h"
u8 cd_command_read_index = 0;
u8 cd_command_mode_byte = 0;
u32 cd_read_tail_word_address = 0;
SlusCdResult cd_command_result = {0};
u8 D_80080AD0 = 0;
u16 cd_command_poll_ticks = 0;
u16 cd_retry_counters_pending = 0;
s32 cd_read_sync_result = 0;
void *cd_event_payload = 0;
s32 cd_queue_buffered_argument_word_0 = 0;
s32 cd_queue_buffered_argument_word_1 = 0;

extern u8 cd_command_phase[2];

#include "w_8003E34C.c"
#include "w_8003E4FC.c"
#include "w_8003E758.c"
#include "../build/partition_sources/code2__cd_command_state.c"
#include "w_8003F2A4.c"
#include "w_8003F368.c"
#include "w_8003F5AC.c"
#include "w_8003F624.c"

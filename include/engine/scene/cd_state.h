#ifndef SLUS_CD_STATE_H
#define SLUS_CD_STATE_H
#include "common.h"

/* CdSync/CdControl may write eight bytes; location recovery saves word zero. */
typedef union {
    u32 first_word;
    u8 bytes[8];
} SlusCdResult;

extern SlusCdResult cd_command_result;
extern u8 D_80080AD0;
extern u16 cd_command_poll_ticks;
extern u16 cd_retry_counters_pending;
extern s32 cd_read_sync_result;
extern void *cd_event_payload;
extern u32 cd_read_tail_word_address;
extern u8 cd_command_read_index;
extern u8 cd_command_mode_byte;
extern u8 cd_command_phase[2];
extern s32 cd_queue_buffered_argument_word_0;
extern s32 cd_queue_buffered_argument_word_1;
u8 get_previous_cd_command_byte(void);
#endif

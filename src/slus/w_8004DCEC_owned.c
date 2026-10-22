/* Message-mode selection and dispatch of strings containing embedded control-word addresses. */
#include "slus/message_mode_81550.h"

s32 message_output_control_word = 0;
s32 message_handler_mode = 0;

#include "../build/partition_sources/code__message_mode_81550.c"
#include "w_8004DCEC.c"
#include "w_8004DE88.c"
#include "w_8004DF8C.c"

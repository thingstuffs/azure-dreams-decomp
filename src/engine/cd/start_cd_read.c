#include "engine/scene/command_words.h"

#include "common.h"

/* Inferred present ownership; canonical row body is included unchanged. */
volatile s32 cd_read_command_words = 0;
s32 cd_read_command_second_word = 0;

#include "engine/scene/command_words.h"
#include "engine/cd.h"

/* Copies a CD descriptor, packs its size with the low 23 argument bits, and waits for the read command. */
void start_cd_read(S_80053CFC *source, s32 packed_value)
{
    s32 saved_value;
    s32 low_bits;
    s32 *command;

    saved_value = packed_value;
    *(S_80053CFC *)&cd_read_command_words = *source;
    low_bits = saved_value & 0x7FFFFF;
    command = (s32 *)&cd_read_command_words;
    *command = ((((u32)*command + 0x7FF) >> 11) << 23) | low_bits;
    Control_CD(6, (void *)command, saved_value);
    drain_cd_command_queue();
}

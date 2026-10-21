#ifndef GLOBALS_H
#define GLOBALS_H

/* Game globals accessed via $gp (small data). Each must be <= 8 bytes so the
 * compiler keeps it in small data and emits %gp_rel($gp) access, matching the
 * original -G8 build. Addresses are resolved by the linker from
 * config/generated/*.undefined_syms.txt. Names/types provisional. */

extern int sound_payload_buffer;
extern int message_handler_mode;
extern int message_command_start_index;
extern int message_command_write_index;

extern unsigned char D_80071298[];

extern volatile int D_80071250[];
extern int D_800712B4[];

extern int card_server_initialized[3];

extern struct S_80083178State saved_view_vectors;

#endif /* GLOBALS_H */

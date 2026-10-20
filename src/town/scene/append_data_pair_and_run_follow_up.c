#include "common.h"
#include "m2c_compat.h"

struct S_8003AF58_1; void append_town_movie_list_node(void *, struct S_8003AF58_1 *);        /* extern */
short SD_Call(int flags);                     /* extern */
void drain_audio_commands_and_service_channels(void);                            /* extern */
extern M2C_UNK town_transition_callback_list;
extern s8 D_80080A88;
extern M2C_UNK D_800D42B4;

/* Pass the town data pair to append_town_movie_list_node, set the shared flag, and invoke the follow-up routines. */
void append_data_pair_and_run_follow_up(void) {
    append_town_movie_list_node(&town_transition_callback_list, (struct S_8003AF58_1 *)(&D_800D42B4));
    D_80080A88 = 1;
    SD_Call(0xBF);
    drain_audio_commands_and_service_channels();
}

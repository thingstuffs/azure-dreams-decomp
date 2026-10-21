#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

typedef struct {
    s32 a;
    s32 b;
    s32 pad[2];
} func_8000DEA0_Pair;







extern void bzero(void *dst, s32 size);

/* Initialize shared state once, run its update, and clear the reset fields. */
void card_boot_init_server(void) {
    s32 *pair_words;

    if (card_server_initialized[0] == 0) {
        card_server_initialized[0] = 1;
        {
            func_8000DEA0_Pair *init_pair;
            (*(func_8000DEA0_Pair *)(&card_slot_completion_flags)).a = 0;
            init_pair = &(*(func_8000DEA0_Pair *)(&card_slot_completion_flags));
            init_pair->b = 0;
            bzero((*(u8 (*)[0x280])(&card_save_slot_metadata)), 0x280);
        }
    }
    card_boot_open_events();
    (*(func_8000DEA0_Pair *)(&card_filtered_status)).a = 0;
    pair_words = (s32 *)&(*(func_8000DEA0_Pair *)(&card_filtered_status));
    pair_words[1] = 0;
    (*(func_8000DEA0_Pair *)(&card_presence_flags)).a = 0;
    pair_words = (s32 *)&(*(func_8000DEA0_Pair *)(&card_presence_flags));
    pair_words[1] = 0;
    (*(func_8000DEA0_Pair *)(&card_operation_state)).a = 0;
}

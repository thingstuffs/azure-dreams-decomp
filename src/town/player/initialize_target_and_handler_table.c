#include "common.h"

extern void clear_entity_record_fields(s32 record);
extern s8 player_handler_reset_byte;
extern void *player_handler_table_address[];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B228;

/* Initialize the target, assign the state table, and clear the global flag. */
void initialize_target_and_handler_table(Struct8009B228 *state, s32 target) {
    clear_entity_record_fields(target);
    state->unk4 = player_handler_table_address;
    player_handler_reset_byte = 0;
}

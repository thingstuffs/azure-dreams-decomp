#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard/message.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Builds a reverse chain using card_message_chain_indices and limit 7. */
void card_boot_link_message_display_entries(S_800491F4 **input) {
    build_reverse_indexed_chain(input, &card_message_chain_indices, 7);
}

#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard/message.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Builds a reverse chain using card_slot_chain_indices and limit 10. */
void card_boot_link_slot_window_entries(S_800491F4 **value) {
    build_reverse_indexed_chain(value, &card_slot_chain_indices, 0xa);
}

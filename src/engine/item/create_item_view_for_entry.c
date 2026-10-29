#include "common.h"
#include "engine/cd.h"
#include "engine/item.h"
#include "slus.h"

typedef struct S_8004B854 {
    u8 a2;
    u8 code;
} S_8004B854;

extern void *create_item_view(int a0, int a1, int a2, S_8004B854 *a3, int a4);

/* Sends a packet containing the entry byte and command code 0x13 to the target; returns the item view it opens. */
void *create_item_view_for_entry(int target, int record_addr, int entry_value)
{
    S_8004B854 local_packet;
    int zero = 0;

    load_bin_nametwin();
    local_packet.a2 = (u8)entry_value;
    local_packet.code = 0x13;
    drain_cd_command_queue();
    return create_item_view(target, zero, zero, &local_packet, record_addr);
}

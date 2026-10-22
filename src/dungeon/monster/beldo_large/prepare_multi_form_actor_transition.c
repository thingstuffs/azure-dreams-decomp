
struct ObjectNodeHeader;
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"

extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);
extern void set_or_clear_actor_status_slot(void *, s32, s32);

extern u8 *beldo_actor_nodes[3];

/* Resets the encounter actor action, sets its transition status, and relinks up to two attached objects. */
void prepare_multi_form_actor_transition(s32 unused0, s32 unused1, s32 unused2, s32 unused3) {
    s32 i;
    u8 *p;
    void *item;
            /* MATCH: keep the byte-store constant in v0, independent of outgoing a2. */
    s32 one;
            /* MATCH: prepare outgoing a0 before materializing the byte-store constant. */
    u8 *callp;

    i = 0;
    p = beldo_actor_nodes[0] + 0x20;
    *(u16 *)(p + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    set_monster_data_pointer();
    p[0xAF] = 0;
    p[0xB0] = 1;
    set_or_clear_actor_status_slot(p, 7, 1);
    p[0xAE] = 2;
    do {
        item = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + i * 4);
        if (item != 0) {
            clear_entry_flag_and_link_owner((u8 *)item - 0x20);
        }
        i++;
    } while (i < 2);
}

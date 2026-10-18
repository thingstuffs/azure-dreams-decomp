#include "common.h"

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
    u8 pad_95[3];
    void *object;
};

extern s32 D_800CFCB4;
extern s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(void);
extern void handle_inserts_first_free_slot_discarding_first_full(void *);

/* Process active type-4 town links that have no associated object. */
void process_unlinked_type_four_entries(void)
{
    TownLink *sentinel = (TownLink *)&D_800CFCB4;
    TownLink *link = sentinel->next;

    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() != 0) {
        return;
    }

    if (link == sentinel) {
        return;
    }

    do {
        if (link->type == 4 && link->state != -1 && link->object == 0) {
            handle_inserts_first_free_slot_discarding_first_full((u8 *)link + 0x4C);
        }
        link = link->next;
    } while (link != sentinel);
}

#include "common.h"
#include "town/shop/state.h"

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
};

extern s32 town_actor_control;

/*
 * Walks town_actor_control through its circular sentinel and counts links of type four whose state
 * differs from -1.
 */
s32 count_type_n_4_links_whose_state_not_n_1(void)
{
    TownLink *link = ((TownLink *)&town_actor_control)->next;
    s32 count = 0;

    if (link != (TownLink *)&town_actor_control) {
        s32 type = 4;
        s32 state = -1;
        TownLink *sentinel = (TownLink *)&town_actor_control;

        do {
            if (link->type == type && link->state != state) {
                count++;
            }
            link = link->next;
        } while (link != sentinel);
    }

    return count;
}

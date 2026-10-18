#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B648C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B648C_0;   /* arg0 in join_monster_status_display_chains */

typedef struct S_800B648C_1 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
} S_800B648C_1;


void *link_monster_status_main_entries();                       /* extern */
s32 link_monster_status_display_entries();                         /* extern */

/* Stores the fetched chain and initializes its terminal link. */
void join_monster_status_display_chains(S_800B648C_0 *owner, M2C_UNK source) {
    S_800B648C_1 *tail;

    tail = link_monster_status_main_entries(source);
    owner->unk_0C = tail;
    if (tail->unk_0C.s != 0) {
        do {
            tail = tail->unk_0C.u;
        } while (tail->unk_0C.s != 0);
    }
    tail->unk_0C.s = link_monster_status_display_entries(source);
}

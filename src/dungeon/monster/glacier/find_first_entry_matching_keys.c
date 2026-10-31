#include "common.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80174A00_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174A00_0_pre;   /* the 0x14 bytes before arg0 in find_first_entry_matching_keys, addressed as arg0[-1] */


typedef struct S_80174A00_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174A00_1;   /* data in find_first_entry_matching_keys */


/* Finds the first entry matching both keys, the value range, and the type filter. */
void *find_first_entry_matching_keys(ActorRecord *body, u16 key_a, u16 key_b, s16 range_center) {
    void *head = body;

    body = (ActorRecord *)(body->next_actor_header + 0x20);
    while (body != head) {
        S_80174A00_1 *node_data = ((S_80174A00_0_pre *)body)[-1].unk_00;
        void *entry = ((void *)body) - 0x20;
        s16 node_value;

        if ((node_data->unk_24 == key_a) &&
            (node_data->unk_25 == key_b) &&
            (node_value = body->ground_height, node_value <= range_center + 0x20) &&
            (node_value >= range_center - 0x20) &&
            ((u32)(body->species - 0x33) < 4)) {
            return entry;
        }
        body = (ActorRecord *)(body->next_actor_header + 0x20);
    }
    return NULL;
}

#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif


extern EntityLinkNode *D_800E3DE8;

/* Unlink a node and advance the global cursor if it references that node. */
void func_8009A028(EntityLinkNode *node) {
    EntityLinkNode *prev;
    EntityLinkNode *next;

    if (D_800E3DE8 == (EntityLinkNode *)((s8 *)node - 0x20)) {
        D_800E3DE8 = node->next;
    }

    prev = node->prev;
    next = node->next;
    if ((prev != NULL) && (next != NULL)) {
        prev->unk7C = next;
        next->unk78 = prev;
        node->next = NULL;
        node->prev = NULL;
    }
}

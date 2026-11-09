#include "common.h"
#include "engine/node.h"
#include "slus.h"

#ifndef NULL
#define NULL 0
#endif

/* Clears caller-provided node storage and links it at the list head like allocate_list_node: next at 0x00,
 * the back-link slot at 0x04, flags at 0x1E, and the optional sprite and position records carved from the
 * storage's tail (word_count words). */
void *initialize_runtime_node_storage(s32 flags, void *storage, s16 word_count, void *list_storage)
{
    ObjectNodeHeader **list_head = list_storage;
    ObjectNodeHeader *old_head;
    u8 *payload_cursor;
    ObjectNodeHeader *node;
    s32 payload_flags;

    flags = flags | 0x80;
    node = storage;
    zero_words((int *)node, word_count);
    node->next = *list_head;
    *list_head = node;
    old_head = node->next;
    node->pprev = list_head;
    if (old_head != NULL) {
        old_head->pprev = &node->next;
    }
    node->flags = flags | 0x4000;
    payload_cursor = (u8 *)node + (word_count << 2);
    if (flags & 6) {
        payload_cursor = payload_cursor - 0x24;
        node->sprite = (struct SpriteFrameState *)payload_cursor;
        payload_flags = flags & 0x57;
    } else if (flags & 0x41) {
        payload_cursor = payload_cursor - 0x18;
        node->sprite = (struct SpriteFrameState *)payload_cursor;
        payload_flags = flags & 0x57;
    } else {
        payload_flags = flags & 0x57;
    }
    if (payload_flags != 0) {
        payload_cursor = payload_cursor - 0x18;
        node->position = (struct ObjectPosition *)payload_cursor;
    }
    return node;
}

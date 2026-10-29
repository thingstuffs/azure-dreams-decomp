#include "common.h"

typedef struct ChainNode ChainNode;
typedef struct {
    u8 before_kind[6];
    s16 kind;
} ChainPayload;
struct ChainNode {
    u8 before_next[0x18];
    ChainNode *next;
    u8 before_body[4];
};
typedef struct {
    u8 before_value[8];
    s32 value;
    ChainPayload *payload;
} ChainHeader;
extern void transform_mesh_and_append_draw_packets(void *, s32, ChainPayload *, s16); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/*
 * Transforms and queues each linked mesh using its payload kind, follows the chain headers, and
 * returns zero at the end.
 */
s32 draw_linked_mesh_chain(void *body, s32 value, ChainPayload *payload) {
    ChainHeader *next;
    do {
        transform_mesh_and_append_draw_packets(body, value, payload, payload->kind);
        next = *(ChainHeader **)((u8 *)body - 8);
        body = (u8 *)next + 0x20;
        if (next != 0) {
            value = next->value;
            payload = next->payload;
        }
    } while (next != 0);
    return 0;
}

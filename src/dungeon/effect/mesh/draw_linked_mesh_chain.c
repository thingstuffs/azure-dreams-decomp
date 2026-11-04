#include "dungeon/effect/mesh_callbacks_api.h"
#include "common.h"
#include "shared/entity.h"
#include "dungeon/effect.h"

typedef struct ChainNode ChainNode;
typedef struct dungeon_mesh_chain_payload {
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
    ObjectPosition *value;
    ChainPayload *payload;
} ChainHeader;

/*
 * Transforms and queues each linked mesh using its payload kind, follows the chain headers, and
 * returns zero at the end.
 */
s32 draw_linked_mesh_chain(void *body, ObjectPosition *value, ChainPayload *payload) {
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

#include "common.h"

typedef struct Entity Entity;

struct Entity {
    s8 pad00[0x13];
    u8 kind;
    u32 flags;
    u32 pad18;
    volatile u32 status;
    u8 pad20[0x3C];
    Entity *next;
    u8 pad60[0xD];
    s8 field6D;
    s16 field6E;
    u8 pad70[0x34];
    void *owner;
    u8 padA8[2];
    s16 fieldAA;
};

typedef struct {
    u8 pad00[0xA];
    u16 fieldA;
    u8 pad0C[8];
} DungeonState;

extern DungeonState D_80083460;
extern volatile u16 D_800DCE68[];
extern Entity *D_800E3D7C[];

/* Mark owned entities of kind 0x1E and increment the dungeon counters. */
void func_800A31D0(Entity *owner_entity) {
    Entity *node;
    Entity *sentinel;
    u16 marked_count;
    u32 node_status;

    if (owner_entity->kind == 0x1E) {
        if (owner_entity->flags & 0x4000) {
            if (owner_entity->fieldAA != 0) {
                sentinel = D_800E3D7C[0];
                node = (Entity *)((u8 *)sentinel->next + 0x20);
                if (node != sentinel) {
                    do {
                        if ((node->kind == 0x1E) &&
                            (node->owner == (void *)((u8 *)owner_entity - 0x20))) {
                            D_80083460.fieldA++;
                            marked_count = D_800DCE68[0];
                            node_status = node->status;
                            node->field6E = 0;
                            marked_count++;
                            node_status |= 0x400000;
                            D_800DCE68[0] = marked_count;
                            node->field6D = 0;
                            node->status = node_status;
                        }
                        node = (Entity *)((u8 *)node->next + 0x20);
                    } while (node != D_800E3D7C[0]);
                }
            }
        }
    }
}

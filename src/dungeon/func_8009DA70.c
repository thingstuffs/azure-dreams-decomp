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

void func_800A31D0(Entity *arg0) {
    Entity *node;
    Entity *sentinel;
    u16 count;
    u32 status;

    if (arg0->kind == 0x1E) {
        if (arg0->flags & 0x4000) {
            if (arg0->fieldAA != 0) {
                sentinel = D_800E3D7C[0];
                node = (Entity *)((u8 *)sentinel->next + 0x20);
                if (node != sentinel) {
                    do {
                        if ((node->kind == 0x1E) &&
                            (node->owner == (void *)((u8 *)arg0 - 0x20))) {
                            D_80083460.fieldA++;
                            count = D_800DCE68[0];
                            status = node->status;
                            node->field6E = 0;
                            count++;
                            status |= 0x400000;
                            D_800DCE68[0] = count;
                            node->field6D = 0;
                            node->status = status;
                        }
                        node = (Entity *)((u8 *)node->next + 0x20);
                    } while (node != D_800E3D7C[0]);
                }
            }
        }
    }
}

/* MECHANISM: Frameless leaf CFG with three short-circuit guards and a sentinel
   do/while traversal; exact-width fields preserve lbu/lh/lhu/sh/sb accesses.
   Global and node bases are held naturally; remaining work is emission order. */

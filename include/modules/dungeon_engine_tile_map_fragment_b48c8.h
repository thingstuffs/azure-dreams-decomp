#ifndef MORE_FRAGMENT_B48C8_H
#define MORE_FRAGMENT_B48C8_H
#include "common.h"
#include "shared/dungeon_floor.h"
typedef struct EntityLinkNode { char pad0[0x58]; struct EntityLinkNode *prev; struct EntityLinkNode *next; char pad60[0x18]; struct EntityLinkNode *unk78; struct EntityLinkNode *unk7C; } EntityLinkNode;
typedef struct ActiveNode { struct ActiveNode *next; u8 pad[0x1E - 4]; u16 field_1E; } ActiveNode;
void unlink_entity_node(EntityLinkNode *node);
#endif

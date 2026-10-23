#ifndef SHARED_OBJECT_NODE_H
#define SHARED_OBJECT_NODE_H

/* ObjectNodeHeader: the 0x20-byte object-list node header that precedes an object's record (EntityRec's "0x20-byte
 * header before the record"), r78 phase 6.  From slus/w_8003FD64 func_8003FD64(flags, head), which takes a free
 * node, clears it (0x49 words), links it at *head (node->next = *head; *head = node; node->pprev = head;
 * next->pprev = node), sets +0x1E = flags | 0x4000 and points +0x0C / +0x08 into the node's payload.
 *
 * D_80083498 is a statically allocated node (dungeon, town; 284 rows name it, 277 migrated): 265 pass it as the `head`
 * (a node's `next` slot is the head of the list linked behind it), town/func_800C438C clears flag 0x2000 at +0x1E
 * before handing it to func_8004EE50 (object task).  Its record half, D_800834B8 (= +0x20), keeps its own D_
 * declaration: town rows form their base AT 0x800834B8 and reach this header at -0x18/-0x14/-0x10, so the original
 * declared the record separately there.  Script variable slot 26 is V_pobj and points at 0x80083498, consistent
 * with an object-list head (docs/SYMBOLS.md; the earlier V_item_type_data reading was the symbol-dump misparse fixed
 * 2026-09-28).  Name stays D_ until V_pobj's meaning is proven.  Other fields stay unk_. */
/* Object-list header preceding a callback-specific body.
 * runtime_reset_object_pool seeds free nodes; allocate_list_node clears and links each allocated node. */
struct ObjectPosition;

struct SpriteFrameState;

typedef struct ObjectNodeHeader {
    /* 0x00 */ struct ObjectNodeHeader *next; /* next object in this list, or null at the end */
    /* 0x04 */ struct ObjectNodeHeader **pprev; /* address of the list slot that points to this node; supports constant-time unlinking */
    /* 0x08 */ struct ObjectPosition *position; /* separate position/motion record; allocator reserves 0x18 bytes before the sprite payload */
    /* 0x0C */ struct SpriteFrameState *sprite; /* sprite/render payload selected by the allocation flags */
    /* 0x10 */ void *update_callback; /* update callback address; active-node dispatch passes body, position and sprite pointers */
    /* 0x14 */ int unk_14; /* draw-registration backlink, stored as an integer address */
    /* 0x18 */ struct ObjectNodeHeader *chain_next; /* next object registered for the same draw callback, or null */
    /* 0x1C */ unsigned char pad_1C[2];
    /* 0x1E */ unsigned short flags; /* allocation flags with 0x4000 set; bit 0x8000 marks completed/retired objects */
} ObjectNodeHeader;

extern ObjectNodeHeader scene_object_list_anchor;
ObjectNodeHeader *allocate_flagged_object_node(int flags);

#endif

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
    /* 0x08 */ struct ObjectPosition *position; /* optional 0x18-byte motion record; allocator leaves null unless flags include 0x157; lifetime follows the node */
    /* 0x0C */ struct SpriteFrameState *sprite; /* optional sprite/render part; flags 0x100, 0x6 or 0x41 select its payload offset; lifetime follows the node */
    /* 0x10 */ void *update_callback; /* update callback address; active-node dispatch passes body, position and sprite pointers */
    /* 0x14 */ struct ObjectNodeHeader *draw_prev; /* draw-registration backlink: the previous node registered for the same draw callback, or the registered_draw_objects slot that heads the chain (register_node/unlink_node) */
    /* 0x18 */ struct ObjectNodeHeader *chain_next; /* next object registered for the same draw callback, or null */
    /* 0x1C */ unsigned short draw_slot; /* registered_draw_objects slot index stored by register_node */
    /* 0x1E */ unsigned short flags; /* allocation/control bits: 0x400 skips update, 0x4000 marks active, 0x8000 requests unlink/removal */
} ObjectNodeHeader;

extern ObjectNodeHeader scene_object_list_anchor;

/* Draw-callback registry (SLUS .bss, 32 slots): register_node files a node under its draw callback's slot and
 * registered_draw_objects[slot] heads that callback's chain (draw_prev / chain_next / draw_slot above);
 * dispatch_registered_draw_callbacks calls each callback with the chain's body, position and sprite. */
extern void *registered_draw_callbacks[0x20];
extern ObjectNodeHeader *registered_draw_objects[0x20];
/* Returns pool storage containing this header and a flag-selected body. */
void *allocate_flagged_object_node(int flags);

#endif

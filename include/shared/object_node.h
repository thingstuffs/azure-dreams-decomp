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
 * declared the record separately there.  Name stays D_: docs/SYMBOLS.md's script slot 26 V_item_type_data points
 * at 0x80083498, which does not fit a list-head node, so it is not adopted.  Other fields stay unk_. */
typedef struct ObjectNodeHeader {
    /* 0x00 */ struct ObjectNodeHeader *next;    /* list link (func_8003FD64) */
    /* 0x04 */ struct ObjectNodeHeader **pprev;  /* the slot that points at this node (func_8003FD64) */
    /* 0x08 */ void *unk_08;                     /* func_8003FD64: payload cursor - 0x18 */
    /* 0x0C */ void *unk_0C;                     /* func_8003FD64: payload cursor */
    /* 0x10 */ void *unk_10;                     /* town/func_800A7BE0 compares it with code addresses */
    /* 0x14 */ int unk_14;
    /* 0x18 */ int unk_18;
    /* 0x1C */ unsigned char pad_1C[2];
    /* 0x1E */ unsigned short flags;             /* flags | 0x4000 at allocation; & 0x200 / & 0x80 tests (func_8003FB98) */
} ObjectNodeHeader;

extern ObjectNodeHeader D_80083498;

#endif

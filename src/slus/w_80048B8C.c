#include "common.h"

#include "common.h"

typedef struct S_80048B8C_node {
    u8 flags;
    u8 pad1[3];
    volatile u16 val;
    u8 pad6[6];
} S_80048B8C_node;

typedef struct S_80048B8C_entry {
    u8 pad0[2];
    s16 type;
    S_80048B8C_node *node;
} S_80048B8C_entry;

typedef struct S_80048B8C {
    u8 *list;
    s32 index;
    u8 *listEnd;
} S_80048B8C;

/* Walk outer 8-byte entries from list+index*4 to listEnd. For type==2 nodes
 * without flag 0x08, set that flag and clear the low 6 bits of each 0x0C-stride
 * node's val then add 0xE, until a node with flag 0x80.
 *
 * Match levers:
 * - signed char mask: hoists li 2 before li -64
 * - volatile u16 val: keeps both same-address stores
 * - ASM_REG pins $2/$3 + empty-asm "=r"/"0" barriers (gcc 2.7.2 has no +r):
 *   force lhu→$v0, and→$v1, first sh of $v1, then addiu $v0,$v1,14 / sh $v0
 */
void func_80048B8C(S_80048B8C *arg0) {
    u8 *cur;
    S_80048B8C_node *node;
    S_80048B8C_entry *entry;
    volatile u16 *valptr;
    register int loaded ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register int new_var ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    signed char mask;

    cur = arg0->list + (arg0->index << 2);
    if (cur < arg0->listEnd) {
        entry = (S_80048B8C_entry *)cur;
        mask = ~0x3F;
        do {
            if (entry->type == 2) {
                node = entry->node;
                if (!(node->flags & 8)) {
                    node->flags |= 8;
                    valptr = &node->val;
                    do {
                        loaded = *valptr;
                        __asm__("" : "=r"(loaded) : "0"(loaded));
                        new_var = loaded & mask;
                        __asm__("" : "=r"(new_var) : "0"(new_var));
                        *valptr = new_var;
                        __asm__("" : "=r"(new_var) : "0"(new_var));
                        loaded = new_var + 0xE;
                        *valptr = loaded;
                        valptr = (volatile u16 *)((u8 *)valptr + 0xC);
                    } while (!((node++)->flags & 0x80));
                }
            }
            entry = (S_80048B8C_entry *)((u8 *)entry + 8);
            cur += 8;
        } while (cur < arg0->listEnd);
    }
}

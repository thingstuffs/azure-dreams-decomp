#include "common.h"

/* Scans the global node list D_80081498 for the first node (other than a1)
 * whose field_1E has bit 0x200 set. If found: refreshes it via
 * func_80044A50/func_8003FFF0, then recycles it via func_80040044 unless
 * bit 0x80 is also set, then dispatches to func_8003FD64(a0,a1) if a1 is
 * non-NULL, else func_8003FC64(a0), and returns that call's result. If no
 * such node exists, returns NULL. */
typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern struct {
    Node *head;
    int pad[2];
} D_80081498;

extern void func_80044A50(void *a0);
extern void func_8003FFF0(void *a0);
extern void func_80040044(void *a0);
extern void *func_8003FD64(void *a0, void *a1);
extern void *func_8003FC64(void *a0);

void *func_8003FB98(void *a0, void *a1)
{
    Node *s0;

    s0 = D_80081498.head;
    if (s0 != 0) {
        do {
            if ((s0->field_1E & 0x200) && a1 != (void *)s0) {
                func_80044A50(s0);
                func_8003FFF0(s0);
                if (!(s0->field_1E & 0x80)) {
                    func_80040044(s0);
                }
                if (a1 != 0) {
                    s0 = func_8003FD64(a0, a1);
                } else {
                    s0 = func_8003FC64(a0);
                }
                return s0;
            }
            s0 = s0->next;
        } while (s0 != 0);
    }
    return 0;
}

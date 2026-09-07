#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

extern void func_8008EFD8(void);
extern Node D_800CFCB4[];

s32 func_8008EFA0(Node *arg0) {
    register u32 page ASM_REG("$3") = 0x800D0000;

    if (arg0 != NULL) {
        Node *head;
        ASM_KEEP(page);
        head = (Node *)(page - 0x34C);
        arg0->prev = head;
        arg0->next = head->next;
        head->next->prev = arg0;
        head->next = arg0;
        return 1;
    }
    ASM_KEEP(page);
    func_8008EFD8();
    return 0;
}

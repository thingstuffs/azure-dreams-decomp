#include "common.h"

typedef struct S_801EAFE8
{
    struct S_801EAFE8 *next;
    u8 pad[0x124 - 4];
} S_801EAFE8;

extern S_801EAFE8 D_801EAFE8[0x100];

typedef struct S_80081490
{
    void *head;
    s32 pad1;
    s32 pad2;
} S_80081490;

extern S_80081490 D_80081490;

typedef struct S_80081498
{
    void *head;
    s32 pad[2];
} S_80081498;

extern S_80081498 D_80081498;

typedef struct S_80044AAC S_80044AAC;

extern S_80044AAC *D_800833E0[0x20];
extern S_80044AAC *D_80083360[0x20];
extern void func_8003DB4C(s32 *p, s32 n);

/* Initialize the node pool free list and reset the pointer tables. */
void func_8003FAD4(void)
{
    s32 index;
    u32 pool_page;
    S_801EAFE8 *free_node;
    S_801EAFE8 *clear_node;
    S_80044AAC **slots_a_base;
    S_80044AAC **slots_b_base;
    S_80044AAC **slot_a;
    S_80044AAC **slot_b;

    pool_page = 0x801F0000;
    ASM_KEEP_NV(pool_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    free_node = (S_801EAFE8 *)(pool_page - 20504);

    for (index = 0, clear_node = free_node; index < 0x100; index++) {
        func_8003DB4C((s32 *)clear_node, 0x49);
        clear_node = (S_801EAFE8 *)(((u8 *)clear_node) + 0x124);
    }

    for (index = 0xFE; index >= 0; index--) {
        free_node->next = (S_801EAFE8 *)(((u8 *)free_node) + 0x124);
        free_node = free_node->next;
    }

    index = 0x1F;
    slots_a_base = D_800833E0;
    slot_a = slots_a_base + 0x1F;
    ASM_KEEP(slots_a_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    slots_b_base = D_80083360;
    slot_b = slots_b_base + 0x1F;
    ASM_KEEP(slots_b_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    free_node->next = 0;
    D_80081498.head = 0;
    D_80081490.head = D_801EAFE8;

    for (; index >= 0; index--) {
        *slot_b = 0;
        *slot_a = 0;
        slot_a--;
        slot_b--;
    }
}

#include "common.h"

#include "common.h"

typedef struct S_8004F5F4_sub {
    u8 pad0[0x4];
    void *result;
} S_8004F5F4_sub;

typedef struct S_8004F5F4_node {
    u8 pad0[0x10];
    void (*callback)(void *self);
    u8 pad14[0x1E - 0x14];
    u16 flags;
    S_8004F5F4_sub sub;
} S_8004F5F4_node;

extern void *func_8003FC64(s32 a0);
extern void func_8004F5B0(void *a0);
extern void *func_8004FDE0(void *a0);
extern s32 D_800814A0;
extern s32 D_800814A0_w asm("D_800814A0");

void *func_8004F5F4(void *a0, void *a1)
{
    S_8004F5F4_node *s0 = (S_8004F5F4_node *)func_8003FC64(0);
    void *new_var;
    S_8004F5F4_sub *v1;
    s32 global_flags;
    u8 *global_page;

    if (s0 != 0) {
        s0->callback = func_8004F5B0;
        v1 = &s0->sub;
        new_var = (v1->result = func_8004FDE0(a1));
        if (new_var == 0) {
            do {
                s0->flags |= 0x8000;
            } while (0);
            global_flags = D_800814A0_w;
            s0 = 0;
            global_flags |= 0x8000;
            
#ifdef NON_MATCHING
            D_800814A0 = global_flags;
#else
            global_page = (u8 *)0x80080000;
            
            *(s32 *)(global_page + 0x14A0) = global_flags;
#endif
        }
    }
    return s0;
}

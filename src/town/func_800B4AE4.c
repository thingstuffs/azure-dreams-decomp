#include "common.h"

extern void func_800B2190(void *arg0, s32 arg1);
extern s32 func_800B2214(void *arg0, s32 arg1, s32 arg2);

/* del_t_item_w_ptr: Find the town item pointer and delete its table entry. */
void del_t_item_w_ptr(s32 item_ptr) {
    func_800B2190((void *)0x8001029C, func_800B2214((void *)0x8001029C, item_ptr, 0x14));
}

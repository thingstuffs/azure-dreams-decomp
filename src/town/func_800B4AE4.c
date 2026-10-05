#include "common.h"

extern void func_800B2190(void *list_addr, s32 index);
extern s32 func_800B2214(void *values, s32 target_value, s32 count);

/* del_t_item_w_ptr: Find the town item pointer and delete its table entry. */
void del_t_item_w_ptr(s32 item_ptr) {
    func_800B2190((void *)0x8001029C, func_800B2214((void *)0x8001029C, item_ptr, 0x14));
}

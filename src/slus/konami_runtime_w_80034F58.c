#include "common.h"

#include "common.h"
#include "slus/owned_80035484.h"
void func_80035484(s32 object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config);   /* extern */
extern u8 D_80081EB0[];
extern u8 D_800820A8[];

/* Passes the fixed runtime data pair and supplied value to func_80035484. */
void func_80034F58(s32 value) {
    func_80035484(&D_800820A8, &D_80081EB0, value);
}

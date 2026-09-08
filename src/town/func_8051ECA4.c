#include "common.h"

extern s32 func_80017710(s32 *arg0, s32 arg1);
extern s32 D_80018D78[];

/* Look up a key in D_80018D78 and return the entry value. */
s32 func_8051ECA4(s32 unused_first, s32 unused_second, s32 lookup_key) {
    s32 *table_base = D_80018D78;
    s32 entry_index = func_80017710(table_base, lookup_key);
    
    return *(s32 *)((s8 *)table_base + (entry_index * 8) + 4);
}

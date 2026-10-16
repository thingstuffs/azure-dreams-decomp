#include "common.h"
extern void func_80172A58(void *,void *,void *,void *);

/* Logical switch allocation owned by func_80172A58.
 * This ledger projection is not included in the native TU. The complete
 * C switch owner independently emits every physical case relocation. */
const u32 D_80170838[7]={
 (u32)((u8 *)func_80172A58+0x11C),
 (u32)((u8 *)func_80172A58+0x114),
 (u32)((u8 *)func_80172A58+0x10C),
 (u32)((u8 *)func_80172A58+0x124),
 (u32)((u8 *)func_80172A58+0xCC),
 (u32)((u8 *)func_80172A58+0xC4),
 (u32)((u8 *)func_80172A58+0xBC),
};

#include "common.h"
extern u8 *func_800990FC(void);
extern u8 *func_80099734(void *,u8 *);
extern u8 *func_80099194(u8 *,u8 *);
extern void *func_80099290(s8 *);
extern s32 func_800A5720(s8 *);
extern u8 D_801745F8[];
/* Build an encoded message from the record and this bank's suffix. */
void func_801744B8(void *record) {
 u8 *original;
 u8 *current;
 u8 *cursor;
 cursor=func_80099734(record,current=func_800990FC());
 original=current;
 current=cursor;
 func_80099290((s8 *)func_80099194(D_801745F8,current));
 func_800A5720((s8 *)original);
}

/* Relink of matched town/func_800B8368; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"

extern void func_800B5C60(s32, void *, s32);                            /* extern */
extern void func_800B5D70(void *, void *);                /* extern */
extern void func_800B5E28(void *, void *);                /* extern */
extern void func_800B63EC(void *, s32);                /* extern */

/* Run four setup routines with the supplied context and data. */
void func_800B640C(s32 context, void * data, s32 value) {
    func_800B5C60(context, data, value);
    func_800B5D70(context, data);
    func_800B5E28(context, data);
    func_800B63EC(context, data);
}

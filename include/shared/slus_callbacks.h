#ifndef SHARED_SLUS_CALLBACKS_H
#define SHARED_SLUS_CALLBACKS_H

/* SLUS functions whose ADDRESS the overlays pass around, declared once.  The decompiler first saw these as data
 * (`extern u8 D_80045340[];`, `&D_80045340`): no row ever loads or stores through them, and the retail bytes at the
 * address are code (0x80045340: addiu $sp,-32 / sw $s0 ...), defined by slus/w_80045340.
 * func_80045340: the callback 442 dungeon/town rows hand to func_8004491C (effect/particle registration); it walks
 * a group's entry chain (see slus/w_80045340).  Parameter types are void * here; the row keeps its own views. */
int func_80045340(void *group_data, int context, void *entry, int unused);

#endif

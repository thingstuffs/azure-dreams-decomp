#include "common.h"

/* Global >8-byte struct accessed via %hi/%lo (passed by address to func_8003DB94
 * as its `Elem`-shaped table argument). */
extern u8 D_800720AC[12];

/* callback/update-function pointers, assigned by address only */
extern void func_800517CC(void);
extern void func_80044BB0(void);

/* struct Elem / struct Dst mirror the layout used by the already-matched
 * func_8003DB94 (src/code.c), extended with the extra fields (0x1C/0x1E)
 * this function also touches — the real struct is larger than what
 * func_8003DB94 alone accesses. */
typedef struct S_80051BFC_Elem {
    u8 b0;
    u8 pad1;
    u8 pad2;
    u8 pad3;
    s32 f4;
} S_80051BFC_Elem;

typedef struct S_80051BFC_Dst {
    S_80051BFC_Elem *f0;
    u8 f4;
    u8 f5;
    u8 pad6;
    u8 pad7;
    s32 f8;
    s32 fc;
    s32 f10;
    u16 f14;
    u8 pad16[0x1C - 0x16];
    u16 f1c;
    u16 f1e;
} S_80051BFC_Dst;

extern void func_8003DB94(S_80051BFC_Dst *a0, S_80051BFC_Elem *a1, s16 a2);
extern void func_8004491C(void *a0, void *a1);

/* Sub-record living at offset 0x20 of the top-level object: a word value
 * followed by three shorts. */
typedef struct S_80051BFC_Sub {
    s32 val;
    s16 x;
    s16 y;
    s16 z;
} S_80051BFC_Sub;

/* Top-level object initialized by this function. */
typedef struct S_80051BFC_Obj {
    u8 pad0[0x8];
    s32 *f8;              /* pointer to a 3-word render-color/vector block */
    S_80051BFC_Dst *fc;
    void (*f10)(void);    /* update-function pointer */
    u8 pad14[0x20 - 0x14];
    S_80051BFC_Sub sub;
} S_80051BFC_Obj;

/* Initializes the object's slot state, callbacks, and default rendering values. */
void func_80051BFC(void *object_ptr, void *slot)
{
    S_80051BFC_Obj *object = (S_80051BFC_Obj *)object_ptr;
    S_80051BFC_Sub *slot_state;
    S_80051BFC_Dst *render_state;
    s32 *render_vector;

    object->f10 = func_800517CC;
    slot_state = &object->sub;
    object->sub.val = (s32)slot;
    slot_state->x = 0;
    slot_state->y = 0;
    slot_state->z = 0;

    render_state = object->fc;
    render_state->fc = 0x808080;
    func_8003DB94(render_state, (S_80051BFC_Elem *)D_800720AC, 0);

    render_state->f1e = 0x1000;
    render_state->f1c = 0x1000;
    func_8004491C(object, (void *)func_80044BB0);

    render_vector = object->f8;
    render_vector[0] = 0x01A00000;
    render_vector[1] = 0x00600000;
    render_vector[2] = 0x00700000;
}

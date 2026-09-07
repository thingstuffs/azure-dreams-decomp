#include "common.h"

/* S_80048500_elem: 8-byte element type indexed by a0 within a D_800710E4[a1] sub-array. */
typedef struct {
    s32 w0;
    s32 w1;
} S_80048500_elem;

/* Sized array (>8B) => forces %hi/%lo addressing (not $gp-relative). */
extern S_80048500_elem *D_800710E4[100];

/* S_80048500_target: struct pointed to by D_80081480.field_0; only the s16 field at
 * offset 0x18 is accessed here. */
typedef struct {
    s8 pad[0x18];
    s16 unk18;
} S_80048500_target;

/* S_80081480: >8B struct forced to hi/lo addressing; field_0 holds a pointer value. */
typedef struct {
    S_80048500_target *field_0;
    s32 pad4;
    s32 pad8;
} S_80081480;

extern S_80081480 D_80081480;

extern void func_80041284(void *arg);
extern void func_8003F320(void);
extern void DrawSync(s32 a0);
extern s32 func_8004846C(s32 a0);

/* Processes the selected element and passes the target value to func_8004846C after drawing completes. */
s32 func_80048500(s32 elem_index, s32 array_index)
{
    s32 target_value;

    func_80041284(&D_800710E4[array_index][elem_index]);
    func_8003F320();
    target_value = D_80081480.field_0->unk18;
    DrawSync(0);
    return func_8004846C(target_value);
}

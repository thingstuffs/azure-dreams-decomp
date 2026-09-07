#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800224E0_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    union { struct { void * v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    u8 pad_24[0x4];
    s16 unk_28;
} S_800224E0_0;   /* obj in func_800224E0 */

typedef struct S_800224E0_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800224E0_1;   /* prim in func_800224E0 */

typedef struct S_800224E0_2 {
    u8 pad_00[0x48];
    void * unk_48;
} S_800224E0_2;   /* parent in func_800224E0 */

typedef struct S_800224E0_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_800224E0_3;   /* slot in func_800224E0 */

typedef struct S_800224E0_4 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800224E0_4;   /* draw in func_800224E0 */



extern u8 D_80020224[];
extern u8 D_80022768[];
extern u8 D_80023404[];
extern u8 D_80023DE0[];
extern u8 D_80023EB0[];
extern u8 D_8002415C[];
extern u8 D_80024470[];
extern u8 D_800244A0[];
extern s32 D_80024628[];
extern u8 D_80024640[];
extern u8 D_80024680[];
extern u8 D_800246E0[];
extern u8 D_80046398[];

extern void func_80022290();
extern void func_80033B9C();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8004E9E4();
extern void func_8006733C();
extern void func_8008F104();

/* Creates parent and child display objects and uploads their graphics data. */
void func_800224E0(void)
{
    s16 upload_rect[4];
    s32 child_index;
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *obj;
    u8 *parent_state;
    u8 *child_slot;
    u8 *callback;
    u8 *prim;
    u8 *draw_state;
    u8 *object_state;
    u8 *child_script;
    u32 neutral_color;
    u8 *render_state;

    parent_state = NULL;
    callback = D_80020224;
    func_8004E9E4();
    D_80024628[0] = 0;
    func_80022290(D_800246E0);
    func_80033B9C(0xA4);

    obj = func_8003FC64(0x32);
    if (obj != NULL) {
        parent_state = obj + 0x20;
        prim = ((S_800224E0_0 *)obj)->unk_08;
        ((S_800224E0_0 *)obj)->unk_10 = D_80022768;
        ((S_800224E0_1 *)prim)->unk_00 = 0x04600000;
        ((S_800224E0_1 *)prim)->unk_04 = 0x03600000;
        ((S_800224E0_2 *)parent_state)->unk_48 = callback;
        func_8008F104(parent_state, prim, D_80024470);
    }

    child_index = 2;
    child_script = D_80023404;
    child_slot = parent_state + 8;
    do {
        obj = func_8003FC64(2);
        ((S_800224E0_3 *)child_slot)->unk_4C = obj;
        if (obj != NULL) {
            ((S_800224E0_0 *)obj)->unk_10 = child_script;
            ((S_800224E0_0 *)obj)->unk_28 = child_index;
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
        }
        child_index--;
        child_slot -= 4;
    } while (child_index >= 0);

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        neutral_color = 0x00808080;
        render_state = obj + 0x28;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_800224E0_0 *)obj)->unk_10 = D_80023DE0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        value = 0x1000;
        ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        prim = ((S_800224E0_0 *)obj)->unk_08;
        draw_state = ((S_800224E0_0 *)obj)->unk_0C;
        ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
        ((S_800224E0_4 *)draw_state)->unk_1C = value;
        ((S_800224E0_4 *)draw_state)->unk_1E = value;
        ((S_800224E0_4 *)draw_state)->unk_20 = value;
        ((S_800224E0_4 *)draw_state)->unk_08 = 0x2C;
        ((S_800224E0_4 *)draw_state)->unk_12 = 0;
        ((S_800224E0_4 *)draw_state)->unk_14 = 0;
        ((S_800224E0_4 *)draw_state)->unk_10 = 0;
        ((S_800224E0_4 *)draw_state)->unk_16 = 0;
        ((S_800224E0_4 *)draw_state)->unk_18 = 0;
        ((S_800224E0_4 *)draw_state)->unk_1A = 0;
        ((S_800224E0_4 *)draw_state)->unk_00 = 0;
        ((S_800224E0_4 *)draw_state)->unk_04 = 0;
        ((S_800224E0_4 *)draw_state)->unk_05 = 0;
        ((S_800224E0_4 *)draw_state)->unk_0C = neutral_color;
        ((S_800224E0_1 *)prim)->unk_00 = 0x04400000;
        ((S_800224E0_1 *)prim)->unk_04 = 0x02C00000;
        object_state = obj + 0x20;
        ((S_800224E0_1 *)prim)->unk_08 = 0;
        (*(void * volatile *)((u8 *)object_state + 0x50)) = callback;
        func_8008F104(render_state, ((S_800224E0_0 *)obj)->unk_08, D_800244A0);
    }

    child_index = 4;
    do {
        obj = func_8003FC64(0x100);
        if (obj != NULL) {
            func_8004491C(obj, D_8002415C);
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
            ((S_800224E0_0 *)obj)->unk_10 = D_80023EB0;
            obj += 0x20;
            ((S_800224E0_0 *)obj)->unk_20.at02.v = child_index;
            switch (child_index) {
            case 0:
                value = 1;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 1:
                value = 2;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 2:
                value = 3;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 3:
            case 4:
            default:
                break;
            }
        }
        child_index--;
    } while (child_index >= 0);

    upload_rect[0] = 0x40;
    upload_rect[1] = 0x1D0;
    upload_rect[2] = 0x20;
    upload_rect[3] = 1;
    func_8006733C(upload_rect, D_80024640);
    upload_rect[0] = 0xC0;
    upload_rect[1] = 0x1F8;
    upload_rect[2] = 0x30;
    upload_rect[3] = 1;
    func_8006733C(upload_rect, D_80024680);
}

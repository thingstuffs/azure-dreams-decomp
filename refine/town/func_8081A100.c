#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024100_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80024100_0;   /* obj in func_80024100 */

typedef struct S_80024100_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x4];
    s16 unk_0A;
    u16 unk_0C;
} S_80024100_1;   /* root in func_80024100 */

typedef struct S_80024100_2 {
    u8 pad_00[0x4];
    union { s32 i; void * p; } unk_04;   /* accessed as both */
    union { void * p; s32 i; } unk_08;   /* accessed as both */
    union { struct { void * v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s16 unk_14;
    union { s16 s; u16 u; } unk_16;   /* accessed as both */
    s16 unk_18;
    s16 unk_1A;
} S_80024100_2;   /* part in func_80024100 */


typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;


extern Vec3i D_80020090;
extern Vec3i D_800200A8;
extern s32 D_800243D8;
extern s32 D_80024954;
extern s32 D_800249A0;
extern s32 D_80024A30;
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_80083498[];

extern void func_80033B9C(s32);
extern void func_8003E188(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80048568(s32);
extern s32 rand(void);
extern void func_800C15C0(s32, s32);

/* Initializes shared state and three columns of linked display objects. */
s32 func_80024100(void)
{
    Vec3i primary_values;
    Vec3i secondary_values;
    void *parent_state;
    void *object;
    S_80024100_2 *element;
    void *update_callback;
    void *render_data;
    void *value_ptr;
    s32 column;
    register s32 x_pos ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 random_value;
    u16 element_flags;

    parent_state = NULL;
    primary_values = D_80020090;
    secondary_values = D_800200A8;

    func_800C15C0(0x24, 0x200);
    func_80033B9C(0x552);
    func_80033B9C(0xA4);
    func_80033B9C(0xA5);
    func_80048568(7);
    func_8003E188(0x3F, parent_state);

    object = func_8003FD64(0x136, D_80083498);
    if (object != NULL) {
        parent_state = (u8 *)object + 0x20;
        ((S_80024100_0 *)object)->unk_10 = &D_800243D8;
        ((S_80024100_1 *)parent_state)->unk_0A = 0x1E;
        random_value = rand();
        ((S_80024100_1 *)parent_state)->unk_04 = random_value & 3;
        ((S_80024100_1 *)parent_state)->unk_0C |= 4;
    }

    column = 2;
    update_callback = &D_80024954;
    x_pos = 0xD0;
    do {
        object = func_8003FD64(1, D_80083498);
        element = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            func_8004491C(object, D_80053858);
            element->unk_16.s = 0xB4;
            element->unk_18 = 3;
            element->unk_1A = 0x7C80;
            element->unk_14 = x_pos;
            element->unk_10.at00.v = 0x808080;
            element->unk_04.i = ((s32 *)&primary_values)[column];
            element->unk_0C.at00.v = parent_state;
        }
        column--;
        x_pos -= 0x58;
    } while (column >= 0);

    column = 2;
    update_callback = &D_800249A0;
    x_pos = 0xD8;
    do {
        object = func_8003FD64(1, D_80083498);
        element = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            func_8004491C(object, D_80053858);
            element->unk_16.s = 0xC4;
            element->unk_18 = 3;
            element->unk_1A = 0x7C80;
            element->unk_14 = x_pos;
            element->unk_10.at00.v = 0x808080;
            element->unk_04.i = ((s32 *)&secondary_values)[column];
            switch (column) {
            case 0:
                value_ptr = (u8 *)parent_state + 6;
                break;
            case 1:
                value_ptr = (u8 *)parent_state + 8;
                break;
            case 2:
                value_ptr = (u8 *)parent_state + 0xA;
                break;
            default:
                element->unk_0C.at00.v = parent_state;
                goto second_continue;
            }
            element->unk_08.p = value_ptr;
            element->unk_0C.at00.v = parent_state;
        }
second_continue:
        column--;
        x_pos -= 0x58;
    } while (column >= 0);

    column = 2;
    update_callback = &D_80024A30;
    x_pos = 0xCC;
    do {
        object = func_8003FD64(1, D_80083498);
        if (object != NULL) {
            render_data = &D_80053A88;
            ASM_KEEP(render_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
            element = (u8 *)object + 0x20;
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            func_8004491C(object, render_data);
            element_flags = element->unk_16.u;
            element->unk_0C.at02.v = 0xB0;
            element->unk_10.at00u.v = 0x50;
            element->unk_10.at02.v = 0x20;
            element->unk_0C.at00u.v = x_pos;
            element->unk_14 = 2;
            element->unk_08.i = 0x404040;
            element->unk_04.p = parent_state;
            element_flags |= 1;
            element->unk_16.u = element_flags;
        }
        column--;
        x_pos -= 0x58;
    } while (column >= 0);

    return 0;
}

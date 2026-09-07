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

s32 func_80024100(void)
{
    Vec3i first;
    Vec3i second;
    void *root;
    void *obj;
    S_80024100_2 *part;
    void *callback;
    void *final_callback;
    void *link;
    s32 i;
    register s32 coord ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 value;
    u16 flags;

    root = NULL;
    first = D_80020090;
    second = D_800200A8;

    func_800C15C0(0x24, 0x200);
    func_80033B9C(0x552);
    func_80033B9C(0xA4);
    func_80033B9C(0xA5);
    func_80048568(7);
    func_8003E188(0x3F, root);

    obj = func_8003FD64(0x136, D_80083498);
    if (obj != NULL) {
        root = (u8 *)obj + 0x20;
        ((S_80024100_0 *)obj)->unk_10 = &D_800243D8;
        ((S_80024100_1 *)root)->unk_0A = 0x1E;
        value = rand();
        ((S_80024100_1 *)root)->unk_04 = value & 3;
        ((S_80024100_1 *)root)->unk_0C |= 4;
    }

    i = 2;
    callback = &D_80024954;
    coord = 0xD0;
    do {
        obj = func_8003FD64(1, D_80083498);
        part = (u8 *)obj + 0x20;
        if (obj != NULL) {
            ((S_80024100_0 *)obj)->unk_10 = callback;
            func_8004491C(obj, D_80053858);
            part->unk_16.s = 0xB4;
            part->unk_18 = 3;
            part->unk_1A = 0x7C80;
            part->unk_14 = coord;
            part->unk_10.at00.v = 0x808080;
            part->unk_04.i = ((s32 *)&first)[i];
            part->unk_0C.at00.v = root;
        }
        i--;
        coord -= 0x58;
    } while (i >= 0);

    i = 2;
    callback = &D_800249A0;
    coord = 0xD8;
    do {
        obj = func_8003FD64(1, D_80083498);
        part = (u8 *)obj + 0x20;
        if (obj != NULL) {
            ((S_80024100_0 *)obj)->unk_10 = callback;
            func_8004491C(obj, D_80053858);
            part->unk_16.s = 0xC4;
            part->unk_18 = 3;
            part->unk_1A = 0x7C80;
            part->unk_14 = coord;
            part->unk_10.at00.v = 0x808080;
            part->unk_04.i = ((s32 *)&second)[i];
            switch (i) {
            case 0:
                link = (u8 *)root + 6;
                break;
            case 1:
                link = (u8 *)root + 8;
                break;
            case 2:
                link = (u8 *)root + 0xA;
                break;
            default:
                part->unk_0C.at00.v = root;
                goto second_continue;
            }
            part->unk_08.p = link;
            part->unk_0C.at00.v = root;
        }
second_continue:
        i--;
        coord -= 0x58;
    } while (i >= 0);

    i = 2;
    callback = &D_80024A30;
    coord = 0xCC;
    do {
        obj = func_8003FD64(1, D_80083498);
        if (obj != NULL) {
            final_callback = &D_80053A88;
            ASM_KEEP(final_callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
            part = (u8 *)obj + 0x20;
            ((S_80024100_0 *)obj)->unk_10 = callback;
            func_8004491C(obj, final_callback);
            flags = part->unk_16.u;
            part->unk_0C.at02.v = 0xB0;
            part->unk_10.at00u.v = 0x50;
            part->unk_10.at02.v = 0x20;
            part->unk_0C.at00u.v = coord;
            part->unk_14 = 2;
            part->unk_08.i = 0x404040;
            part->unk_04.p = root;
            flags |= 1;
            part->unk_16.u = flags;
        }
        i--;
        coord -= 0x58;
    } while (i >= 0);

    return 0;
}

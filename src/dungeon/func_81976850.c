#include "common.h"

typedef struct S_81976850_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    u16 unk_10;
} S_81976850_0;   /* arg0 in func_81976850 */

typedef struct S_81976850_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_81976850_1;   /* source in func_81976850 */

typedef struct S_81976850_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81976850_2;   /* arg1 in func_81976850 */

typedef struct S_81976850_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81976850_3;   /* coords in func_81976850 */

typedef struct S_81976850_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_81976850_4;   /* arg2 in func_81976850 */

typedef struct S_81976850_5 {
    s32 unk_00;
    s32 unk_04;
} S_81976850_5;   /* target in func_81976850 */

typedef struct S_81976850_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_81976850_6;   /* global in func_81976850 */

typedef struct S_81976850_7 {
    void * unk_00;
} S_81976850_7;   /* (void *)index in func_81976850 */

typedef struct S_81976850_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_81976850_8;   /* ((S_81976850_0 *)arg0)->unk_00 in func_81976850 */

typedef struct S_81976850_9 {
    u16 unk_00;
} S_81976850_9;   /* ((S_81976850_0 *)arg0)->unk_08 in func_81976850 */

typedef struct S_81976850_10 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81976850_10;   /* ((S_81976850_0 *)arg0)->unk_04 in func_81976850 */



typedef struct Vec16 {
    s16 x;
    s16 y;
    s16 z;
} Vec16;

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 *D_800E3D18;

extern void func_80024188(void) __attribute__((noreturn));
extern void func_80024380() __attribute__((noreturn));
extern void func_800243A0(void) __attribute__((noreturn));
extern s32 func_8003DE58(void *, void *, Vec16 *, s16);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);

void func_81976850(void *arg0, void *arg1, void *arg2)
{
    Vec16 delta;
    void *source;
    void *coords;
    void *target;
    void *global;
    void *object;
    u8 *collision;
    register void *incoming_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 tail_z;
    s32 random;
    s32 index;
    s16 state;
    s16 timer;
    u16 value;
    u8 color;

    state = ((S_81976850_0 *)arg0)->unk_0C.s;
    if (state != 1) {
        if (state < 2) {
            object = (u8 *)arg0 - 0x20;
            if (state == 0) {
                goto initialize;
            }
            func_80024380(object);
            return;
        }
        collision = (u8 *)0x80080000;
        if (state == 2) {
            goto state_two;
        }
        func_80024380(incoming_a0, collision);
        return;
    }

    goto state_one;

initialize:
    func_8004491C(object, &D_80045340);
    ((S_81976850_0 *)arg0)->unk_0C.u++;

state_one:
    source = ((S_81976850_8 *)(((S_81976850_0 *)arg0)->unk_00))->unk_0C;
    if ((((S_81976850_1 *)source)->unk_14 & 0x8000) ||
        func_8003DE58(((S_81976850_1 *)source)->unk_08, source, &delta, 0)) {
        coords = ((S_81976850_8 *)(((S_81976850_0 *)arg0)->unk_00))->unk_08;
        ((S_81976850_2 *)arg1)->unk_00.at02.v = ((S_81976850_3 *)coords)->unk_02;
        ((S_81976850_2 *)arg1)->unk_04.at02.v = ((S_81976850_3 *)coords)->unk_06;
        value = ((S_81976850_3 *)coords)->unk_0A;
        ((S_81976850_2 *)arg1)->unk_08.at02.v = value;

        if (!(((S_81976850_1 *)source)->unk_14 & 0x8000)) {
            ((S_81976850_2 *)arg1)->unk_00.at02.v += delta.x;
            ((S_81976850_2 *)arg1)->unk_04.at02.v += delta.y;
            ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            tail_z = ((S_81976850_2 *)arg1)->unk_08.at02.v;
            tail_z += delta.z;
            ASM_TAILSLOT_PIN(tail_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024188();
            return;
        }
        ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_81976850_2 *)arg1)->unk_08.at02.v = value - 0x20;
    }

    if (((S_81976850_9 *)(((S_81976850_0 *)arg0)->unk_08))->unk_00 & 0x80) {
        ((S_81976850_0 *)arg0)->unk_0E.s = 10;
        ((S_81976850_0 *)arg0)->unk_0C.u++;
        func_80024380();
        return;
    }
    goto epilogue_work;

state_two:
    ASM_KEEP(collision);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    collision += 0x2E80;
    color = ((S_81976850_4 *)arg2)->unk_0E + 8;
    ((S_81976850_4 *)arg2)->unk_0E = color;
    ((S_81976850_4 *)arg2)->unk_0D = color;
    ((S_81976850_4 *)arg2)->unk_0C = color;

    target = ((S_81976850_10 *)(((S_81976850_0 *)arg0)->unk_04))->unk_08;
    ((S_81976850_2 *)arg1)->unk_0C = ((S_81976850_5 *)target)->unk_00;
    (*(s32 *)((u8 *)arg1 + 0x10)) = ((S_81976850_5 *)target)->unk_04;

    global = D_800814A8;
    ((S_81976850_2 *)arg1)->unk_14 =
        (((S_81976850_6 *)global)->unk_88 - 0x50) << 16;

    index = ((D_80083228 + ((S_81976850_6 *)global)->unk_2A + 0x100) >> 7) & 0x1C;
    index += (s32)D_800E3D18;
    if (func_8003DE58(
            ((S_81976850_7 *)((void *)index))->unk_00,
            collision,
            &delta,
            0) != 0) {
        ((S_81976850_2 *)arg1)->unk_0C += delta.x << 16;
        ((S_81976850_2 *)arg1)->unk_10 += delta.y << 16;
        ((S_81976850_2 *)arg1)->unk_14 += delta.z << 16;
    }

    ((S_81976850_2 *)arg1)->unk_00.at00.v +=
        (((S_81976850_2 *)arg1)->unk_0C - ((S_81976850_2 *)arg1)->unk_00.at00.v) /
        ((S_81976850_0 *)arg0)->unk_0E.s;

    ((S_81976850_2 *)arg1)->unk_04.at00.v +=
        (((S_81976850_2 *)arg1)->unk_10 - ((S_81976850_2 *)arg1)->unk_04.at00.v) /
        ((S_81976850_0 *)arg0)->unk_0E.s;

    random = func_800644B8(((S_81976850_0 *)arg0)->unk_0E.s * 0xAA) << 7;
    ((S_81976850_2 *)arg1)->unk_08.at00.v +=
        (((S_81976850_2 *)arg1)->unk_14 - ((S_81976850_2 *)arg1)->unk_08.at00.v) /
        ((S_81976850_0 *)arg0)->unk_0E.s - random;

    timer = ((S_81976850_0 *)arg0)->unk_0E.u - 1;
    ((S_81976850_0 *)arg0)->unk_0E.s = timer;
    if (timer <= 0) {
        ((S_81976850_2 *)arg1)->unk_00.at00.v = ((S_81976850_2 *)arg1)->unk_0C;
        ((S_81976850_2 *)arg1)->unk_04.at00.v = ((S_81976850_2 *)arg1)->unk_10;
        ((S_81976850_2 *)arg1)->unk_08.at00.v = ((S_81976850_2 *)arg1)->unk_14;
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800243A0();
        return;
    }

epilogue_work:
    ((S_81976850_0 *)arg0)->unk_10++;
    ((S_81976850_4 *)arg2)->unk_1A += 0x300;
}

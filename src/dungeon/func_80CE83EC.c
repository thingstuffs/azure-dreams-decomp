#include "common.h"

typedef struct S_80171BEC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x2C];
    void * unk_40;
} S_80171BEC_0;   /* object in func_80171BEC */

typedef struct S_80171BEC_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80171BEC_1;   /* render in func_80171BEC */

typedef struct S_80171BEC_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80171BEC_2;   /* position in func_80171BEC */

typedef struct S_80171BEC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171BEC_3;   /* arg1 in func_80171BEC */

typedef struct S_80171BEC_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80171BEC_4_pre;   /* the 0x14 bytes before arg0 in func_80171BEC, addressed as arg0[-1] */

typedef struct S_80171BEC_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80171BEC_5;   /* owner in func_80171BEC */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Offset3;

typedef struct {
    u8 bytes[12];
} Packed3;

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern s32 func_8003DE58(s32, void *, Offset3 *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_80171A38;
extern Packed3 D_80175EE8;

void func_80171BEC(void *arg0, S_80171BEC_3 *arg1)
{
    Offset3 offset;
    void *object;
    S_80171BEC_1 *render;
    register u8 *copy_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register PackedWord *copy_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 copy0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 copy1 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 copy2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_80171BEC_2 *position;
    S_80171BEC_5 *owner;

    object = func_8003FD64(0x212, &D_80083498);
    if (object != 0) {
        ((S_80171BEC_0 *)object)->unk_40 = arg0;
        ((S_80171BEC_0 *)object)->unk_10 = &D_80171A38;
        func_8004491C(object, &D_80045340);

        render = ((S_80171BEC_0 *)object)->unk_0C;
        render->unk_10 = 0x20;
        render->unk_06 = 8;
        render->unk_14 |= 0xC;

        position = ((S_80171BEC_0 *)object)->unk_08;
        position->unk_00.at00.v = arg1->unk_00;
        position->unk_04.at00.v = arg1->unk_04;
        position->unk_08.at00.v = arg1->unk_08;

        owner = ((S_80171BEC_4_pre *)arg0)[-1].unk_00;
        if (func_8003DE58(owner->unk_08, owner, &offset, 0) != 0) {
            position->unk_00.at02.v += offset.x;
            position->unk_04.at02.v += offset.y;
            position->unk_08.at02.v += offset.z;
        }

        render = ((S_80171BEC_0 *)object)->unk_0C;
        render->unk_1E = 0x800;
        render->unk_1C = 0x800;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        copy_page = (u8 *)0x80170000;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        copy_source = (PackedWord *)(copy_page + 0x5EE8);
        copy0 = copy_source[0].value;
        copy1 = copy_source[1].value;
        copy2 = copy_source[2].value;
        ((PackedWord *)((u8 *)object + 0x44))[0].value = copy0;
        ((PackedWord *)((u8 *)object + 0x44))[1].value = copy1;
        ((PackedWord *)((u8 *)object + 0x44))[2].value = copy2;
        ASM_KEEP(copy2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render->unk_08 = (u8 *)object + 0x44;
    }
}

/* MECHANISM: One Offset3 call-output object yields stack slots 0x10/0x12/0x14
   and exactly the retail s3/s2/s1/s0 hold set; render is held in a3.
   A post-store fence and opaque v0 page feed the 0x5EE8 addiu into held a2.
   PackedWord live ranges in v1/a0/a1 reproduce the six unaligned copy pairs. */

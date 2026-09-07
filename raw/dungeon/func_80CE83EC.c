#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_80171BEC(void *arg0, void *arg1)
{
    Offset3 offset;
    void *object;
    register void *render ASM_REG("$7");
    register u8 *copy_page ASM_REG("$2");
    register PackedWord *copy_source ASM_REG("$6");
    register u32 copy0 ASM_REG("$3");
    register u32 copy1 ASM_REG("$4");
    register u32 copy2 ASM_REG("$5");
    void *position;
    void *owner;

    object = func_8003FD64(0x212, &D_80083498);
    if (object != 0) {
        FIELD(object, void *, 0x40) = arg0;
        FIELD(object, void *, 0x10) = &D_80171A38;
        func_8004491C(object, &D_80045340);

        render = FIELD(object, void *, 0xC);
        FIELD(render, s16, 0x10) = 0x20;
        FIELD(render, s16, 6) = 8;
        FIELD(render, u16, 0x14) |= 0xC;

        position = FIELD(object, void *, 8);
        FIELD(position, s32, 0) = FIELD(arg1, s32, 0);
        FIELD(position, s32, 4) = FIELD(arg1, s32, 4);
        FIELD(position, s32, 8) = FIELD(arg1, s32, 8);

        owner = FIELD(arg0, void *, -0x14);
        if (func_8003DE58(FIELD(owner, s32, 8), owner, &offset, 0) != 0) {
            FIELD(position, u16, 2) += offset.x;
            FIELD(position, u16, 6) += offset.y;
            FIELD(position, u16, 0xA) += offset.z;
        }

        render = FIELD(object, void *, 0xC);
        FIELD(render, s16, 0x1E) = 0x800;
        FIELD(render, s16, 0x1C) = 0x800;
        FIELD(render, u8, 0xE) = 0x80;
        FIELD(render, u8, 0xD) = 0x80;
        FIELD(render, u8, 0xC) = 0x80;

        ASM_SCHED_BARRIER();
        copy_page = (u8 *)0x80170000;
        ASM_KEEP(copy_page);
        copy_source = (PackedWord *)(copy_page + 0x5EE8);
        copy0 = copy_source[0].value;
        copy1 = copy_source[1].value;
        copy2 = copy_source[2].value;
        ASM_KEEP(copy_source);
        ((PackedWord *)((u8 *)object + 0x44))[0].value = copy0;
        ((PackedWord *)((u8 *)object + 0x44))[1].value = copy1;
        ((PackedWord *)((u8 *)object + 0x44))[2].value = copy2;
        ASM_KEEP(copy0);
        ASM_KEEP(copy1);
        ASM_KEEP(copy2);
        FIELD(render, void *, 8) = (u8 *)object + 0x44;
        ASM_KEEP(render);
    }
}

/* MECHANISM: One Offset3 call-output object yields stack slots 0x10/0x12/0x14
   and exactly the retail s3/s2/s1/s0 hold set; render is held in a3.
   A post-store fence and opaque v0 page feed the 0x5EE8 addiu into held a2.
   PackedWord live ranges in v1/a0/a1 reproduce the six unaligned copy pairs. */

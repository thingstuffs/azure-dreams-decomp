#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern u8 D_80171704[];
extern u8 D_80171CC0[];
extern u8 D_80171D90[];
extern u8 D_80171E60[];

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_80171FAC(void) __attribute__((noreturn));
extern void func_80172074(void) __attribute__((noreturn));

void func_80171F30(void *arg0, s32 arg1, s16 arg2_in, s16 arg3_in)
{
    void *object;
    void *header;
    register void *call_object ASM_REG("$4");
    register void *call_global ASM_REG("$5");
    register void *tail ASM_REG("$16");
    register s32 dispatch ASM_REG("$2");
    register s16 mode ASM_REG("$19");
    register s32 selector ASM_REG("$3");
    register s16 arg2 ASM_REG("$20");
    register s16 arg3 ASM_REG("$16");
    register s32 alloc_kind ASM_REG("$4");
    register void *alloc_source ASM_REG("$5");

    alloc_kind = 0x211;
    alloc_source = arg0;
    ASM_KEEP_NV(alloc_kind);
    ASM_KEEP_NV(alloc_source);
    arg3 = arg3_in;
    arg2 = arg2_in;
    object = func_8003FD64(alloc_kind, alloc_source);
    if (object == 0) {
        return;
    }

    mode = arg3;
    ASM_KEEP(mode);
    dispatch = ((s32)arg3) << 16;
    selector = dispatch >> 16;
    ASM_KEEP(selector);
    dispatch = (s32)0x80170000;
    if (selector == 0) {
        ASM_KEEP(dispatch);
        dispatch += 0x1CC0;
        ASM_TAILSLOT_PIN(dispatch);
        func_80171FAC();
    }
    ASM_KEEP(dispatch);
    dispatch = 1;
    if (selector == dispatch) {
        dispatch = (s32)0x80170000;
        ASM_KEEP(dispatch);
        dispatch += 0x1D90;
        ASM_TAILSLOT_PIN(dispatch);
        func_80171FAC();
    }

    ASM_KEEP(object);
    FIELD(object, void *, 0x10) = D_80171E60;
    FIELD(FIELD(object, void *, 8), u16, 2) =
        FIELD(FIELD(arg0, void *, 8), u16, 2);
    FIELD(FIELD(object, void *, 8), u16, 6) =
        FIELD(FIELD(arg0, void *, 8), u16, 6);
    FIELD(FIELD(object, void *, 8), u16, 0xA) =
        FIELD(FIELD(arg0, void *, 8), u16, 0xA);

    ASM_KEEP(mode);
    if ((mode << 16) == 0) {
        register void *data ASM_REG("$4");
        register s32 random ASM_REG("$2");
        register s32 coord ASM_REG("$3");

        random = rand();
        data = FIELD(object, void *, 8);
        coord = FIELD(data, u16, 2);
        random &= 7;
        coord -= 4;
        coord += random;
        FIELD(data, u16, 2) = coord;
        random = rand();
        data = FIELD(object, void *, 8);
        coord = FIELD(data, u16, 6);
        random &= 7;
        coord -= 4;
        ASM_KEEP(data);
        ASM_KEEP(random);
        ASM_TAILSLOT_PIN(coord);
        func_80172074();
    }

    ASM_KEEP(mode);
    {
        register void *data ASM_REG("$4");
        register s32 random ASM_REG("$2");
        register s32 coord ASM_REG("$3");

        random = rand();
        data = FIELD(object, void *, 8);
        coord = FIELD(data, u16, 2);
        random &= 0xF;
        coord -= 0xC;
        coord += random;
        FIELD(data, u16, 2) = coord;
        random = rand();
        data = FIELD(object, void *, 8);
        coord = FIELD(data, u16, 6);
        random &= 0xF;
        coord -= 0xC;
        coord += random;
        FIELD(data, u16, 6) = coord;
        ASM_KEEP(data);
        ASM_KEEP(random);
        ASM_KEEP(coord);
    }

    call_object = object;
    call_global = D_80171704;
    ASM_KEEP(call_object);
    ASM_KEEP(call_global);
    header = FIELD(object, void *, 0xC);
    ASM_KEEP(header);
    tail = (u8 *)object + 0x20;
    ASM_KEEP(tail);
    FIELD(header, s16, 6) = 0;
    FIELD(tail, s16, 0x32) = arg2;
    FIELD(tail, s16, 0x34) = arg2;
    func_8004491C(call_object, call_global);
    FIELD(object, s32, 0x20) = arg1;
    FIELD(tail, s32, 8) = arg1;
}

/* MECHANISM: Six callee-saved lifetimes give the 0x30 frame; non-volatile keeps
   on pinned allocator args order li/move before s0/s4 saves without blocking
   the jal delay-slot save.  Fixed v0/v1/a0 continuation values plus sanctioned
   tail-slot pins reproduce both dispatch arms and the RNG continuation. */

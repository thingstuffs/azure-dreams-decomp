#include "common.h"

typedef struct {
    s32 v[5];
} Word5;

typedef struct {
    s32 v[8];
} Word8;

typedef struct {
    s32 v[4];
} Word4;

typedef struct {
    s32 w0;
    s32 w4;
} __attribute__((packed)) Packed8;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    s32 w8;
    s16 hC;
    s16 hE;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    s32 pad18[4];
} Init40;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    void *p8;
    void *pC;
    s32 w10;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 pad1E;
    s32 pad20[4];
} Init10;

#define AT(type, base, off) (*(type *)((u8 *)(base) + (off)))

extern Word5 D_80020100[];
extern Word8 D_80020114[];
extern Word4 D_80020134[];
extern Packed8 D_80020144[];
extern u8 D_800218E4[];
extern u8 D_80022484[];
extern u8 D_800225F0[];
extern u8 D_80023158[];
extern u8 D_80023260[];
extern u8 D_80023A00[];
extern u8 D_80023C80[];
extern Packed8 D_80024310[];
extern u8 D_80045340[];
extern u8 D_80046398[];
extern u8 D_80082E80[];
extern s32 D_80082EA8[];
extern u8 D_80083498[];
extern u8 D_800F15E4[];
extern s32 D_800135B4[];

extern void func_8002108C();
extern void func_80021120();
extern void func_80022FD8();
extern void func_80023DA0();
extern void func_80033B9C();
extern void func_8003DB94();
extern void func_8003E188();
extern u8 *func_8003FC64();
extern u8 *func_8003FD64();
extern void func_8004491C();
extern s16 func_800C2AE8();

s32 func_800212B8(void) {
    u8 *owner = 0;
    Init10 init10;
    Init40 init40;
    Word5 table5 = D_80020100[0];
    Word8 table8 = D_80020114[0];
    Word4 table4 = D_80020134[0];
    u8 *obj;
    u8 *sprite;
    u8 *child;
    u8 *state;
    s32 *timer;
    s32 *tablep;
    Packed8 *packed;
    s32 i;
    s32 offset;
    s16 value;

    func_80033B9C(0x58D);
    func_80033B9C(0x58E);
    func_8003E188(0xE, 0);

    obj = func_8003FD64(1, D_80083498);
    if (obj != 0) {
        owner = obj + 0x20;
        AT(s16, owner, 0x2E) = 0x2D;
        AT(void *, obj, 0x10) = D_800218E4;
    }
    AT(void *, D_80083498, 0x74) = owner;
    func_80023DA0(owner);

    init40.hC = 0x10;
    init40.hE = 0x10;
    init40.h10 = 0x68;
    init40.h12 = 0x40;
    init40.h14 = 2;
    init40.h16 = 1;
    init40.w8 = 0x404040;
    init40.h0 = 0;
    init40.p4 = owner;
    func_80021120(D_80022484, &init40);

    {
        i = 3;
        init40.hC = -2;
        init40.hE = -2;
        init40.h14 = 0;
        init40.h16 = 0;
        do {
            init40.w8 = (0x80 << (i * 8)) & 0xFFFFFF;
            init40.p4 = owner + i * 4;
            func_80021120(D_80023C80, &init40);
            i--;
        } while (i >= 0);
    }

    {
        s32 loop_i;
        Init10 *loop_init10;
        init10.h14 = 0x14;
        init10.h18 = 3;
        init10.h1C = 0;
        init10.h1A = 0x7C80;
        init10.w10 = 0x808080;
        init10.h0 = 0;
        init10.pC = owner;
        loop_i = 4;
        loop_init10 = &init10;
        do {
            register u8 *a0v ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
            register Init10 *a1v ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            a0v = D_800225F0;
            a1v = loop_init10;
            ASM_KEEP_DEP_NV(a1v, a0v);   /* MATCH pin: keeps a statement from moving across a call/branch */
            init10.h16 = loop_i * 0xC + 0x14;
            init10.p4 = (void *)((s32 *)&init10)[0x16 + loop_i];
            loop_i--;
            func_8002108C(a0v, a1v);
        } while (loop_i >= 0);
    }

    init10.h14 = 0x3C;
    timer = (s32 *)0x800135B4;
    if (*timer == 0) {
        *timer = 0x258;
    }
    AT(u16, owner, 0x38) = *(u16 *)timer;
    {
        s32 loop_i = 4;
        register s32 copy_page ASM_REG("$20") = (s32)0x80020000;   /* MATCH pin: retail keeps a computation the compiler would drop */
        register s32 loop_offset ASM_REG("$19") = 0x38;   /* MATCH pin: retail register colouring depends on it */
        s16 loop_value = 0x44;
        Packed8 *packed_v0 = D_80024310;
        Packed8 *loop_packed = packed_v0 + 4;
        s32 call_page;
        do {
            register Packed8 *copy_src ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            copy_src = (Packed8 *)(copy_page + 0x144);
            ASM_KEEP_NV(copy_src);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            *loop_packed = *copy_src;
            AT(s8, loop_packed, 7) = 0;
            init10.h16 = loop_value;
            init10.p4 = loop_packed;
            init10.p8 = owner + loop_offset;
            call_page = (s32)0x80020000;
            ASM_KEEP_DEP_NV(call_page, copy_page);   /* MATCH pin: load-bearing for the whole function shape */
            func_8002108C((u8 *)(call_page + 0x2FD8), &init10);
            loop_offset -= 2;
            loop_value -= 0xC;
            loop_i--;
            loop_packed--;
        } while (loop_i >= 0);
    }

    {
        s32 loop_i = 7;
        s32 asset_v0 = (s32)0x80020000;
        u8 *loop_asset;
        register s16 loop_scale ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
        u8 *loop_sprite;
        ASM_KEEP(asset_v0);   /* MATCH pin: keeps a constant in a register as retail does */
        loop_asset = (u8 *)(asset_v0 + 0x3158);
        loop_scale = 0x1000;
        do {
            obj = func_8003FC64(0x136);
            if (obj != 0) {
                func_8004491C(obj, D_80046398);
                loop_sprite = AT(u8 *, obj, 0xC);
                AT(void *, obj, 0x10) = loop_asset;
                AT(s32, loop_sprite, 0xC) = 0x808080;
                AT(s16, loop_sprite, 0x1C) = loop_scale;
                AT(s16, loop_sprite, 0x1E) = loop_scale;
                AT(s16, loop_sprite, 0x20) = loop_scale;
                AT(s32, loop_sprite, 8) = table8.v[loop_i];
                AT(s32, AT(u8 *, obj, 8), 0) = ((loop_i >> 2) << 22) + 0x0FE00000;
                AT(s32, AT(u8 *, obj, 8), 4) = ((loop_i % 4) << 22) + 0x03E00000;
                AT(s32, AT(u8 *, obj, 8), 8) = 0;
                AT(void *, obj, 0x20) = owner;
            }
            loop_i--;
        } while (loop_i >= 0);
    }

    i = 3;
    do {
        obj = func_8003FC64(0x136);
        if (obj != 0) {
            func_8004491C(obj, D_80045340);
            sprite = AT(u8 *, obj, 0xC);
            AT(void *, obj, 0x10) = D_80023158;
            AT(s16, sprite, 0x1E) = 0x1000;
            AT(s16, sprite, 0x1C) = 0x1000;
            AT(s32, sprite, 0xC) = 0x808080;
            func_8003DB94(sprite, (void *)table4.v[i], 0);
            AT(u16, sprite, 0x12) = 0xFFC0;
            AT(s32, AT(u8 *, obj, 8), 0) = ((i >> 2) << 22) + 0x0FD00000;
            AT(s32, AT(u8 *, obj, 8), 4) = ((i % 4) << 22) + 0x04100000;
            AT(s32, AT(u8 *, obj, 8), 8) = 0xFF600000;
            AT(void *, obj, 0x20) = owner;
        }
        i--;
    } while (i >= 0);

    {
        u8 *ret_v0;
        register u8 *obj_s0 ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
        register s32 loop_i ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
        u8 *loop_state;
        s16 loop_value;
        register u8 *loop_tablep ASM_REG("$20");   /* MATCH pin: retail keeps a computation the compiler would drop */
        loop_state = D_80082E80;
        loop_i = 2;
        ASM_KEEP_DEP_NV(loop_i, loop_state);   /* MATCH pin: keeps a constant in a register as retail does */
        loop_value = 0xC;
        loop_tablep = owner + 8;
        do {
            ret_v0 = func_8003FD64(0x136, D_80083498);
            obj_s0 = ret_v0;
            ASM_KEEP(obj_s0);   /* MATCH pin: retail register colouring depends on it */
            AT(void *, loop_tablep, 0x20) = ret_v0;
            if (obj_s0 != 0) {
                obj = obj_s0;
                AT(void *, obj, 0x10) = D_80023260;
                func_8004491C(obj, D_80045340);
                sprite = AT(u8 *, obj, 0xC);
                AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
                AT(s32, AT(u8 *, obj, 8), 4) = (loop_i << 22) + 0x04200000;
                child = obj + 0x20;
                AT(s16, AT(u8 *, obj, 8), 0xA) = func_800C2AE8(AT(void *, obj, 8));
                AT(s16, sprite, 0x1E) = 0x1000;
                AT(s16, sprite, 0x1C) = 0x1000;
                AT(s32, sprite, 0x28) = AT(s32, loop_state, 0x28);
                AT(s16, child, 0x2A) = 0x800;
                func_8003DB94(sprite, D_800F15E4, 0);
                AT(s32, sprite, 0xC) = 0x808080;
                AT(s16, sprite, 0x12) = loop_value;
                AT(void *, obj, 0x20) = owner;
                AT(s16, child, 0x24) = loop_i + 1;
            }
            loop_value -= 4;
            loop_i--;
            loop_tablep -= 4;
        } while (loop_i >= 0);
    }

    obj = func_8003FD64(0x136, D_80083498);
    if (obj != 0) {
        AT(void *, obj, 0x10) = D_80023A00;
        func_8004491C(obj, D_80045340);
        sprite = AT(u8 *, obj, 0xC);
        AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
        AT(s32, AT(u8 *, obj, 8), 4) = 0x03E00000;
        child = obj + 0x20;
        AT(s16, AT(u8 *, obj, 8), 0xA) = func_800C2AE8(AT(void *, obj, 8));
        AT(s16, sprite, 0x1E) = 0x1000;
        AT(s16, sprite, 0x1C) = 0x1000;
        AT(s32, sprite, 0x28) = D_80082EA8[0];
        AT(s16, child, 0x2A) = 0x800;
        func_8003DB94(sprite, D_800F15E4, 0);
        AT(s32, sprite, 0xC) = 0x808080;
        AT(void *, obj, 0x20) = owner;
    }
    return 0;
}

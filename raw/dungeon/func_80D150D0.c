#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800C8788(void *, void *);

extern u8 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern s32 D_80083498;
extern s8 D_800DCECC[];
extern u8 D_80170000[];
extern u8 D_80170AD0[];
extern u8 D_80171760[];

typedef struct {
    s16 delta[3];
    u16 pad06;
    u16 pos[3];
    u16 pad0E;
    s32 out0[2];
    s32 out1;
    s32 out2;
    void *owner;
    u8 pad24[4];
    u16 count;
    u8 pad2A[6];
    void *p[3];
} LocalFrame;

typedef struct {
    s32 w[4];
} Copy16;

void func_801748D0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    LocalFrame local;
    void *obj;
    register void *body ASM_REG("$18");
    void *mesh;
    register void *anchor ASM_REG("$19");
    void *link;
    void *link_value;
    register void *body_link ASM_REG("$2");
    register void *src ASM_REG("$7");
    void *dst;
    void *src_end;
    void *resultp;
    register void *scratch ASM_REG("$9");
    register s32 height ASM_REG("$16");
    s32 second_height;
    u16 state;
    u16 timer;
    u16 z;
    u16 flags;
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register void *tex_base ASM_REG("$2");
    register u16 mesh_flags ASM_REG("$3");
    register s32 calc_a0 ASM_REG("$4");
    register s32 calc_v1 ASM_REG("$3");
    register u8 loop_mode ASM_REG("$2");
    s32 mode;

    scratch = (u8 *)arg0 - 0x20;
    local.owner = scratch;
    mode = FIELD(arg0, u8, 0x9B);
    if (mode == 1) {
        goto state1;
    }
    if ((s32)mode < 2) {
        if (mode == 0) {
            goto state0;
        }
        goto done;
    }
    if (mode == 2) {
        goto state2;
    }
    if (mode == 3) {
        goto state3;
    }
    goto done;

state0:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s32)(timer << 16) <= 0) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        flags = FIELD(arg2, u16, 0x14);
        FIELD(arg2, u16, 0x14) = flags & 0xF7FF;
    }
    goto done;

state1:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_800A56E0(0x80D);
    }
    scratch = &local.pos[0];
    local.p[0] = scratch;
    scratch = &local.out0[0];
    local.p[1] = scratch;
    scratch = &local.out1;
    resultp = &local.out2;
    local.count = 0;
    local.p[2] = scratch;
    ASM_KEEP(scratch);
state1_loop:
    call_a0 = (void *)0x112;
    ASM_KEEP(call_a0);
state1_call:
#ifdef __mips__
    call_a1 = (void *)0x80080000;
#else
    call_a1 = (u8 *)&D_80083498 - 0x3498;
#endif
    ASM_KEEP(call_a1);
    call_a1 = (u8 *)call_a1 + 0x3498;
    obj = func_8003FD64((s32)call_a0, call_a1);
    body = (u8 *)obj + 0x20;
    if (obj == 0) {
        goto state1_next;
    }
    ASM_KEEP(body);
    FIELD(body, s16, 0x96) = 0x2D;
    FIELD(body, s16, 0x9E) = 0x2D;
    FIELD(obj, void *, 0x10) = D_80170AD0;
    body_link = FIELD(arg3, void *, 0x60);
    if (body_link == 0) {
        FIELD(body, void *, 0xA8) = arg1;
        FIELD(body, s16, 0xA2) = 0;
    } else {
        link_value = FIELD(body_link, void *, -0x18);
        FIELD(body, s16, 0xA2) = 1;
        FIELD(body, void *, 0xA8) = link_value;
    }
    FIELD(body, u16, 0x94) = FIELD(arg3, s16, 0x2A);
    mesh = FIELD(obj, void *, 0xC);
    anchor = FIELD(body, void *, 0xA8);
    src = arg2;
    dst = mesh;
    src_end = (u8 *)arg2 + 0x30;
    do {
        *(Copy16 *)dst = *(Copy16 *)src;
        src = (u8 *)src + 0x10;
        dst = (u8 *)dst + 0x10;
    } while (src != src_end);
    call_a0 = obj;
    call_a1 = &D_80045340;
    ASM_KEEP(call_a1);
    mesh_flags = FIELD(mesh, u16, 0x14);
    ASM_KEEP(mesh_flags);
    FIELD(mesh, s16, 0x1E) = 0x400;
    FIELD(mesh, s16, 0x1C) = 0x400;
    FIELD(mesh, u8, 0xE) = 0x80;
    FIELD(mesh, u8, 0xD) = 0x80;
    FIELD(mesh, u8, 0xC) = 0x80;
    FIELD(mesh, s16, 0x10) = 0x20;
    FIELD(mesh, u16, 0x12) = 0xFF80;
    ASM_KEEP(mesh);
    mesh_flags |= 0xC;
    FIELD(mesh, u16, 0x14) = mesh_flags;
    func_8004491C(call_a0, call_a1);
    call_a0 = mesh;
    call_a2 = 0;
    ASM_KEEP(call_a2);
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);
#else
    tex_base = D_80170000;
#endif
    call_a1 = (void *)(s32)FIELD(tex_base, u8, 0x4ED0);
    tex_base = (u8 *)tex_base + 0x4ED0;
    FIELD(mesh, u8 *, 0x2C) = tex_base;
    func_80047784(call_a0, (s32)call_a1, call_a2);
    obj = FIELD(obj, void *, 8);
    FIELD(obj, u16, 2) = FIELD(anchor, u16, 2);
    FIELD(obj, u16, 6) = FIELD(anchor, u16, 6);
    z = FIELD(anchor, u16, 0xA);
    FIELD(obj, u16, 0xA) = z;
    if (FIELD(arg3, void *, 0x60) == 0) {
        scratch = local.owner;
        link = FIELD(scratch, void *, 0xC);
        if (func_8003DE58(FIELD(link, s32, 8), link, local.delta, 0) != 0) {
            FIELD(obj, u16, 2) += local.delta[0];
            FIELD(obj, u16, 6) += local.delta[1];
            FIELD(obj, u16, 0xA) += local.delta[2];
        }
        local.pos[0] = FIELD(obj, u16, 2);
        local.pos[1] = FIELD(obj, u16, 6);
        local.pos[2] = FIELD(obj, u16, 0xA);
        body_link = (void *)func_80065420(local.p[0], local.p[1], local.p[2], resultp);
        mesh_flags = FIELD(anchor, u16, 2);
        call_a0 = local.p[0];
        call_a1 = local.p[1];
        call_a2 = (s32)local.p[2];
        ASM_KEEP(call_a0);
        ASM_KEEP(call_a1);
        ASM_KEEP(call_a2);
        local.pos[0] = mesh_flags;
        mesh_flags = FIELD(anchor, u16, 6);
        ASM_KEEP(mesh_flags);
        src = resultp;
        ASM_KEEP(src);
        local.pos[1] = mesh_flags;
        mesh_flags = FIELD(anchor, u16, 0xA);
        ASM_KEEP_DEP_NV(body_link, mesh_flags);
        height = (s32)body_link;
        local.pos[2] = mesh_flags;
        second_height = func_80065420(call_a0, call_a1, (void *)call_a2, src);
#ifdef __mips__
        calc_v1 = 0x80080000;
#else
        calc_v1 = (s32)((u8 *)&D_80083228 - 0x3228);
#endif
        ASM_KEEP(calc_v1);
        calc_a0 = FIELD((void *)calc_v1, s16, 0x3228);
        calc_v1 = (s16)FIELD(body, u16, 0x94);
        calc_a0 += calc_v1;
        calc_a0 += 0x100;
        calc_a0 >>= 9;
        calc_a0 &= 7;
        calc_v1 = (s32)D_800DCECC;
        ASM_KEEP(calc_v1);
        calc_a0 += calc_v1;
        ASM_KEEP(calc_a0);
        calc_v1 = FIELD((void *)calc_a0, s8, 0);
        height -= second_height;
        calc_v1 <<= 1;
        height -= calc_v1;
        FIELD(mesh, s16, 6) = height;
        goto state1_next;
    }
    FIELD(obj, u16, 0xA) = z - 0x1E;
    FIELD(mesh, s16, 6) = 4;

state1_next:
    scratch = (void *)(u32)local.count;
    timer = (u32)scratch + 1;
    local.count = timer;
    call_a0 = (void *)0x112;
    if ((s32)(timer << 16) <= 0) {
        goto state1_call;
    }
    loop_mode = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(loop_mode);
    mesh_flags = 0x2D;
    ASM_KEEP(mesh_flags);
    FIELD(arg0, u16, 0x96) = mesh_flags;
    goto increment_state_loaded;

state2:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
#ifdef __mips__
        tex_base = (void *)0x80170000;
        ASM_KEEP(tex_base);
#else
        tex_base = D_80170000;
#endif
        calc_v1 = (s32)FIELD(arg2, void *, 0x2C);
        call_a0 = (u8 *)tex_base + 0x4E88;
        if ((void *)calc_v1 != call_a0) {
            FIELD(arg2, void *, 0x2C) = call_a0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
#ifdef __mips__
            tex_base = (void *)0x80080000;
#else
            tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
            ASM_KEEP(tex_base);
            timer = ((FIELD(tex_base, s16, 0x3228) +
                      FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            call_a0 = arg2;
            calc_v1 = (s32)FIELD(arg2, void *, 0x2C);
            call_a1 = (void *)(s32)FIELD((void *)(calc_v1 + timer), u8, 0);
            call_a2 = 0;
            func_80047784(call_a0, (s32)call_a1, call_a2);
        }
    }
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);
#else
    tex_base = D_80170000;
#endif
    calc_v1 = (s32)FIELD(arg2, void *, 0x2C);
    call_a0 = (u8 *)tex_base + 0x4E88;
    if ((void *)calc_v1 != call_a0) {
        FIELD(arg2, void *, 0x2C) = call_a0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
#ifdef __mips__
        tex_base = (void *)0x80080000;
#else
        tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
        ASM_KEEP(tex_base);
        timer = ((FIELD(tex_base, s16, 0x3228) +
                  FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        call_a0 = arg2;
        calc_v1 = (s32)FIELD(arg2, void *, 0x2C);
        call_a1 = (void *)(s32)FIELD((void *)(calc_v1 + timer), u8, 0);
        call_a2 = 0;
        func_80047784(call_a0, (s32)call_a1, call_a2);
    }
increment_state:
    loop_mode = FIELD(arg0, u8, 0x9B);
increment_state_loaded:
    loop_mode++;
    FIELD(arg0, u8, 0x9B) = loop_mode;
    goto done;

state3:
    link = FIELD(arg3, void *, 0x60);
    if (link != 0) {
        func_800C8788(arg3, link);
    }
    func_800AD594(arg3, 0x400);
    FIELD(arg0, void *, 0x8C) = D_80171760;
#ifdef __mips__
    body_link = (void *)0x80080000;
#else
    body_link = (u8 *)&D_8008346C - 0x346C;
#endif
    ASM_KEEP(body_link);
    FIELD(body_link, s32, 0x346C) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;

done:
    return;
}

#include "common.h"

typedef struct S_801748D0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801748D0_0;   /* arg0 in func_801748D0 */

typedef struct S_801748D0_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801748D0_1;   /* arg1 in func_801748D0 */

typedef struct S_801748D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801748D0_2;   /* arg2 in func_801748D0 */

typedef struct S_801748D0_3 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} S_801748D0_3;   /* body in func_801748D0 */

typedef struct S_801748D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
    void * unk_10;
} S_801748D0_4;   /* obj in func_801748D0 */

typedef struct S_801748D0_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
} S_801748D0_5;   /* arg3 in func_801748D0 */

typedef struct S_801748D0_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801748D0_6_pre;   /* the 0x18 bytes before body_link in func_801748D0, addressed as body_link[-1] */

typedef struct S_801748D0_6 {
    u8 pad_00[0x346C];
    s32 unk_346C;
} S_801748D0_6;   /* body_link in func_801748D0 */

typedef struct S_801748D0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_801748D0_7;   /* mesh in func_801748D0 */

typedef struct S_801748D0_8 {
    u8 pad_00[0x3228];
    s16 unk_3228;
    u8 pad_322A[0x1CA6];
    u8 unk_4ED0;
} S_801748D0_8;   /* tex_base in func_801748D0 */

typedef struct S_801748D0_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801748D0_9;   /* anchor in func_801748D0 */

typedef struct S_801748D0_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_801748D0_10;   /* scratch in func_801748D0 */

typedef struct S_801748D0_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_801748D0_11;   /* link in func_801748D0 */

typedef struct S_801748D0_12 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_801748D0_12;   /* (void *)calc_v1 in func_801748D0 */

typedef struct S_801748D0_13 {
    s8 unk_00;
} S_801748D0_13;   /* (void *)calc_a0 in func_801748D0 */

typedef struct S_801748D0_14 {
    u8 unk_00;
} S_801748D0_14;   /* (void *)(calc_v1 + timer) in func_801748D0 */



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

void func_801748D0(void *arg0, S_801748D0_1 *arg1, void *arg2, S_801748D0_5 *arg3)
{
    LocalFrame local;
    void *obj;
    register void *body ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_801748D0_7 *mesh;
    register void *anchor ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_801748D0_11 *link;
    void *link_value;
    void *body_link;
    void *src;
    void *dst;
    void *src_end;
    void *resultp;
    register void *scratch ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 height ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 second_height;
    u16 state;
    u16 timer;
    u16 z;
    u16 flags;
    register void *call_a0 ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    void *call_a1;
    s32 call_a2;
    void *tex_base;
    u16 mesh_flags;
    s32 calc_a0;
    register s32 calc_v1 ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 loop_mode;
    s32 mode;

    scratch = (u8 *)arg0 - 0x20;
    local.owner = scratch;
    mode = ((S_801748D0_0 *)arg0)->unk_9B;
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
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    timer = ((S_801748D0_0 *)arg0)->unk_96 - 1;
    ((S_801748D0_0 *)arg0)->unk_96 = timer;
    if (((s32)(timer << 16) <= 0) ||
        (((S_801748D0_2 *)arg2)->unk_14 & 0x8000)) {
        ((S_801748D0_0 *)arg0)->unk_96 = 0;
        ((S_801748D0_0 *)arg0)->unk_9B++;
        flags = ((S_801748D0_2 *)arg2)->unk_14;
        ((S_801748D0_2 *)arg2)->unk_14 = flags & 0xF7FF;
    }
    goto done;

state1:
    if (!(((S_801748D0_2 *)arg2)->unk_14 & 0x8000)) {
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
    ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
state1_loop:
    call_a0 = (void *)0x112;
state1_call:
#ifdef __mips__
    call_a1 = (void *)0x80080000;
#else
    call_a1 = (u8 *)&D_80083498 - 0x3498;
#endif
    ASM_KEEP(call_a1);   /* MATCH pin: load-bearing for the whole function shape */
    call_a1 = (u8 *)call_a1 + 0x3498;
    obj = func_8003FD64((s32)call_a0, call_a1);
    body = (u8 *)obj + 0x20;
    if (obj == 0) {
        goto state1_next;
    }
    ASM_KEEP(body);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_801748D0_3 *)body)->unk_96 = 0x2D;
    ((S_801748D0_3 *)body)->unk_9E = 0x2D;
    ((S_801748D0_4 *)obj)->unk_10 = D_80170AD0;
    body_link = arg3->unk_60;
    if (body_link == 0) {
        ((S_801748D0_3 *)body)->unk_A8 = arg1;
        ((S_801748D0_3 *)body)->unk_A2 = 0;
    } else {
        link_value = ((S_801748D0_6_pre *)body_link)[-1].unk_00;
        ((S_801748D0_3 *)body)->unk_A2 = 1;
        ((S_801748D0_3 *)body)->unk_A8 = link_value;
    }
    ((S_801748D0_3 *)body)->unk_94 = arg3->unk_2A;
    mesh = ((S_801748D0_4 *)obj)->unk_0C;
    anchor = ((S_801748D0_3 *)body)->unk_A8;
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
    mesh_flags = mesh->unk_14;
    mesh->unk_1E = 0x400;
    mesh->unk_1C = 0x400;
    mesh->unk_0E = 0x80;
    mesh->unk_0D = 0x80;
    mesh->unk_0C = 0x80;
    mesh->unk_10 = 0x20;
    mesh->unk_12 = 0xFF80;
    ASM_KEEP(mesh);   /* MATCH pin: retail schedule: same instructions, different order without it */
    mesh_flags |= 0xC;
    mesh->unk_14 = mesh_flags;
    func_8004491C(call_a0, call_a1);
    call_a0 = mesh;
    call_a2 = 0;
    ASM_KEEP(call_a2);   /* MATCH pin: retail schedule: same instructions, different order without it */
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
    tex_base = D_80170000;
#endif
    call_a1 = (void *)(s32)((S_801748D0_8 *)tex_base)->unk_4ED0;
    tex_base = (u8 *)tex_base + 0x4ED0;
    mesh->unk_2C = tex_base;
    func_80047784(call_a0, (s32)call_a1, call_a2);
    obj = ((S_801748D0_4 *)obj)->unk_08.at00.v;
    ((S_801748D0_4 *)obj)->unk_02 = ((S_801748D0_9 *)anchor)->unk_02;
    ((S_801748D0_4 *)obj)->unk_06 = ((S_801748D0_9 *)anchor)->unk_06;
    z = ((S_801748D0_9 *)anchor)->unk_0A;
    ((S_801748D0_4 *)obj)->unk_08.at02.v = z;
    if (arg3->unk_60 == 0) {
        scratch = local.owner;
        link = ((S_801748D0_10 *)scratch)->unk_0C;
        if (func_8003DE58(link->unk_08, link, local.delta, 0) != 0) {
            ((S_801748D0_4 *)obj)->unk_02 += local.delta[0];
            ((S_801748D0_4 *)obj)->unk_06 += local.delta[1];
            ((S_801748D0_4 *)obj)->unk_08.at02.v += local.delta[2];
        }
        local.pos[0] = ((S_801748D0_4 *)obj)->unk_02;
        local.pos[1] = ((S_801748D0_4 *)obj)->unk_06;
        local.pos[2] = ((S_801748D0_4 *)obj)->unk_08.at02.v;
        body_link = (void *)func_80065420(local.p[0], local.p[1], local.p[2], resultp);
        mesh_flags = ((S_801748D0_9 *)anchor)->unk_02;
        call_a0 = local.p[0];
        call_a1 = local.p[1];
        call_a2 = (s32)local.p[2];
        local.pos[0] = mesh_flags;
        mesh_flags = ((S_801748D0_9 *)anchor)->unk_06;
        ASM_KEEP(mesh_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
        src = resultp;
        ASM_KEEP(src);   /* MATCH pin: load-bearing for the whole function shape */
        local.pos[1] = mesh_flags;
        mesh_flags = ((S_801748D0_9 *)anchor)->unk_0A;
        height = (s32)body_link;
        local.pos[2] = mesh_flags;
        second_height = func_80065420(call_a0, call_a1, (void *)call_a2, src);
#ifdef __mips__
        calc_v1 = 0x80080000;
#else
        calc_v1 = (s32)((u8 *)&D_80083228 - 0x3228);
#endif
        ASM_KEEP(calc_v1);   /* MATCH pin: load-bearing for the whole function shape */
        calc_a0 = ((S_801748D0_12 *)((void *)calc_v1))->unk_3228;
        calc_v1 = (s16)((S_801748D0_3 *)body)->unk_94;
        calc_a0 += calc_v1;
        calc_a0 += 0x100;
        calc_a0 >>= 9;
        calc_a0 &= 7;
        calc_v1 = (s32)D_800DCECC;
        calc_a0 += calc_v1;
        ASM_KEEP(calc_a0);   /* MATCH pin: retail delay-slot fill depends on it */
        calc_v1 = ((S_801748D0_13 *)((void *)calc_a0))->unk_00;
        height -= second_height;
        calc_v1 <<= 1;
        height -= calc_v1;
        mesh->unk_06 = height;
        goto state1_next;
    }
    ((S_801748D0_4 *)obj)->unk_08.at02.v = z - 0x1E;
    mesh->unk_06 = 4;

state1_next:
    scratch = (void *)(u32)local.count;
    timer = (u32)scratch + 1;
    local.count = timer;
    call_a0 = (void *)0x112;
    if ((s32)(timer << 16) <= 0) {
        goto state1_call;
    }
    loop_mode = ((S_801748D0_0 *)arg0)->unk_9B;
    mesh_flags = 0x2D;
    ((S_801748D0_0 *)arg0)->unk_96 = mesh_flags;
    goto increment_state_loaded;

state2:
    if (((S_801748D0_2 *)arg2)->unk_14 & 0xE000) {
#ifdef __mips__
        tex_base = (void *)0x80170000;
        ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
        tex_base = D_80170000;
#endif
        calc_v1 = (s32)((S_801748D0_2 *)arg2)->unk_2C;
        call_a0 = (u8 *)tex_base + 0x4E88;
        if ((void *)calc_v1 != call_a0) {
            ((S_801748D0_2 *)arg2)->unk_2C = call_a0;
            ((S_801748D0_2 *)arg2)->unk_14 &= 0xF7FF;
#ifdef __mips__
            tex_base = (void *)0x80080000;
#else
            tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
            timer = ((((S_801748D0_8 *)tex_base)->unk_3228 +
                      arg3->unk_2A + 0x100) >> 9) & 7;
            call_a0 = arg2;
            calc_v1 = (s32)((S_801748D0_2 *)arg2)->unk_2C;
            call_a1 = (void *)(s32)((S_801748D0_14 *)((void *)(calc_v1 + timer)))->unk_00;
            call_a2 = 0;
            func_80047784(call_a0, (s32)call_a1, call_a2);
        }
    }
    if (!(((S_801748D0_2 *)arg2)->unk_14 & 0x8000)) {
        timer = ((S_801748D0_0 *)arg0)->unk_96 - 1;
        ((S_801748D0_0 *)arg0)->unk_96 = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, ((S_801748D0_2 *)arg2)->unk_24, ((S_801748D0_2 *)arg2)->unk_25);
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
    tex_base = D_80170000;
#endif
    calc_v1 = (s32)((S_801748D0_2 *)arg2)->unk_2C;
    call_a0 = (u8 *)tex_base + 0x4E88;
    if ((void *)calc_v1 != call_a0) {
        ((S_801748D0_2 *)arg2)->unk_2C = call_a0;
        ((S_801748D0_2 *)arg2)->unk_14 &= 0xF7FF;
#ifdef __mips__
        tex_base = (void *)0x80080000;
#else
        tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
        timer = ((((S_801748D0_8 *)tex_base)->unk_3228 +
                  arg3->unk_2A + 0x100) >> 9) & 7;
        call_a0 = arg2;
        calc_v1 = (s32)((S_801748D0_2 *)arg2)->unk_2C;
        call_a1 = (void *)(s32)((S_801748D0_14 *)((void *)(calc_v1 + timer)))->unk_00;
        call_a2 = 0;
        func_80047784(call_a0, (s32)call_a1, call_a2);
    }
increment_state:
    loop_mode = ((S_801748D0_0 *)arg0)->unk_9B;
increment_state_loaded:
    loop_mode++;
    ((S_801748D0_0 *)arg0)->unk_9B = loop_mode;
    goto done;

state3:
    link = arg3->unk_60;
    if (link != 0) {
        func_800C8788(arg3, link);
    }
    func_800AD594(arg3, 0x400);
    ((S_801748D0_0 *)arg0)->unk_8C = D_80171760;
#ifdef __mips__
    body_link = (void *)0x80080000;
#else
    body_link = (u8 *)&D_8008346C - 0x346C;
#endif
    ASM_KEEP(body_link);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_801748D0_6 *)body_link)->unk_346C = 0;
    arg3->unk_46 &= 0x7FFF;

done:
    return;
}

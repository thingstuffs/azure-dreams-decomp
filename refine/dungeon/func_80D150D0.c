#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801748D0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801748D0_0;   /* arg0 in func_801748D0 */


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

/* Advances a timed actor effect, spawning and positioning its visual object before cleanup. */
void func_801748D0(void *effect_state, Rec_D_800E3D7C *position, void *source_mesh, Rec_D_800E3D7C *actor)
{
    LocalFrame frame;
    void *effect;
    register void *effect_body ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_801748D0_7 *effect_mesh;
    register void *anchor_pos ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_801748D0_11 *owner_link;
    void *linked_owner;
    void *linked_body;
    void *copy_src;
    void *copy_dst;
    void *copy_end;
    void *height_out;
    register void *frame_ptr ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 height_delta ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 anchor_height;
    u16 timer;
    u16 anchor_z;
    u16 flags;
    register void *call_target ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    void *call_data;
    s32 call_value;
    void *tex_base;
    u16 mesh_flags;
    s32 direction_entry;
    register s32 lookup_value ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 next_state;
    s32 phase;

    frame_ptr = (u8 *)effect_state - 0x20;
    frame.owner = frame_ptr;
    phase = ((S_801748D0_0 *)effect_state)->unk_9B;
    if (phase == 1) {
        goto spawn_effect;
    }
    if ((s32)phase < 2) {
        if (phase == 0) {
            goto wait_start;
        }
        goto done;
    }
    if (phase == 2) {
        goto wait_finish;
    }
    if (phase == 3) {
        goto finish_effect;
    }
    goto done;

wait_start:
    position->unk_14.as_s32 = 0;
    position->unk_10.at00_s32.v = 0;
    position->unk_0C.as_s32 = 0;
    timer = ((S_801748D0_0 *)effect_state)->unk_96 - 1;
    ((S_801748D0_0 *)effect_state)->unk_96 = timer;
    if (((s32)(timer << 16) <= 0) ||
        (((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
        ((S_801748D0_0 *)effect_state)->unk_96 = 0;
        ((S_801748D0_0 *)effect_state)->unk_9B++;
        flags = ((S_801748D0_2 *)source_mesh)->unk_14;
        ((S_801748D0_2 *)source_mesh)->unk_14 = flags & 0xF7FF;
    }
    goto done;

spawn_effect:
    if (!(((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
        func_800A56E0(0x80D);
    }
    frame_ptr = &frame.pos[0];
    frame.p[0] = frame_ptr;
    frame_ptr = &frame.out0[0];
    frame.p[1] = frame_ptr;
    frame_ptr = &frame.out1;
    height_out = &frame.out2;
    frame.count = 0;
    frame.p[2] = frame_ptr;
    ASM_KEEP(frame_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_target = (void *)0x112;
allocate_effect:
#ifdef __mips__
    call_data = (void *)0x80080000;
#else
    call_data = (u8 *)&D_80083498 - 0x3498;
#endif
    ASM_KEEP(call_data);   /* MATCH pin: load-bearing for the whole function shape */
    call_data = (u8 *)call_data + 0x3498;
    effect = func_8003FD64((s32)call_target, call_data);
    effect_body = (u8 *)effect + 0x20;
    if (effect == 0) {
        goto next_effect;
    }
    ASM_KEEP(effect_body);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_801748D0_3 *)effect_body)->unk_96 = 0x2D;
    ((S_801748D0_3 *)effect_body)->unk_9E = 0x2D;
    ((S_801748D0_4 *)effect)->unk_10 = D_80170AD0;
    linked_body = actor->unk_60.as_pv;
    if (linked_body == 0) {
        ((S_801748D0_3 *)effect_body)->unk_A8 = position;
        ((S_801748D0_3 *)effect_body)->unk_A2 = 0;
    } else {
        linked_owner = ((S_801748D0_6_pre *)linked_body)[-1].unk_00;
        ((S_801748D0_3 *)effect_body)->unk_A2 = 1;
        ((S_801748D0_3 *)effect_body)->unk_A8 = linked_owner;
    }
    ((S_801748D0_3 *)effect_body)->unk_94 = actor->unk_2A.as_s16;
    effect_mesh = ((S_801748D0_4 *)effect)->unk_0C;
    anchor_pos = ((S_801748D0_3 *)effect_body)->unk_A8;
    copy_src = source_mesh;
    copy_dst = effect_mesh;
    copy_end = (u8 *)source_mesh + 0x30;
    do {
        *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
        copy_src = (u8 *)copy_src + 0x10;
        copy_dst = (u8 *)copy_dst + 0x10;
    } while (copy_src != copy_end);
    call_target = effect;
    call_data = &D_80045340;
    mesh_flags = effect_mesh->unk_14;
    effect_mesh->unk_1E = 0x400;
    effect_mesh->unk_1C = 0x400;
    effect_mesh->unk_0E = 0x80;
    effect_mesh->unk_0D = 0x80;
    effect_mesh->unk_0C = 0x80;
    effect_mesh->unk_10 = 0x20;
    effect_mesh->unk_12 = 0xFF80;
    ASM_KEEP(effect_mesh);   /* MATCH pin: retail schedule: same instructions, different order without it */
    mesh_flags |= 0xC;
    effect_mesh->unk_14 = mesh_flags;
    func_8004491C(call_target, call_data);
    call_target = effect_mesh;
    call_value = 0;
    ASM_KEEP(call_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
    tex_base = D_80170000;
#endif
    call_data = (void *)(s32)((S_801748D0_8 *)tex_base)->unk_4ED0;
    tex_base = (u8 *)tex_base + 0x4ED0;
    effect_mesh->unk_2C = tex_base;
    func_80047784(call_target, (s32)call_data, call_value);
    effect = ((S_801748D0_4 *)effect)->unk_08.at00.v;
    ((S_801748D0_4 *)effect)->unk_02 = ((S_801748D0_9 *)anchor_pos)->unk_02;
    ((S_801748D0_4 *)effect)->unk_06 = ((S_801748D0_9 *)anchor_pos)->unk_06;
    anchor_z = ((S_801748D0_9 *)anchor_pos)->unk_0A;
    ((S_801748D0_4 *)effect)->unk_08.at02.v = anchor_z;
    if (actor->unk_60.as_pv == 0) {
        frame_ptr = frame.owner;
        owner_link = ((S_801748D0_10 *)frame_ptr)->unk_0C;
        if (func_8003DE58(owner_link->unk_08, owner_link, frame.delta, 0) != 0) {
            ((S_801748D0_4 *)effect)->unk_02 += frame.delta[0];
            ((S_801748D0_4 *)effect)->unk_06 += frame.delta[1];
            ((S_801748D0_4 *)effect)->unk_08.at02.v += frame.delta[2];
        }
        frame.pos[0] = ((S_801748D0_4 *)effect)->unk_02;
        frame.pos[1] = ((S_801748D0_4 *)effect)->unk_06;
        frame.pos[2] = ((S_801748D0_4 *)effect)->unk_08.at02.v;
        linked_body = (void *)func_80065420(frame.p[0], frame.p[1], frame.p[2], height_out);
        mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_02;
        call_target = frame.p[0];
        call_data = frame.p[1];
        call_value = (s32)frame.p[2];
        frame.pos[0] = mesh_flags;
        mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_06;
        ASM_KEEP(mesh_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
        copy_src = height_out;
        ASM_KEEP(copy_src);   /* MATCH pin: load-bearing for the whole function shape */
        frame.pos[1] = mesh_flags;
        mesh_flags = ((S_801748D0_9 *)anchor_pos)->unk_0A;
        height_delta = (s32)linked_body;
        frame.pos[2] = mesh_flags;
        anchor_height = func_80065420(call_target, call_data, (void *)call_value, copy_src);
#ifdef __mips__
        lookup_value = 0x80080000;
#else
        lookup_value = (s32)((u8 *)&D_80083228 - 0x3228);
#endif
        ASM_KEEP(lookup_value);   /* MATCH pin: load-bearing for the whole function shape */
        direction_entry = ((S_801748D0_12 *)((void *)lookup_value))->unk_3228;
        lookup_value = (s16)((S_801748D0_3 *)effect_body)->unk_94;
        direction_entry += lookup_value;
        direction_entry += 0x100;
        direction_entry >>= 9;
        direction_entry &= 7;
        lookup_value = (s32)D_800DCECC;
        direction_entry += lookup_value;
        ASM_KEEP(direction_entry);   /* MATCH pin: retail delay-slot fill depends on it */
        lookup_value = ((S_801748D0_13 *)((void *)direction_entry))->unk_00;
        height_delta -= anchor_height;
        lookup_value <<= 1;
        height_delta -= lookup_value;
        effect_mesh->unk_06 = height_delta;
        goto next_effect;
    }
    ((S_801748D0_4 *)effect)->unk_08.at02.v = anchor_z - 0x1E;
    effect_mesh->unk_06 = 4;

next_effect:
    frame_ptr = (void *)(u32)frame.count;
    timer = (u32)frame_ptr + 1;
    frame.count = timer;
    call_target = (void *)0x112;
    if ((s32)(timer << 16) <= 0) {
        goto allocate_effect;
    }
    next_state = ((S_801748D0_0 *)effect_state)->unk_9B;
    mesh_flags = 0x2D;
    ((S_801748D0_0 *)effect_state)->unk_96 = mesh_flags;
    goto increment_state_loaded;

wait_finish:
    if (((S_801748D0_2 *)source_mesh)->unk_14 & 0xE000) {
#ifdef __mips__
        tex_base = (void *)0x80170000;
        ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
        tex_base = D_80170000;
#endif
        lookup_value = (s32)((S_801748D0_2 *)source_mesh)->unk_2C;
        call_target = (u8 *)tex_base + 0x4E88;
        if ((void *)lookup_value != call_target) {
            ((S_801748D0_2 *)source_mesh)->unk_2C = call_target;
            ((S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
#ifdef __mips__
            tex_base = (void *)0x80080000;
#else
            tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
            timer = ((((S_801748D0_8 *)tex_base)->unk_3228 +
                      actor->unk_2A.as_s16 + 0x100) >> 9) & 7;
            call_target = source_mesh;
            lookup_value = (s32)((S_801748D0_2 *)source_mesh)->unk_2C;
            call_data = (void *)(s32)((S_801748D0_14 *)((void *)(lookup_value + timer)))->unk_00;
            call_value = 0;
            func_80047784(call_target, (s32)call_data, call_value);
        }
    }
    if (!(((S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
        timer = ((S_801748D0_0 *)effect_state)->unk_96 - 1;
        ((S_801748D0_0 *)effect_state)->unk_96 = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
    }
    position->unk_14.as_s32 = 0;
    position->unk_10.at00_s32.v = 0;
    position->unk_0C.as_s32 = 0;
    func_800A2B04(position, ((S_801748D0_2 *)source_mesh)->unk_24, ((S_801748D0_2 *)source_mesh)->unk_25);
#ifdef __mips__
    tex_base = (void *)0x80170000;
    ASM_KEEP(tex_base);   /* MATCH pin: retail immediate-load split depends on it */
#else
    tex_base = D_80170000;
#endif
    lookup_value = (s32)((S_801748D0_2 *)source_mesh)->unk_2C;
    call_target = (u8 *)tex_base + 0x4E88;
    if ((void *)lookup_value != call_target) {
        ((S_801748D0_2 *)source_mesh)->unk_2C = call_target;
        ((S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
#ifdef __mips__
        tex_base = (void *)0x80080000;
#else
        tex_base = (u8 *)&D_80083228 - 0x3228;
#endif
        timer = ((((S_801748D0_8 *)tex_base)->unk_3228 +
                  actor->unk_2A.as_s16 + 0x100) >> 9) & 7;
        call_target = source_mesh;
        lookup_value = (s32)((S_801748D0_2 *)source_mesh)->unk_2C;
        call_data = (void *)(s32)((S_801748D0_14 *)((void *)(lookup_value + timer)))->unk_00;
        call_value = 0;
        func_80047784(call_target, (s32)call_data, call_value);
    }
    next_state = ((S_801748D0_0 *)effect_state)->unk_9B;
increment_state_loaded:
    next_state++;
    ((S_801748D0_0 *)effect_state)->unk_9B = next_state;
    goto done;

finish_effect:
    owner_link = actor->unk_60.as_pv;
    if (owner_link != 0) {
        func_800C8788(actor, owner_link);
    }
    func_800AD594(actor, 0x400);
    ((S_801748D0_0 *)effect_state)->unk_8C = D_80171760;
#ifdef __mips__
    linked_body = (void *)0x80080000;
#else
    linked_body = (u8 *)&D_8008346C - 0x346C;
#endif
    ASM_KEEP(linked_body);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_801748D0_6 *)linked_body)->unk_346C = 0;
    actor->unk_44.at02_u16.v &= 0x7FFF;

done:
    return;
}

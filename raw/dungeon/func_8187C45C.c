#include "common.h"

typedef struct {
    s16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    Point p[8];
} PointTable __attribute__((packed));

typedef struct {
    u32 w[3];
} Copy12 __attribute__((packed));

typedef struct {
    u8 pad[0x98];
    Copy12 copy;
} PackedArg0 __attribute__((packed));

typedef struct {
    u8 pad[0x64];
    Copy12 copy;
} PackedSpawn __attribute__((packed));

extern PointTable D_80024074;
extern Copy12 D_80026934;
extern Copy12 D_80026940;
extern s16 D_8002694C[5];
extern u8 D_8007CCD8[];
extern u8 D_8007CCE8[];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800DDC40[];
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void *func_8003FC64(s32);
extern s32 func_80069EF8(void);
extern void func_800250B0(void *, s32, u32, u32, s32, s32, s32);
extern void func_800251E8(s32, u32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800240B8(void *, u8, void *);
extern void func_800A56E0(s32);
extern void *memcpy(void *, const void *, unsigned int);

extern void func_80045340(void);
extern void func_8002569C(void);
extern void func_800257E0(void);
extern void *D_80024098[];

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

void func_80025C5C(void *in0, void *in1, void *in2) {
    static void *const dispatch_keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7
    };
    u16 delta[4];
    PointTable points;
    register void *arg0 ASM_REG("$18") = in0;
    register void *arg1 ASM_REG("$19") = in1;
    register void *arg2 ASM_REG("$21") = in2;
    register void *owner ASM_REG("$20");
    register void *base ASM_REG("$16");
    register void *position ASM_REG("$17");
    register void *a0ptr ASM_REG("$4");
    register void *call_gfx ASM_REG("$5");
    register void *v1ptr ASM_REG("$3");
    register void *a3ptr ASM_REG("$7");
    void *gfx;
    void *child;
    register void **jump_table ASM_REG("$2");
    register PointTable *copy_src ASM_REG("$6");
    register u16 next_state ASM_REG("$2");
    u16 render_flags;
    register s32 value ASM_REG("$22");
    s32 count;
    s32 color;
    s32 busy;
    s32 count4;
    s32 count6;
    register s32 fade_n1 ASM_REG("$5");
    register s32 fade_n2 ASM_REG("$4");
    register s32 fade_n3 ASM_REG("$3");
    register s32 fade_result ASM_REG("$2");
    register s32 z ASM_REG("$3");
    register s32 z_result ASM_REG("$2");
    register s32 z_addend ASM_REG("$3");
    register s32 difference ASM_REG("$2");

    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg1);
    ASM_KEEP_NV(arg2);
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);
    owner = PTR(arg0, 0);
    ASM_KEEP(owner);
    copy_src = (PointTable *)((u8 *)jump_table + 0x4074);
    ASM_KEEP_NV(copy_src);
    memcpy(&points, copy_src, 12);
    memcpy((u8 *)&points + 12, (u8 *)copy_src + 12, 12);
    memcpy((u8 *)&points + 24, (u8 *)copy_src + 24, 8);
    ASM_USE_NV(jump_table);
    count = S16(arg0, 0xA);
    ASM_KEEP(count);
    base = (u8 *)owner - 0x20;
    ASM_KEEP(base);
    position = PTR(base, 8);

    if ((u32)count >= 8) {
        goto end;
    }
    goto *D_80024098[count];

state_0:
    U32(arg2, 0xC) = 0x00808080;
    U16(arg2, 0x1E) = 0x1000;
    U16(arg2, 0x1C) = 0x1000;
    ASM_KEEP(arg2);
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);
    copy_src = (PointTable *)((u8 *)jump_table + 0x6934);
    ASM_KEEP_NV(copy_src);
    memcpy((u8 *)arg0 + 0x98, copy_src, 12);
    ASM_USE_NV(jump_table);
    {
    void *cd = (u8 *)arg0 + 0x98;
    ASM_KEEP(cd);
    a0ptr = (void *)0x80020000;
    ASM_KEEP_NV(a0ptr);
    PTR(arg2, 8) = cd;
    }
    jump_table = (void **)(u32)U16(owner, 0x2A);
    ASM_KEEP_NV(jump_table);
    v1ptr = (void *)1;
    S16(a0ptr, 0x694C) = (u32)v1ptr;
    ASM_KEEP(a0ptr);
    v1ptr = (void *)(u32)U16(arg0, 0xA);
    ASM_KEEP_NV(v1ptr);
    jump_table = (void **)(((u32)jump_table >> 9) & 7);
    v1ptr = (void *)((u32)v1ptr + 1);
    ASM_KEEP_NV(v1ptr);
    U16(arg0, 0x7E) = (u32)jump_table;
    U16(arg0, 0xA) = (u32)v1ptr;

    call_gfx = PTR(base, 0xC);
    ASM_KEEP_NV(call_gfx);
    if (func_8003DF74(PTR(call_gfx, 8), call_gfx, delta, 0) == 0) {
        if (!(U16(PTR(base, 0xC), 0x14) & 0x8000)) {
            goto end;
        }
    }

    U16(arg1, 2) = U16(position, 2);
    U16(arg1, 6) = U16(position, 6);
    z = U16(position, 0xA);
    U16(arg1, 0xA) = z;
    if (!(U16(PTR(base, 0xC), 0x14) & 0x8000)) {
        U16(arg1, 2) = U16(arg1, 2) + delta[0];
        ASM_KEEP(arg1);
        U16(arg1, 6) = U16(arg1, 6) + delta[1];
        ASM_KEEP(arg1);
        z_result = U16(arg1, 0xA);
        z_addend = delta[2];
        z_result += z_addend;
        goto store_z;
    }
    z_result = z - 0x40;
store_z:
    ASM_KEEP(z_result);
    U16(arg1, 0xA) = z_result;

state_1:
    if (!(U16(PTR(arg0, 4), 0) & 0x80)) {
        goto end;
    }

    ASM_KEEP(arg0);
    if (!(U8(arg0, 0x7A) & 4)) {
        a0ptr = (u8 *)arg0 - 0x20;
        ASM_KEEP_NV(a0ptr);
        func_8004491C(a0ptr, func_80045340);
        a0ptr = (void *)0x20;
        ASM_KEEP_NV(a0ptr);
        v1ptr = (void *)(u32)U16(arg2, 0x14);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)0x80;
        ASM_KEEP_NV(jump_table);
        U16(arg2, 0x10) = (u32)a0ptr;
        U8(arg2, 0xD) = (u32)jump_table;
        U8(arg2, 0xC) = (u32)jump_table;
        U8(arg2, 0xE) = (u32)a0ptr;
        ASM_KEEP(arg2);
        v1ptr = (void *)((u32)v1ptr | 0xC);
        ASM_KEEP_NV(v1ptr);
        U16(arg2, 0x14) = (u32)v1ptr;
        U8(arg0, 0x7A) |= 4;
    }

    jump_table = PTR(owner, 0x60);
    v1ptr = (void *)0x10;
    if (jump_table != 0) {
        base = PTR(jump_table, -0x18);
        U16(arg0, 0x74) = U16(base, 2);
        U16(arg0, 0x76) = U16(base, 6);
        ASM_KEEP(arg0);
        v1ptr = PTR(owner, 0x60);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)0x800E0000;
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)(u32)U8(v1ptr, 0x13);
        jump_table = (void **)((u8 *)jump_table - 0x23C0);
        v1ptr = (u8 *)v1ptr + (u32)jump_table;
        ASM_KEEP_DEP_NV(v1ptr, jump_table);
        jump_table = (void **)(u32)U8(v1ptr, 0);
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)(u32)U16(base, 0xA);
        jump_table = (void **)((u32)jump_table + 0x20);
        v1ptr = (void *)((u32)v1ptr - (u32)jump_table);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)0x80070000;
        ASM_KEEP_NV(jump_table);
        jump_table = (void **)((u8 *)jump_table - 0x3328);
        ASM_KEEP_NV(jump_table);
        U16(arg0, 0x78) = (u32)v1ptr;
        ASM_KEEP(arg0);
        v1ptr = (void *)(s32)S16(arg0, 0x7E);
        ASM_KEEP(v1ptr);
        a0ptr = PTR(owner, -0x14);
        ASM_KEEP(a0ptr);
        v1ptr = (void *)((s32)v1ptr * 2);
        v1ptr = (u8 *)v1ptr + (u32)jump_table;
        ASM_KEEP_DEP_NV(v1ptr, jump_table);
        jump_table = (void **)(u32)U8(a0ptr, 0x24);
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)(u32)U8(v1ptr, 0);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)((u32)jump_table + (u32)v1ptr);
        ASM_KEEP_NV(jump_table);
        U8(arg0, 0xA4) = (u32)jump_table;

        jump_table = (void **)0x80070000;
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)(s32)S16(arg0, 0x7E);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)((u8 *)jump_table - 0x3318);
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)((s32)v1ptr * 2);
        v1ptr = (u8 *)v1ptr + (u32)jump_table;
        ASM_KEEP_DEP_NV(v1ptr, jump_table);
        jump_table = (void **)(u32)U8(a0ptr, 0x25);
        ASM_KEEP_NV(jump_table);
        v1ptr = (void *)(u32)U8(v1ptr, 0);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)((u32)jump_table + (u32)v1ptr);
        ASM_KEEP_NV(jump_table);
        U8(arg0, 0xA5) = (u32)jump_table;

        {
            register s32 owner_axis ASM_REG("$2") = S8(owner, 0x72);
            register u32 sprite_axis ASM_REG("$3") = U8(a0ptr, 0x24);

            if (owner_axis != sprite_axis) {
                difference = owner_axis - sprite_axis;
            } else {
                owner_axis = S8(owner, 0x73);
                sprite_axis = U8(a0ptr, 0x25);
                difference = owner_axis - sprite_axis;
            }
        }
        if (difference < 0) {
            difference = -difference;
        }
        U8(arg0, 0x7B) = difference * 2 - 1;
    } else {
        jump_table = (void **)(s32)S16(arg0, 0x7E);
        ASM_KEEP(arg0);
        a0ptr = (void *)(s32)S16(arg0, 0x7E);
        U8(arg0, 0x7B) = (u32)v1ptr;
        call_gfx = &points.p[0];
        ASM_KEEP4_NV(jump_table, v1ptr, a0ptr, call_gfx);
        jump_table = (void **)((s32)jump_table * 4);
        jump_table = (void **)((u8 *)call_gfx + (u32)jump_table);
        ASM_KEEP_DEP_NV(jump_table, call_gfx);
        a0ptr = (void *)((s32)a0ptr * 4);
        call_gfx = (u8 *)call_gfx + (u32)a0ptr;
        v1ptr = (void *)(u32)U16(jump_table, 0);
        jump_table = (void **)(u32)U16(arg1, 2);
        v1ptr = (void *)((u32)v1ptr << 4);
        jump_table = (void **)((u32)jump_table + (u32)v1ptr);
        U16(arg0, 0x74) = (u32)jump_table;
        jump_table = (void **)(u32)U8(arg0, 0x7B);
        v1ptr = (void *)(u32)U16(call_gfx, 2);
        ASM_KEEP4_NV(jump_table, v1ptr, call_gfx, arg0);
        jump_table = (void **)((u32)jump_table << 24);
        jump_table = (void **)((s32)jump_table >> 24);
        U16(arg0, 0x76) = U16(arg1, 6) +
            (u32)v1ptr * (s32)jump_table;
        U16(arg0, 0x78) = U16(owner, 0x88) - 0x50;
    }

    S32(arg1, 0xC) = points.p[S16(arg0, 0x7E)].x << 16;
    S32(arg1, 0x10) = points.p[S16(arg0, 0x7E)].y << 16;
    S32(arg1, 0x14) = ((S16(arg0, 0x78) << 16) - S32(arg1, 8)) / S8(arg0, 0x7B);
    next_state = U16(arg0, 0xA);
    U16(arg0, 0x82) = 0;
    ASM_KEEP_NV(next_state);
    goto advance_state;

state_2:
    value = 0x60;
state2_loop:
    base = func_8003FC64(0x12);
    position = (u8 *)base + 0x20;
    if (base != 0) {
        U16(position, 2) = 8;
        U16(position, 4) = 8;
        PTR(base, 0x10) = func_8002569C;
        func_8004491C(base, func_80045340);

        a3ptr = PTR(base, 0xC);
        ASM_KEEP_NV(a3ptr);
        v1ptr = (void *)(u32)U16(a3ptr, 0x14);
        ASM_KEEP_NV(v1ptr);
        jump_table = (void **)0x20;
        ASM_KEEP_NV(jump_table);
        U16(a3ptr, 0x10) = (u32)jump_table;
        ASM_KEEP(a3ptr);
        v1ptr = (void *)((u32)v1ptr | 0xC);
        U16(a3ptr, 0x14) = (u32)v1ptr;
        v1ptr = PTR(base, 8);
        ASM_KEEP_NV(v1ptr);
        U16(v1ptr, 2) = U16(arg1, 2);
        U16(v1ptr, 6) = U16(arg1, 6);
        jump_table = (void **)(u32)U16(arg1, 0xA);
        ASM_KEEP_NV(jump_table);
        U16(v1ptr, 0xA) = (u32)jump_table;
        ASM_KEEP(v1ptr);
        a3ptr = PTR(base, 0xC);
        ASM_KEEP_NV(a3ptr);
        jump_table = (void **)0x1000;
        ASM_KEEP_NV(jump_table);
        U16(a3ptr, 0x1E) = (u32)jump_table;
        U16(a3ptr, 0x1C) = (u32)jump_table;
        jump_table = (void **)0x10;
        ASM_KEEP_NV(jump_table);
        U8(a3ptr, 0xD) = value;
        U8(a3ptr, 0xC) = value;
        U8(a3ptr, 0xE) = (u32)jump_table;
        U8(position, 0x38) = (u32)jump_table;
        U8(position, 0x37) = value;
        U8(position, 0x36) = value;
        jump_table = (void **)0x80020000;
        ASM_KEEP(jump_table);
        copy_src = (PointTable *)((u8 *)jump_table + 0x6934);
        ASM_KEEP_NV(copy_src);
        memcpy((u8 *)base + 0x64, copy_src, 12);
        ASM_USE_NV(jump_table);
        PTR(a3ptr, 8) = (u8 *)base + 0x64;
        ASM_KEEP(base);
    }

    if ((s16)func_800A4778(U16(arg1, 2), U16(arg1, 6), S16(arg1, 0xA),
                           PTR(owner, 0x60)) != 0) {
        goto collision_hit;
    }

    U8(arg0, 0x7B) = U8(arg0, 0x7B) - 1;
    if (S8(arg0, 0x7B) <= 0) {
        if (PTR(owner, 0x60) != 0) {
            goto child_done;
        }
        U16(arg0, 0xA) = 7;
        U16(arg0, 0x82) = 0;
        render_flags = U16(arg2, 0x14);
        U8(arg2, 0xE) = 0;
        U8(arg2, 0xD) = 0;
        U8(arg2, 0xC) = 0;
        goto set_render_flag;
    }

    S32(arg1, 0xC) = ((S16(arg0, 0x74) << 16) - S32(arg1, 0)) / S8(arg0, 0x7B);
    S32(arg1, 0x10) = ((S16(arg0, 0x76) << 16) - S32(arg1, 4)) / S8(arg0, 0x7B);
    jump_table = (void **)(s32)S8(arg0, 0x7B);
    v1ptr = (void *)(u32)S32(arg1, 8);
    a0ptr = (void *)(u32)(S16(arg0, 0x78) << 16);
    ASM_KEEP4_NV(jump_table, v1ptr, a0ptr, arg1);
    a0ptr = (void *)((s32)a0ptr - (s32)v1ptr);
    ASM_KEEP_NV(a0ptr);
    a0ptr = (void *)((s32)a0ptr / (s32)jump_table);
    jump_table = (void **)(u32)S32(arg1, 0);
    v1ptr = (void *)(u32)S32(arg1, 0xC);
    ASM_KEEP4_NV(jump_table, v1ptr, arg1, arg0);
    jump_table = (void **)((s32)jump_table + (s32)v1ptr);
    S32(arg1, 0) = (s32)jump_table;
    jump_table = (void **)(u32)S32(arg1, 4);
    v1ptr = (void *)(u32)S32(arg1, 8);
    *(volatile s32 *)((u8 *)arg1 + 0x14) = (s32)a0ptr;
    a0ptr = (void *)(u32)S32(arg1, 0x10);
    call_gfx = (void *)(u32)S32(arg1, 0x14);
    ASM_KEEP4_NV(jump_table, v1ptr, a0ptr, call_gfx);
    jump_table = (void **)((s32)jump_table + (s32)a0ptr);
    v1ptr = (void *)((s32)v1ptr + (s32)call_gfx);
    S32(arg1, 4) = (s32)jump_table;
    S32(arg1, 8) = (s32)v1ptr;
    goto state2_loop;

state_3:
    if (S16(arg0, 0x96) == 0) {
        U16(arg0, 0x96) = 1;
        U8(arg0, 0xA0) = U8(arg0, 0xA0) + 0x18;
    } else {
        U16(arg0, 0x96) = 0;
        U8(arg0, 0xA0) = U8(arg0, 0xA0) - 0x18;
    }

    base = func_8003FC64(0x12);
    position = (u8 *)base + 0x20;
    if (base != 0) {
        U16(position, 2) = 8;
        U16(position, 4) = 8;
        U16(position, 0xA) = 0x30;
        S16(position, 0xC) = -0xDE;
        PTR(base, 0x10) = func_800257E0;
        a3ptr = PTR(base, 0xC);
        ASM_KEEP(a3ptr);
        U16(a3ptr, 0x10) = 0x20;
        U16(a3ptr, 0x14) |= 0xC;
        v1ptr = PTR(base, 8);
        ASM_KEEP_NV(v1ptr);
        U16(v1ptr, 2) = U16(arg1, 2);
        U16(v1ptr, 6) = U16(arg1, 6);
        U16(v1ptr, 0xA) = U16(arg1, 0xA);
        ASM_SCHED_BARRIER();
        jump_table = (void **)0x80020000;
        ASM_KEEP(jump_table);
        copy_src = (PointTable *)((u8 *)jump_table + 0x6940);
        ASM_KEEP_NV(copy_src);
        memcpy((u8 *)base + 0x64, copy_src, 12);
        ASM_USE_NV(jump_table);
        PTR(a3ptr, 8) = (u8 *)base + 0x64;
        ASM_KEEP(base);
    }
    U8(arg0, 0x92) = 0;
    U8(arg0, 0x91) = 0;
    U8(arg0, 0x90) = 0;
    U16(arg0, 0xA) = 4;
    U16(arg0, 0x82) = 0;
    goto end;

state_4:
    {
        u16 raw = U16(arg0, 0x82) + 1;
        count4 = (s16)raw;
        U16(arg0, 0x82) = raw;
    }
    if (count4 >= 0x14) {
        goto state4_advance;
    }

    U8(arg2, 0xC) = ((0x14 - count4) * 0xE0) / 0x14;
    U8(arg2, 0xD) = ((0x14 - S16(arg0, 0x82)) * 0xE0) / 0x14;
    U8(arg2, 0xE) = ((0x14 - S16(arg0, 0x82)) * 0x20) / 0x14;
    if (S16(arg0, 0x96) == 0) {
        U16(arg0, 0x96) = 1;
        U8(arg0, 0xA0) = U8(arg0, 0xA0) + 0x18;
    } else {
        U16(arg0, 0x96) = 0;
        U8(arg0, 0xA0) = U8(arg0, 0xA0) - 0x18;
    }

    position = 0;
    do {
        position = (u8 *)position + 1;
        color = func_80069EF8();
        {
        register void *task ASM_REG("$4");
        register s32 kind ASM_REG("$6");
        register s32 particle ASM_REG("$7");
        task = (u8 *)arg0 - 0x20;
        ASM_KEEP(task);
        kind = 0x0020E0E0;
        ASM_KEEP(kind);
        color &= 0xFF;
        particle = color | 0x80;
        ASM_KEEP(particle);
        func_800250B0(task, S16(arg0, 0x7E), kind, particle, 0, 0, 0);
        }
    } while ((s32)position < 4);
    goto end;

state4_advance:
    next_state = U16(arg0, 0xA);
    U16(arg0, 0x82) = 0;
    ASM_KEEP_NV(next_state);
    goto advance_state;

state_5:
    U16(arg0, 0x82) = U16(arg0, 0x82) + 1;
    position = 0;
    fade_n1 = S16(arg0, 0x82) * 0x20;
    ASM_KEEP_NV(fade_n1);
    fade_result = fade_n1 / 0x28;
    U8(arg0, 0x92) = fade_result;
    fade_n2 = S16(arg0, 0x82) * 8;
    ASM_KEEP_NV(fade_n2);
    fade_n2 = (fade_n2 - S16(arg0, 0x82)) * 32;
    fade_result = fade_n2 / 0x28;
    U8(arg0, 0x91) = fade_result;
    fade_n3 = S16(arg0, 0x82) * 8;
    ASM_KEEP_NV(fade_n3);
    fade_n3 = (fade_n3 - S16(arg0, 0x82)) * 32;
    fade_result = fade_n3 / 0x28;
    ASM_KEEP_NV(fade_result);
    U8(arg0, 0x90) = fade_result;

    jump_table = (void **)0x800E0000;
    ASM_KEEP(jump_table);
    v1ptr = PTR(owner, 0x60);
    ASM_KEEP_NV(v1ptr);
    arg1 = (u8 *)jump_table - 0x23C0;
    ASM_KEEP_NV(arg1);
    base = PTR(v1ptr, -0x18);
    do {
        copy_src = (PointTable *)0x80;
        position = (u8 *)position + 1;
        ASM_KEEP(position);
        color = (U8(arg0, 0x92) << 16) + (U8(arg0, 0x91) << 8) + U8(arg0, 0x90);
        func_800251E8((*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)arg1) >> 1) + 4,
                      color, (s32)copy_src, S16(base, 2), S16(base, 6),
                      (s16)(U16(base, 0xA) -
                            (*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)arg1) >> 1)));
    } while ((s32)position < 2);
    if (S16(arg0, 0x82) >= 0x28) {
        next_state = U16(arg0, 0xA);
        U16(arg0, 0x82) = 0;
        goto advance_state;
    }
    goto end;

state_6:
    {
        u16 raw = U16(arg0, 0x82) + 1;
        count6 = (s16)raw;
        U16(arg0, 0x82) = raw;
    }
    position = 0;
    if (count6 >= 0x24) {
        U8(arg0, 0x92) = ((0x46 - count6) * 0x20) / 0x23;
        U8(arg0, 0x91) = ((0x46 - S16(arg0, 0x82)) * 0xE0) / 0x23;
        U8(arg0, 0x90) = ((0x46 - S16(arg0, 0x82)) * 0xE0) / 0x23;
    }

    jump_table = (void **)0x800E0000;
    ASM_KEEP(jump_table);
    v1ptr = PTR(owner, 0x60);
    ASM_KEEP_NV(v1ptr);
    arg1 = (u8 *)jump_table - 0x23C0;
    ASM_KEEP_NV(arg1);
    base = PTR(v1ptr, -0x18);
    do {
        copy_src = (PointTable *)0x80;
        position = (u8 *)position + 1;
        ASM_KEEP(position);
        color = (U8(arg0, 0x92) << 16) + (U8(arg0, 0x91) << 8) + U8(arg0, 0x90);
        func_800251E8((*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)arg1) >> 1) + 4,
                      color, (s32)copy_src, S16(base, 2), S16(base, 6),
                      (s16)(U16(base, 0xA) -
                            (*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)arg1) >> 1)));
    } while ((s32)position < 2);

    child = PTR(owner, 0x60);
    ASM_KEEP_NV(child);
    jump_table = (void **)(u32)U32(child, 0x1C);
    ASM_KEEP_NV(jump_table);
    v1ptr = (void *)0x10000000;
    ASM_KEEP_NV(v1ptr);
    jump_table = (void **)((u32)jump_table | (u32)v1ptr);
    U32(child, 0x1C) = (u32)jump_table;
    jump_table = (void **)(s32)S16(arg0, 0x82);
    ASM_KEEP_NV(jump_table);
    call_gfx = PTR(child, -0x14);
    ASM_KEEP_NV(call_gfx);
    if ((s32)jump_table >= 0x24) {
        U8(call_gfx, 0xC) -= 3;
        U8(call_gfx, 0xD) -= 3;
        U8(call_gfx, 0xE) += 2;
    } else {
        U8(call_gfx, 0xC) += 3;
        U8(call_gfx, 0xD) += 3;
        U8(call_gfx, 0xE) -= 2;
    }
    if (S16(arg0, 0x82) < 0x46) {
        goto end;
    }

    v1ptr = PTR(owner, 0x60);
    call_gfx = PTR(v1ptr, -0x14);
    U32(v1ptr, 0x1C) &= 0xEFFFFFFF;
    U8(call_gfx, 0xE) = 0x80;
    U8(call_gfx, 0xD) = 0x80;
    U8(call_gfx, 0xC) = 0x80;
    func_800240B8(PTR(owner, 0x60), U8(arg0, 9), owner);
    next_state = U16(arg0, 0xA);
    U16(arg0, 0x82) = 0x14;

advance_state:
    U16(arg0, 0xA) = next_state + 1;
    goto end;

state_7:
    count = U16(arg0, 0x82);
    U16(arg0, 0x82) = count + 1;
    if ((s16)count < 0x15) {
        goto end;
    }
    a0ptr = (void *)0x80020000;
    ASM_KEEP_NV(a0ptr);
    busy = S16(a0ptr, 0x694C);
    U16(arg0, 0x82) = count;
    if (busy == 0) {
        jump_table = (void **)0x80080000;
        ASM_KEEP_NV(jump_table);
        S32(jump_table, 0x346C) = 0;
        U16(arg0, -2) |= 0x8000;
        v1ptr = (void *)0x80080000;
        ASM_KEEP(v1ptr);
        U32(v1ptr, 0x14A0) |= 0x8000;
        goto end;
    }
    goto clear_busy;
collision_hit:
    U16(arg0, 0xA) = 7;
    U16(arg0, 0x82) = 0;
    render_flags = U16(arg2, 0x14);
set_render_flag:
    render_flags |= 0x80;
    U16(arg2, 0x14) = render_flags;
    goto end;

child_done:
    ASM_SCHED_BARRIER();
    U16(arg0, 0xA) = 3;
    U16(arg0, 0x82) = 0;
    jump_table = PTR(owner, 0x60);
    base = PTR(jump_table, -0x18);
    U16(arg1, 2) = U16(base, 2);
    U16(arg1, 6) = U16(base, 6);
    U16(arg1, 0xA) = U16(arg0, 0x78);
    func_800A56E0(0x300);
    goto end;

clear_busy:
    S16(a0ptr, 0x694C) = 0;

end:
    return;
}

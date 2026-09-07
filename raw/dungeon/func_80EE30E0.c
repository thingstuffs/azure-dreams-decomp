#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Copy32;

extern Copy32 D_80170808;
extern u8 D_80045340;
extern u8 D_80077C50[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801708BC[];
extern s32 D_80171CE8;
extern u8 D_80174EB8[];
extern u8 D_80174F18[];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

void func_801748E0(void *arg0, void *arg1, void *arg2, void *arg3) {
    Copy32 local_copy = D_80170808;
    s32 state;
    u16 counter;
    u16 flags;
    u8 *table;
    s32 index;
    void *actor;
    void *actor_data;
    void *actor_work;
    void *actor_pos;
    void *copy_base;
    s16 sample;
    s32 value;

    state = U8_AT(arg0, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    S32_AT(arg1, 0x14) = 0;
    S32_AT(arg1, 0x10) = 0;
    S32_AT(arg1, 0x0C) = 0;
    counter = U16_AT(arg0, 0x96) + 1;
    U16_AT(arg0, 0x96) = counter;
    if (((s16)counter < 0x14) && !(U16_AT(arg2, 0x14) & 0x8000)) {
        goto done;
    }
    table = D_80174F18;
    PTR_AT(arg2, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228 + S16_AT(arg3, 0x2A) + 0x100) >> 9) & 7], 0);
    U16_AT(arg0, 0x96) = 0x14;
    U8_AT(arg0, 0x9B) = U8_AT(arg0, 0x9B) + 1;

state_1:
    if ((S16_AT(arg0, 0x96) == 0x13) || (U16_AT(arg2, 0x14) & 0x8000)) {
        if (!(U16_AT(arg2, 0x14) & 0x8000)) {
            func_800A56E0(0x707);
        }
        actor = func_8003FC64(0x12);
        if (actor != 0) {
            PTR_AT(actor, 0x10) = D_801708BC;
            actor_work = (u8 *)actor + 0x20;
            func_8004491C(actor, &D_80045340);
            actor_data = PTR_AT(actor, 0x0C);
            U16_AT(actor_data, 0x14) &= 0xFFF3;
            PTR_AT(actor_work, 0x40) = arg0;
            actor_pos = PTR_AT(actor, 8);
            S16_AT(actor_pos, 2) = U16_AT(arg1, 2);
            S16_AT(actor_pos, 6) = U16_AT(arg1, 6);
            S16_AT(actor_pos, 0x0A) = U16_AT(arg1, 0x0A) - 0x20;
            ASM_SCHED_BARRIER();
            copy_base = &local_copy;
            index = ((u16)S16_AT(arg3, 0x2A) >> 7) & 0x1C;
            S32_AT(actor_work, 0x6C) = S16_AT(copy_base, index) << 0x13;
            index = ((u16)S16_AT(arg3, 0x2A) >> 7) & 0x1C;
            S32_AT(actor_work, 0x70) =
                (*(u16 *)(index + (u8 *)copy_base + 2)) << 0x13;
            S32_AT(actor_work, 0x74) = 0xFFF20000;
            S32_AT(actor_work, 0x80) = 0x14900;
            S16_AT(actor_work, 0x34) = ((u16)S16_AT(arg3, 0x2A) >> 9) & 7;
            actor_data = PTR_AT(actor, 0x0C);
            S16_AT(actor_data, 0x1E) = 0x1000;
            S16_AT(actor_data, 0x1C) = 0x1000;
            index = ((u16)S16_AT(arg3, 0x2A) >> 7) & 0x1C;
            copy_base = index + (u8 *)copy_base;
            sample = *(volatile u16 *)((u8 *)copy_base + 2);
            S16_AT(actor_data, 6) = sample * 6;
            S16_AT(arg0, 0xA4) = 0x4D;
            value = S16_AT(arg1, 2);
            if (value < 0) {
                value += 0x3F;
            }
            S8_AT(actor_work, 0x5C) = value >> 6;
            value = S16_AT(arg1, 6);
            if (value < 0) {
                value += 0x3F;
            }
            S8_AT(actor_work, 0x5D) = value >> 6;
            U8_AT(actor_data, 0x0E) = 0x80;
            U8_AT(actor_data, 0x0D) = 0x80;
            U8_AT(actor_data, 0x0C) = 0x80;
            PTR_AT(actor_data, 8) = D_80077C50;
        }
    }
    if ((S16_AT(arg0, 0x96) == 0x12) || (U16_AT(arg2, 0x14) & 0x8000)) {
        U16_AT(arg2, 0x14) |= 0x800;
    }
    counter = U16_AT(arg0, 0x96) - 1;
    U16_AT(arg0, 0x96) = counter;
    if (((s32)(counter << 16) <= 0) || (U16_AT(arg2, 0x14) & 0x8000)) {
        U8_AT(arg0, 0x9B) = U8_AT(arg0, 0x9B) + 1;
        U16_AT(arg2, 0x14) &= 0xF7FF;
        goto done;
    }
    goto done;

state_2:
    if (((S8_AT(arg2, 4) == state) && (U16_AT(arg2, 0x14) & 0x1000)) ||
        (U16_AT(arg2, 0x14) & 0x8000)) {
        U16_AT(arg2, 0x14) |= 0x800;
        U16_AT(arg0, 0x96) = 0x23;
    }
    counter = U16_AT(arg0, 0x96) - 1;
    U16_AT(arg0, 0x96) = counter;
    if (((s32)(counter << 16) <= 0) || (U16_AT(arg2, 0x14) & 0x8000)) {
        U16_AT(arg0, 0x96) = 0;
        U16_AT(arg2, 0x14) &= 0xF7FF;
    }
    if (!(U16_AT(arg2, 0x14) & 0xE000)) {
        goto done;
    }
    S32_AT(arg1, 0x14) = 0;
    S32_AT(arg1, 0x10) = 0;
    S32_AT(arg1, 0x0C) = 0;
    func_800A2B04(arg1, U8_AT(arg2, 0x24), U8_AT(arg2, 0x25));
    if (PTR_AT(arg2, 0x2C) == D_80174EB8) {
        goto done;
    }
    PTR_AT(arg2, 0x2C) = D_80174EB8;
    U16_AT(arg2, 0x14) &= 0xF7FF;
    index = ((D_80083228 + S16_AT(arg3, 0x2A) + 0x100) >> 9) & 7;
    func_80047784(arg2, U8_AT(PTR_AT(arg2, 0x2C), index), 0);
    U8_AT(arg0, 0x9B) = U8_AT(arg0, 0x9B) + 1;
    goto done;

state_3:
    if (S16_AT(arg0, 0xA4) != 0x4D) {
        func_800AD594(arg3, 0x2000);
        PTR_AT(arg0, 0x8C) = &D_80171CE8;
        D_8008346C = 0;
        U16_AT(arg3, 0x46) &= 0x7FFF;
    }

done:
    return;
}

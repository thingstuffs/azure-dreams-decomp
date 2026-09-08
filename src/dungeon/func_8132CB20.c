#include "common.h"

typedef struct S_80174320_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * s; u8 * u; } unk_2C;   /* accessed as both */
} S_80174320_0;   /* entity in func_80174320 */

typedef struct S_80174320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x53];
    s8 unk_9B;
    u8 pad_9C[0x16];
    s16 unk_B2;
} S_80174320_1;   /* obj in func_80174320 */

typedef struct S_80174320_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80174320_2;   /* ctx in func_80174320 */



extern void func_80047784(void *, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A152C(s32, s32);
extern void func_800A9A0C(void *);
extern void func_8016FCE4(void *, void *, void *, void *);
extern void func_80171594(u8, u8, s16);
extern void func_801724D4(void);
extern void func_801740F8(void *, void *, void *, void *);
extern void func_801744C0(void) __attribute__((noreturn));
extern void func_8017464C(void) __attribute__((noreturn));
extern void func_80174658(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u8 D_80174A2C[];
extern u8 D_80174A9C[];
extern u8 D_80174AA4[];
extern u8 D_80174AAC[];
extern u8 *D_80174AB4;
extern s16 D_80174AB8;

s32 func_80174320(void *arg0, void *arg1, void *arg2) {
    s32 var_a2;
    s16 temp_v0;
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    u16 temp_v0_2;
    register u8 temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 stream_count;
    u8 *stream;
    void *call_arg0;
    register void *obj ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *ctx;
    void *entity;
    register s32 zero_ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u32 page;
    void *old_anim;
    u8 *anim;
    u8 audio_x;
    u8 audio_y;
    register s32 angle_val ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u16 flags;
    s32 case_d0;

    call_arg0 = arg0;
    ctx = arg1;
    ASM_KEEP_NV(ctx);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    entity = arg2;
    obj = arg0;
    if (((S_80174320_0 *)entity)->unk_14 & 0x40) {
        return 0;
    }

    stream = D_80174AB4;
    if (stream == 0) {
        zero_ret = 0;
        return zero_ret;
    }

    temp_a3 = stream[1];
    ASM_KEEP_NV(temp_a3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_t0 = temp_a3 & 0xFF;
    if (temp_t0 == 0) {
        ((S_80174320_1 *)obj)->unk_B2 = 0;
        func_8017464C();
    }

    stream_count = stream[0];
    temp_v0 = *(u16 *)&D_80174AB8 + 1;
    D_80174AB8 = temp_v0;
    if ((s32)stream_count < temp_v0) {
        D_80174AB4 = stream + 2;
        D_80174AB8 = 0;
        ((S_80174320_1 *)obj)->unk_9B = 0;
    }

    angle_val = temp_a3 & 7;
    flags = ((S_80174320_1 *)obj)->unk_46;
    ASM_KEEP_NV(flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    angle_val <<= 9;
    ((S_80174320_1 *)obj)->unk_2A = angle_val;
    case_d0 = 0xD0;
    ASM_USE(case_d0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    flags |= 0x8000;
    ((S_80174320_1 *)obj)->unk_46 = flags;
    temp_v1 = temp_t0 & 0xF8;
    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

    if (temp_v1 == case_d0) {
        goto block_D0;
    }
    if (temp_v1 < 0xD1) {
        if (temp_v1 == 0x10) {
            goto block_10;
        }
        if (temp_v1 < 0x11) {
            if (temp_v1 == 8) {
                goto block_8;
            }
            func_8017464C();
        }
        if (temp_v1 == 0xC0) {
            goto block_C0;
        }
        if (temp_v1 == 0xC8) {
            goto block_C8;
        }
        func_8017464C();
    }
    if (temp_v1 == 0xE8) {
        goto block_E8;
    }
    if (temp_v1 < 0xE9) {
        if (temp_v1 == 0xD8) {
            goto block_D8;
        }
        if (temp_v1 == 0xE0) {
            goto block_E0;
        }
        func_8017464C();
    }
    if (temp_v1 == 0xF0) {
        goto block_F0;
    }
    if (temp_v1 == 0xF8) {
        goto block_F8;
    }
    func_8017464C();

block_8:
        call_arg0 = obj;
        ASM_KEEP_NV(call_arg0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        func_8016FCE4(call_arg0, ctx, entity, call_arg0);
        zero_ret = 0;
        ASM_TAILSLOT_PIN(zero_ret);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80174658();

block_C0:
        ((S_80174320_1 *)obj)->unk_9B = 0;
block_C8:
        func_801740F8(call_arg0, ctx, entity, obj);
        func_8017464C();

block_10:
        old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
        ASM_KEEP(old_anim);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        page = 0x80170000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        stream = (u8 *)(page + 0x4A2C);
        ASM_TAILSLOT_PIN(stream);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_801744C0();

block_F8:
        page = 0x80170000;
        ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
        ASM_KEEP(old_anim);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        stream = (u8 *)(page + 0x4AA4);
        ASM_TAILSLOT_PIN(stream);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_801744C0();

block_F0:
        old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
        anim = D_80174AAC;
        if (old_anim != anim) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
            func_80047784(entity,
                anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            func_8017464C();
        }
        goto block_common;

block_E8:
        old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
        anim = D_80174A9C;
        if (old_anim != anim) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
            func_80047784(entity,
                anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            func_80171594(((S_80174320_0 *)entity)->unk_24, ((S_80174320_0 *)entity)->unk_25,
                ((S_80174320_2 *)ctx)->unk_0A);
            func_800A152C(0x15, 1);
            func_8017464C();
        }
        goto block_common;

block_D8:
        old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
        anim = D_80174A9C;
        if (old_anim != anim) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
            func_80047784(entity,
                anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80174320_0 *)entity)->unk_14 |= 0x800;
            func_8017464C();
        }
        goto block_common;

block_D0:
        temp_v0_2 = ((S_80174320_0 *)entity)->unk_14 & 0x800;
        ((S_80174320_0 *)entity)->unk_14 = temp_v0_2;
        if (temp_v0_2 != 0) {
            ((S_80174320_0 *)entity)->unk_14 = 0;
            func_8017464C();
        }
        goto block_common;

block_E0:
        anim = D_80174A2C + 0x50;
        if (((S_80174320_0 *)entity)->unk_2C.u != anim) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
            func_80047784(entity,
                anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            func_801724D4();
            audio_x = ((S_80174320_0 *)entity)->unk_24;
            audio_y = ((S_80174320_0 *)entity)->unk_25;
            var_a2 = 0x3000;
            if (((S_80174320_1 *)obj)->unk_1C & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(audio_x, audio_y, var_a2);
        }
        goto block_common;

block_common:
    func_800A9A0C(obj);
    return 0;
}

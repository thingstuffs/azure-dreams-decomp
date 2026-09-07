#include "common.h"

#define FIELD(obj, type, off) (*(type *)((u8 *)(obj) + (off)))

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
    register s32 temp_t0 ASM_REG("$8");
    register s32 temp_v1 ASM_REG("$3");
    u16 temp_v0_2;
    register u8 temp_a3 ASM_REG("$7");
    u8 stream_count;
    register u8 *stream ASM_REG("$5");
    register void *call_arg0 ASM_REG("$4");
    register void *obj ASM_REG("$17");
    register void *ctx ASM_REG("$18");
    register void *entity ASM_REG("$16");
    register s32 zero_ret ASM_REG("$2");
    register u32 page ASM_REG("$2");
    register void *old_anim ASM_REG("$3");
    u8 *anim;
    u8 audio_x;
    u8 audio_y;
    register s32 angle_val ASM_REG("$2");
    register u16 flags ASM_REG("$3");
    register s32 case_d0 ASM_REG("$2");

    call_arg0 = arg0;
    ctx = arg1;
    ASM_KEEP_NV(ctx);
    entity = arg2;
    ASM_KEEP_NV(entity);
    obj = arg0;
    if (FIELD(entity, u16, 0x14) & 0x40) {
        return 0;
    }

    stream = D_80174AB4;
    if (stream == 0) {
        zero_ret = 0;
        return zero_ret;
    }

    temp_a3 = stream[1];
    ASM_KEEP_NV(temp_a3);
    temp_t0 = temp_a3 & 0xFF;
    if (temp_t0 == 0) {
        FIELD(obj, s16, 0xB2) = 0;
        func_8017464C();
    }

    stream_count = stream[0];
    temp_v0 = *(u16 *)&D_80174AB8 + 1;
    D_80174AB8 = temp_v0;
    if ((s32)stream_count < temp_v0) {
        D_80174AB4 = stream + 2;
        D_80174AB8 = 0;
        FIELD(obj, s8, 0x9B) = 0;
    }

    angle_val = temp_a3 & 7;
    flags = FIELD(obj, u16, 0x46);
    ASM_KEEP_NV(flags);
    angle_val <<= 9;
    FIELD(obj, s16, 0x2A) = angle_val;
    case_d0 = 0xD0;
    ASM_USE(case_d0);
    flags |= 0x8000;
    FIELD(obj, u16, 0x46) = flags;
    ASM_SCHED_BARRIER();
    temp_v1 = temp_t0 & 0xF8;
    ASM_KEEP(stream);
    ASM_KEEP(temp_a3);
    ASM_KEEP(temp_t0);
    ASM_KEEP(call_arg0);

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
        ASM_KEEP_NV(call_arg0);
        func_8016FCE4(call_arg0, ctx, entity, call_arg0);
        zero_ret = 0;
        ASM_TAILSLOT_PIN(zero_ret);
        func_80174658();

block_C0:
        FIELD(obj, s8, 0x9B) = 0;
block_C8:
        func_801740F8(call_arg0, ctx, entity, obj);
        func_8017464C();

block_10:
        old_anim = FIELD(entity, void *, 0x2C);
        ASM_KEEP(old_anim);
        page = 0x80170000;
        ASM_KEEP(page);
        stream = (u8 *)(page + 0x4A2C);
        ASM_TAILSLOT_PIN(stream);
        func_801744C0();

block_F8:
        page = 0x80170000;
        ASM_KEEP_NV(page);
        old_anim = FIELD(entity, void *, 0x2C);
        ASM_KEEP(old_anim);
        stream = (u8 *)(page + 0x4AA4);
        ASM_TAILSLOT_PIN(stream);
        func_801744C0();

block_F0:
        old_anim = FIELD(entity, void *, 0x2C);
        ASM_KEEP(old_anim);
        anim = D_80174AAC;
        if (old_anim != anim) {
            FIELD(entity, u8 *, 0x2C) = anim;
            func_80047784(entity,
                anim[((D_80083228 + FIELD(obj, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_8017464C();
        }
        goto block_common;

block_E8:
        old_anim = FIELD(entity, void *, 0x2C);
        ASM_KEEP(old_anim);
        anim = D_80174A9C;
        if (old_anim != anim) {
            FIELD(entity, u8 *, 0x2C) = anim;
            func_80047784(entity,
                anim[((D_80083228 + FIELD(obj, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_80171594(FIELD(entity, u8, 0x24), FIELD(entity, u8, 0x25),
                FIELD(ctx, s16, 0xA));
            func_800A152C(0x15, 1);
            func_8017464C();
        }
        goto block_common;

block_D8:
        old_anim = FIELD(entity, void *, 0x2C);
        ASM_KEEP(old_anim);
        anim = D_80174A9C;
        if (old_anim != anim) {
            FIELD(entity, u8 *, 0x2C) = anim;
            func_80047784(entity,
                anim[((D_80083228 + FIELD(obj, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(entity, u16, 0x14) |= 0x800;
            func_8017464C();
        }
        goto block_common;

block_D0:
        temp_v0_2 = FIELD(entity, u16, 0x14) & 0x800;
        FIELD(entity, u16, 0x14) = temp_v0_2;
        if (temp_v0_2 != 0) {
            FIELD(entity, u16, 0x14) = 0;
            func_8017464C();
        }
        goto block_common;

block_E0:
        anim = D_80174A2C + 0x50;
        if (FIELD(entity, u8 *, 0x2C) != anim) {
            FIELD(entity, u8 *, 0x2C) = anim;
            func_80047784(entity,
                anim[((D_80083228 + FIELD(obj, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_801724D4();
            audio_x = FIELD(entity, u8, 0x24);
            audio_y = FIELD(entity, u8, 0x25);
            var_a2 = 0x3000;
            if (FIELD(obj, s32, 0x1C) & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(audio_x, audio_y, var_a2);
        }
        goto block_common;

block_common:
    func_800A9A0C(obj);
    return 0;
}

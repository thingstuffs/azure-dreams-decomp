#include "common.h"

typedef struct PtrSet {
    void *ptr[3];
} PtrSet;

typedef struct DeepRecord {
    u8 pad00[0x10];
    s32 value10;
} DeepRecord;

typedef struct MidRecord {
    u8 pad00[8];
    DeepRecord *deep08;
} MidRecord;

typedef struct RootRecord {
    u8 pad00[4];
    MidRecord *mid04;
    u8 pad08[0x2e];
    s16 state36;
} RootRecord;

typedef struct StateRecord {
    RootRecord *root00;
    s16 mode04;
    s16 timer06;
    u16 flags08;
} StateRecord;

typedef struct MotionRecord {
    u8 pad00[8];
    s32 value08;
    s32 value0c;
    s32 value10;
    s32 value14;
} MotionRecord;

typedef struct SpriteRecord {
    void *kind00;
    u8 pad04[8];
    s32 color0c;
    u8 pad10[4];
    u16 flags14;
} SpriteRecord;

extern PtrSet D_80020048;
extern u8 D_800F2A34[0x28];
extern u8 D_800F2A5C[0x68];
extern u8 D_800F2AC4[0x40];
extern u8 D_800F2B04[0x28];
extern u8 D_800F2B2C[0x28];
extern s32 D_800814A0[3];

extern void func_8003DB94(SpriteRecord *, void *, s32);
extern void func_800478B8(SpriteRecord *);
extern s32 rand(void);
extern void func_8009539C(MotionRecord *);
extern s32 func_800C2AE8(MotionRecord *);

void func_80022698(StateRecord *state, MotionRecord *motion, SpriteRecord *sprite)
{
    RootRecord *root;
    DeepRecord *deep;
    PtrSet local;
    void *selected;
    PtrSet *localp;

    selected = 0;
    root = state->root00;
    deep = root->mid04->deep08;
    local = D_80020048;
    func_800478B8(sprite);
    func_8009539C(motion);
    localp = &local;

    switch (state->mode04) {
    case 0:
        sprite->color0c += 0x101010;
        if ((u8)sprite->color0c < 0xa0) {
            goto done;
        }
        sprite->color0c = 0x808080;
        {
            u16 flags_zero = sprite->flags14;

            flags_zero &= 0xfff3;
            
            sprite->flags14 = flags_zero;
        }
        goto increment_mode;

    case 1:
        if (state->flags08 & 1) {
            selected = localp->ptr[rand() % 3];
            motion->value0c = ((rand() & 0x7f) - 0x40) << 15;
            motion->value14 = (0 - ((rand() & 0xf) + 8)) << 16;
            if (motion->value0c > 0) {
                sprite->flags14 |= 1;
            }
            motion->value10 = deep->value10;
            state->mode04 = 0x20;
        }
        if (root->state36 != 10) {
            goto done;
        }
        if (rand() & 1) {
            selected = D_800F2B04;
        } else {
            selected = D_800F2B2C;
        }
        state->mode04 = 0x100;
        goto done;

    case 0x20: {
        s32 value;

        motion->value14 += 0x40000;
        value = (s16)func_800C2AE8(motion);
        if (value < motion->value08) {
            motion->value08 = value;
            motion->value14 = (-motion->value14) >> 3;
        }
        if (sprite->flags14 & 0x6000) {
            state->timer06 = 10;
            if (sprite->kind00 == D_800F2AC4) {
                sprite->color0c = 0xa0a0a0;
                sprite->flags14 |= 0xc;
                state->mode04 = 0x22;
                goto done;
            }
            if (rand() & 1) {
                selected = D_800F2A34;
            } else {
                selected = D_800F2A5C;
            }
            state->mode04++;
        }
        motion->value0c -= motion->value0c >> 3;
        motion->value10 -= motion->value10 >> 3;
        goto done;
    }

    case 0x21: {
        s32 value;
        u16 flags_21;

        motion->value14 += 0x40000;
        value = (s16)func_800C2AE8(motion);
        if (value < motion->value08) {
            motion->value08 = value;
            motion->value14 = (-motion->value14) >> 3;
        }
        motion->value0c -= motion->value0c >> 3;
        motion->value10 -= motion->value10 >> 3;
        flags_21 = sprite->flags14;
        if (!(flags_21 & 0x6000)) {
            goto done;
        }
        sprite->flags14 = flags_21 | 0xc;
        sprite->color0c = 0xa0a0a0;
increment_mode:
        state->mode04++;
        goto done;
    }

    case 0x22:
        sprite->color0c += (s32)0xffdfdfe0;
        if (motion->value08 > 0) {
            motion->value14 = 0;
            motion->value08 = 0;
        }
        if ((u8)sprite->color0c < 0x20) {
            sprite->color0c = 0;
        }
        if (root->state36 != 9) {
            state->timer06--;
            if (state->timer06 > 0) {
                goto done;
            }
        }
        state->mode04 = 0xfff;
        goto done;

    case 0x100:
        sprite->color0c = 0xa0a0a0;
        sprite->flags14 |= 0xc;
        state->mode04++;
        /* fallthrough */
    case 0x101:
        sprite->color0c += (s32)0xffdfdfe0;
        if ((u8)sprite->color0c < 0x20) {
            sprite->color0c = 0;
            state->mode04 = 0xfff;
        }
        goto done;

    case 0xfff:
        ((u16 *)state)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;

    default:
        goto done;
    }

done:
    if (selected != 0) {
        func_8003DB94(sprite, selected, 0);
        sprite->flags14 &= 0x9fff;
    }
}

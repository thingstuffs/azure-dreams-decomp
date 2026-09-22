#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 value;
} __attribute__((packed)) Packed4;

/* owner in func_80174234 */
typedef struct S_80174234_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80174234_0;

/* part in func_80174234 */
typedef struct S_80174234_1 {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} S_80174234_1;

/* actor in func_80174234.  0x48 is written as one packed word (retail's
   lwl/lwr + swl/swr pair) and read one byte deep at 0x49, so the two views
   share a union rather than overlapping members. */
typedef struct S_80174234_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1C];
    union {
        Packed4 at48;
        struct {
            u8 pad_48[0x1];
            u8 at49;
        } bytes;
    } unk_48;
    u8 pad_4C[0x21];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80174234_2;

/* the counter block at D_80083460 */
typedef struct S_80174234_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174234_3;

M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
M2C_UNK func_80099368();                 /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
s32 func_800A6D30();                                /* extern */
void *func_80170908();                /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern M2C_UNK D_8017089C;
extern M2C_UNK D_801708AC;
extern M2C_UNK D_801708B8;
extern M2C_UNK D_801708BC;
extern u8 D_80174F58[];

/* Start the actor's attack step: clear its 0x71 busy bit, latch the 0x400 link flag with a random facing nudge, run the animation chain for the sprite record it owns, then arm owner state 0x17 and point the part at the direction table. */
void func_80174234(S_80174234_0 *owner, void *unused, S_80174234_1 *part, S_80174234_2 *actor) {
    s32 session;
    s32 anim;
    s32 link_flags;
    void *sprite;
    S_80174234_3 *counters;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(actor) << 0x10) == 0)) {
        if (actor->unk_1C & 0x400) {
            link_flags = actor->unk_14;
            if (!(link_flags & 0x80000000)) {
                link_flags |= 0x80000000;
                actor->unk_14 = (s32)link_flags;
                actor->unk_2A = (u16) (actor->unk_2A + ((func_800A6D30() & 7) << 9));
            }
        }
        session = func_800990FC();
        if (actor->unk_48.bytes.at49 == 0) {
            sprite = func_80170908(part, actor);
            if (sprite != NULL) {
                actor->unk_48.at48 = *(Packed4 *) sprite;
                anim = func_80099368(sprite, func_80099194(&D_801708AC, func_8009929C(0xA, func_80099194(&D_8017089C, func_80099734(actor, session)))));
                anim = func_80099194(&D_801708B8, anim);
            } else {
                anim = func_80099194(&D_801708BC, func_80099734(actor, session));
            }
        } else {
            anim = func_80099194(&D_801708BC, func_80099734(actor, session));
        }
        func_80099290(anim);
        func_800A5720(session);
        owner->unk_9A = 0x17;
        owner->unk_8C = 0;
        owner->unk_9B = 0;
        *(u8 **)((s8 *)part + 0x2C) = D_80174F58;   /* the struct-member form `part->unk_2C = ...` is NOT byte-exact here: reorder-only 4 (same-multiset, one addiu+sw pair drifts) */
        func_80047784(part, D_80174F58[((D_80083228 + (s16) actor->unk_2A + 0x100) >> 9) & 7], 0);
        counters = (S_80174234_3 *) &D_80083460;
        actor->unk_6D = (u8) (actor->unk_6D - 1);
        counters->unk_0A = (u16) (counters->unk_0A + 1);
    }
}

/* MECHANISM: The four-argument ABI and true-space merge preserve retail's s1/a3, s4/a2, s3/a0, s2/s0 roles.
   A packed four-byte assignment restores lwl/lwr/swl/swr; guarded v0-field and branch-local calls close local roles.
   Byte-table indexing plus a held D_80083460 base fixes the tail and its one-word displacement cascade.
   The final packed-copy scratch is v0 only at 2.7.2-cdk-G0; 2.8.1-G0 leaves the four-word t0 residue. */

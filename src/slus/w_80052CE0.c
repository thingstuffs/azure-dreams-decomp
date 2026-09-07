/* func_80052CE0 -- BYTE-EXACT, LINKABLE candidate (computed-goto idiom).
 * Config: tools/match.py --gcc 2.7.2-cdk --opt O2 (aspsx 2.56), no maspsx flags.
 *
 * The switch was rewritten as a computed goto through the RETAIL table
 * jtbl_8002EFF0 (an absolute in config/generated/slus_006.14.undefined_syms.txt),
 * so this TU emits NO compiler-generated jump table into .text-referenced
 * .rodata and links. Idiom copied from src/w_800595C0.c: the `keepalive` array
 * exists only to keep the case labels alive for gcc; it lands in .rodata but is
 * unreferenced from .text, so the linker discards it silently.
 */
#include "common.h"

typedef struct S_52CE0_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_52CE0_Rect;

typedef struct S_52CE0 {
    s16 state;
    s16 timer;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} S_52CE0;

typedef struct S_52CE0_Pos {
    s32 x;
    s32 y;
} S_52CE0_Pos;

typedef struct S_52CE0_Ent {
    u8 pad0[0x14];
    u16 flags;
} S_52CE0_Ent;

extern void *jtbl_8002EFF0[];

extern void func_80052774(s16 a0, s16 a1, s16 a2, s16 a3);
extern void MoveImage(S_52CE0_Rect *rect, s32 x, s32 y);

void func_80052CE0(S_52CE0 *o, S_52CE0_Pos *pos, S_52CE0_Ent *ent)
{
    S_52CE0_Rect rect;
    s16 d;
    s32 idx;
    static void *const keepalive[] = {
        &&L_state0, &&L_state1, &&L_state2, &&L_state3,
        &&L_state4, &&L_state5, &&L_state6, &&L_state7
    };
    (void)keepalive;

    o->timer++;
    idx = o->state;
    if ((u32)idx >= 8) {
        goto L_end;
    }
    goto *jtbl_8002EFF0[idx];

L_state0:
    if (o->unk6 == 1) {
        o->timer = 0;
        o->unk6 = 2;
        o->state++;
        ent->flags &= 0xFF7F;
        pos->x = o->unkA << 16;
        pos->y = o->unkC << 16;
        func_80052774(o->unk10, o->unkC + 15, o->unkE, 0);
    }
    goto L_end;

L_state1:
    o->unk10 += 6;
    if (o->timer >= 16) {
        o->timer = 0;
        o->state++;
    }
    func_80052774(o->unk10, o->unkC + 15, o->unkE, 0);
    goto L_end;

L_state2:
    o->unk10 += 6;
    o->unkA += 8;
    if (o->timer >= 0x30) {
        o->timer = 0;
        o->state++;
    }
    pos->x = o->unkA << 16;
    func_80052774(o->unk10, o->unkC + 15, o->unkE, 0);
    goto L_end;

L_state3:
    if (o->timer >= 0x50) {
        o->timer = 0;
        o->state++;
    }
    func_80052774(o->unk10, o->unkC + 15, o->unkE, 0);
    goto L_end;

L_state4:
    o->timer++;
    if (o->timer >= 2) {
        o->timer = 0;
        o->unk4++;
        rect.x = 0x3C0;
        rect.y = (o->unk8 + 1) * 16 - o->unk4;
        rect.w = 0x3F;
        rect.h = 1;
        MoveImage(&rect, 0x380, (o->unk8 + 1) * 16 - o->unk4);
        if (o->unk4 < 16) {
            d = o->unk4 - 15;
            func_80052774(o->unk10, o->unkC - d, o->unkE,
                          o->timer + o->unk4 * 2);
        } else {
            o->timer = 0;
            o->unk4 = 0;
            o->state++;
        }
    } else {
        d = o->unk4 - 15;
        func_80052774(o->unk10, o->unkC - d, o->unkE,
                      o->timer + o->unk4 * 2);
    }
    goto L_end;

L_state5:
    if (o->timer >= 0x50) {
        o->timer = 0;
        o->state++;
    }
    goto L_end;

L_state6:
    o->unkA -= 8;
    if (o->timer >= 0x30) {
        o->timer = 0;
        o->state++;
    }
    pos->x = o->unkA << 16;
    goto L_end;

L_state7:
    ent->flags |= 0x80;
    o->state = 0;
    o->timer = 0;
    o->unk4 = 0;
    o->unk6 = 0;
    o->unkA = 0;
    o->unkC = 0;
    o->unkE = 0;
    o->unk10 = 0;

L_end:
    ;
}

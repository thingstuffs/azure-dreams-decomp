#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800BE214_3 {
    M2C_UNK * unk_00;
} S_800BE214_3;   /* (s8 *)sp10 + (arg0->unk_68 * 4) in func_800BE214 */

typedef struct S_800BE214_4 {
    M2C_UNK * unk_00;
} S_800BE214_4;   /* (s8 *)sp10 + (arg0->unk_A4 * 4) in func_800BE214 */


typedef union {
    s16 state;
    u16 raw;
} StateWord;

struct Dst;
struct Elem;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC();
extern void func_8003DB94(struct Dst *, struct Elem *, s16);
extern M2C_UNK func_800478B8();
extern s32 func_80064584();
extern s32 rand();
extern s32 func_800C2AB4();

extern M2C_UNK D_80089684[9];
extern void *D_800896A8[];
extern M2C_UNK D_800F9D80[3];

typedef struct S_800BE214_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    u8 pad_6E[0x32];
    u16 unk_A0;
    u8 pad_A2[0x2];
    s32 unk_A4;
} S_800BE214_0;   /* arg0 in func_800BE214 */


typedef struct S_800BE214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE214_2;   /* arg1 in func_800BE214 */

/* Advances the actor animation state and applies a timed pose offset. */
void func_800BE214(S_800BE214_0 *actor, S_800BE214_2 *pose, Rec_D_80082E80 *animation) {
    void *animations[9];
    Copy16 *copy_src;
    Copy16 *copy_dst;
    Copy16 *copy_end;
    s16 animation_index;
    s32 state;
    u16 elapsed_frames;

    copy_dst = (Copy16 *)animations;
    copy_src = (Copy16 *)&D_80089684;
    copy_end = copy_src + 2;
    do {
        *copy_dst = *copy_src;
        copy_src++;
        copy_dst++;
    } while (copy_src != copy_end);
    copy_dst->w0 = copy_src->w0;
    do { } while (0);
    func_800478B8(animation);
    state = actor->unk_68;
    if ((u32)state >= 0x61) {
        goto L_default;
    }
    switch (state) {
    case 0: goto L_case_0;
    case 0x20: goto L_case_20;
    case 0x23: goto L_case_23;
    case 0x24: goto L_case_24;
    case 0x25: goto L_case_25;
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x27: goto L_case_212227;
    case 0x40: goto L_case_40;
    case 0x60: goto L_case_60;
    default: goto L_default;
    }

L_case_0:
    if ((func_800352FC() != 0) && (func_800C2AB4(actor) != 0)) {
        animation_index = rand() & 7;
        actor->unk_68 = animation_index;
        actor->unk_A4 = (u32)animation_index;
        func_8003DB94((struct Dst *)animation, (struct Elem *)((S_800BE214_3 *)((s8 *)animations + (actor->unk_68 * 4)))->unk_00, 0);
        actor->unk_68 = (s16)((u16)actor->unk_68 + 0x20);
    }
    goto L_default;

L_case_20:
    if (!(animation->unk_14.at00_u16.v & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)animation, (struct Elem *)animations[0], 0);
    actor->unk_6C = 0;
    actor->unk_A4 = 0;
    pose->unk_0A = (u16)actor->unk_A0;
    goto L_block_16;

L_case_23:
    if (!(animation->unk_14.at00_u16.v & 0x6000)) goto L_return;
    actor->unk_6C = 6;
    actor->unk_A4 = 8;
    func_8003DB94((struct Dst *)animation, (struct Elem *)animations[8], 0);
    actor->unk_68 = 0x40;
    goto L_default;

L_case_24:
    if (!(animation->unk_14.at00_u16.v & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)animation, (struct Elem *)&D_800F9D80, 0);
    {
        StateWord next_state = { 0x20 };
        actor->unk_68 = next_state.state;
    }
    goto L_default;

L_case_25:
    if (!(animation->unk_14.at00_u16.v & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)animation, (struct Elem *)D_800F9D80, 0);
    goto L_block_19;

L_case_212227:
    if (!(animation->unk_14.at00_u16.v & 0x6000)) goto L_return;
    goto L_block_16;

L_block_16:
    actor->unk_68 = 0x60;
    goto L_default;

L_case_40:
    pose->unk_0A = (u16)(actor->unk_A0 + (func_80064584((actor->unk_6C << 0xC) / 22) >> 8));
    elapsed_frames = (u16)actor->unk_6C;
    actor->unk_6C = (s16)(elapsed_frames + 1);
    if ((s16)elapsed_frames >= 0xDC) goto L_block_19;
    goto L_default;

L_block_19:
    actor->unk_68 = 0x20;
    goto L_default;

L_case_60:
    if ((func_800352FC() == 0) || (func_800C2AB4(actor) == 0)) {
        actor->unk_68 = 0;
    }
    goto L_default;

L_default:
    if (animation->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94((struct Dst *)animation, (struct Elem *)((S_800BE214_4 *)((s8 *)animations + (actor->unk_A4 * 4)))->unk_00, 0);
    }

L_return:
    return;
}

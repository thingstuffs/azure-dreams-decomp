#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


typedef struct S_80024078_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024078_2_pre;   /* the 0x18 bytes before parent in func_80024078, addressed as parent[-1] */

typedef struct S_80024078_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80024078_3;   /* arg0 in func_80024078 */

typedef struct S_80024078_4 {
    u8 pad_00[0x2C];
    s16 unk_2C;
} S_80024078_4;   /* arg0->child in func_80024078 */



typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

typedef struct {
    void *field_0;
    u16 *field_4;
    u8 field_8;
    u8 field_9;
    s16 state;
    void *child;
    u8 pad_10[0xA];
    s16 timer_1A;
    s16 timer_1C;
    u8 pad_1E[2];
    s16 phase_20;
    s16 timer_22;
} State;

extern s32 func_80040490(u8 *, Rect *);
extern s32 func_8003F80C();
extern void *func_80024578(void *, s32);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);

extern u8 D_80028F68[];
extern u8 D_8002964C[];
extern s16 D_8002966C[6];
extern u8 D_8002966E[12];
extern s32 D_80029670[3];
extern u16 D_800281F8[];
extern u8 D_800281FC[12];

/* Advances the screen transition, updates fade timers, and releases completed state. */
void func_80024078(State *ctx)
{
    GameWork *screen = &gameWork;
    switch (ctx->state) {
    case 0: {
        s32 rect_words[2];
        s32 phase;
        s32 fade_duration;
        void *parent;
        EntityRec *object;
        void *child;
        s16 previous_state;

        rect_words[0] = 0x010003A0;
        rect_words[1] = 0x00400020;
        func_80040490(D_80028F68, (Rect *)rect_words);
        func_8003F80C(D_8002964C, 0x7AC0, 1, 2);
        D_8002966C[0] = 1;
        D_8002966E[0] = ctx->field_9;
        D_80029670[0] = (s32)ctx->field_0;

        object = D_800814A8;
        object->unk_F4 = D_800281FC;
        object->unk_96 = 0x14;
        object->unk_A8 = ctx->field_8;
        D_800814A8->unk_102 = 1;

        ctx->state++;
        ASM_MEM_BARRIER();
        if ((*ctx->field_4 & 0x80) == 0) {
            break;
        }

        parent = ctx->field_0;
        child = func_80024578(((S_80024078_2_pre *)parent)[-1].unk_00, (s32)parent);
        ctx->child = child;
        if (child == 0) {
            break;
        }

        fade_duration = 0x20;
        {
            previous_state = ((S_80024078_3 *)ctx)->unk_0A;
        }
        phase = -1;
        ctx->timer_1A = fade_duration;
        ctx->phase_20 = phase;
        ctx->timer_22 = fade_duration;
        ctx->state = previous_state + 1;
        break;
    }

    case 1:
        if (((S_80024078_4 *)(ctx->child))->unk_2C != 1) {
            break;
        }
        ctx->timer_1C = 0x18;
        ctx->state++;
        ASM_MEM_BARRIER();
        ctx->timer_1C--;
        if (ctx->timer_1C >= 0xB) {
            break;
        }
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2))--;
        func_800A56E0(func_80053EF0(4) != 2 ? 0x300 : 0x4300);
        goto advance_state;

    case 2:
        if (D_8002966C[0] != 0) {
            break;
        }
        ctx->timer_1A = 0x20;
        ctx->phase_20 = 0;
        ctx->state++;
        break;

    case 3:
        screen->view.unk_091 += (0x80 - screen->view.unk_091) / ctx->timer_1A;
        screen->view.unk_092 += (0x80 - screen->view.unk_092) / ctx->timer_1A;
        ctx->timer_1A--;
        if (ctx->timer_1A > 0) {
            break;
        }
        screen->view.unk_091 = 0x80;
        screen->view.unk_092 = 0x80;
advance_state:
        ctx->state++;
        break;

    case 4:
        if ((s16)D_800281F8[0] != 0) {
            break;
        } else {
            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_0A--;
        }
        (*(u16 *)((u8 *)ctx + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 5:
    case 6:
    default:
        break;
    }

    if (ctx->phase_20 < 0) {
        screen->view.unk_091 += (0x20 - screen->view.unk_091) / ctx->timer_22;
        screen->view.unk_092 += (0x20 - screen->view.unk_092) / ctx->timer_22;
        ctx->timer_22--;
        if (ctx->timer_22 <= 0) {
            ctx->phase_20 = 0;
        }
    }
    D_800281F8[0] = 0;
}

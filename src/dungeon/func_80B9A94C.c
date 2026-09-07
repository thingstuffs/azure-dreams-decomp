#include "common.h"

typedef struct EffectState {
    u8 pad00[4];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad07[0x16 - 7];
    s16 phase;
    u8 pad18[2];
    s16 lifetime;
    u8 pad1C[2];
    s16 grid_offset;
    u16 spawn_count;
    u8 pad22[0x64 - 0x22];
    u16 grid[4][3];
} EffectState;

typedef struct EffectColor {
    u8 pad00[0xC];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

typedef struct RenderData {
    u8 pad00[6];
    s16 field06;
    void *texture;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad0F;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_y;
    s16 scale_x;
} RenderData;

typedef struct EffectObject {
    u8 pad00[8];
    s32 *position;
    RenderData *render;
    void *update;
    u8 pad14[0xC];
    u8 sub[0x80];
} EffectObject;

typedef struct Packed12 {
    u8 bytes[12];
} Packed12;

extern EffectObject *func_8003FC64(s32 kind);
extern void func_8004491C(void *object, void *callback);
extern s32 D_800814A0;
extern u8 D_801740B4[];
extern u8 D_80174108[];
extern Packed12 D_80174FC0;

void func_8017414C(EffectState *state, s32 *position, EffectColor *color)
{
    EffectObject *object;
    u8 *sub;
    RenderData *render;
    s32 *object_position;
    u8 *texture;
    u8 *entry;
    s16 object_index;
    s16 color_index;
    s16 row;
    s16 column;
    s16 next_offset;
    s16 current_offset;

    if (state->phase == 1) {
        goto phase_one;
    } else if (state->phase < 2) {
        if (state->phase == 0) {
            goto phase_zero;
        }
        goto state_done;
    } else {
        if (state->phase == 2) {
            goto phase_two;
        }
        goto state_done;
    }

phase_zero:
    color->red = state->red * (50 - state->lifetime) / 10;
    color->green = state->green * (50 - state->lifetime) / 10;
    color->blue = state->blue * (50 - state->lifetime) / 10;
    if (state->lifetime < 41) {
        state->phase++;
    }
    goto state_done;

phase_one:
    if (state->lifetime < 12) {
        state->phase++;
    }
    goto state_done;

phase_two:
    color->red = state->red * state->lifetime / 10;
    color->green = state->green * state->lifetime / 10;
    color->blue = state->blue * state->lifetime / 10;

state_done:
    state->spawn_count++;
    object_index = 0;
    do {
        object = func_8003FC64(0x12);
        if (object != 0) {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            sub = object->sub;
            *(s16 *)(sub + 0x1A) = 1;
            *(s16 *)(sub + 0x1C) = 1;
            object->update = D_80174108;
            func_8004491C(object, D_801740B4);

            render = object->render;
            render->field10 = 0x20;
            render->flags |= 0xC;
            object_position = object->position;
            object_position[0] = position[0];
            object_position[1] = position[1];
            color_index = 0;
            object_position[2] = position[2];
            render = object->render;
            render->scale_x = 0x1000;
            render->scale_y = 0x1000;
            render->blue = 0x80;
            render->green = 0x80;
            render->red = 0x80;

            do {
                entry = sub + color_index * 4;
                entry[4] = color->red;
                entry[5] = color->green;
                entry[6] = color->blue;
                color_index++;
            } while (color_index < 4);

            if (object_index == 3) {
                sub[0xA] = 0;
                sub[9] = 0;
                sub[8] = 0;
                sub[6] = 0;
                sub[5] = 0;
                sub[4] = 0;
            }

            render->field06 = 0;
            *(Packed12 *)(sub + 0x28) = D_80174FC0;
            row = 0;
            render->texture = sub + 0x28;
            texture = render->texture;
            texture[8] += state->grid_offset * 4;
            texture = render->texture;
            texture[9] += (state->spawn_count & 3) * 8;

            do {
                column = 0;
                do {
                    ((EffectState *)sub)->grid[row][column] =
                        state->grid[row][column];
                    column++;
                } while (column < 3);
                row++;
            } while (row < 4);

            next_offset = -((object_index + 1) * 0x10);
            current_offset = -(object_index * 0x10);
            *(s16 *)(sub + 0x6E) = next_offset;
            *(s16 *)(sub + 0x68) = next_offset;
            *(s16 *)(sub + 0x7A) = current_offset;
            *(s16 *)(sub + 0x74) = current_offset;
        }
        object_index++;
    } while (object_index < 4);

    state->lifetime--;
    if (state->lifetime <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: retail word 129 (`addiu $v0,$s3,1` in the `beqz $s0` delay slot) is
   gcc reorg STEALING the first insn of the branch TARGET block ($L17 = the loop
   increment) and retargeting the branch one word past it. Our gcc predicts the
   EQ branch not-taken, so fill_eager_delay_slots searches the FALLTHROUGH thread
   first and takes `addiu $s1,$s0,0x20` instead (292 words, 1 short).
   ASM_SCHED_BARRIER() as the first statement of the `if (object != 0)` body makes
   stop_search_p() abort the fallthrough search at word 0, so reorg falls back to
   the target thread and performs retail's steal. Loop index is a plain `i++` at
   the loop bottom (NOT an explicit next-index phi: that shape emits the addiu in
   both preds and misplaces the body copy into the inner-loop back-branch slot).
   The state[-1] RMW must NOT be volatile: reorg's resource_conflicts_p returns 1
   unconditionally once needed.volatil is set, so a volatile load at the head of
   the bgtz fallthrough thread blocks every later candidate and the tail
   `lui $v1,%hi(D_800814A0)` cannot reach the branch delay slot. */

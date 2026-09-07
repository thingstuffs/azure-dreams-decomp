#include "common.h"

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Position16 {
    u16 pad0;
    s16 x;
    u16 pad4;
    s16 y;
    u16 pad8;
    s16 z;
} Position16;

typedef struct EffectState {
    void *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field_14;
    s16 x;
    s16 y;
    s16 z;
    u8 status;
    u8 pad1D[0x7B];
} EffectState;

typedef struct ColorPart {
    u8 pad[0xC];
    u32 color;
} ColorPart;

typedef struct Scratch {
    s16 work[8];
    u8 gap[8];
    s16 probe[3];
    u8 result_gap[2];
    s16 result;
    u16 map_flags;
} Scratch;

#define U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n) (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))
#define probe scratch.probe
#define result scratch.result
#define map_flags scratch.map_flags

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern void *D_800814A8[4];
extern u32 D_800814A0[4];
extern s32 D_8008346C;
extern u8 D_80082E80[];
extern void *D_80024008[];
extern s16 D_8006CCD8_early[] __asm__("D_8006CCD8");
extern s16 D_8006CCE8_early[] __asm__("D_8006CCE8");
extern void *D_800814A8_early[4] __asm__("D_800814A8");
extern u8 D_80082E80_early[] __asm__("D_80082E80");

extern s16 func_800A0818(u8, u8, s16, s16, s16 *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s16 func_800BCAD0(void *);
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A45D8(u16, u16);
extern s32 func_800A5690(void);
extern void func_800A56E0(s32);
extern void func_800240CC(void *, void *, s16);
extern void func_8002441C(void *, void *);
extern void func_800245CC(void *, void *);
extern void *func_800D24A8(u8, s16, s16, s16);
extern void func_80042640(void *, s32);
extern s32 func_800A6D30(void);

extern void func_80024888(void) __attribute__((noreturn));
extern void func_80024980(void) __attribute__((noreturn));
extern void func_80024AE4(void) __attribute__((noreturn));
extern void func_80024D54(void) __attribute__((noreturn));
extern void func_80024DE0(void) __attribute__((noreturn));

void func_81898EBC(EffectState *arg0, Motion *arg1, ColorPart *arg2)
{
    register EffectState *state ASM_REG("$16") = arg0;
    register Motion *motion ASM_REG("$18") = arg1;
    register ColorPart *part ASM_REG("$19");
    register void *owner ASM_REG("$17");
    register void *meta ASM_REG("$20");
    void *node;
    void *source;
    register u8 *origin;
    Scratch scratch;
    u8 *global_page;
    s32 state_id;
    register s32 source_z ASM_REG("$3");
    register s32 adjusted_z ASM_REG("$2");
    register s32 i ASM_REG("$6");
    register u8 *scan ASM_REG("$5");

    ASM_KEEP_NV(state);
    ASM_KEEP_NV(motion);
    state->timer++;
    state_id = state->state;
    owner = state->owner;

    part = arg2;
    switch (state_id) {
    case 0:

        origin = D_80082E80_early;
        ASM_SCHED_BARRIER();

        {
            register u32 work_v0 ASM_REG("$2") =
                (u32)PTR_AT((u8 *)owner - 0x20, 0xC);
            register s32 start_x ASM_REG("$4") = U8_AT(work_v0, 0x24);
            register s32 start_y ASM_REG("$5") = U8_AT(work_v0, 0x25);
            register u32 origin_x ASM_REG("$6");
            register u32 base_x ASM_REG("$7");
            u32 chain_x;
            u32 chain_y;

            base_x = (u32)D_8006CCD8_early;
            work_v0 = (u32)D_800814A8_early[0];
            chain_y = U16_AT(work_v0, 0x2A);
            origin_x = origin[0x24];
            chain_y = (chain_y >> 8) & 0xE;
            chain_x = chain_y + base_x;
            work_v0 = (u32)D_8006CCE8_early;
            chain_y += work_v0;
            chain_x = U16_AT(chain_x, 0);
            chain_y = U16_AT(chain_y, 0);

            U16_AT(owner, 0x2A) = func_800A0818(
                start_x, start_y, origin_x + chain_x, origin[0x25] + chain_y, &result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;
        ASM_CLOBBER("$19");

    case 1:
        meta = (u8 *)owner - 0x20;
        ASM_KEEP(meta);
        node = PTR_AT(meta, 0xC);
        if (func_8003DE58(PTR_AT(node, 8), node, probe, 0) == 0) {
            if (!(U16_AT(PTR_AT(meta, 0xC), 0x14) & 0x8000)) {
                goto done;
            }
        }

        source = PTR_AT(meta, 8);
        U16_AT(motion, 2) = U16_AT(source, 2);
        U16_AT(motion, 6) = U16_AT(source, 6);
        source_z = U16_AT(source, 0xA);
        ASM_KEEP(source_z);
        U16_AT(motion, 0xA) = source_z;
        if (!(U16_AT(PTR_AT(meta, 0xC), 0x14) & 0x8000)) {
            U16_AT(motion, 2) += probe[0];
            U16_AT(motion, 6) += probe[1];
            ASM_MEM_BARRIER();
            adjusted_z = U16_AT(motion, 0xA);
            source_z = U16_AT(probe, 4);
            adjusted_z += source_z;
            ASM_TAILSLOT_PIN(adjusted_z);
            func_80024888();
        }

        ASM_KEEP(source_z);
        adjusted_z = source_z - 0x40;
        ASM_KEEP(adjusted_z);
        U16_AT(motion, 0xA) = adjusted_z;
        if (!(U16_AT(state->image, 0) & 0x80)) {
            goto done;
        }

        /* This expression is intentionally kept in its retail form. */
        if ((U16_AT(meta, 0x1E) | 0x2000) != 0) {
            register u8 *position_base ASM_REG("$4") = D_80082E80;
            register void *direction_node ASM_REG("$5") = D_800814A8[0];
            register u32 direction_x ASM_REG("$2");
            register u32 direction_y ASM_REG("$2");

            direction_x = U16_AT(direction_node, 0x2A);
            state->x = position_base[0x24] +
                ((s16 *)((u8 *)D_8006CCD8 +
                ((direction_x >> 8) & 0xE)))[0];
            direction_y = U16_AT(direction_node, 0x2A);
            state->y = position_base[0x25] +
                ((s16 *)((u8 *)D_8006CCE8 +
                ((direction_y >> 8) & 0xE)))[0];
            func_80024980();
        }

        {
        s16 *work = scratch.work;

        ASM_SCHED_BARRIER();
        state->x = D_80082E80[0x24] + D_8006CCD8[state->direction];
        state->y = D_80082E80[0x25] + D_8006CCE8[state->direction];
        ASM_SCHED_BARRIER();
        {
            register void *height_node ASM_REG("$3");
            register s32 work_coord ASM_REG("$2");

            work_coord = state->x;
            global_page = (u8 *)0x80080000;
            S16_AT(work, 2) = work_coord * 64 + 0x20;
            work_coord = state->y;
            height_node = PTR_AT(global_page, 0x14A8);
            S16_AT(work, 6) = work_coord * 64 + 0x20;
            S16_AT(work, 0xA) = ((s16 *)height_node)[0x44] - 0x20;
        }
        S16_AT(work, 0xA) = func_800BCAD0(work);
        state->z = S16_AT(work, 0xA);
        func_8009A350(state->x - 1, state->y, 0, &map_flags);
        if (map_flags & 0x3300) {
            register s32 tail_value ASM_REG("$2");

            tail_value =
                ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
            S32_AT((u8 *)work, 8) = tail_value;
            tail_value = 6;
            ASM_TAILSLOT_PIN(tail_value);
            func_80024AE4();
        }
        {
            register s32 work_z ASM_REG("$6") = S16_AT(work, 0xA);
            register s32 in_range ASM_REG("$2");

            in_range = work_z < 0x201;
            ASM_KEEP(in_range);
            if (!in_range) {
                register s32 tail_value ASM_REG("$2");

                tail_value =
                    ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                S32_AT((u8 *)work, 8) = tail_value;
                tail_value = 6;
                ASM_TAILSLOT_PIN(tail_value);
                func_80024AE4();
            }
        }
        if ((func_800A45D8(U16_AT(work, 2), U16_AT(work, 6)) << 16) != 0) {
            register s32 tail_value ASM_REG("$2");

            tail_value =
                ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
            S32_AT((u8 *)work, 8) = tail_value;
            tail_value = 6;
            ASM_TAILSLOT_PIN(tail_value);
            func_80024AE4();
        }
        if ((func_800A5690() << 16) == 0) {
            register s32 tail_value ASM_REG("$2");

            tail_value =
                ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
            S32_AT((u8 *)work, 8) = tail_value;
            tail_value = 6;
            ASM_TAILSLOT_PIN(tail_value);
            func_80024AE4();
        }
        if ((U16_AT(meta, 0x1E) | 0x2000) != 0) {
            state->status = 1;
        } else {
            state->status = 2;
        }
        state->state++;
        ASM_SCHED_BARRIER();

        {
            register s32 delta_x ASM_REG("$4");
            register s32 zbase ASM_REG("$3");
            s32 delta_y;
            s32 delta_z;

            i = 1;
            scan = (u8 *)&scratch + 2;
            ASM_KEEP(i);
            ASM_KEEP(scan);
            delta_x = S16_AT(work, 2) - S16_AT(motion, 2);
            if (delta_x < 0) {
                delta_x = -delta_x;
            }
            probe[0] = delta_x;
            delta_y = S16_AT(work, 6) - S16_AT(motion, 6);
            if (delta_y < 0) {
                delta_y = -delta_y;
            }
            probe[1] = delta_y;
            zbase = S16_AT(motion, 0xA) + 160;
            delta_z = S16_AT(work, 0xA) - zbase;
            if (delta_z < 0) {
                delta_z = -delta_z;
            }
            probe[2] = delta_z;
            state->duration = delta_x;
        }
        do {
            register s32 scan_value ASM_REG("$3");

            scan_value = S16_AT(scan, 24);
            if (state->duration < scan_value) {
                state->duration = U16_AT(scan, 24);
            }
            i++;
            scan += 2;
        } while (i < 3);
        state->duration =
            (state->duration >> 4) + (state->duration >> 5);
        if (state->duration == 0) {
            state->duration = 1;
        }
        S32_AT(motion, 0xC) =
            (S32_AT(work, 0) - S32_AT(motion, 0)) / state->duration;
        {
            register s32 ybase ASM_REG("$4");
            register s32 yvalue ASM_REG("$2");
            register s32 yduration ASM_REG("$3");

            ybase = S32_AT(motion, 4);
            yvalue = S32_AT(work, 4) - ybase;
            yduration = state->duration;
            yvalue /= yduration;
            ASM_KEEP(yvalue);
            S32_AT(motion, 0x10) = yvalue;
        }
        {
            register s32 zbase ASM_REG("$3");
            register s32 zoff ASM_REG("$2");

            zoff = 0x00A00000;
            zbase = S32_AT(motion, 8) + zoff;
            S32_AT(motion, 0x14) =
                (S32_AT(work, 8) - zbase) / state->duration;
        }
        func_800240CC(state, motion, state->duration);
        func_800240CC(state, motion, state->duration);
        func_800240CC(state, motion, state->duration);
        state->timer = 0;
        func_80024DE0();
        }

    case 2:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        S32_AT(motion, 8) += S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            goto done;
        }
        func_8002441C(state, motion);
        func_800A56E0(0x300);
        func_80024D54();

    case 3:
        if (state->timer < 0x10) {
            goto done;
        }
        func_800245CC(state, motion);
        func_80024D54();

    case 4:
        if (state->timer < 0x11) {
            goto done;
        }
        if (state->status != 0) {
            void *effect = func_800D24A8(state->status, state->x, state->y,
                                         state->z);
            register s32 next ASM_REG("$4");
            register s32 value ASM_REG("$2");
            s32 id;
            s32 color;

            func_80042640(effect, 52);
            color = func_800A6D30();
            id = U8_AT(state, 9);
            next = id >> 1;
            next += id << 1;
            next += color & 3;
            next += 16;
            value = next;
            ASM_KEEP(next);
            if (next >= 256) {
                value = 255;
            }
            U8_AT(effect, 0x28) = value;
            U8_AT(effect, 0x29) = value;
        }
        state->timer = 0;
        state->state++;
        func_80024DE0();

    case 5:
        if (state->field_14 != 0) {
            goto done;
        }
        D_8008346C = 0;
        U16_AT(state, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80024DE0();

    case 6:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

done:
    state->field_14 = 0;
}

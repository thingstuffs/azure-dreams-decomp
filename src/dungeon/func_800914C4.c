#include "common.h"

extern u16 D_80013714[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s16 D_80083464;
extern u8 D_80096384[];
extern u8 D_800DD274[];

extern s32 func_8003DB94();
extern void func_80094ED4();
extern void func_80096DE4();
extern void func_80096E08();
extern void func_80096F28();
extern void func_80096F84();
extern void func_8009701C();
extern void func_80099F04();
extern void func_80099F70();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009ABA0();
extern void func_8009F644();
extern s32 func_800A5C70();
extern void func_800A67F4(void);

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define P32(p, o) (*(void **)((u8 *)(p) + (o)))

void func_80096C24(void *obj, s32 arg1, void *actor, void *map)
{
    register u8 *globals;
    register s16 kind;
    register s32 result ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u16 *state;
    register u16 *state2;
    register u8 *state_base;
    register u8 *handler;
    register s32 n;
    void *tail_obj;
    static void *const keepalive[] = {
        &&after_positive_9701C,
        &&after_nonpositive_9701C,
    };

    globals = D_80083160;
    func_800A67F4();
    result = func_8009ABA0(S16(map, 0x2A), arg1, actor, S16(map, 0x88), 0x20);
    kind = (s16)result;
    if (kind > 0) {

    U8(obj, 0x9B) = 0;
    func_8009A3D0(U8(actor, 0x24), U8(actor, 0x25), 0x300);
    {
        register u8 *adjust_base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
        s32 index;

        adjust_base = D_8006CCD8;
        index = (U16(map, 0x2A) >> 8) & 0xE;
        U8(actor, 0x24) = U8(actor, 0x24) + adjust_base[index];
        U8(actor, 0x25) = U8(actor, 0x25) + D_8006CCE8[index];
    }
    func_8009A21C(U8(actor, 0x24), U8(actor, 0x25), 0x300);

    state_base = (u8 *)&D_80083460;
    state = (u16 *)state_base;
    state[1] |= 8;
    S32(obj, 0x8C) = 0;

    if (kind != 4) {
        if (D_80013714[0] & 2) {
            void *entry;
            register void *call_actor ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

            state[1] |= 0x80;
            handler = D_800DD274;
            if (P32(actor, 0x2C) != handler) {
                P32(actor, 0x2C) = handler;
                call_actor = actor;
                n = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
                entry = handler + (n & 0x1C);
                ASM_TAILSLOT_PIN(entry);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                return func_80096DE4(call_actor);
            }
        } else if ((S32(globals, 8) & 0x20) && func_800A5C70()) {
            register u8 *second_handler;

            state[1] |= 0x80;
            second_handler = D_800DD274;
            P32(actor, 0x2C) = second_handler;
            n = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
            func_8003DB94(actor, *(void **)(second_handler + (n & 0x1C)), 0);
            {
                u32 page;

                page = 0x80080000;
                ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
            }
            return func_80096E08();
        } else {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            do {
                result = 5;
            } while (0);
            U8(obj, 0x9B) = 10;
        }
    }

    {
        s16 kind;
        register u8 *late_handler ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

        state2 = (u16 *)&D_80083460;
        kind = (s16)result;
        if ((state2[1] & 0x80) || kind == 1) {
        func_80099F70(S32(map, 0x5C));
        func_80099F04(S32(map, 0x5C));
        if (!(state2[1] & 0x80)) {
            late_handler = D_800DD274;
            P32(actor, 0x2C) = late_handler;
            n = (D_80083228 + S16(map, 0x2A) + 0x100) >> 7;
            func_8003DB94(actor, *(void **)(late_handler + (n & 0x1C)), 0);
        }
        U8(obj, 0x9A) = 0x35;
        state2[2] = 8;
            return func_80096F84();
    }

    U16(obj, 0x98) |= 0xC;
    late_handler = D_800DD274 + 0x20;
    P32(actor, 0x2C) = late_handler;
    n = (D_80083228 + S16(map, 0x2A) + 0x100) >> 7;
    func_8003DB94(actor, *(void **)(late_handler + (n & 0x1C)), 0);
    if (kind < 4) {
        U16(obj, 0xA2) |= 1;
        return func_80096F28();
    }
    if (kind == 2 || kind == 4) {
        U8(obj, 0x9B) = 8;
    }
    func_80094ED4(obj, arg1, actor, map);
    {
        register void *call_map ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

        call_map = map;
        D_80083464 = 8;
        U8(obj, 0x9A) = 0x36;
        U16(obj, 0x96) = 2;
        S32(call_map, 0x1C) |= 0x40000000;
        func_8009F644(call_map, 8, 0, 0);
    }
        return func_8009701C();
after_positive_9701C:
        func_8009F644(map, 8, 0, 0);
        tail_obj = obj;
        goto after_nonpositive_9701C;
    }

    } else {
    u8 *nonpositive_handler;
    s32 map_flags;

    nonpositive_handler = D_800DD274;
    P32(actor, 0x2C) = nonpositive_handler;
    n = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
    func_8003DB94(actor, *(void **)(nonpositive_handler + (n & 0x1C)), 0);
    S32(obj, 0x8C) = (s32)D_80096384;
    return func_8009701C();
after_nonpositive_9701C:
    func_80094ED4(tail_obj, arg1, actor, map);
    map_flags = S32(map, 0x1C);
    {
        register s32 map_flag_mask ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        map_flag_mask = 0x40000000;
        map_flags |= map_flag_mask;
    }
    state_base = (u8 *)&D_80083460;
    {
        register u8 *final_state_base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        final_state_base = state_base;
        S32(map, 0x1C) = map_flags;
        ((u16 *)final_state_base)[1] |= 0x812;
    }
    }
}

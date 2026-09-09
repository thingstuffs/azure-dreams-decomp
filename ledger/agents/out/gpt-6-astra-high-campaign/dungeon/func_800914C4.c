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

/* Moves the actor and updates its animation, movement state, and map flags. */
void func_80096C24(void *obj, s32 move_mode, void *actor, void *map)
{
    register u8 *globals;
    register s16 move_kind;
    register s32 move_result;
    register u16 *move_state;
    register u16 *updated_state;
    register u8 *state_base;
    register u8 *anim_table;
    register s32 facing_offset;
    void *tail_obj;

    ASM_USE_NV(obj);
    globals = D_80083160;
    func_800A67F4();
    move_result = func_8009ABA0(S16(map, 0x2A), move_mode, actor, S16(map, 0x88), 0x20);
    move_kind = (s16)move_result;
    if (move_kind > 0) {
        U8(obj, 0x9B) = 0;
        func_8009A3D0(U8(actor, 0x24), U8(actor, 0x25), 0x300);
        {
            register u8 *x_offsets ASM_REG("$3");
            s32 step_index;

            x_offsets = D_8006CCD8;
            step_index = (U16(map, 0x2A) >> 8) & 0xE;
            U8(actor, 0x24) = U8(actor, 0x24) + x_offsets[step_index];
            U8(actor, 0x25) = U8(actor, 0x25) + D_8006CCE8[step_index];
        }
        func_8009A21C(U8(actor, 0x24), U8(actor, 0x25), 0x300);

        state_base = (u8 *)&D_80083460;
        move_state = (u16 *)state_base;
        move_state[1] |= 8;
        S32(obj, 0x8C) = 0;

        if (move_kind != 4) {
            if (D_80013714[0] & 2) {
                void *anim_entry;

                move_state[1] |= 0x80;
                anim_table = D_800DD274;
                if (P32(actor, 0x2C) != anim_table) {
                    P32(actor, 0x2C) = anim_table;
                    facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
                    anim_entry = anim_table + (facing_offset & 0x1C);
                    func_8003DB94(actor, *(void **)anim_entry, 0);
                }
            } else if ((S32(globals, 8) & 0x20) && func_800A5C70()) {
                register u8 *alternate_anim;

                move_state[1] |= 0x80;
                alternate_anim = D_800DD274;
                P32(actor, 0x2C) = alternate_anim;
                facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
                func_8003DB94(actor, *(void **)(alternate_anim + (facing_offset & 0x1C)), 0);
            } else {
                move_result = 5;
                U8(obj, 0x9B) = 10;
            }
        }

        {
            s16 move_kind;
            register u8 *next_anim ASM_REG("$5");

            updated_state = (u16 *)&D_80083460;
            move_kind = (s16)move_result;
            if ((updated_state[1] & 0x80) || move_kind == 1) {
                func_80099F70(S32(map, 0x5C));
                func_80099F04(S32(map, 0x5C));
                if (!(updated_state[1] & 0x80)) {
                    next_anim = D_800DD274;
                    P32(actor, 0x2C) = next_anim;
                    facing_offset = (D_80083228 + S16(map, 0x2A) + 0x100) >> 7;
                    func_8003DB94(actor, *(void **)(next_anim + (facing_offset & 0x1C)), 0);
                }
                U8(obj, 0x9A) = 0x35;
                updated_state[2] = 8;
                goto update_map;
            }

            U16(obj, 0x98) |= 0xC;
            next_anim = D_800DD274 + 0x20;
            P32(actor, 0x2C) = next_anim;
            facing_offset = (D_80083228 + S16(map, 0x2A) + 0x100) >> 7;
            func_8003DB94(actor, *(void **)(next_anim + (facing_offset & 0x1C)), 0);
            if (move_kind < 4) {
                U16(obj, 0xA2) |= 1;
            } else if (move_kind == 2 || move_kind == 4) {
                U8(obj, 0x9B) = 8;
            }
            func_80094ED4(obj, move_mode, actor, map);
            {
                D_80083464 = 8;
                U8(obj, 0x9A) = 0x36;
                U16(obj, 0x96) = 2;
                S32(map, 0x1C) |= 0x40000000;
                func_8009F644(map, 8, 0, 0);
            }
            return;
update_map:
            func_8009F644(map, 8, 0, 0);
            tail_obj = obj;
            goto finish_move;
        }
    } else {
        u8 *idle_anim;
        s32 map_flags;

        idle_anim = D_800DD274;
        P32(actor, 0x2C) = idle_anim;
        facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
        func_8003DB94(actor, *(void **)(idle_anim + (facing_offset & 0x1C)), 0);
        S32(obj, 0x8C) = (s32)D_80096384;
        return;
finish_move:
        func_80094ED4(tail_obj, move_mode, actor, map);
        map_flags = S32(map, 0x1C);
        {
            register s32 map_flag_mask ASM_REG("$3");

            map_flag_mask = 0x40000000;
            map_flags |= map_flag_mask;
        }
        state_base = (u8 *)&D_80083460;
        {
            register u8 *final_state_base ASM_REG("$3");

            final_state_base = state_base;
            S32(map, 0x1C) = map_flags;
            ((u16 *)final_state_base)[1] |= 0x812;
        }
    }
}

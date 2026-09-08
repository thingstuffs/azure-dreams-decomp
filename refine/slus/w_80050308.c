#include "common.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0x10). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * that touch other fields of the same global. */
typedef struct {
    u8 pad00[0x8];
    s32 unk08;
    u8 pad0C[0x4];
    s32 unk10;
} S_80050308_D80083160;

extern S_80050308_D80083160 D_80083160;

/* Object struct for this function's argument. The object is embedded 0x20
 * bytes into a larger allocation (base = (char*)obj - 0x20, passed to the
 * sibling init/reset routines func_80050DA8/func_80050EA8), and has a
 * "next state" callback pointer at offset -0x10. */
typedef struct S_80050308 {
    u8 pad00[0x4];
    s32 unk04;        /* saved previous state-fn value */
    u8 pad08[0x4];
    s32 unk0C;         /* counter */
    s32 unk10;         /* mode value (2 or 3) */
    s32 unk14;
    s32 unk18;
    s32 unk1C;         /* wrapped index */
    s32 unk20;         /* result of func_800502E0 */
    u8 pad24[0x4];
    void *unk28;       /* arg passed to func_800502E0 */
    u8 pad2C[0x68 - 0x2C];
    s32 unk68;         /* arg0 for func_800500B4 */
} S_80050308;

typedef void (*StateFn_80050308)(void *);

extern s16 func_80053DA8(s32 a0);
extern void func_80050DA8(void *a0);
extern void func_80050EA8(void *a0);
extern s32 func_800502E0(void *a0);
extern s32 func_8004FF20(void *a0);
extern void func_8004FFA8(void *a0);
extern s32 func_80049DE8(s32 a0, s32 a1, s32 a2);
extern void func_800500B4(s32 a0, void *a1);

/* Handles object state changes and directional index updates from global input flags. */
void func_80050308(void *object)
{
    S_80050308 *obj = (S_80050308 *)object;
    S_80050308_D80083160 *input_state = &D_80083160;
    s32 action_flags;
    s32 direction;

    if (input_state->unk08 != 0) {
        action_flags = input_state->unk10;
        if (action_flags & 0x20) {
            func_80053DA8(0x515);
            func_80050DA8((char *)obj - 0x20);
        } else if (action_flags & 0x40) {
            func_80053DA8(0x514);
            obj->unk20 = func_800502E0(obj->unk28);
            if (func_8004FF20(obj) == 0) {
                s32 prev_state = *(s32 *)((char *)obj - 0x10);

                *(StateFn_80050308 *)((char *)obj - 0x10) = func_8004FFA8;
                obj->unk04 = prev_state;
            } else {
                func_80050EA8((char *)obj - 0x20);
            }
        } else if (input_state->unk08 & 0x5000) {
            direction = 0;
            if (action_flags & 0x4000) {
                direction = 1;
                goto set_mode3;
            }
            if (action_flags & 0x1000) {
                direction = -1;
                goto set_mode3;
            }
            goto check_counter;

        set_mode3:
            obj->unk0C = 0;
            obj->unk10 = 3;
            goto apply_direction;

        check_counter:
            if (obj->unk0C >= 3) {
                s32 repeat_flags;

                obj->unk0C = obj->unk0C - 1;
                repeat_flags = input_state->unk08;
                if (repeat_flags & 0x4000) {
                    direction = 1;
                } else if (repeat_flags & 0x1000) {
                    direction = -1;
                } else {
                    goto apply_direction;
                }
                obj->unk10 = 2;
            } else {
                obj->unk0C = obj->unk0C + 1;
            }

        apply_direction:
            if (direction != 0) {
                func_80053DA8(0x502);
                obj->unk18 = obj->unk1C;
                obj->unk14 = 0;
                obj->unk1C = func_80049DE8(obj->unk1C, direction, 6);
            }
        }
    }
    func_800500B4(obj->unk68, obj);
}

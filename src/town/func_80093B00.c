#include "common.h"


extern s32 func_80033B2C();
extern void func_8008B158();
extern s32 func_8008C180();
extern void func_80093D48();
extern void func_80093E58();
extern void func_80093F48();
extern void func_80093FC8();
extern void func_80094088();
extern void func_800942B0();
extern void func_80094378();
extern void func_800943B8();
extern void func_800944BC();
extern void func_8009451C();
extern void func_80094944();
extern void func_80094C1C();
extern void func_80094C74();
extern void func_80094DA8();
extern void func_8009503C();
extern void func_800951B4();
extern s32 func_8009567C();
extern s32 func_80095840();
extern s16 func_80095978();
extern void func_80095A94();
extern void func_80095C80();
extern void func_80098868();
extern s32 func_800C1D44();

extern u8 D_80083160[];
extern s32 D_800CFCB4[];
extern u8 D_800CFCEF[];
extern u8 D_800FE488[];


typedef struct S_80091260_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80091260_0;   /* arg1 in func_80091260 */

typedef struct S_80091260_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091260_1;   /* state in func_80091260 */

typedef struct S_80091260_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    u8 pad_30[0xE];
    union { u16 u; s16 s; } unk_3E;   /* accessed as both */
} S_80091260_2;   /* arg0 in func_80091260 */

/* Dispatch actor actions from input flags and position checks. */
void func_80091260(S_80091260_2 *actor, S_80091260_0 *position, s32 context) {
    u8 *input_state = D_80083160;
    s32 input_flags;
    s32 action_result;
    s32 tile_id;
    s16 height;
    s16 remaining_count;
    s32 *action_data;

    func_80095C80(position);
    func_800951B4(position);

    height = func_80095978(position, D_800FE488);
    if ((height - position->unk_08.at02.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(position, height, D_800FE488);
    }

    input_flags = ((S_80091260_1 *)input_state)->unk_10;
    if (input_flags & 0x10) {
        func_800942B0(actor, position, context);
        return;
    }

    if (input_flags & 0x40) {
        action_result = func_80095840(actor, D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(actor, position, context);
                return;
            } else {
                func_800944BC(actor, position, context);
                return;
            }
        } else if (func_80033B2C(0xA4) != 0) {
            func_80094088(actor, position, context);
            return;
        }
        return;
    }

    action_data = D_800CFCB4;
    action_result = func_8009567C(action_data);
    if (action_result != 0) {
        if (action_result == -1) {
            func_80094C1C(actor);
            func_80098868(actor, position, context);
            actor->unk_2C = 0;
            func_8008B158(action_data[4]);
            return;
        } else {
            func_800943B8(actor, position, context);
            return;
        }
        return;
    }

    input_flags = ((S_80091260_1 *)input_state)->unk_08;
    if (input_flags & 0x20) {
        if (actor->unk_16 == 1) {
            tile_id = func_8008C180(position->unk_02, position->unk_06);
            if (func_800C1D44((u16)tile_id) != 0 && position->unk_08.at00.v > 0) {
                func_80093FC8(actor, position, context);
                return;
            } else {
                func_80093E58(actor, position, context);
                return;
            }
        } else {
            func_80093F48(actor, position, context);
            func_80094C1C(actor);
            func_8009503C(position);
            return;
        }
        return;
    }

    if (input_flags & 0xF000) {
        remaining_count = actor->unk_3E.u - 1;
        actor->unk_3E.s = remaining_count;
        func_80094944(remaining_count, 12);
        func_80094C1C(actor);
        func_80094C74(position);
        func_80094DA8(position);
        return;
    } else {
        func_80093D48(actor, position, context);
    }
}

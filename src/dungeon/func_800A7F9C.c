#include "common.h"

typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
    u8 pad26[0x40];
    u8 unk66;
} DungeonState;

extern s32 func_800990FC(void);
extern s32 func_80042900(DungeonState *entry, s32 effect_id);
extern s32 func_80099194(u8 *src, u8 *dst);
extern s32 func_80099734(void *record, u8 *out);
extern void func_80099290(s8 *byte_ptr);
extern void func_800A56E0(s32 query_value);
extern void func_800A5720(s8 *text);

extern u8 D_80089084[];
extern u8 D_800E0CAE[];
extern u8 D_800E0CDC[];
extern u8 D_800E0CF3[];
extern u8 D_800E0D1B[];
extern u8 D_800E0D36[];

/* Displays the mode-specific message and updates the state meter within its limit. */
s32 func_800AD6FC(DungeonState *state, s32 mode, u8 *item, s32 text_arg) {
    s32 message;
    s32 meter;
    s32 base_message;
    s32 old_meter;

    base_message = func_800990FC();
    message = base_message;
    if ((func_80042900(state, 0x19) << 16) != 0) {
        func_80099290(func_80099194(D_80089084,
                                    func_80099734(state,
                                                  func_80099194(D_800E0CAE, base_message))));
        func_800A5720(base_message);
        return 0;
    }

    if ((mode == 3) && (item != 0)) {
        if ((item[1] == 2) && (item[0] == 1)) {
            mode = 2;
        } else if ((item[1] == 0xC) && (item[0] == 6)) {
            mode = 2;
        }
    }

    meter = state->unk24;
    old_meter = meter;
    switch (mode) {
    case 0:
        message = func_80099194(D_80089084,
                                func_80099734(state,
                                              func_80099194(D_800E0CDC, message)));
        break;
    case 1:
        do {
            message = func_80099194(D_800E0CF3, func_80099734(state, message));
        } while (0);
        meter += 0x300;
        break;
    case 2:
        message = func_80099194(D_800E0D1B, func_80099734(state, message));
        if ((item != 0) && (item[1] == 0xC) && (item[0] == 6)) {
            meter += 0xA00;
        } else {
            meter += 0x3200;
        }
        break;
    case 3:
        message = func_80099194(D_800E0D36, func_80099734(state, message));
        meter += 0x6400;
        break;
    }

    if (item != 0) {
        func_80099290(message);
        func_800A5720(base_message);
    } else if (mode == 0) {
        func_80099290(message);
        func_800A5720(base_message);
    }
    if (old_meter != meter) {
        func_800A56E0(0x51E);
    }
    if (meter > 0x10000) {
        meter = 0xFFFF;
    }
    state->unk24 = (u16)meter;
    if (((u8 *)state)[0x25] != 0) {
        state->unk1C &= ~8;
    }
    if (state->unk66 < ((u8 *)state)[0x25]) {
        ((u8 *)state)[0x25] = state->unk66;
        ((u8 *)state)[0x24] = 0xFF;
    }
    return mode;
}

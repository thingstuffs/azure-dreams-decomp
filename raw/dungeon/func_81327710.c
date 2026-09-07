#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80047784();
extern s32 func_800A9A0C();
extern s32 func_800BBA40();
extern s32 func_8016A928();
extern s32 func_8016BF74();
extern void func_8016F128() __attribute__((noreturn));

extern s16 D_80083228[];
extern s32 D_80083460[];
extern u8 D_800DF45C[];
extern u8 D_8016EEBC[];
extern u8 D_8017467C[];
extern u8 D_80174694[];
extern u8 D_801746FC[];
extern u8 *D_80174CCC[];
extern s16 D_80174CD0[];

s32 func_8016EF10(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 *actor = arg0;
    u8 *entity = arg2;
    u8 *stream;
    u16 command;
    s32 command_wide;
    u8 limit;
    s16 counter;
    s32 kind;
    s32 index;

    if (FIELD(entity, u16, 0x14) & 0x40) {
        return 0;
    }

    stream = D_80174CCC[0];
    command = stream[1];
    command_wide = command;
    if (command_wide == 0) {
        FIELD(actor, u8, 0xB2) = 0;
        func_800A9A0C(actor);
        return 0;
    }

    limit = stream[0];
    counter = D_80174CD0[0] + 1;
    D_80174CD0[0] = counter;
    if (limit < counter) {
        D_80174CCC[0] = stream + 2;
        D_80174CD0[0] = 0;
    }

    FIELD(actor, s16, 0x2A) = (command & 7) << 9;
    FIELD(actor, u16, 0x46) |= 0x8000;
    kind = command_wide & 0xF8;

    switch (kind) {
    default:
        func_800A9A0C(actor);
        return 0;

    case 8: {
        register s32 result ASM_REG("$2");

        func_8016BF74(actor, arg1, entity, actor);
        result = 0;
        ASM_TAILSLOT_PIN(result);
        func_8016F128();
        return 0;
    }

    case 0x10:
        if (FIELD(entity, u8 *, 0x2C) != D_8017467C) {
            FIELD(entity, u8 *, 0x2C) = D_8017467C;
            index = ((D_80083228[0] + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(entity, D_8017467C[index], 0);
        }
        break;

    case 0xF8:
        if (FIELD(entity, u8 *, 0x2C) != D_801746FC) {
            FIELD(entity, u8 *, 0x2C) = D_801746FC;
            index = ((D_80083228[0] + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(entity, D_801746FC[index], 0);
        }
        break;

    case 0xF0:
        if (FIELD(actor, u8, 0x9B) == 0) {
            FIELD(actor, s16, 0x2A) = func_8016A928(arg1) << 9;
            if (FIELD(entity, u8 *, 0x2C) != D_80174694) {
                FIELD(entity, u8 *, 0x2C) = D_80174694;
                index = ((D_80083228[0] + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
                func_80047784(entity, D_80174694[index], 0);
            }
            if (func_800BBA40(FIELD(entity, u8, 0x24),
                              FIELD(entity, u8, 0x25),
                              FIELD(actor, s16, 0x88),
                              D_800DF45C, 0x2800, 0x208020,
                              D_8016EEBC) == 0) {
                return 0;
            }
            FIELD(actor, s16, 0x96) = 0;
            FIELD(actor, u8, 0x9B)++;
            {
                u8 *global_base = (u8 *)D_80083460;
                FIELD(global_base, u16, 0xA) += 2;
            }
        }
        break;

    }

    func_800A9A0C(actor);
    return 0;
}

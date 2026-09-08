#include "common.h"

typedef struct S_8016EF10_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016EF10_0;   /* entity in func_8016EF10 */

typedef struct S_8016EF10_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x40];
    s16 unk_88;
    u8 pad_8A[0xC];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x16];
    u8 unk_B2;
} S_8016EF10_1;   /* actor in func_8016EF10 */

typedef struct S_8016EF10_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016EF10_2;   /* global_base in func_8016EF10 */



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

    if (((S_8016EF10_0 *)entity)->unk_14 & 0x40) {
        return 0;
    }

    stream = D_80174CCC[0];
    command = stream[1];
    command_wide = command;
    if (command_wide == 0) {
        ((S_8016EF10_1 *)actor)->unk_B2 = 0;
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

    ((S_8016EF10_1 *)actor)->unk_2A = (command & 7) << 9;
    ((S_8016EF10_1 *)actor)->unk_46 |= 0x8000;
    kind = command_wide & 0xF8;

    switch (kind) {
    default:
        func_800A9A0C(actor);
        return 0;

    case 8: {
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        func_8016BF74(actor, arg1, entity, actor);
        result = 0;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8016F128();
        return 0;
    }

    case 0x10:
        if (((S_8016EF10_0 *)entity)->unk_2C != D_8017467C) {
            ((S_8016EF10_0 *)entity)->unk_2C = D_8017467C;
            index = ((D_80083228[0] + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
            func_80047784(entity, D_8017467C[index], 0);
        }
        break;

    case 0xF8:
        if (((S_8016EF10_0 *)entity)->unk_2C != D_801746FC) {
            ((S_8016EF10_0 *)entity)->unk_2C = D_801746FC;
            index = ((D_80083228[0] + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
            func_80047784(entity, D_801746FC[index], 0);
        }
        break;

    case 0xF0:
        if (((S_8016EF10_1 *)actor)->unk_9B == 0) {
            ((S_8016EF10_1 *)actor)->unk_2A = func_8016A928(arg1) << 9;
            if (((S_8016EF10_0 *)entity)->unk_2C != D_80174694) {
                ((S_8016EF10_0 *)entity)->unk_2C = D_80174694;
                index = ((D_80083228[0] + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
                func_80047784(entity, D_80174694[index], 0);
            }
            if (func_800BBA40(((S_8016EF10_0 *)entity)->unk_24,
                              ((S_8016EF10_0 *)entity)->unk_25,
                              ((S_8016EF10_1 *)actor)->unk_88,
                              D_800DF45C, 0x2800, 0x208020,
                              D_8016EEBC) == 0) {
                return 0;
            }
            ((S_8016EF10_1 *)actor)->unk_96 = 0;
            ((S_8016EF10_1 *)actor)->unk_9B++;
            {
                u8 *global_base = (u8 *)D_80083460;
                ((S_8016EF10_2 *)global_base)->unk_0A += 2;
            }
        }
        break;

    }

    func_800A9A0C(actor);
    return 0;
}

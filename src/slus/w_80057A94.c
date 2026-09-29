#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x4C];
    u8 f4C;
    u8 f4D;
    u8 f4E;
} S_80057A94;

typedef struct {
    u8 pad00[1];
    u8 x1;
    u8 pad2[4];
    u8 x6;
    u8 x7;
    u8 pad8[8];
    u16 h10;
    u16 h12;
} S_80057A94_cell;

typedef struct {
    s32 type;
    s32 f4;
    s16 x;
    s16 y;
    s32 fc;
    s32 f10;
    s32 f14;
} S_80057A94_msg;

extern s32 func_80057A50(void *arg0, s32 arg1);
extern s32 func_8005DA68(void);
extern void func_8005D88C(s32 arg0);
extern s32 func_8005DA88(void *arg0);

extern u8 D_8007382B[0x10];

/* Apply a command value to a cell field or dispatch a control message. */
void func_80057A94(S_80057A94 *command) {
    S_80057A94_cell *cell;
    S_80057A94_msg message;
    u32 operation;

    cell = (S_80057A94_cell *)func_80057A50(command, command->f4D & 0xF);
    operation = command->f4C;
    switch (operation) {
    case 1:
        cell->x1 = command->f4E;
        break;
    case 2:
        cell->x6 = command->f4E;
        break;
    case 3:
        cell->x7 = command->f4E;
        break;
    case 4:
        cell->h10 = (cell->h10 & 0xFF) | ((0x7F - command->f4E) << 8);
        break;
    case 5:
        cell->h10 = (cell->h10 & 0xFF) | ((0x7F - command->f4E) << 8) | 0x8000;
        break;
    case 6:
        cell->h10 = (cell->h10 & 0xFF0F) | ((command->f4E << 1) & 0xF0);
        break;
    case 7:
        cell->h10 = (cell->h10 & 0xFFF0) | (command->f4E >> 3);
        break;
    case 8:
        cell->h12 = (cell->h12 & 0x603F) | ((0x7F - command->f4E) << 6);
        break;
    case 9:
        cell->h12 = (cell->h12 & 0x603F) | ((0x7F - command->f4E) << 6) | 0x8000;
        break;
    case 10:
        cell->h12 = (cell->h12 & 0xFFC0) | ((0x7F - command->f4E) >> 3);
        break;
    case 11:
        cell->h12 = ((cell->h12 & 0xFFC0) | ((0x7F - command->f4E) >> 3)) | 0x20;
        break;
    case 12:
        if (command->f4E < 0x41) {
            cell->h12 |= 0x4000;
        } else {
            cell->h12 &= 0xBFFF;
        }
        break;
    case 15:
        if (func_8005DA68() == 1) {
            func_8005D88C(0);
        }
        if (command->f4E != 0) {
            message.type = 1;
            message.f4 = command->f4E;
            D_8007382B[0] = command->f4E;
            func_8005DA88(&message);
            func_8005D88C(1);
        }
        break;
    case 16:
        message.type = 6;
        message.x = command->f4E << 8;
        message.y = command->f4E << 8;
        func_8005DA88(&message);
        func_8005D88C(1);
        break;
    case 17:
        message.type = 0x10;
        message.f10 = command->f4E;
        func_8005DA88(&message);
        break;
    case 18:
    case 19:
        message.type = 8;
        message.fc = command->f4E;
        func_8005DA88(&message);
        break;
    case 0:
    case 13:
    case 14:
    case 20:
    case 21:
    case 22:
    default:
            break;
    }
}

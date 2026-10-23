#include "slus/jtbl_80057A94.h"
#include "common.h"



/*
 * Changes a selected tone's fields and envelope bits, or configures SPU reverb from a channel
 * command.
 *
 * Rodata owner: the row's switch emits its jump table(s) into this object's .rodata, placed at the
 * retail address by config/slus_modules.json (assets/800.bin carve).
 */
void apply_tone_parameter_command(S_80057A94 *command) {
    S_80057A94_cell *cell;
    S_80057A94_msg message;
    u32 operation;

    cell = (S_80057A94_cell *)audio_get_current_bank_tone_record(command, command->f4D & 0xF);
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
        if (is_tone_parameter_flag_set() == 1) {
            SpuSetReverb(0);
        }
        if (command->f4E != 0) {
            message.type = 1;
            message.f4 = command->f4E;
            sound_ram_reserve_mode[0] = command->f4E;
            SpuSetReverbModeParam(&message);
            SpuSetReverb(1);
        }
        break;
    case 16:
        message.type = 6;
        message.x = command->f4E << 8;
        message.y = command->f4E << 8;
        SpuSetReverbModeParam(&message);
        SpuSetReverb(1);
        break;
    case 17:
        message.type = 0x10;
        message.f10 = command->f4E;
        SpuSetReverbModeParam(&message);
        break;
    case 18:
    case 19:
        message.type = 8;
        message.fc = command->f4E;
        SpuSetReverbModeParam(&message);
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

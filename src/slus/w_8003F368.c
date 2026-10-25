#include "engine/scene/cd_state.h"


extern u8 cd_location_second_byte_alias[2];
extern u8 cd_location_third_byte_alias[1];

extern s32 CdSync(s32 mode, u8 *result);
extern s32 CdControl(u8 com, u8 *param, u8 *result);
extern s32 CdPosToInt(u8 *loc);
extern void func_8003E70C(void);
extern void cd_set_mode_with_retry(void);
extern s32 func_8003F688(u8 val);

/* Reads and validates the CD location, returning its sector position or zero. */
s32 query_validated_cd_sector_with_retry(void)
{
    u32 saved_loc;
    u8 cd_loc[4];
    u8 sync_result[8]; /* CdSync copies eight result bytes. */
    s32 retries_left;
    s32 sector_pos;
    u8 index_is_zero;
    u8 *recovery_state;

    saved_loc = cd_command_result.first_word;
    cd_command_result.first_word = 0;

    if (CdSync(1, sync_result) != 2) {
        return 0;
    }

    retries_left = 0x10;

L8003F3A4:
    for (;;) {
        if (CdControl(0x10, 0, (cd_location_second_byte_alias - 1)) == 1) {
            break;
        }
        if (--retries_left == 0) {
            func_8003E70C();
            retries_left = 0x10;
            cd_set_mode_with_retry();
        }
    }

    retries_left = 0x10;
    recovery_state = cd_command_phase;
    while (CdSync(1, (cd_location_second_byte_alias - 1)) != 2) {
        if (--retries_left != 0) {
            continue;
        }
        func_8003E70C();
        if ((get_previous_cd_command_byte() & 0xFF) == 0x1B) {
            index_is_zero = (recovery_state[-3] == 0);
            cd_command_phase[0] = 0xFF;
            if (!index_is_zero) {
                cd_command_read_index -= 1;
            } else {
                recovery_state[-3] = 0x1F;
            }
            cd_command_read_index &= 0x1F;
            retries_left = 0x10;
            cd_set_mode_with_retry();
            goto L8003F3A4;
        }
        cd_command_result.first_word = saved_loc;
        retries_left = 0x10;
    }

    cd_loc[0] = cd_command_result.bytes[0];
    cd_loc[1] = cd_location_second_byte_alias[0];
    cd_loc[2] = cd_location_third_byte_alias[0];
    sector_pos = CdPosToInt(cd_loc);

    if (func_8003F688(cd_command_result.bytes[0]) >= 0x4B) {
        return 0;
    }
    {
        s32 result;

        if (func_8003F688((*(cd_location_third_byte_alias - 1))) < 0x3C) {
            s32 sector_valid;
            sector_valid = func_8003F688(cd_location_second_byte_alias[1]) < 0x4B;
            result = 0;
            if (!sector_valid) {
                return result;
            }
            if (sector_pos > 0) {
                return sector_pos;
            }
        }
        result = 0;
        return result;
    }
}

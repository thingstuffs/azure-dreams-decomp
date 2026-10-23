#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"
#include "sdk/libetc.h"

extern void erase(void *);

typedef struct {
    s32 unk0[32];
} func_8000F19C_Unk80083E98Elem;

typedef struct {
    s32 unk0[8];
} func_8000F19C_Sp10Buf;



/* Erase a memory card file, wait for completion, and clear its cached entry. */
s32 card_boot_erase_slot_file(s32 file_index) {
    func_8000F19C_Sp10Buf file_path;
    s32 erase_status;

    card_boot_build_slot_path(&file_path, file_index);
    _card_wait(0);
    _card_wait(1);
    card_boot_drain_hardware_events();
    erase(&file_path);
    do {
        erase_status = card_boot_take_hardware_status();
        if (erase_status == 0) {
            VSync(0);
        }
    } while (erase_status == 0);
    if (file_index < 5) {
        (*(func_8000F19C_Unk80083E98Elem (*)[])(&card_save_slot_metadata))[file_index].unk0[0] = 0;
        card_boot_refresh_directory_summary();
    }
    return erase_status == 1;
}

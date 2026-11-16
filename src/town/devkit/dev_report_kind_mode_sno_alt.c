#include "common.h"
#include "town/devkit.h"
#include "town/devkit/list_methods_data.h"

typedef void (*TownCallback)(void *, void *, s32);

extern u8 D_807007B4[];
extern u8 D_807007C0[];
extern u8 D_807007C8[];
extern u8 D_807007D0[];
extern s32 D_80700710[];
extern s32 devkit_scene_list_length[];

/* Reports the supplied kind and the stored mode and scene number (sno). */
void dev_report_kind_mode_sno_alt(s32 kind) {
    u8 *callback_data = D_807007B4;
    TownCallback callback;

    callback = devkit_list_methods[0]->func68;
    callback(callback_data, D_807007C0, kind);
    callback = devkit_list_methods[0]->func68;
    callback(callback_data, D_807007C8, D_80700710[0]);
    callback = devkit_list_methods[0]->func68;
    callback(callback_data, D_807007D0, devkit_scene_list_length[0]);
}

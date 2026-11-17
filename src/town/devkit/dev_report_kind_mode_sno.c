#include "common.h"
#include "town/devkit.h"
#include "town/data.h"
#include "town/devkit/shop_selection_data.h"

extern char D_80701FCC[];
extern char D_80701FD8[];
extern char D_80701FE0[];
extern char D_80701FE8[];
extern s32 devkit_selected_shop_row;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void dev_report_kind_mode_sno(s32 kind)
{
    devkit_runtime_methods->print(D_80701FCC, D_80701FD8, kind);
    devkit_runtime_methods->print(D_80701FCC, D_80701FE0, devkit_shop_selection);
    devkit_runtime_methods->print(D_80701FCC, D_80701FE8, devkit_selected_shop_row);
}

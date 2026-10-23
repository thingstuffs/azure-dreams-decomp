#include "common.h"

typedef void (*PrintValue)(char *format, char *name, s32 value);

typedef struct PrintInterface {
    u8 pad_00[0x68];
    PrintValue print_value;
} PrintInterface;

extern PrintInterface *devkit_runtime_methods;
extern char D_80701FCC[];
extern char D_80701FD8[];
extern char D_80701FE0[];
extern char D_80701FE8[];
extern s32 devkit_selected_shop_row;
extern s32 devkit_shop_selection;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void dev_report_kind_mode_sno(s32 kind)
{
    devkit_runtime_methods->print_value(D_80701FCC, D_80701FD8, kind);
    devkit_runtime_methods->print_value(D_80701FCC, D_80701FE0, devkit_shop_selection);
    devkit_runtime_methods->print_value(D_80701FCC, D_80701FE8, devkit_selected_shop_row);
}

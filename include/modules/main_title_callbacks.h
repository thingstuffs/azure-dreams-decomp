#ifndef MAIN_TITLE_CALLBACKS_H
#define MAIN_TITLE_CALLBACKS_H
#include "common.h"

struct Menu;
struct MainTitleValueEntry;
struct MainValue;
struct ColorRampEffect;
struct ColorEffect;
s32 func_8008896C(u8 *entry_data, u8 *scroll_data);
void func_80088930(s32 object_data_addr);
void func_800888D0(void *entry);
void func_80089A14(unsigned short *data);
void func_8008A288(struct Menu *menu);
s32 func_8008A794(void *node_data, void *scroll_state);
void func_8008AA40(void *record);
void func_8008AA84(void *entry);
void func_8008AAE4(struct MainTitleValueEntry *entry);
void func_8008AB44(void *dest);
void func_8008ACB4(struct MainValue **value_slot, u8 *output, struct MainValue *value);
void func_8008AD58(struct ColorRampEffect *effect);
void func_8008AEEC(struct ColorEffect *effect);
#endif

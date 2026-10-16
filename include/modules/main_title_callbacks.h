#ifndef MAIN_TITLE_CALLBACKS_H
#define MAIN_TITLE_CALLBACKS_H
#include "common.h"

struct Menu;
struct MainTitleValueEntry;
struct MainValue;
struct ColorRampEffect;
struct ColorEffect;
s32 mainQueueSettingsSpriteGrid(u8 *entry_data, u8 *scroll_data);
void mainAssignObjectDescriptorOnCheck(s32 object_data_addr);
void mainRunFlagHandlerAndSet2000Flags(void *entry);
void func_80089A14(unsigned short *data);
void mainHandleSettingsMenuInput(struct Menu *menu);
s32 mainBuildSettingsSpriteTiles(void *node_data, void *scroll_state);
void func_8008AA40(void *record);
void func_8008AA84(void *entry);
void func_8008AAE4(struct MainTitleValueEntry *entry);
void func_8008AB44(void *dest);
void func_8008ACB4(struct MainValue **value_slot, u8 *output, struct MainValue *value);
void mainUpdateSettingsEffectColor(struct ColorRampEffect *effect);
void func_8008AEEC(struct ColorEffect *effect);
#endif

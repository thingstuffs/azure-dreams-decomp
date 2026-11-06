#ifndef FRONTEND_SETTINGS_INITIALIZATION_H
#define FRONTEND_SETTINGS_INITIALIZATION_H
#include "common.h"
#include "shared/entity.h"
/* Stack templates copied by the settings constructors. The panel copy is
 * 0x28 bytes, the text copy is 0x30 bytes, and both retain their observed
 * integer address fields at the generic construction boundary. */
typedef struct SettingsPanelTemplate {
    s16 flags;
    u8 pad_02[2];
    void *owner;
    s32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 style;
    s16 shading;
    s32 index;
    u8 pad_1C[0xC];
} SettingsPanelTemplate;

typedef struct SettingsLabelTemplate {
    s16 flags;
    s16 order;
    s32 text;
    u8 pad_08[4];
    void *owner;
    s32 color;
    s16 x;
    u16 y;
    s16 style;
    s16 font;
    s16 extra;
    u8 pad_1E[2];
    s32 value;
    s32 index;
    u8 pad_28[8];
} SettingsLabelTemplate;

/* The first two fixed-point coordinates in the settings construction frame. */
typedef struct SettingsPositionPair {
    Fixed1616 x;
    Fixed1616 y;
} SettingsPositionPair;

typedef union SettingsInitializationFrame {
    u8 bytes[0x278];
    struct {
        SettingsPositionPair position;
        u8 pad_08[0x10];
        SettingsPanelTemplate panel;
        SettingsLabelTemplate label;
        u16 palette[0x100];
        u8 rectangle[8];
    } fields;
} SettingsInitializationFrame;

#endif

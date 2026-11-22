#ifndef FRONTEND_SETTINGS_INITIALIZATION_H
#define FRONTEND_SETTINGS_INITIALIZATION_H
#include "common.h"
#include "shared/entity.h"
#include "frontend/settings.h"
/* Stack templates copied by the settings constructors. The panel copy is
 * 0x28 bytes, the text copy is 0x30 bytes, and both retain their observed
 * integer address fields at the generic construction boundary. */
typedef MainTitleValueEntry SettingsPanelTemplate;

typedef ColorEffect SettingsLabelTemplate;

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

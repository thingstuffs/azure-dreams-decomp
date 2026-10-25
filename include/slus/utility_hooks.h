#ifndef INCLUDE_SLUS_UTILITY_HOOKS_H
#define INCLUDE_SLUS_UTILITY_HOOKS_H

#include "common.h"

s32 return_zero_variadic(s32 unused, ...);

/* Empty channel notification receives kind, channel and value. */
void noop_channel_control_notification(s32 kind, s32 channel, s32 value);

#endif

#ifndef TOWN_LINE_PACKETS_H
#define TOWN_LINE_PACKETS_H

#include "shared/gpu_packets.h"

/* The two-vertex line renderer reserves five words, copies both colors and
 * projected XY pairs, and links the packet by its low 24 address bits. */
typedef struct TownGradientLinePacket {
    GpuLinkTag tag;
    int first_color;
    int first_xy;
    int second_color;
    int second_xy;
} TownGradientLinePacket;

/* SetLineF2 initializes the command byte in the single color word. Both
 * endpoints receive the packed XY outputs of the projection routine. */
typedef struct TownFlatLinePacket {
    GpuLinkTag tag;
    int color;
    int first_xy;
    int second_xy;
} TownFlatLinePacket;

#endif

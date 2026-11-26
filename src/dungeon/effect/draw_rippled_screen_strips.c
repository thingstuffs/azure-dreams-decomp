#include "modules/dungeon_ovl_18fa800.h"
#include "dungeon/effect/particle/vertex_transform.h"
#include "engine/graphics/frame_context.h"
#include "common.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_packets.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/rand.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_node.h"

/* Body of one rippling screen patch. Its creator fills it and its update callback counts the timer down from 40,
 * raising the brightness by 8 a tick up to 80 and lowering it to eight times the timer over the last 8 ticks. */
typedef struct RippleBody {
    /* 0x00 */ void *owner; /* body of the spell that created the patch */
    /* 0x04 */ SVECTOR position;
    /* 0x0C */ s32 brightness; /* starts at -64; the strips are drawn in grey of this level while it is positive */
    /* 0x10 */ s16 timer; /* ticks left */
    /* 0x12 */ s16 unk_12; /* set to 1 by the creator, not read here */
} RippleBody;

/* One corner of the screen bounding box, both halves in one word. */
typedef struct ScreenCorner {
    int x : 16;
    int y : 16;
} ScreenCorner;

/* Draw callback of the patch chain. For every patch it projects a 96-wide quad standing at the patch position,
 * takes the screen box of the four points, has the GPU copy that box to the work page and draws it back over
 * itself as four layers of two-line strips, each shifted sideways by a sine of its row. */
s32 draw_rippled_screen_strips(void *arg) {
    RECT area;
    SVECTOR buffer[4];
    VertexTransformRequest request;
    s32 screen; /* the projected point as RotTransPers writes it: x in the low half, y in the high half */
    s32 n; /* half width of the quad, then the unused outputs of RotTransPers, then the layer counter */
    RippleBody *body;
    s32 depth;
    ScreenCorner low, high;
    POLY_FT4 *poly;
    DR_PRIO *priority;
    DR_MOVE *move;
    int i, top, bottom, limit, phase, colour;
    int y, frame_y, h;

    /* BYTES: Alias the draw-buffer slot so every packet reloads the current context. */
    FrameDrawContextSlot *draw = (FrameDrawContextSlot *)&g_game_work.draw_buffer;

    depth = 0;
    for (;;) {
        GameWork *game = &g_game_work;
        SVECTOR *vertices = buffer;
        int page_x = 0x340; /* where the work page lies in VRAM */
        int page_y = 0x100;

        n = 48;
        body = arg;
        for (i = 3; i >= 0; i--) {
            vertices[i].vx = n;
            if (i < 2) {
                vertices[i].vx = -n;
            }
            vertices[i].vy = 0;
            if (i & 1) {
                vertices[i].vz = -128;
            } else {
                vertices[i].vz = 16;
            }
        }
        request.rotation.vx = request.rotation.vy = 0;
        request.source = vertices;
        request.destination = vertices;
        request.rotation.vz = game->view.view_rotation_offset.parts.view_rotation_offset_z -
                              game->view.camera_rotation.parts.viewAngle;
        request.translation = body->position;
        request.count = 4;
        request.rotation_mode = 0;
        transform_rotated_vertices(&request);
        low.x = low.y = 30000;
        high.x = high.y = -30000;
        for (i = 3; i >= 0; i--) {
            depth += RotTransPers(&vertices[i], &screen, &n, &n) - 8;
            if (high.x < (s16)screen) {
                high.x = (s16)screen;
            } else if ((s16)screen < low.x) {
                low.x = (s16)screen;
            }
            if (high.y < (s16)((u32)screen >> 16)) {
                high.y = (s16)((u32)screen >> 16);
            } else if ((s16)((u32)screen >> 16) < low.y) {
                low.y = (s16)((u32)screen >> 16);
            }
        }
        y = low.y;
        area.w = high.x - low.x;
        area.x = low.x;
        depth >>= 2;
        /* The lower draw context's frame lies 224 lines down in VRAM. */
        frame_y = y;
        if (game->draw_buffer != upper_draw_context) {
            frame_y += 224;
        }
        h = high.y - y;
        area.y = frame_y;
        area.h = h;
        if (depth >= 0 && depth < 480) {
            /* The box may not run past the bottom of its frame. */
            limit = area.y + area.h;
            if (area.y / 224 != limit / 224) {
                limit = limit / 224 * 224;
            }
            if (game->view.view_rotation_offset.parts.view_rotation_offset_z) {
                bottom = 40 - body->timer;
                top = area.y;
                if (bottom > 8) {
                    bottom = 8;
                }
                bottom = area.h * bottom / 8 + top;
            } else {
                top = body->timer - 32;
                if (top < 0) {
                    top = 0;
                }
                top = area.h * top / 8 + area.y;
                bottom = limit;
            }
            for (n = 4; n > 0; n--) {
                phase = (body->timer + n) << 7;
                if (!(n & 1)) {
                    phase += 0x800;
                }
                if (body->brightness > 0) {
                    colour = (body->brightness << 16) + (body->brightness << 8) + body->brightness;
                } else {
                    colour = 0;
                }
                for (i = top; i <= bottom; i++) {
                    poly = draw->context->packetCursor;
                    draw->context->packetCursor = poly + 1;
                    phase += 80 + n * 4;
                    if (body->timer > 8) {
                        colour += 0x080808;
                        if (colour > 0x484848) {
                            colour = 0x484848;
                        }
                    }
                    /* BYTES: Store the complete color word before SetPolyFT4 writes the command byte. */
                    *(s32 *)&poly->r0 = colour;
                    SetPolyFT4(poly);
                    SetSemiTrans(poly, 1);
                    poly->tpage = GetTPage(2, 3, page_x, page_y);
                    poly->u0 = poly->u1 = (area.w >> 3) + (area.w >> 4);
                    poly->u2 = poly->u3 = area.w - poly->u0;
                    poly->v0 = poly->v2 = i - area.y;
                    poly->v1 = poly->v3 = poly->v0 + 2;
                    poly->x0 = poly->x1 = poly->u0 + (area.x + (rsin(phase) >> 10));
                    poly->x2 = poly->x3 = poly->x0 + area.w - poly->u0;
                    poly->y0 = poly->y2 = i % 224 - n;
                    poly->y1 = poly->y3 = poly->y0 + 2;
                    addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, poly);
                }
            }
            if (top == 0) {
                for (i = 4; i >= 0; i--) {
                    poly = draw->context->packetCursor;
                    draw->context->packetCursor = poly + 1;
                    /* BYTES: Store the complete color word before SetPolyFT4 writes the command byte. */
                    *(s32 *)&poly->r0 = 0x808080;
                    SetPolyFT4(poly);
                    SetSemiTrans(poly, 1);
                    poly->tpage = GetTPage(2, 0, page_x, page_y);
                    poly->x0 = poly->x1 = area.x + rand() % 5 - 2;
                    poly->x2 = poly->x3 = poly->x0 + area.w;
                    poly->y0 = poly->y2 = area.y % 224 + rand() % 5 - 2;
                    poly->y1 = poly->y3 = poly->y0 + area.h;
                    poly->u0 = poly->u1 = 0;
                    poly->u2 = poly->u3 = area.w;
                    poly->v0 = poly->v2 = 0;
                    poly->v1 = poly->v3 = area.h;
                    addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, poly);
                }
            }
            priority = draw->context->packetCursor;
            draw->context->packetCursor = priority + 1;
            SetPriority(priority, 0, 0);
            addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, priority);
            move = draw->context->packetCursor;
            draw->context->packetCursor = move + 1;
            SetDrawMove(move, &area, page_x, page_y);
            addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, move);
            poly = draw->context->packetCursor;
            draw->context->packetCursor = poly + 1;
            /* BYTES: Store the complete color word before SetPolyFT4 writes the command byte. */
            *(s32 *)&poly->r0 = 0x808080;
            SetPolyFT4(poly);
            poly->tpage = GetTPage(2, 0, page_x, page_y);
            poly->x0 = poly->x1 = area.x;
            poly->x2 = poly->x3 = poly->x0 + area.w;
            poly->y0 = poly->y2 = area.y % 224;
            poly->y1 = poly->y3 = poly->y0 + area.h;
            poly->u0 = poly->u1 = 0;
            poly->u2 = poly->u3 = area.w;
            poly->v0 = poly->v2 = 0;
            poly->v1 = poly->v3 = area.h;
            addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, poly);
            priority = draw->context->packetCursor;
            draw->context->packetCursor = priority + 1;
            SetPriority(priority, 0, 1);
            addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, priority);
            move = draw->context->packetCursor;
            draw->context->packetCursor = move + 1;
            SetDrawMove(move, &area, page_x, page_y);
            addPrim(&draw->context->orderTag[GPU_ORDER_DEPTH_BASE] + depth, move);
        }
        if (!NODE_HEADER(arg)->chain_next) {
            break;
        }
        arg = NODE_BODY(NODE_HEADER(arg)->chain_next);
    }
    return 0;
}

/* Movie display setup (G00426).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00426 - CL:ovmovie/func_800402D8, CL:ovmovie/func_8004033C, CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D8, PD:ovmovie/ovmovie_bin:80189390.
 */
#include "ovmovie/movie_display_setup_g00426.h"

/* Plays the selected movie and resets both frame buffers afterward. */
void play_selected_movie_and_restore_display(void) {
    u8 *frame_buffers;
    s32 movie_flag;
    s32 saved_movie_flag;
    u8 *resident_globals_hi = (u8 *) 0x80080000;
    u8 *movie_globals_hi;

    runtime_dispatch_state.field_0 &= ~1;
    if (scene_music_hold == 0) {
        SD_Call(0x7F);
        drain_audio_commands_and_service_channels();
    }

    submit_tagged_driver_byte(0, 0, 1);
    movie_volume = 0x7F;
    submit_scaled_driver_halfword_pair(0, (s16) movie_volume, (s16) movie_volume);

    movie_flag = (u32) movie_frame_control >> 31;
    movie_globals_hi = (u8 *) 0x80180000;
    *(s32 *) (movie_globals_hi - 0x7E1C) = movie_flag;
    clear_movie_display_area(movie_flag);
    func_80066F78(0);

    frame_buffers = upper_draw_context;
    frame_buffers[0x6D] = 1;
    frame_buffers[0x10941] = 1;
    saved_movie_flag = *(s32 *) (movie_globals_hi - 0x7E1C);
    clear_movie_display_area(saved_movie_flag);

    movie_rgb24_mode = 1;
    set_movie_strip_offsets(0, ((movie_frame_control & 0x40000000) == 0) * 0x10);
    play_movie_frames_with_skip_fade(0, movie_frame_control & 0x3FFFFFFF, movie_start_sector, *(s32 *) (movie_globals_hi - 0x7E1C));
    func_80066F78(0);

    {
        u8 *active_buffer;

        active_buffer = *(u8 **) (resident_globals_hi + 0x3160);
        frame_buffers[0x6D] = 0;
        frame_buffers[0x10941] = 0;
        func_800678E0(active_buffer + 0x5C);
    }
    func_80067014(0);
    func_8005FE18(2);
    func_80060DE8(0);
    Control_CD(9, 0, 0);
    drain_cd_command_queue();
    register_mode_one_callback(0);
    func_80061208(0);
    func_80067014(0);
    clear_movie_display_area(*(s32 *) (movie_globals_hi - 0x7E1C));

    {
        u8 *active_buffer;
        u8 *next_buffer;

        active_buffer = *(u8 **) (resident_globals_hi + 0x3160);
        next_buffer = frame_buffers;
        frame_buffers[0x6D] = 0;
        frame_buffers[0x10941] = 0;
        if (active_buffer == frame_buffers) {
            next_buffer = frame_buffers + 0x108D4;
        }
        *(u8 **) (resident_globals_hi + 0x3160) = next_buffer;
        func_8006751C(next_buffer + 0x70, 0x218);
        func_80067688(*(void **) (resident_globals_hi + 0x3160));
    }
    func_8005FE18(0);
    {
        u8 *next_buffer;

        next_buffer = frame_buffers;
        if (*(u8 **) (resident_globals_hi + 0x3160) == frame_buffers) {
            next_buffer = frame_buffers + 0x108D4;
        }
        *(u8 **) (resident_globals_hi + 0x3160) = next_buffer;
        func_8006751C(next_buffer + 0x70, 0x218);
        func_80067688(*(void **) (resident_globals_hi + 0x3160));
    }
    func_8005FE18(0);
    clear_movie_display_area(*(s32 *) (movie_globals_hi - 0x7E1C));
}

void clear_movie_display_area(s32 useFullHeight) {
    s16 clearRect[4];
    s16 extent;
    s32 blackComponent;

    func_80067014(0);
    extent = 0x1E0;
    clearRect[0] = 0;
    clearRect[1] = 0;
    clearRect[2] = extent;
    if (useFullHeight == 0) {
        extent = 0x1C0;
    }
    blackComponent = 0;
    clearRect[3] = extent;
    func_800671A8(clearRect, blackComponent, blackComponent, blackComponent);
    func_80067014(0);
}

/* Stores two signed values in the movie state globals. */
void set_movie_strip_offsets(s16 value_d8, s16 value_dc) {
    movie_strip_x_offset = (s32) value_d8;
    movie_strip_y_offset = (s32) value_dc;
}

/* Reset movie state and apply the requested playback settings. */
void initialize_movie_decoder_and_start_stream(void *playback_state, void (*playback_option)(void)) {
    set_movie_decode_mode(0);
    *(s32 *)((u8 *)active_movie + 0x34) = 0;
    register_mode_one_callback(playback_option);
    func_80060B04((u8 *)active_movie + 0x40, 0x20);
    func_800636AC(movie_rgb24_mode & 1, 1, -1, 0, 0);
    start_movie_cd_stream_and_wait_ready(playback_state);
}

/* Initializes movie buffer pointers and frame rectangles for the current mode. */
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y) {
    s32 buffer_offset = 0x15A40;
    s32 next_buffer_offset = 0x22AB0;
    s32 work_offset = 0x10040;
    u8 *buffer_base = (u8 *)active_movie;
    s32 movie_flags = *(s32 *)((u8 *)&movie_rgb24_mode + 0);   /* read through a plain pointer: the array spelling sets MEM_IN_STRUCT_P and reschedules the two global loads */

    movie->unk08 = 0;
    movie->unk20 = 0;
    movie->unk2C = 0;
    movie->unk00 = buffer_base + buffer_offset;
    movie->unk04 = buffer_base + next_buffer_offset;
    movie->unk0C = buffer_base + work_offset;
    if (movie_flags & 1) {
        movie->unk14 = 0x1E0;
        movie->unk1C = 0x1E0;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x18;
        movie->unk2A = 0xF0;
    } else {
        movie->unk14 = 0x140;
        movie->unk1C = 0x140;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x10;
        movie->unk2A = 0xF0;
    }
}

void upload_movie_strip_and_advance_buffer(void) {
    MovieRect rectangle;
    MovieState *movie;
    if (movie_rgb24_mode & 1) {
        if (D_80086D8C) {
            func_8006390C();
            D_80086D8C = 0;
        }
    }
    rectangle = active_movie->strip;
    if (movie_rgb24_mode & 1) {
        rectangle.x += (movie_strip_x_offset / 3) * 3;
        rectangle.y += (movie_strip_y_offset / 3) * 3;
    } else {
        rectangle.x += movie_strip_x_offset;
        rectangle.y += movie_strip_y_offset;
    }
    func_800672D8(&rectangle, active_movie->output);
    func_80067014(0);
    movie = active_movie;
    movie->strip.x += movie->strip.w;
    if (movie->strip.x < movie->screen[movie->screen_index].x + movie->screen[movie->screen_index].w) {
        request_decoder_output_dma((s32)movie->output, (movie->strip.w * movie->strip.h) / 2);
    } else {
        movie->ready = 1;
        movie->screen_index = !movie->screen_index;
        movie->strip.x = movie->screen[movie->screen_index].x;
        movie->strip.y = movie->screen[movie->screen_index].y;
    }
}

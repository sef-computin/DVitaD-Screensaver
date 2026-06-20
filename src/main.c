
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

/*
 * Symbol of the image.png file
 */
extern unsigned char _binary_res_mask_png_start;

#define SCREEN_WTH 960
#define SCREEN_HGT 544
#define COLORS_COUNT 25

unsigned char rndtable[256] = {
    0,   8, 109, 220, 222, 241, 149, 107,  75, 248, 254, 140,  16,  66 ,
    74,  21, 211,  47,  80, 242, 154,  27, 205, 128, 161,  89,  77,  36 ,
    95, 110,  85,  48, 212, 140, 211, 249,  22,  79, 200,  50,  28, 188 ,
    52, 140, 202, 120,  68, 145,  62,  70, 184, 190,  91, 197, 152, 224 ,
    149, 104,  25, 178, 252, 182, 202, 182, 141, 197,   4,  81, 181, 242 ,
    145,  42,  39, 227, 156, 198, 225, 193, 219,  93, 122, 175, 249,   0 ,
    175, 143,  70, 239,  46, 246, 163,  53, 163, 109, 168, 135,   2, 235 ,
    25,  92,  20, 145, 138,  77,  69, 166,  78, 176, 173, 212, 166, 113 ,
    94, 161,  41,  50, 239,  49, 111, 164,  70,  60,   2,  37, 171,  75 ,
    136, 156,  11,  56,  42, 146, 138, 229,  73, 146,  77,  61,  98, 196 ,
    135, 106,  63, 197, 195,  86,  96, 203, 113, 101, 170, 247, 181, 113 ,
    80, 250, 108,   7, 255, 237, 129, 226,  79, 107, 112, 166, 103, 241 ,
    24, 223, 239, 120, 198,  58,  60,  82, 128,   3, 184,  66, 143, 224 ,
    145, 224,  81, 206, 163,  45,  63,  90, 168, 114,  59,  33, 159,  95 ,
    28, 139, 123,  98, 125, 196,  15,  70, 194, 253,  54,  14, 109, 226 ,
    71,  17, 161,  93, 186,  87, 244, 138,  20,  52, 123, 251,  26,  36 ,
    17,  46,  52, 231, 232,  76,  31, 221,  84,  37, 216, 165, 212, 106 ,
    197, 242,  98,  43,  39, 175, 254, 145, 190,  84, 118, 222, 187, 136 ,
    120, 163, 236, 249
};

// '#ff0000', '#ff4000', '#ff8000', '#ffbf00', '#ffff00', '#bfff00', '#80ff00', '#40ff00', '#00ff00', '#00ff40', '#00ff80', '#00ffbf', '#00ffff', '#00bfff', '#0080ff', '#0040ff', '#0000ff', '#4000ff', '#8000ff', '#bf00ff', '#ff00ff', '#ff00bf', '#ff0080', '#ff0040', '#ff0000'
int colors[COLORS_COUNT] = {
  0xffff0000, 0xffff4000, 0xffff8000, 0xffffbf00, 0xffffff00,
  0xffbfff00, 0xff80ff00, 0xff40ff00, 0xff00ff00, 0xff00ff40,
  0xff00ff80, 0xff00ffbf, 0xff00ffff, 0xff00bfff, 0xff0080ff,
  0xff0040ff, 0xff0000ff, 0xff4000ff, 0xff8000ff, 0xffbf00ff,
  0xffff00ff, 0xffff00bf, 0xffff0080, 0xffff0040, 0xffff0000
};

int main()
{
	SceCtrlData pad;
	vita2d_pgf *pgf;
	vita2d_pvf *pvf;
	vita2d_texture *image;
  int p_width = 256, p_height = 138;
  int px = SCREEN_WTH / 2; int py = SCREEN_HGT / 2;
  int dir_x = 1; int dir_y = -1;
  int velocity = 5;

  int rnd_ind = 0;

	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

	pgf = vita2d_load_default_pgf();
	pvf = vita2d_load_default_pvf();

	/*
	 * Load the statically compiled image.png file.
	 */
	image = vita2d_load_PNG_buffer(&_binary_res_mask_png_start);

	memset(&pad, 0, sizeof(pad));

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);

		if (pad.buttons & SCE_CTRL_START)
			break;

		vita2d_start_drawing();
		vita2d_clear_screen();

    vita2d_draw_texture_tint(image, px, py, colors[rndtable[rnd_ind]%COLORS_COUNT]);

		vita2d_end_drawing();
		vita2d_swap_buffers();


    px += velocity * dir_x;
    py += velocity * dir_y;

    if (px <= 0   && dir_x < 0) { dir_x = 1; rnd_ind = (rnd_ind+1)%256; }
    if (px+p_width >= SCREEN_WTH && dir_x > 0) { dir_x = -1; rnd_ind = (rnd_ind+1)%256; }
    if (py <= 0   && dir_y < 0) { dir_y = 1; rnd_ind = (rnd_ind+1)%256; }
    if (py+p_height >= SCREEN_HGT && dir_y > 0) { dir_y = -1; rnd_ind = (rnd_ind+1)%256; }
    
	}

	/*
	 * vita2d_fini() waits until the GPU has finished rendering,
	 * then we can free the assets freely.
	 */
	vita2d_fini();
	vita2d_free_texture(image);
	vita2d_free_pgf(pgf);
	vita2d_free_pvf(pvf);

	sceKernelExitProcess(0);
	return 0;
}

/* Lib Aldaron --- Copyright (c) 2016 Jeron A. Lau */
/* This file must be distributed with the GNU LESSER GENERAL PUBLIC LICENSE. */
/* DO NOT REMOVE THIS NOTICE */

#include <la_config.h>
#ifdef LA_FEATURE_DISPLAY

#include <la_draw.h>
#include <la_ro.h>
#include <la_text.h>

typedef struct {
	la_v3_t where[2];
	la_ro_t vo[3]; // Vertex object [ Full, Slider 1, Slider 2 ].
}la_gui_slider_draw;

typedef struct {
	float* x1;
	float* x2;
	uint8_t isRange;
	la_gui_slider_draw draw;
}la_gui_slider_main;

void jlgr_mouse_draw__(la_window_t* jlgr);

extern float la_banner_size;

/*static void jlgr_gui_textbox_cursor__(la_window_t* jlgr, jlgr_input_t input) {
	if(input.h == 2) jlgr->gui.textbox.counter += jlgr->jl->time.psec;
	if(input.h != 1 && jlgr->gui.textbox.do_it != 1) return;
	switch(input.k) {
		case JLGR_INPUT_DIR_RT: {
			if(jlgr->gui.textbox.string->curs <
			 jlgr->gui.textbox.string->size)
				jlgr->gui.textbox.string->curs++;
			jlgr_input_typing_disable();
			jlgr->gui.textbox.cursor = 1;
			jlgr->gui.textbox.counter = 0.f;
			break;
		}
		case JLGR_INPUT_DIR_LT: {
			if(jlgr->gui.textbox.string->curs)
				jlgr->gui.textbox.string->curs--;
			jlgr_input_typing_disable();
			jlgr->gui.textbox.cursor = 1;
			jlgr->gui.textbox.counter = 0.f;
			break;
		}
	}
}*/

/**
 * Prepare to draw an image that takes up the entire pre-renderer or
 * screen.
 * @param jlgr: The library context.
 * @param tex: The texture to draw.
 * @param w: Width ( in characters ) of character map.
 * @param h: Height ( in characters ) of character map.
 * @param c: is -1 unless you want to use the image as
 * 	a charecter map, then it will zoom into charecter 'chr'.
**/
void jlgr_fill_image_set(la_window_t* jlgr, uint32_t tex, uint8_t w, uint8_t h, 
	int16_t c)
{
	if(!tex) la_panic("jlgr_fill_image_set: Texture Must Be Nonzero!\n");
//	la_rect_t rc = { 0., (.5f * la_window_h(jlgr)) - 1.f, 1.f, 2.f };

	la_ro_image_rect(jlgr, &jlgr->gui.vos.whole_screen, tex, 1.f, 2.f);
	la_ro_change_image(&jlgr->gui.vos.whole_screen, tex, w, h, c, 0);
}

/**
 * Draw the image prepared with jlgr_fill_image_set().
 * @param jl: The library context.
**/
void jlgr_fill_image_draw(la_window_t* jlgr) {
	la_ro_draw(&jlgr->gui.vos.whole_screen);
}

/**
 * Draw text within the boundary of a sprite
 * @param 'jl': library context
 * @param 'spr': the boundary sprite
 * @param 'txt': the text to draw
**/
/*void jlgr_text_draw_area(la_window_t* jlgr, la_ro_t * spr, const char* txt) {
	float fontsize = .9 / strlen(txt);
	jlgr_text_draw(jlgr, txt,
		(la_v3_t) { .05,.5 * (la_ro_ar(jlgr) - fontsize),0. });
}*/

/**
 * Draw a sprite, then draw text within the boundary of a sprite
 * @param 'jl': library context
 * @param 'spr': the boundary sprite
 * @param 'txt': the text to draw
**/
/*void jlgr_draw_text_sprite(la_window_t* jlgr, la_ro_t* spr, const char* txt) {
	jlgr_fill_image_set(jlgr, jlgr->textures.icon, 16, 16, 1);
	jlgr_fill_image_draw(jlgr);
	jlgr_text_draw_area(jlgr, spr, txt);
}*/

// TODO: MOVE
/*static void jlgr_gui_slider_touch(la_window_t* jlgr, jlgr_input_t input) {
	la_ro_t* spr = input.data;
	la_gui_slider_main* slider = jlgr_sprite_getcontext(spr);

	if(jlgr_sprite_collide(jlgr, &spr->pr, &jlgr->mouse.pr) == 0 ||
	 input.h == 0)
		return;
	float x = al_safe_get_float(&jlgr->main.ct.msx) - (la_ro_ar(jlgr) * .05 * spr->pr.cb.ofs.x);
	x -= spr->pr.cb.pos.x;
	x /= spr->pr.cb.ofs.x;
//		x += 1.5;// - (la_ro_ar(jl->jlgr) * .1);
	if(x <= 0.) x = 0.;
	if(x > 1. - (la_ro_ar(jlgr) * .15))
		x = 1. - (la_ro_ar(jlgr) * .15);
//
	if(slider->isRange) {
		double v0 = fabs((*slider->x1) - x);
		double v1 = fabs((*slider->x2) - x);
		if(v1 < v0) {
			(*slider->x2) = x /
				(1. - (la_ro_ar(jlgr) * .15));
			slider->draw.where[1].x = x;
		}else{
			(*slider->x1) = x /
				(1. - (la_ro_ar(jlgr) * .15));
			slider->draw.where[0].x = x;
		}
	}else{
		(*slider->x1) = x / (1. - (la_ro_ar(jlgr) * .15));
		slider->draw.where[0].x = x;
	}
	jlgr_sprite_redraw(jlgr, spr, &slider->draw);
}*/

//static void jlgr_gui_slider_singleloop(void* jl, la_ro_t* spr) {
//	jlgr_input_do(jl->jlgr, JL_INPUT_PRESS, jlgr_gui_slider_touch, spr);
//}

//static void jlgr_gui_slider_doubleloop(void* jl, la_ro_t* spr) {
//	jlgr_input_do(jl->jlgr, JL_INPUT_PRESS, jlgr_gui_slider_touch, spr);
//}

/*static void jlgr_gui_slider_draw(void* d2, uint8_t resize, void* data){
	la_window_t* jlgr = d2;
	la_gui_slider_draw* slider = data;

	la_rect_t rc = { 0.005, 0.005, .99, la_ro_ar(jlgr) - .01 };
	la_rect_t rc1 = { 0.0012, 0.0012, (la_ro_ar(jlgr) * .5) + .0075,
		la_ro_ar(jlgr) - .0024};
	la_rect_t rc2 = { 0.005, 0.005, (la_ro_ar(jlgr) * .5) -.001,
		la_ro_ar(jlgr) - .01};
	float colors[] = { .06f, .04f, 0.f, 1.f };

	la_window_clear(.01, .08, 0., 1.);
	jlgr_vo_set_image(jlgr, &(slider->vo[0]), rc, jlgr->textures.font);
	jlgr_vo_txmap(jlgr, &(slider->vo[0]), 0, 16, 16, 235);
	jlgr_vo_set_image(jlgr, &(slider->vo[1]), rc2, jlgr->textures.game);
	jlgr_vo_txmap(jlgr, &(slider->vo[1]), 0, 16, 16, 16);
	
	jlgr_vo_set_rect(jlgr, &(slider->vo[2]), rc1, colors, 0);
	// Draw Sliders
	la_ro_draw(&(slider->vo[0]));
	// Draw Slide 1
	la_ro_move(&slider->vo[2], slider->where[0]);
	la_ro_draw(&slider->vo[2]);
	la_ro_move(&slider->vo[1], slider->where[0]);
	la_ro_draw(&slider->vo[1]);
	// Draw Slide 2
	la_ro_move(&slider->vo[2], slider->where[1]);
	la_ro_draw(&slider->vo[2]);
	la_ro_move(&slider->vo[1], slider->where[1]);
	la_ro_draw(&slider->vo[1]);
}*/

/**
 * Create a slider sprite.
 * THREAD: Drawing thread only.
 * @param jlgr: The library context.
 * @param sprite: Uninitialized sprite to initialize.
 * @param rectange: Area to put the slider in.
 * @param isdouble: 1 to select range, 0 to select a specific value.
 * @param x1: Pointer to a permanent location for the slider value.
 * @param x2: Pointer to a permanent location for the second slider
	value.  Ignored if #isdouble is 0.
 * @returns: The slider sprite.
**/
/*void jlgr_gui_slider(la_window_t* jlgr, la_ro_t* sprite, la_rect_t rectangle,
	uint8_t isdouble, float* x1, float* x2)
{
//	jlgr_sprite_loop_fnt jlgr_gui_slider_loop;

//	if(isdouble) {
//		jlgr_gui_slider_loop = jlgr_gui_slider_doubleloop;
//	}else{
//		jlgr_gui_slider_loop = jlgr_gui_slider_singleloop;
//	}

	la_gui_slider_main slider;

	slider.draw.where[0] = (la_v3_t) { 0., 0., 0. };
	slider.draw.where[1] = (la_v3_t) { 1. - (la_ro_ar(jlgr) * .075),
		0., 0. };
	slider.x1 = x1, slider.x2 = x2;
	(*slider.x1) = 0.;
	(*slider.x2) = 1.;
	slider.isRange = isdouble;

//	jlgr_sprite_init(jlgr, sprite, rectangle,
//		jlgr_gui_slider_loop, jlgr_gui_slider_draw,
//		&slider, sizeof(la_gui_slider_main),
//		&slider.draw, sizeof(la_gui_slider_draw));
}*/

/**
 * Draw a background on the screen
**/
void jlgr_draw_bg(la_window_t* jlgr, uint32_t tex, uint8_t w, uint8_t h, int16_t c) {
	jlgr_fill_image_set(jlgr, tex, w, h, c);
	jlgr_fill_image_draw(jlgr);
}

void jlgr_draw_loadingbar(la_window_t* jlgr, double loaded) {
	float colors[] = { 0., 1., 0., 1. };

	la_ro_plain_rect(jlgr, NULL, colors, .95, la_ro_ar(jlgr) * .45);
}

//TODO: MOVE
static void jlgr_draw_msge__(la_window_t* window) {
	float fc[4] = { 0.f, 0.f, 0.f, 1.f };

	jlgr_draw_bg(window, window->gui.msge.t, 16, 16, window->gui.msge.c);
	if(window->gui.msge.message[0])
		la_text_centered(window, window->gui.msge.message, 9./32., fc);
}

/**
 * Print message on the screen.
 * @param jlgr: The library context.
 * @param tex: The background texture.
 * @param c: The character map setting.
 * @param format: The message
 */
void jlgr_draw_msge(la_window_t* jlgr, uint32_t tex, uint8_t c, char* format, ...) {
	la_print("jlgr_draw_msge");
	if(format) {
		va_list arglist;

		// Print on screen.
		va_start(arglist, format);
		vsprintf(jlgr->gui.msge.message, format, arglist);
		va_end(arglist);
	}else{
		jlgr->gui.msge.message[0] = '\0';
	}
	jlgr->gui.msge.t = tex;
	jlgr->gui.msge.c = c;
	la_print("DRAW LOADSCREEN");
	
	jlgr_draw_msge__(jlgr);
	la_print("DREW LOADSCREEN");
}

/**
 * Re-draw/-size a slide button, and activate if it is pressed.
 * @param jlgr: The library context.
 * @param spr: The slide button sprite.
 * @param txt: The text to draw on the button.
**/
/*void jlgr_slidebtn_rsz(la_window_t* jlgr, la_ro_t * spr, const char* txt) {
	jlgr_draw_text_sprite(jlgr, spr, txt);
}*/

/**
 * Run the Slide Button loop. ( activated when pressed, moved when
 *  hovered over. ) - And Draw Slide Button.
 * @param 'jl': the libary context
 * @param 'spr': the Slide Button Sprite.
 * @param 'defaultx': the default x position of the button.
 * @param 'slidex': how much the x should change when hovered above.
 * @param 'prun': the function to run when pressed.
**/
/*void jlgr_slidebtn_loop(la_window_t* jlgr, la_ro_t * spr, float defaultx,
	float slidex, jlgr_fnct prun)
{
	spr->pr.cb.pos.x = defaultx;
//	if(jlgr_sprite_collide(jlgr, &jlgr->mouse.pr, &spr->pr)) {
//		jlgr_input_do(jlgr, JL_INPUT_PRESS, prun, NULL);
//		spr->pr.cb.pos.x = defaultx + slidex;
//	}
//	jlgr_sprite_draw(jlgr, spr);
}*/

/**
 * Draw a glow button, and activate if it is pressed.
 * @param 'jl': the libary context
 * @param 'spr': the sprite to draw
 * @param 'txt': the text to draw on the button.
 * @param 'prun': the function to run when pressed.
**/
/*void jlgr_glow_button_draw(la_window_t* jlgr, la_ro_t * spr,
	char *txt, jlgr_fnct prun)
{
//		jlgr_sprite_redraw(jlgr, spr);
//	jlgr_sprite_draw(jlgr, spr);
	if(jlgr_sprite_collide(jlgr, &jlgr->mouse.pr, &spr->pr)) {
		la_rect_t rc = { spr->pr.cb.pos.x, spr->pr.cb.pos.y,
			spr->pr.cb.ofs.x, spr->pr.cb.ofs.y };
		float glow_color[] = { 1., 1., 1., .25 };

		// Draw glow
		jlgr_vo_set_rect(jlgr, &jlgr->gl.temp_vo, rc, glow_color, 0);
		la_ro_draw(&jlgr->gl.temp_vo);
		// Description
		jlgr_text_draw(jlgr, txt,
			(la_v3_t)
				{0., la_ro_ar(jlgr) - .0625, 0.},
				jlgr->fontcolor, .05 });
		// Run if press
//		jlgr_input_do(jlgr, JL_INPUT_PRESS, prun, NULL);
	}
}*/

/**
 * Set the data string for a textbox.
 * @param jlgr: The library context.
 * @param string: The string to store to.
**/
void jlgr_gui_textbox_init(la_window_t* jlgr, la_buffer_t* string) {
	jlgr->gui.textbox.string = string;
}

/**
 * Check for keyboard input and store in string.  Do not call before
 *	jlgr_gui_textbox_init().
 * @param jlgr: The library context.
 * @returns 1: if return/enter is pressed.
 * @returns 0: if not.
**/
uint8_t jlgr_gui_textbox_loop(la_window_t* jlgr) {
	int i;

//	jlgr->gui.textbox.counter += jlgr->jl->time.psec;
	if(jlgr->gui.textbox.counter > .5) {
		jlgr->gui.textbox.counter -= .5;
		jlgr->gui.textbox.do_it = 1;
		if(jlgr->gui.textbox.cursor) jlgr->gui.textbox.cursor = 0;
		else jlgr->gui.textbox.cursor = 1;
	}else{
		jlgr->gui.textbox.do_it = 0;
	}
#if JL_PLAT == JL_PLAT_COMPUTER
//	jlgr_input_do(jlgr, JL_INPUT_JOYC, jlgr_gui_textbox_cursor__, NULL);
#endif
	for(i = 0; i < strlen(jlgr->input.text); i++) {
		la_buffer_ins(jlgr->gui.textbox.string,
			jlgr->input.text[i]);
	}
	if(jlgr->input.keyboard.h && jlgr->input.keyboard.p) {
		switch(jlgr->input.keyboard.k) {
		case '\b':
			if(jlgr->gui.textbox.string->curs == 0) return 0;
			jlgr->gui.textbox.string->curs--;
			la_buffer_del(jlgr->gui.textbox.string);
			break;
		case '\02':
			la_buffer_del(jlgr->gui.textbox.string);
			break;
		case '\n':
			return 1;
		default:
			break;
		}
	}
	return 0;
}

/**
 * Draw A Textbox.  Must be paired on main thread by jlgr_gui_textbox_loop().
 * @param jlgr: The library context.
 * @param rc: Dimensions to draw textbox.
*/
void jlgr_gui_textbox_draw(la_window_t* jlgr, la_rect_t rc){
	float cursor_color[] = { 0.1f, 0.1f, 0.1f, 1.f };

//(la_rect_t) {
//			rc.x + (jlgr->gui.textbox.string->curs * rc.h * .75),
//			rc.y, rc.h * .05, rc.h }
	if(jlgr->gui.textbox.cursor) {
		la_ro_plain_rect(jlgr, &jlgr->gl.temp_vo, cursor_color,
			rc.h * .05, rc.h);
		la_ro_draw(&jlgr->gl.temp_vo);
	}
	la_text(jlgr, (char*)(jlgr->gui.textbox.string->data));
//	jlgr_text_draw(jlgr, (char*)(jlgr->gui.textbox.string->data),
//		(la_v3_t) {rc.x, rc.y, 0.},
//		jlgr_draw_image(jl, 0, 0,
//			x + (h*((float)string->curs-.5)), y, h, h, 252, 1.);

}

/**
 * THREAD: Main thread.
 * Pop-Up a notification bar.
 * @param jl: the libary context
 * @param notification: The message to display.
*/
void jlgr_notify(la_window_t* jlgr, const char* notification, ...) {
	char message[256];
	va_list arglist;

	va_start( arglist, notification );
	vsprintf( message, notification, arglist );
	va_end( arglist );

	la_safe_set_string(&jlgr->protected.notification.message, message);
	la_safe_set_float(&jlgr->protected.notification.timeTilVanish, 4.5);
}

void _jlgr_loopa(la_window_t* jlgr) {
	float time_until_vanish = la_safe_get_float(
		&jlgr->protected.notification.timeTilVanish);

	// Notifications:
	if(time_until_vanish > 0.f) {
		if(time_until_vanish > .5) {
			float color[] = { 1., 1., 1., 1. };
			la_text_centered(jlgr, la_safe_get_string(
				&jlgr->protected.notification.message),0,color);
		}else{
			float color[] = { 1., 1., 1., (time_until_vanish / .5)};
			la_text_centered(jlgr, la_safe_get_string(
				&jlgr->protected.notification.message),0,color);
		}
		la_safe_set_float(&jlgr->protected.notification.timeTilVanish,
			time_until_vanish - jlgr->psec);
	}
#if JL_PLAT == JL_PLAT_COMPUTER
	// Draw mouse
	jlgr_mouse_draw__(jlgr);
#endif
}

#endif
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

LV_IMG_DECLARE(img_arrow_down)
LV_IMG_DECLARE(img_large_gift)
LV_IMG_DECLARE(img_award)
LV_IMG_DECLARE(img_lock)
LV_IMG_DECLARE(img_wifi)
LV_IMG_DECLARE(img_tik)
LV_IMG_DECLARE(img_close)
LV_IMG_DECLARE(img_person)
LV_IMG_DECLARE(img_person_new)

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_disp_t* hal_init(lv_coord_t w, lv_coord_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t *arrowIcon;

#define CANVAS_WIDTH  200
#define CANVAS_HEIGHT  150

void moveArrow(void *obj, int32_t y) {
	lv_obj_set_y((lv_obj_t*) obj, y);
}

void returnBackArrow(lv_anim_t *anim) {
//	lv_anim_set_values(anim, 60, -70);
//	lv_anim_set_time(anim, 100);
//	lv_anim_start(anim);
}

void startAnimationArrow() {
	lv_obj_set_pos(arrowIcon, 0, -70);

	lv_anim_t anim;
	lv_anim_init(&anim);
	lv_anim_set_var(&anim, arrowIcon);
	lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t) moveArrow);
	lv_anim_set_time(&anim, 4000);
	lv_anim_set_values(&anim, -70, 60);
	lv_anim_set_ready_cb(&anim, returnBackArrow);
	lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
	lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);

	lv_anim_start(&anim);
}

static void event_handler(lv_event_t *e) {
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *d = lv_event_get_user_data(e);

	if (code == LV_EVENT_CLICKED) {
		lv_obj_clear_flag(d, LV_OBJ_FLAG_HIDDEN);
	}
}

static void event_handler2(lv_event_t *e) {
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *d = lv_event_get_user_data(e);

	if (code == LV_EVENT_CLICKED) {
		lv_obj_add_flag(d, LV_OBJ_FLAG_HIDDEN);
	}
}

static void ta_event_cb(lv_event_t *e) {
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED) {
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}

	if (code == LV_EVENT_DEFOCUSED) {
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}

	else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
		lv_indev_reset(NULL, ta); /*To forget the last clicked object to make it focusable again*/
	}
}

static void lv_keyboard_btn(lv_event_t *e) {
	/*Create a keyboard to use it with an of the text areas*/
	lv_obj_t *kb = lv_event_get_user_data(e);
	lv_event_code_t code = lv_event_get_code(e);

	if (code == LV_EVENT_CLICKED) {
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}

//	lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
}

static void fade_anim_cb(void *obj, int32_t v) {
	lv_obj_set_style_opa(obj, v, 0);
}

static void fade_in_anim_ready(lv_anim_t *a) {
	lv_obj_remove_local_style_prop(a->var, LV_STYLE_OPA, 0);
}

int main(int argc, char **argv) {
	(void) argc; /*Unused*/
	(void) argv; /*Unused*/

	/*Initialize LVGL*/
	lv_init();

	/*Create a default group for keyboard navigation*/
	lv_group_set_default(lv_group_create());

	/*Initialize the HAL (display, input devices, tick) for LVGL*/
	hal_init(480, 272);

	lv_obj_t *screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_base_dir(screen, LV_BASE_DIR_RTL, LV_STATE_DEFAULT);

	lv_obj_t *container1 = lv_obj_create(screen);
	lv_obj_set_size(container1, 480, 28);
	lv_obj_set_scrollbar_mode(container1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(container1, LV_OBJ_FLAG_SCROLLABLE);

	static lv_style_t styleContainer1;
	lv_style_init(&styleContainer1);
	lv_style_set_bg_color(&styleContainer1, lv_color_hex(0xFF202020));
	lv_style_set_align(&styleContainer1, LV_ALIGN_TOP_MID);
	lv_style_set_radius(&styleContainer1, 0);
	lv_style_set_border_width(&styleContainer1, 0);
	lv_style_set_pad_left(&styleContainer1, 15);
	lv_style_set_pad_right(&styleContainer1, 15);
	lv_obj_add_style(container1, &styleContainer1, LV_STATE_DEFAULT);

	lv_obj_t *w_1 = lv_label_create(container1);
//    lv_obj_set_style_text_font(w_1, &font_icon_16, LV_STATE_DEFAULT);
	lv_label_set_text(w_1, LV_SYMBOL_WIFI);
	lv_obj_set_style_text_color(w_1, lv_color_hex(0xFFFFFF), LV_STATE_CHECKED);
	lv_obj_set_style_text_color(w_1, lv_color_hex(0x888888), LV_STATE_DEFAULT);
	lv_obj_set_style_align(w_1, LV_ALIGN_RIGHT_MID, LV_STATE_DEFAULT);
//    lv_obj_align(w_1,LV_ALIGN_OUT_LEFT_MID, -10, 0);

	lv_obj_t *time = lv_label_create(container1);
	lv_obj_set_style_text_font(time, &iran_yekan_regular_18, LV_STATE_DEFAULT);
	lv_label_set_text(time, "12:14");
	lv_obj_set_style_base_dir(time, LV_BASE_DIR_LTR, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(time, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
	lv_obj_set_align(time, LV_ALIGN_LEFT_MID);

	lv_obj_t *date = lv_label_create(container1);
	lv_obj_set_style_text_font(date, &iran_yekan_regular_18, LV_STATE_DEFAULT);
	lv_label_set_text(date, "1402/2/30");
	lv_obj_set_style_base_dir(date, LV_BASE_DIR_LTR, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(date, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
	lv_obj_align_to(date, time, LV_ALIGN_OUT_RIGHT_MID, 16, 0);

	lv_obj_t *daysOfWeek = lv_label_create(container1);
	lv_obj_set_style_text_font(daysOfWeek, &iran_yekan_regular_18,
			LV_STATE_DEFAULT);
	lv_label_set_text(daysOfWeek, "دوشنبه");
	lv_obj_set_style_text_color(daysOfWeek, lv_color_hex(0xFFFFFF),
			LV_STATE_DEFAULT);
	lv_obj_align_to(daysOfWeek, date, LV_ALIGN_OUT_RIGHT_MID, 8, 0);

	lv_obj_t *container2 = lv_obj_create(screen);
//	lv_obj_set_flex_flow(container2, LV_FLEX_FLOW_COLUMN);

	lv_obj_set_size(container2, 480, 244);
//	lv_obj_set_style_flex_cross_place(container2, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
//	lv_obj_set_style_flex_cross_place(container2, LV_FLEX_ALIGN_END,
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_flex_main_place(container2, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(container2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(container2, lv_color_hex(0xFFEDEDED),
			LV_STATE_DEFAULT);
	lv_obj_set_style_align(container2, LV_ALIGN_BOTTOM_MID, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(container2, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(container2, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(container2, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(container2, 27, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(container2, 27, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(container2, 0, LV_STATE_DEFAULT);

	lv_obj_t *img_1 = lv_img_create(container2);
	lv_img_set_src(img_1, &img_person_new);
	lv_obj_align(img_1, LV_ALIGN_TOP_RIGHT, -4, 12);

	lv_obj_t *name = lv_label_create(container2);
	lv_obj_set_style_text_font(name, &iran_yekan_regular_18, LV_STATE_DEFAULT);
	lv_label_set_text(name, "علی نخعی شاه محمود");
	lv_obj_align_to(name, img_1, LV_ALIGN_OUT_LEFT_MID, -4, -2);

//		lv_obj_t *img_2 = lv_img_create(container2);
//		lv_img_set_src(img_2, &img_wifi);
//		lv_obj_align(img_2, LV_ALIGN_TOP_LEFT, -12, 12);

	lv_obj_t *btn_1 = lv_btn_create(container2);
	lv_obj_set_style_radius(btn_1, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(btn_1, LV_OPA_30, LV_STATE_DEFAULT);
	lv_obj_set_size(btn_1, 200, 60);

	lv_obj_align(btn_1, LV_ALIGN_CENTER, 0, -20);

	lv_obj_t *label_btn_1 = lv_label_create(btn_1);
	lv_obj_set_style_text_font(label_btn_1, &iran_yekan_regular_22,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_btn_1, "شروع به کار");
	lv_obj_set_style_text_color(label_btn_1, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);

	lv_obj_center(label_btn_1);

	lv_obj_t *btn_2 = lv_btn_create(container2);
	lv_obj_set_style_radius(btn_2, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(btn_2, LV_OPA_30, LV_STATE_DEFAULT);
	lv_obj_set_size(btn_2, 120, 50);
	lv_obj_t *label_btn_2 = lv_label_create(btn_2);
	lv_obj_set_style_text_font(label_btn_2, &iran_yekan_regular_22,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_btn_2, "تنظیمات");
	lv_obj_set_style_text_color(label_btn_2, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_btn_2);

	lv_obj_align_to(btn_2, btn_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

	lv_obj_t *dialog = lv_obj_create(screen);
	lv_obj_set_size(dialog, 480, 246);
	lv_obj_set_style_bg_color(dialog, lv_color_hex(0x00000), LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(dialog, LV_OPA_30, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(dialog, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(dialog, 0, LV_STATE_DEFAULT);
	lv_obj_align(dialog, LV_ALIGN_BOTTOM_MID, 0, 0);

	lv_obj_add_flag(dialog, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *box = lv_obj_create(dialog);
	lv_obj_set_style_pad_all(box, 8, LV_STATE_DEFAULT);
	lv_obj_set_size(box, 240, 220);
	lv_obj_center(box);

	lv_obj_t *title = lv_label_create(box);
	lv_obj_set_style_text_font(title, &iran_yekan_regular_18, LV_STATE_DEFAULT);
	lv_label_set_text(title, "تنظیمات");
	lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);

	lv_obj_t *box_btn_1 = lv_btn_create(box);

	lv_obj_set_size(box_btn_1, 150, 40);
	lv_obj_set_style_radius(box_btn_1, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(box_btn_1, LV_OPA_20, LV_STATE_DEFAULT);

	lv_obj_align(box_btn_1, LV_ALIGN_CENTER, 0, -20);

	lv_obj_t *label_box_btn_1 = lv_label_create(box_btn_1);
	lv_obj_set_style_text_font(label_box_btn_1, &iran_yekan_regular_18,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_box_btn_1, "وای فای");
	lv_obj_set_style_text_color(label_box_btn_1, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_box_btn_1);

	lv_obj_align_to(box_btn_1, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 16);

	lv_obj_t *box_btn_2 = lv_btn_create(box);

	lv_obj_set_size(box_btn_2, 150, 40);
	lv_obj_set_style_radius(box_btn_2, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(box_btn_2, LV_OPA_20, LV_STATE_DEFAULT);

	lv_obj_align(box_btn_2, LV_ALIGN_CENTER, 0, -20);

	lv_obj_t *label_box_btn_2 = lv_label_create(box_btn_2);
	lv_obj_set_style_text_font(label_box_btn_2, &iran_yekan_regular_18,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_box_btn_2, "احراز هویت");
	lv_obj_set_style_text_color(label_box_btn_2, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_box_btn_2);

	lv_obj_align_to(box_btn_2, box_btn_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

	lv_obj_t *exit = lv_btn_create(box);

	lv_obj_set_size(exit, 90, 34);
	lv_obj_set_style_radius(exit, 8, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(exit, LV_OPA_20, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(exit, lv_color_hex(0xF66547), LV_STATE_DEFAULT);

	lv_obj_align(exit, LV_ALIGN_BOTTOM_MID, 0, 0);

	lv_obj_t *label_exit = lv_label_create(exit);
	lv_obj_set_style_text_font(label_exit, &iran_yekan_regular_16,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_exit, "بستن");
	lv_obj_set_style_text_color(label_exit, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_exit);

	lv_obj_add_event(btn_2, event_handler, LV_EVENT_ALL, dialog);
	lv_obj_add_event(exit, event_handler2, LV_EVENT_ALL, dialog);

	lv_obj_t *ready_to_work = lv_obj_create(screen);
	lv_obj_set_size(ready_to_work, 480, 244);
	lv_obj_align(ready_to_work, LV_ALIGN_BOTTOM_MID, 0, 0);
	lv_obj_set_style_radius(ready_to_work, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ready_to_work, 0, LV_STATE_DEFAULT);
	lv_obj_clear_flag(ready_to_work, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_all(ready_to_work, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ready_to_work, 20, LV_STATE_DEFAULT);

	lv_obj_t *box12_1 = lv_obj_create(ready_to_work);
	lv_obj_set_size(box12_1, 480, 100);
//	lv_obj_set_style_bg_opa(box12_1, LV_OPA_20, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(box12_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box12_1, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(box12_1, 20, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_hor(box12_1, 50, LV_STATE_DEFAULT);

//	lv_obj_set_style_bg_color(box12_1, lv_color_hex(0xF66547), LV_STATE_DEFAULT);
	lv_obj_set_flex_flow(box12_1, LV_FLEX_FLOW_ROW);
	lv_obj_set_style_flex_main_place(box12_1, LV_FLEX_ALIGN_SPACE_BETWEEN,
			LV_STATE_DEFAULT);
	lv_obj_set_style_flex_cross_place(box12_1, LV_FLEX_ALIGN_CENTER,
			LV_STATE_DEFAULT);
	lv_obj_clear_flag(box12_1, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_t *box_btn_12 = lv_btn_create(box12_1);

	lv_obj_set_size(box_btn_12, 100, 70);
	lv_obj_set_style_radius(box_btn_12, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(box_btn_12, LV_OPA_30, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(box_btn_12, lv_color_hex(0xF66547),
//			LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box_btn_12, 10, 0);

//	lv_obj_align(box_btn_12, LV_ALIGN_TOP_RIGHT, 0, 0);

	lv_obj_t *label_box_btn_12 = lv_label_create(box_btn_12);
	lv_obj_set_style_text_font(label_box_btn_12, &iran_yekan_regular_16,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_box_btn_12, "بارکد");
	lv_obj_set_style_text_color(label_box_btn_12, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_box_btn_12);

	lv_obj_t *box12 = lv_obj_create(box_btn_12);
	lv_obj_set_size(box12, 15, 15);
	lv_obj_set_style_bg_color(box12, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(box12, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box12, 40, LV_STATE_DEFAULT);
	lv_obj_clear_flag(box12, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_align(box12, LV_ALIGN_TOP_RIGHT, 10, -6);

	lv_obj_t *box_btn_13 = lv_btn_create(box12_1);

	lv_obj_set_size(box_btn_13, 100, 70);
	lv_obj_set_style_radius(box_btn_13, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(box_btn_13, LV_OPA_20, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(box_btn_13, lv_color_hex(0xF66547),
			LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box_btn_13, 10, 0);

//	lv_obj_align_to(box_btn_13, box_btn_12, LV_ALIGN_OUT_LEFT_MID, -4, 0);

	lv_obj_t *label_box_btn_13 = lv_label_create(box_btn_13);
	lv_obj_set_style_text_font(label_box_btn_13, &iran_yekan_regular_16,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_box_btn_13, "نمره کاربر");
	lv_obj_set_style_text_color(label_box_btn_13, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_box_btn_13);

	lv_obj_t *box13 = lv_obj_create(box_btn_13);
	lv_obj_set_size(box13, 15, 15);
	lv_obj_set_style_bg_color(box13, lv_color_hex(0xF66547), LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(box13, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box13, 40, LV_STATE_DEFAULT);
	lv_obj_clear_flag(box13, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_align(box13, LV_ALIGN_TOP_RIGHT, 10, -6);

	lv_obj_t *box_btn_14 = lv_btn_create(box12_1);

	lv_obj_set_size(box_btn_14, 100, 70);
	lv_obj_set_style_radius(box_btn_14, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(box_btn_14, LV_OPA_20, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(box_btn_14, lv_color_hex(0xF66547),
			LV_STATE_DEFAULT);
	lv_obj_set_style_radius(box_btn_14, 10, 0);

//	lv_obj_align_to(box_btn_14, box_btn_13, LV_ALIGN_OUT_LEFT_MID, -4, 0);

	lv_obj_t *label_box_btn_14 = lv_label_create(box_btn_14);
	lv_obj_set_style_text_font(label_box_btn_14, &iran_yekan_regular_16,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_box_btn_14, "تست برنامه");
	lv_obj_set_style_text_color(label_box_btn_14, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_box_btn_14);

//	lv_obj_t *box14 = lv_obj_create(box_btn_14);
//	lv_obj_set_size(box14, 15, 15);
//	lv_obj_set_style_bg_color(box14, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(box14, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(box14, 40, LV_STATE_DEFAULT);
//	lv_obj_clear_flag(box14, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_align(box14, LV_ALIGN_TOP_RIGHT, 10, -6);

	lv_anim_t a;
	lv_anim_init(&a);
	lv_anim_set_var(&a, box13);
	lv_anim_set_values(&a, 0, LV_OPA_COVER);
	lv_anim_set_exec_cb(&a, fade_anim_cb);
	lv_anim_set_ready_cb(&a, fade_in_anim_ready);
	lv_anim_set_time(&a, 1000);
	lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
	lv_anim_set_delay(&a, 0);
	lv_anim_start(&a);

//	lv_obj_del_anim_ready_cb(&a);

	lv_obj_t *sendInformation = lv_btn_create(ready_to_work);
	lv_obj_set_style_radius(sendInformation, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(sendInformation, LV_OPA_30, LV_STATE_DEFAULT);
	lv_obj_set_size(sendInformation, 120, 50);
	lv_obj_t *label_sendInformation = lv_label_create(sendInformation);
	lv_obj_set_style_text_font(label_sendInformation, &iran_yekan_regular_22,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_sendInformation, "تنظیمات");
	lv_obj_set_style_text_color(label_sendInformation, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_sendInformation);
	lv_obj_align(sendInformation, LV_ALIGN_BOTTOM_MID, 0, -60);


	lv_obj_t *exit_ready = lv_btn_create(ready_to_work);

	lv_obj_set_size(exit_ready, 90, 34);
	lv_obj_set_style_radius(exit_ready, 8, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(exit_ready, LV_OPA_20, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(exit_ready, lv_color_hex(0xF66547), LV_STATE_DEFAULT);

	lv_obj_align_to(exit_ready, sendInformation, LV_ALIGN_OUT_BOTTOM_MID, 0, 15);

	lv_obj_t *label_exit_ready = lv_label_create(exit_ready);
	lv_obj_set_style_text_font(label_exit_ready, &iran_yekan_regular_16,
			LV_STATE_DEFAULT);
	lv_label_set_text(label_exit_ready, "بستن");
	lv_obj_set_style_text_color(label_exit_ready, lv_color_hex(0x00000),
			LV_STATE_DEFAULT);
	lv_obj_center(label_exit_ready);

//	lv_obj_t *authentication = lv_obj_create(screen);
//	lv_obj_set_size(authentication, 480, 246);
//	lv_obj_align(authentication, LV_ALIGN_BOTTOM_MID, 0, 0);
//	lv_obj_set_style_radius(authentication, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(authentication, 0, LV_STATE_DEFAULT);
//
//	lv_obj_t *box1 = lv_obj_create(authentication);
//	lv_obj_set_size(box1, 100, 100);
//	lv_obj_set_style_radius(box1, 50, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(box1, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(box1, lv_color_hex(0x1F93FF), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(box1, LV_OPA_20, LV_STATE_DEFAULT);
//	lv_obj_align(box1, LV_ALIGN_CENTER, 0, -40);
//
//	lv_obj_t *auth_img = lv_img_create(box1);
//	lv_img_set_src(auth_img, &img_person_new);
//	lv_obj_align(auth_img, LV_ALIGN_CENTER, 0, 0);
//
//	lv_obj_t *authenticatio_name = lv_label_create(authentication);
//	lv_obj_set_style_text_font(authenticatio_name, &iran_yekan_regular_22,
//			LV_STATE_DEFAULT);
//	lv_obj_set_size(authenticatio_name, 210, LV_SIZE_CONTENT);
//	lv_label_set_text(authenticatio_name,
//			"لطفا کارت شناسایی خود را نزدیک دستگاه کنید");
//	lv_obj_set_style_text_align(authenticatio_name, LV_TEXT_ALIGN_CENTER,
//			LV_STATE_DEFAULT);
//	lv_obj_align_to(authenticatio_name, auth_img, LV_ALIGN_OUT_BOTTOM_MID, 0,
//			40);
//
//	lv_obj_t *back = lv_btn_create(authentication);
//
//	lv_obj_set_size(back, 110, 40);
//	lv_obj_set_style_radius(back, 8, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(back, LV_OPA_20, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(back, lv_color_hex(0xF66547), LV_STATE_DEFAULT);
//
//	lv_obj_align(back, LV_ALIGN_TOP_RIGHT, 0, 0);
//
//	lv_obj_t *label_back = lv_label_create(back);
//	lv_obj_set_style_text_font(label_back, &iran_yekan_regular_16,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(label_back, "بازگشت");
//	lv_obj_set_style_text_color(label_back, lv_color_hex(0x00000),
//			LV_STATE_DEFAULT);
//	lv_obj_center(label_back);

//	lv_obj_t *selectWifi = lv_obj_create(screen);
//	lv_obj_set_size(selectWifi, 480, 244);
//	lv_obj_set_style_radius(selectWifi, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(selectWifi, 0, LV_STATE_DEFAULT);
//	lv_obj_clear_flag(selectWifi, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_style_bg_color(selectWifi, lv_color_hex(0xFFEDEDED),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_align(selectWifi, LV_ALIGN_BOTTOM_MID, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(selectWifi, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(selectWifi, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(selectWifi, 0, LV_STATE_DEFAULT);
//
//	lv_obj_t *label_wifi = lv_label_create(selectWifi);
//	lv_obj_set_style_text_font(label_wifi, &iran_yekan_regular_22,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(label_wifi, "لیست مودم ها");
//	lv_obj_set_style_text_color(label_wifi, lv_color_hex(0x00000),
//			LV_STATE_DEFAULT);
//	lv_obj_align(label_wifi, LV_ALIGN_TOP_RIGHT, -12, 0);
//
//	lv_obj_t *wifi_list = lv_list_create(selectWifi);
//
//	lv_obj_set_size(wifi_list, 480, 200);
//	lv_obj_align(wifi_list, LV_ALIGN_BOTTOM_MID, 0, 0);
//	lv_obj_set_scrollbar_mode(wifi_list, LV_SCROLLBAR_MODE_ON);
//	lv_obj_set_scroll_dir(wifi_list, LV_DIR_VER);
//	lv_obj_set_style_pad_left(wifi_list, 50, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_right(wifi_list, 50, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(wifi_list, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(wifi_list, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(wifi_list, lv_color_hex(0xFFEDEDED),
//			LV_STATE_DEFAULT);
//
//	static lv_style_t style_btn;
//	lv_style_init(&style_btn);
//	lv_style_set_bg_color(&style_btn, lv_color_hex(0xD8D8D8));
//	static lv_style_t style_ssid;
//	lv_style_init(&style_ssid);
//	lv_style_set_text_font(&style_ssid, &iran_yekan_regular_16);
//
//
//	lv_obj_t *dialog2 = lv_obj_create(screen);
//	lv_obj_set_size(dialog2, 480, 246);
//	lv_obj_set_style_bg_color(dialog2, lv_color_hex(0x00000), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(dialog2, LV_OPA_30, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(dialog2, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(dialog2, 0, LV_STATE_DEFAULT);
//	lv_obj_align(dialog2, LV_ALIGN_BOTTOM_MID, 0, 0);
//	lv_obj_set_style_pad_all(dialog2, 0, LV_STATE_DEFAULT);
//
//	lv_obj_add_flag(dialog2, LV_OBJ_FLAG_HIDDEN);
//
//
//	lv_obj_t *box2 = lv_obj_create(dialog2);
//	lv_obj_set_style_pad_all(box2, 8, LV_STATE_DEFAULT);
//	lv_obj_set_size(box2, 280, 180);
//	lv_obj_align(box2, LV_ALIGN_CENTER, 0, -15);
//
//	lv_obj_t *kb = lv_keyboard_create(dialog2);
//	lv_obj_set_width(kb, 480);
//	lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
//			lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//
//
//
//
//	lv_obj_t *title_box2 = lv_label_create(box2);
//	lv_obj_set_style_text_font(title_box2, &iran_yekan_regular_18,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(title_box2, "پسورد");
//	lv_obj_align(title_box2, LV_ALIGN_TOP_MID, 0, 0);
//
//
//	lv_obj_t * ta;
//	    ta = lv_textarea_create(box2);
////	    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 0);
//	    lv_obj_align_to(ta, title_box2, LV_ALIGN_OUT_BOTTOM_MID, 10, 4);
//	    lv_obj_add_event(ta, ta_event_cb, LV_EVENT_ALL, kb);
//	    lv_textarea_set_placeholder_text(ta, "Password 8 character");
//	    lv_obj_set_size(ta, 240, 40);
//	    lv_obj_set_style_base_dir(ta, LV_BASE_DIR_LTR, LV_STATE_DEFAULT);
//
//
//	lv_obj_t *exit_box2 = lv_btn_create(box2);
//
//	lv_obj_set_size(exit_box2, 90, 34);
//	lv_obj_set_style_radius(exit_box2, 8, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(exit_box2, LV_OPA_20, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(exit_box2, lv_color_hex(0xF66547),
//			LV_STATE_DEFAULT);
//
//	lv_obj_align(exit_box2, LV_ALIGN_BOTTOM_MID, -50, 0);
//
//	lv_obj_t *label_exit_box2 = lv_label_create(exit_box2);
//	lv_obj_set_style_text_font(label_exit_box2, &iran_yekan_regular_16,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(label_exit_box2, "بستن");
//	lv_obj_set_style_text_color(label_exit_box2, lv_color_hex(0x00000),
//			LV_STATE_DEFAULT);
//	lv_obj_center(label_exit_box2);
//
//	lv_obj_t *submit_box2 = lv_btn_create(box2);
//
//	lv_obj_set_size(submit_box2, 90, 34);
//	lv_obj_set_style_radius(submit_box2, 8, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(submit_box2, LV_OPA_20, LV_STATE_DEFAULT);
//
////	lv_obj_align(submit_box2, LV_ALIGN_BOTTOM_MID, 0, 0);
//	lv_obj_align_to(submit_box2, exit_box2, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
//
//	lv_obj_t *label_submit_box2 = lv_label_create(submit_box2);
//	lv_obj_set_style_text_font(label_submit_box2, &iran_yekan_regular_16,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(label_submit_box2, "تایید");
//	lv_obj_set_style_text_color(label_submit_box2, lv_color_hex(0x00000),
//			LV_STATE_DEFAULT);
//	lv_obj_center(label_submit_box2);
//
//	lv_obj_add_event(submit_box2, event_handler2, LV_EVENT_ALL, dialog2);
//	lv_obj_add_event(exit_box2, event_handler2, LV_EVENT_ALL, dialog2);
//
//	for (int i = 0; i < 20; i++) {
//		lv_obj_t *obj = lv_obj_class_create_obj(&lv_list_btn_class, wifi_list);
//		lv_obj_class_init_obj(obj);
//		lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
//		lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
//		lv_obj_set_style_border_width(obj, 0, LV_STATE_DEFAULT);
//		lv_obj_set_style_bg_color(obj, lv_color_hex(0x1F93FF),
//				LV_STATE_DEFAULT);
//		lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000),
//				LV_STATE_PRESSED);
//		lv_obj_set_style_bg_opa(obj, LV_OPA_20, LV_STATE_DEFAULT);
//		lv_obj_set_style_margin_all(obj, 6, LV_STATE_DEFAULT);
//		lv_obj_set_height(obj, 46);
//		lv_obj_set_style_radius(obj, 8, LV_STATE_DEFAULT);
//		lv_obj_t *label = lv_label_create(obj);
//		lv_obj_set_style_text_font(label, &iran_yekan_regular_16,
//				LV_STATE_DEFAULT);
//		lv_label_set_text(label, "لیست مودم ها");
//		lv_obj_set_style_text_color(label, lv_color_hex(0x00000),
//				LV_STATE_DEFAULT);
//
//		lv_obj_t *icon = lv_label_create(obj);
//		lv_obj_set_pos(icon, 0, 10);
//		lv_label_set_text(icon, LV_SYMBOL_WIFI);
//		lv_obj_set_style_text_color(icon, lv_color_hex(0x00000),
//				LV_STATE_DEFAULT);
//		lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN,
//				LV_STATE_DEFAULT);
//		lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER,
//				LV_STATE_DEFAULT);
//
//		lv_obj_add_event(obj, lv_keyboard_btn, LV_EVENT_ALL, dialog2);
//	}

//	        if (i == 0) {
//	            lv_obj_add_state(screen_1_list_1_item, LV_STATE_CHECKED);
//	        }
//	        lv_obj_set_style_radius(screen_1_list_1_item, 5, LV_STATE_CHECKED);
//	        lv_obj_set_width(screen_1_list_1_item, lv_pct(80));
//	        lv_obj_align(screen_1_list_1_item, LV_ALIGN_CENTER, 0, 0);// set width to fill parent container
//	        lv_obj_t *lab1 = lv_label_create(screen_1_list_1_item);
//	        lv_label_set_text_fmt(lab1, "%s", "f");
//	        lv_obj_add_style(lab1, &style_ssid, LV_STATE_DEFAULT);
//	        lv_obj_set_align(lab1, LV_ALIGN_CENTER);
//	//        lv_obj_set_size(lab1,lv_pct(100)-10,10);
////	        lv_obj_set_pos(lab1, lv_pct(50), 0);
////	        lv_obj_set_width(lab1, lv_pct(100) - 10);
//
//	        lv_obj_t *lab2 = lv_label_create(screen_1_list_1_item);
//	        lv_label_set_text(lab2, LV_SYMBOL_WIFI);
//	        lv_obj_set_align(lab2, LV_ALIGN_BOTTOM_RIGHT);
//	        lv_obj_set_pos(lab2, lv_obj_get_width(screen_1_list_1_item), -5); // align to bottom right corner
//	}

//Write codes screen_1_label_1
//	    ui.screen_1_label_1 = lv_label_create(ui.screen_1_cont_1);
//	    lv_obj_set_scrollbar_mode(ui.screen_1_label_1, LV_SCROLLBAR_MODE_OFF);
//	    lv_label_set_text(ui.screen_1_label_1, "لیست وای فای ");
//	    lv_obj_set_pos(ui.screen_1_label_1, 0, 10);
//	    lv_label_set_long_mode(ui.screen_1_label_1, LV_LABEL_LONG_WRAP);
//	    lv_obj_set_align(ui.screen_1_label_1, LV_ALIGN_TOP_MID);
//	    lv_obj_set_style_text_font(ui.screen_1_label_1, &iran_yekan_regular_22, LV_STATE_DEFAULT

//	lv_obj_t *input_phone = lv_obj_create(container2);
//	lv_obj_set_size(input_phone, 221, 48);
//	lv_obj_set_pos(input_phone, 0, 5);
//	lv_obj_set_style_bg_color(input_phone, lv_color_hex(0x000000),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(input_phone, 12, LV_STATE_DEFAULT);
//	lv_obj_align_to(input_phone,label_phone, LV_ALIGN_OUT_BOTTOM_MID, 0,10);
//
//	lv_obj_t *labelInputObj = lv_label_create(input_phone);
//	lv_obj_set_style_text_font(labelInputObj, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_text_color(labelInputObj, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_align(labelInputObj, LV_ALIGN_CENTER, LV_STATE_DEFAULT);
//	lv_label_set_text(labelInputObj, "09105002040");
//	lv_obj_set_style_text_letter_space(labelInputObj, 2, LV_STATE_DEFAULT);
//	lv_obj_set_scrollbar_mode(input_phone, LV_SCROLLBAR_MODE_OFF);

//=========================================>
//	lv_obj_t *img = lv_img_create(container2);
//	lv_img_set_src(img, &img_close);
//	lv_obj_align(img, LV_ALIGN_TOP_MID, 58, 12);
//
//	lv_obj_t *title = lv_label_create(container2);
//	lv_obj_set_style_text_font(title, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(title, "خرید ناموفق");
//	lv_obj_align_to(title, img, LV_ALIGN_OUT_LEFT_MID, -8, -2);
//
//	lv_obj_t *priceBox = lv_obj_create(container2);
//	lv_obj_set_size(priceBox, 320, 48);
//	lv_obj_set_scrollbar_mode(priceBox, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(priceBox, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_align(priceBox, LV_ALIGN_BOTTOM_LEFT, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_align(priceBox, LV_ALIGN_CENTER, 0, -12);
//
//	lv_obj_t *price = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(price, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(price, "5,000,000");
//	lv_obj_set_style_text_letter_space(price, 2, LV_STATE_DEFAULT);
//	lv_obj_align(price, LV_ALIGN_CENTER, 18, -2);
//
//	lv_obj_t *currency = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(currency, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(currency, "ریال");
//	lv_obj_align_to(currency, price, LV_ALIGN_OUT_LEFT_MID, -4, -2);
//
//	lv_obj_t *message = lv_label_create(container2);
//	lv_obj_set_style_text_font(message, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(message, "رمز نا معتبر است");
//	lv_obj_align_to(message, priceBox, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
//    lv_obj_set_style_text_color(message, lv_color_hex(0xD02D0B), LV_STATE_DEFAULT);

//=================================================>

//	lv_obj_t *img = lv_img_create(container2);
//	lv_img_set_src(img, &img_tik);
//	lv_obj_align(img, LV_ALIGN_TOP_MID, 48, 12);
//
//	lv_obj_t *title = lv_label_create(container2);
//	lv_obj_set_style_text_font(title, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(title, "خرید موفق");
//	lv_obj_align_to(title, img, LV_ALIGN_OUT_LEFT_MID, -8, 0);
//
//	lv_obj_t *priceBox = lv_obj_create(container2);
//	lv_obj_set_size(priceBox, 320, 48);
//	lv_obj_set_scrollbar_mode(priceBox, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(priceBox, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_align(priceBox, LV_ALIGN_BOTTOM_LEFT, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_align(priceBox, LV_ALIGN_CENTER, 0, -12);
//
//	lv_obj_t *price = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(price, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(price, "5,000,000");
//	lv_obj_set_style_text_letter_space(price, 2, LV_STATE_DEFAULT);
//	lv_obj_align(price, LV_ALIGN_CENTER, 18, -2);
//
//	lv_obj_t *currency = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(currency, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(currency, "ریال");
//	lv_obj_align_to(currency, price, LV_ALIGN_OUT_LEFT_MID, -4, -2);
//
//	lv_obj_t *question = lv_label_create(container2);
//	lv_obj_set_style_text_font(question, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(question, "چاپ رسید فروشنده؟");
//	lv_obj_align_to(question, priceBox, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
//
//	lv_obj_t *btn1 = lv_obj_create(container2);
//	lv_obj_set_size(btn1, 86, 32);
//	lv_obj_set_scrollbar_mode(btn1, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(btn1, lv_color_hex(0x01C4A4), LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(btn1, 5, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(btn1, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn1, 0, LV_STATE_DEFAULT);
//	lv_obj_align(btn1, LV_ALIGN_BOTTOM_MID, 46, -10);
//
//	lv_obj_t *textBtn1 = lv_label_create(btn1);
//	lv_obj_set_style_text_font(textBtn1, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(textBtn1, "تایید");
//	lv_obj_align(textBtn1, LV_ALIGN_CENTER,0,-3);
//	lv_obj_set_style_text_color(textBtn1, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);
//
//	lv_obj_t *btn2 = lv_obj_create(container2);
//	lv_obj_set_size(btn2, 86, 32);
//	lv_obj_set_scrollbar_mode(btn2, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(btn2, lv_color_hex(0xF66547), LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(btn2, 5, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(btn2, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn2, 0, LV_STATE_DEFAULT);
//	lv_obj_align_to(btn2, btn1, LV_ALIGN_OUT_LEFT_MID, -8, 0);
//
//	lv_obj_t *textBtn2 = lv_label_create(btn2);
//	lv_obj_set_style_text_font(textBtn2, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(textBtn2, "لغو");
//	lv_obj_align(textBtn2, LV_ALIGN_CENTER,0,-3);
//	lv_obj_set_style_text_color(textBtn2, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);

//================================================>

//	lv_obj_t *title = lv_label_create(container2);
//	lv_obj_set_style_text_font(title, &iran_yekan_regular_22, LV_STATE_DEFAULT);
//	lv_obj_set_style_text_color(title, lv_color_hex(0x323232),
//			LV_STATE_DEFAULT);
//	lv_obj_set_align(title, LV_ALIGN_TOP_MID);
//	lv_label_set_text(title, "مبلغ پرداختی");
//
//	lv_obj_t *mainPrice = lv_label_create(container2);
//	lv_obj_set_style_text_font(mainPrice, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_obj_align(mainPrice, LV_ALIGN_TOP_MID, 18, 25);
//	lv_obj_set_style_text_decor(mainPrice, LV_TEXT_DECOR_STRIKETHROUGH,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(mainPrice, "5,800,000");
//
//	lv_obj_t *currency1 = lv_label_create(container2);
//	lv_obj_set_style_text_font(currency1, &iran_yekan_regular_24,
//			LV_STATE_DEFAULT);
//	lv_obj_align_to(currency1, mainPrice, LV_ALIGN_OUT_LEFT_MID, 2, -1);
//	lv_label_set_text(currency1, "ریال");
//
//	lv_obj_t *priceBox = lv_obj_create(container2);
//	lv_obj_set_size(priceBox, 320, 48);
//	lv_obj_set_scrollbar_mode(priceBox, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(priceBox, lv_color_hex(0xFFFFFF),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(priceBox, 0, LV_STATE_DEFAULT);
//	lv_obj_align(priceBox, LV_ALIGN_CENTER, 0, -12);
//
//	lv_obj_t *finalPrice = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(finalPrice, &iran_yekan_regular_28,
//			LV_STATE_DEFAULT);
//	lv_obj_align(finalPrice, LV_ALIGN_CENTER, 18, -2);
//	lv_label_set_text(finalPrice, "5,000,000");
//
//	lv_obj_t *currency = lv_label_create(priceBox);
//	lv_obj_set_style_text_font(currency, &iran_yekan_regular_28,
//			LV_STATE_DEFAULT);
//	lv_obj_align_to(currency, finalPrice, LV_ALIGN_OUT_LEFT_MID, 2, -2);
//	lv_label_set_text(currency, "ریال");
//
//	lv_obj_t *titlePassword = lv_label_create(container2);
//	lv_obj_set_size(titlePassword, 320, LV_SIZE_CONTENT);
//	lv_obj_set_style_text_font(titlePassword, &iran_yekan_regular_28,
//			LV_STATE_DEFAULT);
//	lv_obj_align_to(titlePassword, priceBox, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
//	lv_obj_set_style_text_align(titlePassword, LV_TEXT_ALIGN_CENTER,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(titlePassword, "رمز خود را وارد کنید");
//
//	lv_obj_t *passwordBox = lv_obj_create(container2);
//	lv_obj_set_flex_flow(passwordBox, LV_FLEX_FLOW_ROW);
//	lv_obj_set_size(passwordBox, 130, LV_SIZE_CONTENT);
//	lv_obj_set_scrollbar_mode(passwordBox, LV_SCROLLBAR_MODE_OFF);
//	lv_obj_set_style_bg_color(passwordBox, lv_color_hex(0xFFEDEDED),
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(passwordBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(passwordBox, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(passwordBox, 0, LV_STATE_DEFAULT);
//	lv_obj_align_to(passwordBox, titlePassword, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
//
//	lv_obj_t *p1 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(p1, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_size(p1, 17, 17);
//	lv_obj_set_style_radius(p1, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p1, lv_color_hex(0xFFEDEDED), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(p1, 2, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_color(p1, lv_color_hex(0x000000), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p1, lv_color_hex(0x01E7C1), LV_STATE_CHECKED);
//
//	lv_obj_t *space1 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(space1, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_style_border_width(space1, 2, LV_STATE_DEFAULT);
//	lv_obj_set_size(space1, 4, 1);
//
//	lv_obj_t *p2 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(p2, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_size(p2, 17, 17);
//	lv_obj_set_style_radius(p2, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p2, lv_color_hex(0xFFEDEDED), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(p2, 2, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_color(p2, lv_color_hex(0x000000), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p2, lv_color_hex(0x01E7C1), LV_STATE_CHECKED);
//
//	lv_obj_t *space2 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(space2, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_style_border_width(space2, 2, LV_STATE_DEFAULT);
//	lv_obj_set_size(space2, 4, 1);
//
//	lv_obj_t *p3 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(p3, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_size(p3, 17, 17);
//	lv_obj_set_style_radius(p3, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p3, lv_color_hex(0xFFEDEDED), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(p3, 2, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_color(p3, lv_color_hex(0x000000), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p3, lv_color_hex(0x01E7C1), LV_STATE_CHECKED);
//
//	lv_obj_t *space3 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(space3, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_style_border_width(space3, 2, LV_STATE_DEFAULT);
//	lv_obj_set_size(space3, 4, 1);
//
//	lv_obj_t *p4 = lv_obj_create(passwordBox);
//	lv_obj_clear_flag(p4, LV_OBJ_FLAG_SCROLLABLE);
//	lv_obj_set_size(p4, 17, 17);
//	lv_obj_set_style_radius(p4, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p4, lv_color_hex(0xFFEDEDED), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(p4, 2, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_color(p4, lv_color_hex(0x000000), LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(p4, lv_color_hex(0x01E7C1), LV_STATE_CHECKED);

//====================================================>

//	lv_obj_t *circle = lv_obj_create(container2);
//	lv_obj_set_style_bg_color(circle, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(circle, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
//	lv_obj_align(circle, LV_ALIGN_TOP_RIGHT, 145, -74);
//	lv_obj_set_size(circle, 290, 286);
//
//	lv_obj_t *img = lv_img_create(circle);
//	lv_img_set_src(img, &img_large_gift);
//	lv_obj_align(img, LV_ALIGN_LEFT_MID, 43, 0);
//
//	lv_obj_t *text = lv_label_create(circle);
//	lv_obj_set_style_text_font(text, &iran_yekan_bold_24, LV_STATE_DEFAULT);
//	lv_obj_align_to(text, img, LV_ALIGN_OUT_BOTTOM_MID, -8, 15);
//	lv_label_set_text(text, "تبریک!");
//
//	lv_obj_t *box = lv_obj_create(container2);
//	lv_obj_set_style_bg_color(box, lv_color_hex(0x00000), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(box, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_flex_flow(box, LV_FLEX_FLOW_COLUMN, LV_STATE_DEFAULT);
//	lv_obj_set_style_pad_all(box, 2, LV_STATE_DEFAULT);
//	lv_obj_set_style_radius(box, 10, LV_STATE_DEFAULT);
//	lv_obj_align(box, LV_ALIGN_LEFT_MID, -8, -20);
//	lv_obj_set_size(box, 226, 68);
//
//	lv_obj_t *price = lv_label_create(box);
//	lv_obj_set_style_text_font(price, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(price, "55,555,000 ریال");
//	lv_obj_set_style_align(price, LV_ALIGN_TOP_MID, LV_STATE_DEFAULT);
//	lv_obj_set_style_text_color(price, lv_color_hex(0x01E7C1),
//			LV_STATE_DEFAULT);
//
//	lv_obj_t *off = lv_label_create(box);
//	lv_obj_set_style_text_font(off, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//	lv_label_set_text(off, "تخفیف");
//	lv_obj_set_style_align(off, LV_ALIGN_BOTTOM_MID, LV_STATE_DEFAULT);
//	lv_obj_set_style_text_color(off, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//
//	lv_obj_t *text_1 = lv_label_create(container2);
//	lv_obj_set_style_text_font(text_1, &iran_yekan_regular_20,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(text_1, "برای ادامه گزینه");
//	lv_obj_align_to(text_1, box, LV_ALIGN_OUT_BOTTOM_MID, 0, 15);
//
//	lv_obj_t *btn = lv_obj_create(container2);
//	lv_obj_set_style_bg_color(btn, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn, 0, LV_STATE_DEFAULT);
//	lv_obj_set_size(btn, 51, 28);
//	lv_obj_set_style_pad_all(btn, 0, LV_STATE_DEFAULT);
//	lv_obj_align_to(btn, text_1, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);
//	lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
//
//	lv_obj_t *btn_text = lv_label_create(btn);
//	lv_obj_set_style_text_font(btn_text, &iran_yekan_regular_20,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(btn_text, "تایید");
//	lv_obj_set_style_align(btn_text, LV_ALIGN_CENTER, LV_STATE_DEFAULT);
//	lv_obj_set_style_text_color(btn_text, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
//
//	lv_obj_t *text_2 = lv_label_create(container2);
//	lv_obj_set_style_text_font(text_2, &iran_yekan_regular_20,
//			LV_STATE_DEFAULT);
//	lv_label_set_text(text_2, "را بزنید");
//	lv_obj_align_to(text_2, btn, LV_ALIGN_OUT_LEFT_MID, -8, -2);

	lv_scr_load(screen);

//  lv_demo_widgets();
//	startAnimationArrow();
	while (1) {
		/* Periodically call the lv_task handler.
		 * It could be done in a timer interrupt or an OS task too.*/
		lv_timer_handler();
		usleep(5 * 1000);
	}

	return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) forLVGL
 */
static lv_disp_t* hal_init(lv_coord_t w, lv_coord_t h) {
	lv_disp_t *disp = lv_sdl_window_create(w, h);
	lv_indev_t *mouse = lv_sdl_mouse_create();
	lv_indev_set_group(mouse, lv_group_get_default());
	lv_indev_set_disp(mouse, disp);

	LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
	lv_obj_t *cursor_obj;
	cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
	lv_img_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
	lv_indev_set_cursor(mouse, cursor_obj); /*Connect the image  object to the driver*/

	lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
	lv_indev_set_disp(mousewheel, disp);
	lv_indev_set_group(mousewheel, lv_group_get_default());

	lv_indev_t *keyboard = lv_sdl_keyboard_create();
	lv_indev_set_disp(keyboard, disp);
	lv_indev_set_group(keyboard, lv_group_get_default());

	return disp;
}

//  lv_example_switch_1();
//  lv_example_calendar_1();
//  lv_example_btnmatrix_2();
//  lv_example_checkbox_1();
//  lv_example_colorwheel_1();
//  lv_example_chart_6();
//  lv_example_table_2();
//  lv_example_scroll_2();
//  lv_example_textarea_1();
//  lv_example_msgbox_1();
//  lv_example_dropdown_2();
//  lv_example_btn_1();
//  lv_example_scroll_1();
//  lv_example_tabview_1();
//  lv_example_tabview_1();
//  lv_example_flex_3();
//  lv_example_label_1();

//lv_obj_t *label_title = lv_label_create(container2);
//	lv_label_set_text(label_title, "تنظیمات");
////	 lv_obj_set_size(label_title, 300, LV_SIZE_CONTENT);
//	lv_obj_set_style_text_font(label_title, &iran_yekan_regular_20,
//			LV_STATE_DEFAULT);
//	lv_obj_set_style_text_align(label_title, LV_TEXT_ALIGN_CENTER,
//			LV_STATE_DEFAULT);
//
//	lv_obj_t *btn_1 = lv_obj_create(container2);
//	lv_obj_set_size(btn_1, 266, 45);
//	lv_obj_set_style_radius(btn_1, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn_1, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(btn_1, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_scrollbar_mode(btn_1, LV_SCROLLBAR_MODE_OFF);
//
//	lv_obj_t *text_1 = lv_label_create(btn_1);
//	lv_label_set_text(text_1, "مودم wifi");
//	lv_obj_set_style_text_font(text_1, &iran_yekan_regular_20,
//			LV_STATE_DEFAULT);
//	lv_obj_set_align(text_1, LV_ALIGN_CENTER);
//
//	lv_obj_t *btn_2 = lv_obj_create(container2);
//	lv_obj_set_size(btn_2, 266, 45);
//	lv_obj_set_style_radius(btn_2, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn_2, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(btn_2, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_scrollbar_mode(btn_2, LV_SCROLLBAR_MODE_OFF);
//
//	lv_obj_t *text_2 = lv_label_create(btn_2);
//		lv_label_set_text(text_2, "انتخاب زبان");
//		lv_obj_set_style_text_font(text_2, &iran_yekan_regular_20,
//				LV_STATE_DEFAULT);
//		lv_obj_set_align(text_2, LV_ALIGN_CENTER);
//
//	lv_obj_t *btn_3 = lv_obj_create(container2);
//	lv_obj_set_size(btn_3, 266, 45);
//	lv_obj_set_style_radius(btn_3, 10, LV_STATE_DEFAULT);
//	lv_obj_set_style_border_width(btn_3, 0, LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_color(btn_3, lv_color_hex(0x01E7C1), LV_STATE_DEFAULT);
//	lv_obj_set_scrollbar_mode(btn_3, LV_SCROLLBAR_MODE_OFF);
//
//	lv_obj_t *text_3 = lv_label_create(btn_3);
//		lv_label_set_text(text_3, "پیکربندی دستگاه");
//		lv_obj_set_style_text_font(text_3, &iran_yekan_regular_20,
//				LV_STATE_DEFAULT);
//		lv_obj_set_align(text_3, LV_ALIGN_CENTER);

//lv_obj_t *container2=lv_obj_create(screen);
//     lv_obj_set_size(container2, 320, 212);
//     lv_obj_set_scrollbar_mode(container2, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_set_style_bg_color(container2, lv_color_hex(0xFFEDEDED), LV_STATE_DEFAULT);
//     lv_obj_set_style_align(container2, LV_ALIGN_BOTTOM_LEFT, LV_STATE_DEFAULT);
//     lv_obj_set_style_radius(container2, 0, LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_all(container2, 20, LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(container2, 0, LV_STATE_DEFAULT);
//
//     lv_obj_t * wifi = lv_img_create  (container2);
//     lv_img_set_src(wifi, &img_wifi);
//     lv_obj_set_style_align(wifi, LV_ALIGN_CENTER, LV_STATE_DEFAULT);
//     lv_obj_set_pos(wifi, 0, -30);
//
//
//     lv_obj_t * title=lv_label_create(container2);
//
//     lv_obj_set_style_text_font(title, &iran_yekan_regular_24, LV_STATE_DEFAULT);
//     lv_obj_set_size(title, 175,LV_SIZE_CONTENT);
//     lv_obj_align_to(title, wifi, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
//     lv_label_set_text(title, "ارتباط با اینترنت قطع شده است");
//     lv_obj_set_style_text_align(title, LV_ALIGN_TOP_MID, LV_STATE_DEFAULT);

//lv_obj_t *container2 = lv_obj_create(screen);
//lv_obj_set_size(container2, 320, 212);
//lv_obj_set_scrollbar_mode(container2, LV_SCROLLBAR_MODE_OFF);
//lv_obj_set_style_bg_color(container2, lv_color_hex(0xFFEDEDED),
//		LV_STATE_DEFAULT);
//lv_obj_set_style_align(container2, LV_ALIGN_BOTTOM_LEFT, LV_STATE_DEFAULT);
//lv_obj_set_style_radius(container2, 0, LV_STATE_DEFAULT);
//lv_obj_set_style_pad_all(container2, 20, LV_STATE_DEFAULT);
//lv_obj_set_style_border_width(container2, 0, LV_STATE_DEFAULT);
//
//lv_obj_t *text = lv_label_create(container2);
//lv_obj_set_style_align(text, LV_ALIGN_TOP_MID, LV_STATE_DEFAULT);
//lv_obj_set_style_text_font(text, &iran_yekan_regular_22, LV_STATE_DEFAULT);
//lv_label_set_text(text, "مبلغ را وارد کنید");
//
//lv_obj_t *price_box = lv_obj_create(container2);
//lv_obj_set_size(price_box, 253, 44);
//lv_obj_set_style_border_width(price_box, 0, LV_STATE_DEFAULT);
//lv_obj_set_style_bg_color(price_box, lv_color_hex(0x01E7C1),
//		LV_STATE_DEFAULT);
//lv_obj_clear_flag(price_box, LV_OBJ_FLAG_SCROLLABLE);
//lv_obj_set_style_pad_bottom(price_box, 0, LV_STATE_DEFAULT);
//lv_obj_set_style_pad_top(price_box, 0, LV_STATE_DEFAULT);
//lv_obj_set_style_pad_left(price_box, 5, LV_STATE_DEFAULT);
//lv_obj_set_style_pad_right(price_box, 5, LV_STATE_DEFAULT);
//
//
//lv_obj_align_to(price_box, text, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
//lv_obj_set_style_radius(price_box, 10, LV_STATE_DEFAULT);
//lv_obj_set_style_flex_flow(price_box, LV_FLEX_FLOW_ROW, LV_STATE_DEFAULT);
//
//lv_obj_t *curency = lv_label_create(price_box);
//lv_obj_set_style_align(curency, LV_ALIGN_LEFT_MID, LV_STATE_DEFAULT);
//lv_obj_set_style_text_font(curency, &iran_yekan_regular_22,
//		LV_STATE_DEFAULT);
//lv_obj_set_pos(curency, 0, -3);
//lv_label_set_text(curency, "ریال");
//
//lv_obj_t *price = lv_label_create(price_box);
//lv_obj_set_style_align(price, LV_ALIGN_RIGHT_MID, LV_STATE_DEFAULT);
//lv_obj_set_style_text_font(price, &iran_yekan_regular_24,
//		LV_STATE_DEFAULT);
//lv_obj_set_pos(price, 0, -2);
//lv_obj_set_style_width(price, 210, LV_STATE_DEFAULT);
//lv_obj_set_style_text_align(price, LV_TEXT_ALIGN_CENTER,LV_STATE_DEFAULT);
//lv_label_set_text(price, "5,800,000");
//
//
//lv_obj_t *word_price=lv_label_create(container2);
//lv_obj_set_style_width(word_price, 253, LV_STATE_DEFAULT);
//lv_obj_set_style_text_font(word_price, &iran_yekan_regular_18,
//			LV_STATE_DEFAULT);
//lv_obj_align_to(word_price, price_box, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
//lv_obj_set_style_text_align(word_price, LV_TEXT_ALIGN_CENTER,LV_STATE_DEFAULT);
//lv_obj_set_style_text_line_space(word_price,0, LV_STATE_DEFAULT);
//
//lv_label_set_text(word_price, "معادل: چهل و نه میلیون و نهصد و نود نو نه هزارو نهصد و نود و نه نو نه هزارو نهصد و نود و نه");
//

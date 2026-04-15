#include <zmk/display/status_screen.h>
#include <lvgl.h>

// ==========================================
// 1. MẢNG DỮ LIỆU LOGO (DÁN MÃ HEX 128x32 VÀO ĐÂY)
// ==========================================
static const uint8_t logomcmc_map[] = {
    /* Dán 512 bytes mã Hex của bạn vào đây */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    // ... (copy toàn bộ các dòng còn lại của bạn)
};

// ==========================================
// 2. KHAI BÁO CẤU TRÚC ẢNH CHUẨN ZMK
// ==========================================
const lv_img_dsc_t mcoi_logo_dsc = {
  .header.always_zero = 0,
  .header.w = 128,
  .header.h = 32,
  .data_size = sizeof(logomcmc_map), 
  .header.cf = LV_IMG_CF_ALPHA_1_BIT, // Khớp với định dạng bạn đã chọn trên Web
  .data = logomcmc_map,
};

// ==========================================
// 3. HÀM HIỂN THỊ (STATUS SCREEN)
// ==========================================
lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    #if IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN)
        // --- MÀN HÌNH TRÁI: PIN & KẾT NỐI ---
        
        // Khung pin
        lv_obj_t *bat_body = lv_obj_create(screen);
        lv_obj_set_size(bat_body, 28, 14);
        lv_obj_align(bat_body, LV_ALIGN_TOP_RIGHT, -5, 2);
        lv_obj_set_style_border_width(bat_body, 1, 0);
        lv_obj_set_style_radius(bat_body, 2, 0);
        lv_obj_set_style_pad_all(bat_body, 0, 0);

        // Đầu pin
        lv_obj_t *bat_tip = lv_obj_create(screen);
        lv_obj_set_size(bat_tip, 2, 6);
        lv_obj_align_to(bat_tip, bat_body, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
        lv_obj_set_style_bg_color(bat_tip, lv_color_white(), 0);

        // Số pin
        lv_obj_t *bat_label = lv_label_create(bat_body);
        lv_label_set_text(bat_label, "95"); 
        lv_obj_center(bat_label);

        // Kết nối
        lv_obj_t *conn = lv_label_create(screen);
        lv_label_set_text(conn, "BLE: 1 | OK"); 
        lv_obj_align(conn, LV_ALIGN_BOTTOM_LEFT, 2, -2);

    #else
        // --- MÀN HÌNH PHẢI: LOGO MCOI ---
        lv_obj_t *img = lv_img_create(screen);
        lv_img_set_src(img, &mcoi_logo_dsc);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    #endif

    return screen;
}

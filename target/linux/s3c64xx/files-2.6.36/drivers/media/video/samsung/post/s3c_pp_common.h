#ifndef _S3C_PP_COMMON_H_
#define _S3C_PP_COMMON_H_

#include "s3c_pp.h"

#define PP_MINOR    253		            // post processor is misc device driver

typedef enum {
	HCLK        = 0, 
    PLL_EXT     = 1, 
    EXT_27MHZ   = 3
} s3c_pp_clk_src_t;

typedef enum {
	POST_IDLE   = 0,
	POST_BUSY
} s3c_pp_state_t;

typedef struct {
    unsigned int src_full_width;		// Source Image Full Width (Virtual screen size)
	unsigned int src_full_height;		// Source Image Full Height (Virtual screen size)
	unsigned int src_start_x; 			// Source Image Start width offset
	unsigned int src_start_y; 			// Source Image Start height offset
	unsigned int src_width;				// Source Image Width
	unsigned int src_height; 			// Source Image Height
	unsigned int src_buf_addr_phy; 		// Base Address of the Source Image : Physical Address
	unsigned int src_next_buf_addr_phy; // Base Address of Source Image to be displayed next time in FIFO_FREERUN Mode
	s3c_color_space_t src_color_space; 	// Color Space of the Source Image

	unsigned int dst_full_width; 		// Destination Image Full Width (Virtual screen size)
	unsigned int dst_full_height; 		// Destination Image Full Height (Virtual screen size)
	unsigned int dst_start_x; 			// Destination Image Start width offset
	unsigned int dst_start_y; 			// Destination Image Start height offset
	unsigned int dst_width; 			// Destination Image Width
	unsigned int dst_height; 			// Destination Image Height
	unsigned int dst_buf_addr_phy;		// Base Address of the Destination Image : Physical Address
	s3c_color_space_t dst_color_space; 	// Color Space of the Destination Image

	s3c_pp_out_path_t out_path; 	    // output and run mode to be used internally
    s3c_pp_scan_mode_t scan_mode;       // INTERLACE_MODE, PROGRESSIVE_MODE

	unsigned int in_pixel_size;			    // source format size per pixel
	unsigned int out_pixel_size;		    // destination format size per pixel

    unsigned int instance_no;               // Instance No
    unsigned int value_changed;             // 0: Parameter is not changed, 1: Parameter is changed 
    //unsigned int RegisterContext[164];    // Register Context
} s3c_pp_instance_context_t;

typedef struct {
	unsigned int pre_h_ratio, pre_v_ratio, h_shift, v_shift, sh_factor;
	unsigned int pre_dst_width, pre_dst_height, dx, dy;
} s3c_pp_scaler_info_t;

typedef struct {
	unsigned int offset_y, offset_cb, offset_cr;
	unsigned int src_start_y, src_start_cb, src_start_cr;
	unsigned int src_end_y, src_end_cb, src_end_cr;
	unsigned int start_pos_y, end_pos_y;
	unsigned int start_pos_cb, end_pos_cb;
	unsigned int start_pos_cr, end_pos_cr;
	unsigned int start_pos_rgb, end_pos_rgb;
	unsigned int dst_start_rgb, dst_end_rgb;
	unsigned int src_frm_start_addr;

	unsigned int offset_rgb, out_offset_cb, out_offset_cr;
	unsigned int out_start_pos_cb, out_start_pos_cr;
	unsigned int out_end_pos_cb, out_end_pos_cr;
	unsigned int out_src_start_cb, out_src_start_cr;
	unsigned int out_src_end_cb, out_src_end_cr;
} s3c_pp_buf_addr_t;





// below functions are used for Post Processor commonly
void set_data_format(s3c_pp_instance_context_t *pp_instance);
void set_src_addr(s3c_pp_instance_context_t *pp_instance);
void set_dest_addr(s3c_pp_instance_context_t *pp_instance);
void set_src_next_buf_addr(s3c_pp_instance_context_t *pp_instance);
void set_scaler(s3c_pp_instance_context_t *pp_instance);
int cal_data_size(s3c_color_space_t color_space, unsigned int width, unsigned int height);

// below functions'body is implemented in each post processor IP file(ex. s3c_pp_6400.c)
void set_scaler_register(s3c_pp_scaler_info_t *scaler_info, s3c_pp_instance_context_t *pp_instance);
void set_src_addr_register(s3c_pp_buf_addr_t *buf_addr, s3c_pp_instance_context_t *pp_instance);
void set_dest_addr_register(s3c_pp_buf_addr_t *buf_addr, s3c_pp_instance_context_t *pp_instance);
void set_src_next_addr_register(s3c_pp_buf_addr_t *buf_addr, s3c_pp_instance_context_t *pp_instance);
void set_data_format_register(s3c_pp_instance_context_t *pp_instance);

s3c_pp_state_t post_get_processing_state(void);

#endif // _S3C_PP_COMMON_H_


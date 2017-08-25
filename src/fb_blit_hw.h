#ifndef _FB_BLIT_HW_
#define _FB_BLIT_HW_

struct fb_blit_hw_param_def {
	void *src_form;
	uint16_t src_nxwd;
	uint16_t src_nxln;
	uint16_t src_nxpl;
	uint16_t src_xmin;
	uint16_t src_ymin;

	void *dst_form;
	uint16_t dst_nxwd;
	uint16_t dst_nxln;
	uint16_t dst_nxpl;
	uint16_t dst_xmin;
	uint16_t dst_ymin;

	uint16_t width;
	uint16_t height;
	uint16_t planes;
};

void fb_blit_hw_start(__reg("a4") struct fb_blit_hw_param_def *);

#endif /* _FB_BLIT_HW_ */


#include <jl.h>
#include "jlgr.h"
#include <la_menu.h>

#define EX_MODE_EDIT 0
#define EX_MODE_MAXX 1

typedef struct{
	jl_vo_t vo1;
	jl_vo_t vo2;
	jl_sprite_t slider[3];
	float s1[3];
	float s2[3];
	uint8_t hasMenu;
	uint32_t lightTex;
	la_menu_t menu;
}ctx_t;
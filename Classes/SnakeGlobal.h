#ifndef __SNAKE_CONSTANTS_H__
#define __SNAKE_CONSTANTS_H__

#include <string>

namespace SnakeGolbal
{
	static const int LAYER_COUNT = 4; 
	static const int LAYER_BACKGROUND = 0;
	static const int LAYER_FOOD = 1;
	static const int LAYER_SNAKE = 2;
	static const int LAYER_UI = 3;

	static const char *SCORE_TTF = "Plok.ttf";
	static const int SCORE_SIZE = 24;
	static const int HIGHEST_SCORE_SIZE = 18;

	static const char *BEGIN_TTF = "Plok.ttf";
	static const int BEGIN_SIZE = 30;

	static const char *GAMEOVER_TTF = "Plok.ttf";
	static const int GAMEOVER_SIZE = 30;

	static const char *BACKGROUND_IMAGE = "background.png";
	static const char *BACKGROUND_LINE_IMAGE = "background_line.png";
	static const char *BACKGROUND_LINE_HEIGHT_IMAGE = "background_line_height.png";
	static const char *BACKGROUND_LINE_WIDTH_IMAGE = "background_line_width.png";
	
	static const char *SNAKE_BODY_IMAGE = "snake_tailpart.png";
	static const char *SNAKE_HEAD_IMAGE = "snake_head.png";
	static const char *FROG_IMAGE = "frog.png";
	static const char *DIAMOND_IMAGE = "Diamond.png";
	static const char *SUPER_DIAMOND_IMAGE = "Super_Diamond.png";
	static const char *RESET_IMAGE = "redo-round.png";
	static const char *PAUSE_ITEM_IMAGE = "pause_item.png";
	static const char *PAUSE_MENU_IMAGE = "pause_menu.png";
	static const char *IN_MENU_CONTINUE_IMAGE = "in_menu_continue.png";
	static const char *IN_MENU_RESET_IMAGE = "in_menu_reset.png";

	static const int CELLS_HORIZON = 19;
	static const int CELLS_VERTICAL = 11;
	static const int CELL_WIDTH = 32;
	static const int CELL_HEIGHT = CELL_WIDTH;
	static const int CELLS_WIDTH_BEGIN = 11;
	static const int CELLS_WIDTH_END = 982;
	static const int BACKGROUND_WIDTH = 960;
	static const int CELLS_ORIGIN_HEIGTH_BEGIN = 8;
	static const int CELLS_ORIGIN_HEIGTH_END = 550;
	static const int BACKGROUND_ORIGIN_HEIGTH = 534;	

	static const double LEAST_MOVE = 1;
	static const double LEAST_TAN_DIRECTION = 0.2;

	extern int g_CellsHorizon;
	extern int g_CellsVertical;
	extern int g_CellsWidthBegin;
	extern int g_CellsWidthEnd;
	extern int g_CellsHeightBegin;
	extern int g_CellsHeightEnd;

	static const int DIAMOND_TIMES = 4;
	static const int FIRST_DIAMOND_RATE = 1;
	static const int SECOND_DIAMOND_RATE = 0.1;
}

#endif
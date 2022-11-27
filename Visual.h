#pragma once

#define MAIN_WND_WIDTH		1440
#define MAIN_WND_HEIGHT		960
#define SIZE_OF_A_PIECE		35
#define SIZE_OF_PIECE_PIC	30
#define SIZE_OF_BOARD_PIC	834
#define SIZE_OF_A_CELL		(SIZE_OF_BOARD_PIC / (BOARD_SIZE - 1))

#define OUTSIDE				16
#define NOBUTTON			16

#define NEW_GAME			0
#define LOAD				1
#define EXIT				2

#define HOMEPAGE			0
#define LOAD_INTERFACE		1
#define MODE_SELECT			2
#define GAME_INTERFACE		4

#define PVP_MODE			0
#define PVC_MODE			1
#define CVC_MODE			2

#define ON_BOARD			0
#define RESET				1
#define NEXT				2
#define BACK_TO_HOMEPAGE	4


int CurrentChosen = 0;
int mouseLocation = OUTSIDE;
int currentInterface = HOMEPAGE;
int currentRound = 0;
int GameResult = GAME_ON;

POINT dropPosition;

//Initialize IMAGE "variables"(class in fact)

IMAGE img_HomePage;

IMAGE img_NewGame, img_Load, img_Exit;
IMAGE img_NewGame_Black, img_Load_Black, img_Exit_Black;

IMAGE img_ModeSelect;
IMAGE img_PVP, img_PVC, img_CVC;
IMAGE img_PVP_Black, img_PVC_Black, img_CVC_Black;

IMAGE img_Game_Interface;
IMAGE img_Reset, img_Next, img_Back_to_HomePage;
IMAGE img_Reset_Black, img_Next_Black, img_Back_to_HomePage_Black;

IMAGE img_Black, img_White, img_Under;
IMAGE img_Black_Small, img_White_Small;


//some rectangulars

RECT  rct_MainWnd = {
	0, 0, MAIN_WND_WIDTH, MAIN_WND_HEIGHT
};



RECT  rct_New_Game = {
	30, 580, 30 + 360, 580 + 90
};

RECT rct_Load = {
	30, 700, 30 + 165, 700 + 90
};

RECT rct_Exit = {
	30, 820, 30 + 135, 820 + 90
};



RECT rct_PVP = {
	1050, 200, 1350, 335
};

RECT rct_PVC = {
	1050, 420, 1350, 555
};

RECT rct_CVC = {
	1050, 630, 1350, 765
};



RECT rct_Reset = {
	950, 40, 950 + 140, 40 + 70
};

RECT rct_Next = {
	1200, 40, 1200 + 125, 40 + 70
};

RECT rct_Back_to_HomePage = {
	950, 120, 950 + 480, 120 + 70
};

RECT rct_Board = {
	63, 63, 63 + 834, 63 + 834
};

RECT rct_indicator = {
	1230, 216, 1230 + 30, 216 + 30
};



//functions
void	LoadImages							();
void	RepaintButtons						(int pre, int cur);
bool	isinRectangular						(RECT rect, int x, int y);
int		GetMouseLocation					(int x, int y);
POINT	pixel2board							(int x, int y);

bool isinRectangular(RECT rect, int x, int y)
{
	return (x >= rect.left) && (x <= rect.right) && (y >= rect.top) && (y <= rect.bottom);
}

int GetMouseLocation(int x, int y)
{
	switch (currentInterface)
	{
	case HOMEPAGE:
		if (isinRectangular(rct_New_Game, x, y))
			return NEW_GAME;
		if (isinRectangular(rct_Load, x, y))
			return LOAD;
		if (isinRectangular(rct_Exit, x, y))
			return EXIT;
	return OUTSIDE;

	case MODE_SELECT:
		if (isinRectangular(rct_PVP, x, y))
			return PVP_MODE;
		if (isinRectangular(rct_PVC, x, y))
			return PVC_MODE;
		if (isinRectangular(rct_CVC, x, y))
			return CVC_MODE;
	return OUTSIDE;

	case GAME_INTERFACE:
		if (isinRectangular(rct_Reset, x, y))
			return RESET;
		if (isinRectangular(rct_Next, x, y))
			return NEXT;
		if (isinRectangular(rct_Back_to_HomePage, x, y))
			return BACK_TO_HOMEPAGE;
		if (isinRectangular(rct_Board, x, y) && (
			(((x - rct_Board.left) % SIZE_OF_A_CELL <= SIZE_OF_A_PIECE) || ((x - rct_Board.left) % SIZE_OF_A_CELL >= SIZE_OF_A_CELL - SIZE_OF_A_PIECE))
			&&
			(((y - rct_Board.top)  % SIZE_OF_A_CELL <= SIZE_OF_A_PIECE) || ((y - rct_Board.top)  % SIZE_OF_A_CELL >= SIZE_OF_A_CELL - SIZE_OF_A_PIECE))
			)
		)
			return ON_BOARD;
	return OUTSIDE;
	
	default:return OUTSIDE;
	}
}

void RepaintButtons(int pre, int cur)
{
	switch (currentInterface)
	{
	case HOMEPAGE:
		switch (pre)
		{
		case NEW_GAME:
			putimage(rct_New_Game.left, rct_New_Game.top, &img_NewGame_Black, SRCAND);
			break;
		case LOAD:
			putimage(rct_Load.left, rct_Load.top, &img_Load_Black, SRCAND);
			break;
		case EXIT:
			putimage(rct_Exit.left, rct_Exit.top, &img_Exit_Black, SRCAND);
			break;
		default:
			break;
		}

		switch (cur)
		{
		case NEW_GAME:
			putimage(rct_New_Game.left, rct_New_Game.top, &img_NewGame, SRCPAINT);
			break;
		case LOAD:
			putimage(rct_Load.left, rct_Load.top, &img_Load, SRCPAINT);
			break;
		case EXIT:
			putimage(rct_Exit.left, rct_Exit.top, &img_Exit, SRCPAINT);
			break;
		default:
			break;
		}
		break;

	case MODE_SELECT:
		switch (pre)
		{
		case PVP_MODE:
			putimage(rct_PVP.left, rct_PVP.top, &img_PVP_Black, SRCCOPY);
			break;
		case PVC_MODE:
			putimage(rct_PVC.left, rct_PVC.top, &img_PVC_Black, SRCCOPY);
			break;
		case CVC_MODE:
			putimage(rct_CVC.left, rct_CVC.top, &img_CVC_Black, SRCCOPY);
			break;
		default:
			break;
		}

		switch (cur)
		{
		case PVP_MODE:
			putimage(rct_PVP.left, rct_PVP.top, &img_PVP, SRCCOPY);
			break;
		case PVC_MODE:
			putimage(rct_PVC.left, rct_PVC.top, &img_PVC, SRCCOPY);
			break;
		case CVC_MODE:
			putimage(rct_CVC.left, rct_CVC.top, &img_CVC, SRCCOPY);
			break;
		default:
			break;
		}
		break;

	case GAME_INTERFACE:
		switch (pre)
		{
		case RESET:
			putimage(rct_Reset.left, rct_Reset.top, &img_Reset_Black, SRCCOPY);
			break;
		case NEXT:
			putimage(rct_Next.left, rct_Next.top, &img_Next_Black, SRCCOPY);
			break;
		case BACK_TO_HOMEPAGE:
			putimage(rct_Back_to_HomePage.left, rct_Back_to_HomePage.top, &img_Back_to_HomePage_Black, SRCCOPY);
			break;
		default:
			break;
		}

		switch (cur)
		{
		case RESET:
			putimage(rct_Reset.left, rct_Reset.top, &img_Reset, SRCCOPY);
			break;
		case NEXT:
			putimage(rct_Next.left, rct_Next.top, &img_Next, SRCCOPY);
			break;
		case BACK_TO_HOMEPAGE:
			putimage(rct_Back_to_HomePage.left, rct_Back_to_HomePage.top, &img_Back_to_HomePage, SRCCOPY);
			break;
		default:
			break;
		}
		break;
	default:break;
	}
}

POINT pixel2board(int x, int y)
{
	POINT dropPosition = {0, 0};
	dropPosition.x = (x - rct_Board.left + SIZE_OF_A_PIECE) / SIZE_OF_A_CELL;
	dropPosition.y = (y - rct_Board.top  + SIZE_OF_A_PIECE) / SIZE_OF_A_CELL;
	return dropPosition;
}

void LoadImages()
{
	loadimage(&img_HomePage,						TEXT("./Pictures/HomePage.png"));

	loadimage(&img_NewGame,							TEXT("./Pictures/NewGame.png"));
	loadimage(&img_Load,							TEXT("./Pictures/Load.png"));
	loadimage(&img_Exit,							TEXT("./Pictures/Exit.png"));

	loadimage(&img_NewGame_Black,					TEXT("./Pictures/NewGame_Black.jpg"));
	loadimage(&img_Load_Black,						TEXT("./Pictures/Load_Black.jpg"));
	loadimage(&img_Exit_Black,						TEXT("./Pictures/Exit_Black.jpg"));

	loadimage(&img_ModeSelect,						TEXT("./Pictures/ModeSelect.png"));

	loadimage(&img_PVP,								TEXT("./Pictures/PVP.jpg"));
	loadimage(&img_PVC,								TEXT("./Pictures/PVC.jpg"));
	loadimage(&img_CVC,								TEXT("./Pictures/CVC.jpg"));

	loadimage(&img_PVP_Black,						TEXT("./Pictures/PVP_Black.jpg"));
	loadimage(&img_PVC_Black,						TEXT("./Pictures/PVC_Black.jpg"));
	loadimage(&img_CVC_Black,						TEXT("./Pictures/CVC_Black.jpg"));

	loadimage(&img_Game_Interface,					TEXT("./Pictures/NoGo_Game_Interface.jpg"));

	loadimage(&img_Reset,							TEXT("./Pictures/Reset.jpg"));
	loadimage(&img_Next,							TEXT("./Pictures/Next.jpg"));
	loadimage(&img_Back_to_HomePage,				TEXT("./Pictures/Back_to_HomePage.jpg"));

	loadimage(&img_Reset_Black,						TEXT("./Pictures/Reset_Black.jpg"));
	loadimage(&img_Next_Black,						TEXT("./Pictures/Next_Black.jpg"));
	loadimage(&img_Back_to_HomePage_Black,			TEXT("./Pictures/Back_to_HomePage_Black.jpg"));

	loadimage(&img_Black,							TEXT("./Pictures/Black.png"));
	loadimage(&img_White,							TEXT("./Pictures/White.jpg"));
	loadimage(&img_Under,							TEXT("./Pictures/Under.jpg"));

	loadimage(&img_Black_Small,						TEXT("./Pictures/Black_Small.jpg"));
	loadimage(&img_White_Small,						TEXT("./Pictures/White_Small.jpg"));
}
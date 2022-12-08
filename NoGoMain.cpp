#include <graphics.h>
#include <mmsystem.h>
#include "NoGo.h"
#include "Visual.h"
#include "MCTS.h"

#pragma comment(lib, "Winmm.lib")

ExMessage m;

int main()
{
	LoadImages();

	//check if the board is succesfully initialized
	if (Board == NULL)
	{
		MessageBox(MainWnd, TEXT("Failed to initialize Board!"), TEXT("Error!"), MB_OK);
		closegraph();
		return 0;
	}

	while (true)
		switch (currentInterface)
		{
case HOMEPAGE:

			cleardevice();
			putimage(rct_MainWnd.left, rct_MainWnd.top, &img_HomePage, SRCCOPY);

			putimage(rct_New_Game.left, rct_New_Game.top, &img_NewGame_Black, SRCAND);
			putimage(rct_Load.left, rct_Load.top, & img_Load_Black, SRCAND);
			putimage(rct_Exit.left, rct_Exit.top, &img_Exit_Black, SRCAND);

			putimage(rct_New_Game.left, rct_New_Game.top, &img_NewGame, SRCPAINT);

			CurrentChosen = NEW_GAME;

			PlaySound(TEXT(".\\Music\\feixiangtian.wav"), NULL, SND_LOOP | SND_ASYNC);

			while (true)
			{
				if (currentInterface != HOMEPAGE)
					break;

				m = getmessage(EX_MOUSE | EX_KEY);

				switch (m.message)
				{
				case WM_MOUSEMOVE:
					mouseLocation = GetMouseLocation(m.x, m.y);
					if (CurrentChosen != mouseLocation && mouseLocation != OUTSIDE)
					{
						RepaintButtons(CurrentChosen, mouseLocation);
						CurrentChosen = mouseLocation;
					}
					break;

				case WM_LBUTTONDOWN:
					mouseLocation = GetMouseLocation(m.x, m.y);
					if (mouseLocation != OUTSIDE)
					{
						CurrentChosen = mouseLocation;
						switch (CurrentChosen)
						{
						case NEW_GAME:
							currentInterface = MODE_SELECT;
							break;

						case LOAD:
							MessageBox(MainWnd, TEXT("Coming Soon..."), TEXT("Sorry"), MB_OK);
							break;

						case EXIT:
							if (MessageBox(MainWnd, TEXT("Ready to quit?"), TEXT("Warning"), MB_YESNO) == IDYES)
							{
								closegraph();
								free_Board(Board);
								return 0;
							}
						}
					}
					break;

				case WM_KEYDOWN:
					switch (m.vkcode)
					{
					case VK_ESCAPE:
						if (MessageBox(MainWnd, TEXT("Ready to quit?"), TEXT("Warning"), MB_YESNO) == IDYES)
						{
							closegraph();
							free_Board(Board);
							return 0;
						}

					case VK_TAB:
					case VK_DOWN:
						RepaintButtons(CurrentChosen, (CurrentChosen + 1) % 3);
						CurrentChosen = (CurrentChosen + 1) % 3;
						break;

					case VK_UP:
						RepaintButtons(CurrentChosen, (CurrentChosen + 2) % 3);
						CurrentChosen = (CurrentChosen + 2) % 3;
						break;

					case VK_RETURN:
						switch (CurrentChosen)
						{
						case NEW_GAME:
							currentInterface = MODE_SELECT;
							break;

						case LOAD:
							MessageBox(MainWnd, TEXT("Coming Soon..."), TEXT("Sorry"), MB_OK);
							break;

						case EXIT:
							if (MessageBox(MainWnd, TEXT("Ready to quit?"), TEXT("Warning"), MB_YESNO) == IDYES)
							{
								closegraph();
								free_Board(Board);
								return 0;
							}
						}
					}
				}
			}
			break;

case MODE_SELECT:

			cleardevice();
			putimage(rct_MainWnd.left, rct_MainWnd.top, &img_ModeSelect, SRCCOPY);

			putimage(rct_PVP.left, rct_PVP.top, &img_PVP, SRCCOPY);
			putimage(rct_PVC.left, rct_PVC.top, &img_PVC_Black, SRCCOPY);
			putimage(rct_CVC.left, rct_CVC.top, &img_CVC_Black, SRCCOPY);

			CurrentChosen = PVP_MODE;

			PlaySound(TEXT(".\\Music\\cuimengxiang.wav"), NULL, SND_LOOP | SND_ASYNC);

			while (true)
			{
				if (currentInterface != MODE_SELECT)
					break;

				m = getmessage(EX_MOUSE | EX_KEY);

				switch (m.message)
				{
				case WM_MOUSEMOVE:
					mouseLocation = GetMouseLocation(m.x, m.y);
					if (mouseLocation != OUTSIDE && mouseLocation != CurrentChosen)
					{
						RepaintButtons(CurrentChosen, mouseLocation);
						CurrentChosen = mouseLocation;
					}
					break;

				case WM_LBUTTONDOWN:
					mouseLocation = GetMouseLocation(m.x, m.y);
					switch (mouseLocation)
					{
					case PVP_MODE:
						currentInterface = GAME_INTERFACE;
						SelectedMode = PVP_MODE;
						PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
						break;

					case PVC_MODE:
						currentInterface = GAME_INTERFACE;
						SelectedMode = PVC_MODE;
						if (MessageBox(MainWnd, TEXT("Would you like to use Black Piece?"), TEXT("Reminder"), MB_YESNO) == IDYES)
							PlayerSelected = BLACK_PIECE;
						else PlayerSelected = WHITE_PIECE;
						PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
						break;

					case CVC_MODE:
						currentInterface = GAME_INTERFACE;
						SelectedMode = CVC_MODE;
						PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
						break;
					}
					break;

				case WM_KEYDOWN:
					switch (m.vkcode)
					{
					case VK_ESCAPE:
						currentInterface = HOMEPAGE;
						break;

					case VK_TAB:
					case VK_DOWN:
						RepaintButtons(CurrentChosen, (CurrentChosen + 1) % 3);
						CurrentChosen = (CurrentChosen + 1) % 3;
						break;

					case VK_UP:
						RepaintButtons(CurrentChosen, (CurrentChosen + 2) % 3);
						CurrentChosen = (CurrentChosen + 2) % 3;
						break;

					case VK_RETURN:
						switch (CurrentChosen)
						{
						case PVP_MODE:
							currentInterface = GAME_INTERFACE;
							SelectedMode = PVP_MODE;
							PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
							break;

						case PVC_MODE:
							currentInterface = GAME_INTERFACE;
							SelectedMode = PVC_MODE;
							if (MessageBox(MainWnd, TEXT("Would you like to use Black Piece?"), TEXT("Reminder"), MB_YESNO) == IDYES)
								PlayerSelected = BLACK_PIECE;
							else PlayerSelected = WHITE_PIECE;
							PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
							break;

						case CVC_MODE:
							currentInterface = GAME_INTERFACE;
							SelectedMode = CVC_MODE;
							PlaySound(TEXT(".\\Music\\jialunyibo.wav"), NULL, SND_LOOP | SND_ASYNC);
							break;
						}
					}

					break;
				}
			}
			break;

case GAME_INTERFACE:

			cleardevice();

			putimage(rct_MainWnd.left, rct_MainWnd.top, &img_Game_Interface, SRCCOPY);

			putimage(rct_Reset.left, rct_Reset.top, &img_Reset_Black, SRCCOPY);
			putimage(rct_Next.left, rct_Next.top, &img_Next_Black, SRCCOPY);
			putimage(rct_Back_to_HomePage.left, rct_Back_to_HomePage.top, &img_Back_to_HomePage_Black, SRCCOPY);
			putimage(rct_indicator.left, rct_indicator.top, &img_Black_Small, SRCCOPY);

			CurrentChosen = NOBUTTON;
			currentRound = 1;
			if (PlayerSelected == WHITE_PIECE && SelectedMode == PVC_MODE)
				AIOperation(MainWnd, Board, MCTS_AI(Board, currentRound));

			doGameRestart = false;

			while (true)
			{
				if (currentInterface != GAME_INTERFACE)
					break;

				m = getmessage(EX_MOUSE | EX_KEY);

				switch (m.message)
				{
				case WM_MOUSEMOVE:
					mouseLocation = GetMouseLocation(m.x, m.y);

					if (mouseLocation != CurrentChosen)
					{
						RepaintButtons(CurrentChosen, mouseLocation);
						CurrentChosen = mouseLocation;
					}
					break;

				case WM_LBUTTONDOWN:
					mouseLocation = GetMouseLocation(m.x, m.y);
					switch (mouseLocation)
					{
					case ON_BOARD:
						switch (SelectedMode)
						{
						case PVP_MODE:
							dropPosition = pixel2board(m.x, m.y);
							PlayerOperation(MainWnd, Board);
							GameJudge();
							break;

						case PVC_MODE:
							if (Round2Color(currentRound) == PlayerSelected)
							{
								dropPosition = pixel2board(m.x, m.y);
								if (PlayerOperation(MainWnd, Board))
								{
									if (GameJudge() == GAME_ON)
									{
										AIOperation(MainWnd, Board, MCTS_AI(Board, currentRound));
										GameJudge();
									}
								}
							}
							else MessageBox(MainWnd, TEXT("Not your Round!"), TEXT("Waring"), MB_OK);
							break;

						case CVC_MODE:
							//undefined
							break;

						default: break;
						}
						

						break;

					case NEXT:
						if (SelectedMode == CVC_MODE)
						{
							AIOperation(MainWnd, Board, MCTS_AI(Board, currentRound));
							GameJudge();
						}
						break;

					case RESET:
						if (currentRound != 1)
						{
							clear_Board(Board);
							doGameRestart = true;
						}

						break;

					case BACK_TO_HOMEPAGE:
						if (MessageBox(MainWnd, TEXT("Back to HomePage?"), TEXT("Warning"), MB_YESNO) == IDYES)
						{
							clear_Board(Board);
							currentInterface = HOMEPAGE;
						}

						break;

					default: break;
					}
					break;
				case WM_KEYDOWN:
					switch (m.vkcode)
					{
					case VK_ESCAPE:
						if (MessageBox(MainWnd, TEXT("Back to HomePage?"), TEXT("Warning"), MB_YESNO) == IDYES)
						{
							clear_Board(Board);
							currentInterface = HOMEPAGE;
						}

						break;

					default: break;
					}

					break;
					
				}
				if (doGameRestart)
					break;
			}
			break;
		}
	closegraph();
	free_Board(Board);
	return 0;
}
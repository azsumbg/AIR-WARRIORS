#include "framework.h"
#include "AIR WARRIORS.h"
#include <mmsystem.h>
#include <d2d1.h>
#include <dwrite.h>
#include "FCheck.h"
#include "errh.h"
#include "d2bmploader.h"
#include "gifresizer.h"
#include "pilots.h"
#include <chrono>
#include <clocale>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "fcheck.lib")
#pragma comment(lib, "errh.lib")
#pragma comment(lib, "d2bmploader.lib")
#pragma comment(lib, "gifresizer.lib")
#pragma comment(lib, "pilots.lib")

constexpr wchar_t bWinClassName[]{ L"AirFight" };
constexpr char tmp_file[]{ ".\\res\\data\\temp.dat" };
constexpr wchar_t Ltmp_file[]{ L".\\res\\data\\temp.dat" };
constexpr wchar_t record_file[]{ L".\\res\\data\\record.dat" };
constexpr wchar_t save_file[]{ L".\\res\\data\\save.dat" };
constexpr wchar_t help_file[]{ L".\\res\\data\\help.dat" };
constexpr wchar_t sound_file[]{ L".\\res\\snd\\main.wav" };

constexpr int mNew{ 1001 };
constexpr int mExit{ 1002 };
constexpr int mSave{ 1003 };
constexpr int mLoad{ 1004 };
constexpr int mHoF{ 1005 };

constexpr int record{ 2001 };
constexpr int no_record{ 2002 };
constexpr int first_record{ 2003 };

WNDCLASS bWinClass{};
HINSTANCE bIns{ nullptr };
HWND bHwnd{ nullptr };
HICON mainIcon{ nullptr };
HCURSOR mainCur{ nullptr };
HCURSOR outCur{ nullptr };
HMENU bBar{ nullptr };
HMENU bMain{ nullptr };
HMENU bStore{ nullptr };
MSG bMsg{};
BOOL bRet{ 0 };
HDC PaintDC{ nullptr };
PAINTSTRUCT bPaint{};
UINT bTimer{ 0 };
POINT cur_pos{};

D2D1_RECT_F b1Rect{ 50.0f, 0, scr_width / 3 - 50.0f, 50.0f };
D2D1_RECT_F b2Rect{ scr_width / 3, 0, scr_width * 2 / 3 - 50.0f, 50.0f };
D2D1_RECT_F b3Rect{ scr_width * 2 / 3, 0, scr_width - 50.0f, 50.0f };

D2D1_RECT_F b1TxtRect{ 80.0f, 10.0f, scr_width / 3 - 50.0f, 50.0f };
D2D1_RECT_F b2TxtRect{ scr_width / 3 + 20.0f, 10.0f, scr_width * 2 / 3 - 50.0f, 50.0f };
D2D1_RECT_F b3TxtRect{ scr_width * 2 / 3 + 20.0f, 10.0f, scr_width - 50.0f, 50.0f };

ID2D1Factory* iFactory{ nullptr };
ID2D1HwndRenderTarget* Draw{ nullptr };

ID2D1RadialGradientBrush* b1BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b2BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b3BckgBrush{ nullptr };

ID2D1SolidColorBrush* TextBrush{ nullptr };
ID2D1SolidColorBrush* InactBrush{ nullptr };
ID2D1SolidColorBrush* HgltBrush{ nullptr };

IDWriteFactory* iWriteFactory{ nullptr };
IDWriteTextFormat* nrmFormat{ nullptr };
IDWriteTextFormat* midFormat{ nullptr };
IDWriteTextFormat* bigFormat{ nullptr };

ID2D1Bitmap* bmpTile{ nullptr };
ID2D1Bitmap* bmpCloud1{ nullptr };
ID2D1Bitmap* bmpCloud2{ nullptr };
ID2D1Bitmap* bmpRiff1{ nullptr };
ID2D1Bitmap* bmpRiff2{ nullptr };
ID2D1Bitmap* bmpRiff3{ nullptr };
ID2D1Bitmap* bmpIntroTxt{ nullptr };
ID2D1Bitmap* bmpSpareParts{ nullptr };

ID2D1Bitmap* bmpIntro[79]{ nullptr };
ID2D1Bitmap* bmpShot[64]{ nullptr };
ID2D1Bitmap* bmpExplosion[24]{ nullptr };

ID2D1Bitmap* bmpHeroU[3]{ nullptr };
ID2D1Bitmap* bmpHeroD[3]{ nullptr };
ID2D1Bitmap* bmpHeroL[3]{ nullptr };
ID2D1Bitmap* bmpHeroR[3]{ nullptr };
ID2D1Bitmap* bmpHeroUR[3]{ nullptr };
ID2D1Bitmap* bmpHeroUL[3]{ nullptr };
ID2D1Bitmap* bmpHeroDR[3]{ nullptr };
ID2D1Bitmap* bmpHeroDL[3]{ nullptr };

ID2D1Bitmap* bmpFighter1U[12]{ nullptr };
ID2D1Bitmap* bmpFighter1D[12]{ nullptr };
ID2D1Bitmap* bmpFighter1L[12]{ nullptr };
ID2D1Bitmap* bmpFighter1R[12]{ nullptr };
ID2D1Bitmap* bmpFighter1UR[12]{ nullptr };
ID2D1Bitmap* bmpFighter1UL[12]{ nullptr };
ID2D1Bitmap* bmpFighter1DR[12]{ nullptr };
ID2D1Bitmap* bmpFighter1DL[12]{ nullptr };

ID2D1Bitmap* bmpFighter2U[24]{ nullptr };
ID2D1Bitmap* bmpFighter2D[24]{ nullptr };
ID2D1Bitmap* bmpFighter2L[24]{ nullptr };
ID2D1Bitmap* bmpFighter2R[24]{ nullptr };
ID2D1Bitmap* bmpFighter2UR[24]{ nullptr };
ID2D1Bitmap* bmpFighter2UL[24]{ nullptr };
ID2D1Bitmap* bmpFighter2DR[24]{ nullptr };
ID2D1Bitmap* bmpFighter2DL[24]{ nullptr };

ID2D1Bitmap* bmpFighter3U[24]{ nullptr };
ID2D1Bitmap* bmpFighter3D[24]{ nullptr };
ID2D1Bitmap* bmpFighter3L[24]{ nullptr };
ID2D1Bitmap* bmpFighter3R[24]{ nullptr };
ID2D1Bitmap* bmpFighter3UR[24]{ nullptr };
ID2D1Bitmap* bmpFighter3UL[24]{ nullptr };
ID2D1Bitmap* bmpFighter3DR[24]{ nullptr };
ID2D1Bitmap* bmpFighter3DL[24]{ nullptr };

ID2D1Bitmap* bmpFighter4U[24]{ nullptr };
ID2D1Bitmap* bmpFighter4D[24]{ nullptr };
ID2D1Bitmap* bmpFighter4L[24]{ nullptr };
ID2D1Bitmap* bmpFighter4R[24]{ nullptr };
ID2D1Bitmap* bmpFighter4UR[24]{ nullptr };
ID2D1Bitmap* bmpFighter4UL[24]{ nullptr };
ID2D1Bitmap* bmpFighter4DR[24]{ nullptr };
ID2D1Bitmap* bmpFighter4DL[24]{ nullptr };

ID2D1Bitmap* bmpBoss1U[4]{ nullptr };
ID2D1Bitmap* bmpBoss1D[4]{ nullptr };
ID2D1Bitmap* bmpBoss1L[4]{ nullptr };
ID2D1Bitmap* bmpBoss1R[4]{ nullptr };
ID2D1Bitmap* bmpBoss1UR[4]{ nullptr };
ID2D1Bitmap* bmpBoss1UL[4]{ nullptr };
ID2D1Bitmap* bmpBoss1DR[4]{ nullptr };
ID2D1Bitmap* bmpBoss1DL[4]{ nullptr };

ID2D1Bitmap* bmpBoss2U[2]{ nullptr };
ID2D1Bitmap* bmpBoss2D[2]{ nullptr };
ID2D1Bitmap* bmpBoss2L[2]{ nullptr };
ID2D1Bitmap* bmpBoss2R[2]{ nullptr };
ID2D1Bitmap* bmpBoss2UR[2]{ nullptr };
ID2D1Bitmap* bmpBoss2UL[2]{ nullptr };
ID2D1Bitmap* bmpBoss2DR[2]{ nullptr };
ID2D1Bitmap* bmpBoss2DL[2]{ nullptr };

ID2D1Bitmap* bmpBoss3U[10]{ nullptr };
ID2D1Bitmap* bmpBoss3D[10]{ nullptr };
ID2D1Bitmap* bmpBoss3L[10]{ nullptr };
ID2D1Bitmap* bmpBoss3R[10]{ nullptr };
ID2D1Bitmap* bmpBoss3UR[10]{ nullptr };
ID2D1Bitmap* bmpBoss3UL[10]{ nullptr };
ID2D1Bitmap* bmpBoss3DR[10]{ nullptr };
ID2D1Bitmap* bmpBoss3DL[10]{ nullptr };

////////////////////////////////////////////////

bool pause = false;
bool in_client = true;
bool show_help = false;
bool sound = true;
bool b1Hglt = false;
bool b2Hglt = false;
bool b3Hglt = false;
bool name_set = false;

bool hero_killed = false;
bool boss_active = false;

wchar_t current_player[16]{ L"TARLYO" };

dirs assets_dir{ dirs::stop };

int level = 1;
int mins = 0;
int secs = 300;
int score = 0;

float scale_x{ 0 };
float scale_y{ 0 };

//////////////////////////////////////////////

std::vector<dll::TILE*>vTiles;





///////////////////////////////////////////////

// CORE FUNCTIONS *****************************

template<typename T>concept HasRelease = requires(T check)
{
	check.Release();
};
template<HasRelease T>bool FreeMem(T** var)
{
	if ((*var))
	{
		(*var)->Release();
		(*var) = nullptr;
		return true;
	}

	return false;
}
int GetIntroFrame()
{
	static int frame{ -1 };

	++frame;
	if (frame > 78)frame = 0;

	return frame;
}
void LogErr(LPCWSTR what)
{
	std::wofstream log(L".\\res\\data\\error.log", std::ios::app);
	log << what << L" Time of error occurrence: " << std::chrono::system_clock::now() << std::endl << std::endl;
	log.close();
}
void ReleaseResources()
{
	if (!FreeMem(&iFactory))LogErr(L"Error releasing D2D1 main Factory !");
	if (!FreeMem(&Draw))LogErr(L"Error releasing D2D1 Render Target !");

	if (!FreeMem(&b1BckgBrush))LogErr(L"Error releasing D2D1 b1BckgBrush !");
	if (!FreeMem(&b2BckgBrush))LogErr(L"Error releasing D2D1 b2BckgBrush !");
	if (!FreeMem(&b3BckgBrush))LogErr(L"Error releasing D2D1 b3BckgBrush !");
	if (!FreeMem(&TextBrush))LogErr(L"Error releasing D2D1 TextBrush !");
	if (!FreeMem(&HgltBrush))LogErr(L"Error releasing D2D1 HgltBrush !");
	if (!FreeMem(&InactBrush))LogErr(L"Error releasing D2D1 InactBrush !");

	if (!FreeMem(&iWriteFactory))LogErr(L"Error releasing D2D1 main WriteFactory !");
	if (!FreeMem(&nrmFormat))LogErr(L"Error releasing DWrite nrmFormat !");
	if (!FreeMem(&midFormat))LogErr(L"Error releasing DWrite midFormat !");
	if (!FreeMem(&bigFormat))LogErr(L"Error releasing DWrite bigFormat !");

	if (!FreeMem(&bmpTile))LogErr(L"Error releasing bmpTile !");
	if (!FreeMem(&bmpIntroTxt))LogErr(L"Error releasing bmpIntroTxt !");
	if (!FreeMem(&bmpSpareParts))LogErr(L"Error releasing bmpSpareParts !");
	if (!FreeMem(&bmpCloud1))LogErr(L"Error releasing bmpCloud1 !");
	if (!FreeMem(&bmpCloud2))LogErr(L"Error releasing bmpCloud2 !");
	if (!FreeMem(&bmpRiff1))LogErr(L"Error releasing bmpRiff1 !");
	if (!FreeMem(&bmpRiff2))LogErr(L"Error releasing bmpRiff2 !");
	if (!FreeMem(&bmpRiff3))LogErr(L"Error releasing bmpRiff3 !");

	for (int i = 0; i < 79; ++i)if (!FreeMem(&bmpIntro[i]))LogErr(L"Error releasing bmpIntro !");
	for (int i = 0; i < 64; ++i)if (!FreeMem(&bmpShot[i]))LogErr(L"Error releasing bmpShot !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpExplosion[i]))LogErr(L"Error releasing bmpExplosion !");

	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroU[i]))LogErr(L"Error releasing bmpHeroU !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroD[i]))LogErr(L"Error releasing bmpHeroD !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroL[i]))LogErr(L"Error releasing bmpHeroL !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroR[i]))LogErr(L"Error releasing bmpHeroR !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroUR[i]))LogErr(L"Error releasing bmpHeroUR !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroDR[i]))LogErr(L"Error releasing bmpHeroDR !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroDL[i]))LogErr(L"Error releasing bmpHeroDL !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroDR[i]))LogErr(L"Error releasing bmpHeroDR !");

	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1U[i]))LogErr(L"Error releasing bmpFighter1U !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1D[i]))LogErr(L"Error releasing bmpFighter1D !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1L[i]))LogErr(L"Error releasing bmpFighter1L !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1R[i]))LogErr(L"Error releasing bmpFighter1R !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1UR[i]))LogErr(L"Error releasing bmpFighter1UR !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1DR[i]))LogErr(L"Error releasing bmpFighter1DR !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1DL[i]))LogErr(L"Error releasing bmpFighter1DL !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1DR[i]))LogErr(L"Error releasing bmpFighter1DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2U[i]))LogErr(L"Error releasing bmpFighter2U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2D[i]))LogErr(L"Error releasing bmpFighter2D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2L[i]))LogErr(L"Error releasing bmpFighter2L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2R[i]))LogErr(L"Error releasing bmpFighter2R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2UR[i]))LogErr(L"Error releasing bmpFighter2UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2DR[i]))LogErr(L"Error releasing bmpFighter2DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2DL[i]))LogErr(L"Error releasing bmpFighter2DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2DR[i]))LogErr(L"Error releasing bmpFighter2DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3U[i]))LogErr(L"Error releasing bmpFighter3U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3D[i]))LogErr(L"Error releasing bmpFighter3D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3L[i]))LogErr(L"Error releasing bmpFighter3L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3R[i]))LogErr(L"Error releasing bmpFighter3R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3UR[i]))LogErr(L"Error releasing bmpFighter3UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3DR[i]))LogErr(L"Error releasing bmpFighter3DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3DL[i]))LogErr(L"Error releasing bmpFighter3DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3DR[i]))LogErr(L"Error releasing bmpFighter3DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4U[i]))LogErr(L"Error releasing bmpFighter4U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4D[i]))LogErr(L"Error releasing bmpFighter4D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4L[i]))LogErr(L"Error releasing bmpFighter4L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4R[i]))LogErr(L"Error releasing bmpFighter4R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4UR[i]))LogErr(L"Error releasing bmpFighter4UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4DR[i]))LogErr(L"Error releasing bmpFighter4DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4DL[i]))LogErr(L"Error releasing bmpFighter4DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4DR[i]))LogErr(L"Error releasing bmpFighter4DR !");

	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1U[i]))LogErr(L"Error releasing bmpBoss1U !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1D[i]))LogErr(L"Error releasing bmpBoss1D !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1L[i]))LogErr(L"Error releasing bmpBoss1L !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1R[i]))LogErr(L"Error releasing bmpBoss1R !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1UR[i]))LogErr(L"Error releasing bmpBoss1UR !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1DR[i]))LogErr(L"Error releasing bmpBoss1DR !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1DL[i]))LogErr(L"Error releasing bmpBoss1DL !");
	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1DR[i]))LogErr(L"Error releasing bmpBoss1DR !");

	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2U[i]))LogErr(L"Error releasing bmpBoss2U !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2D[i]))LogErr(L"Error releasing bmpBoss2D !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2L[i]))LogErr(L"Error releasing bmpBoss2L !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2R[i]))LogErr(L"Error releasing bmpBoss2R !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2UR[i]))LogErr(L"Error releasing bmpBoss2UR !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2DR[i]))LogErr(L"Error releasing bmpBoss2DR !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2DL[i]))LogErr(L"Error releasing bmpBoss2DL !");
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2DR[i]))LogErr(L"Error releasing bmpBoss2DR !");

	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3U[i]))LogErr(L"Error releasing bmpBoss3U !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3D[i]))LogErr(L"Error releasing bmpBoss3D !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3L[i]))LogErr(L"Error releasing bmpBoss3L !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3R[i]))LogErr(L"Error releasing bmpBoss3R !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3UR[i]))LogErr(L"Error releasing bmpBoss3UR !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3DR[i]))LogErr(L"Error releasing bmpBoss3DR !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3DL[i]))LogErr(L"Error releasing bmpBoss3DL !");
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3DR[i]))LogErr(L"Error releasing bmpBoss3DR !");
}
void ErrExit(int what)
{
	MessageBeep(MB_ICONERROR);
	MessageBox(NULL, ErrHandle(what), L"Критична грешка !", MB_OK | MB_APPLMODAL | MB_ICONERROR);

	ReleaseResources();
	std::remove(tmp_file);
	exit(1);
}

void GameOver()
{
	KillTimer(bHwnd, bTimer);
	PlaySound(NULL, NULL, NULL);


	bMsg.message = WM_QUIT;
	bMsg.wParam = 0;
}
void InitGame()
{
	hero_killed = false;
	boss_active = false;

	assets_dir = dirs::stop;

	wcscpy_s(current_player, L"TARLYO");

	level = 1;
	mins = 0;
	secs = 300;
	score = 0;

	if (!vTiles.empty())for (int i = 0; i < vTiles.size(); ++i)FreeMem(&vTiles[i]);
	vTiles.clear();

	for (float rows = 0; rows < 800.0f; rows += 50.0f)
	{
		for (float cols = -50.0f; cols <= scr_width; cols += 50.0f)
		{
			vTiles.push_back(dll::TILE::create(cols, rows));
		}
	}

}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
	switch (ReceivedMsg)
	{
	case WM_INITDIALOG:
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)(mainIcon));
		return true;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;

		case IDOK:
			if (GetDlgItemText(hwnd, IDC_NAME, current_player, 16) < 1)
			{
				wcscpy_s(current_player, L"TARLYO");
				if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);

				MessageBox(bHwnd, L"Ха, ха, ха ! Забрави си името !", L"Забраватор !", MB_OK | MB_APPLMODAL | MB_ICONEXCLAMATION);
				EndDialog(hwnd, IDCANCEL);
				break;
			}
			EndDialog(hwnd, IDOK);
			break;
		}
		break;
	}

	return (INT_PTR)(FALSE);
}
LRESULT CALLBACK WinProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
	switch (ReceivedMsg)
	{
	case WM_CREATE:
		if (bIns)
		{
			SetTimer(hwnd, bTimer, 1000, NULL);

			bBar = CreateMenu();
			bMain = CreateMenu();
			bStore = CreateMenu();

			AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bMain), L"Основно меню");
			AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bStore), L"Меню за данни");

			AppendMenu(bMain, MF_STRING, mNew, L"Нова игра");
			AppendMenu(bMain, MF_SEPARATOR, NULL, NULL);
			AppendMenu(bMain, MF_STRING, mExit, L"Изход");

			AppendMenu(bStore, MF_STRING, mSave, L"Запази игра");
			AppendMenu(bStore, MF_STRING, mLoad, L"Зареди игра");
			AppendMenu(bStore, MF_SEPARATOR, NULL, NULL);
			AppendMenu(bStore, MF_STRING, mHoF, L"Зала на славата");

			SetMenu(hwnd, bBar);
			InitGame();
		}
		break;

	case WM_CLOSE:
		pause = true;
		if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
		if (MessageBox(hwnd, L"Ако излезеш, ще загубиш тази игра !\n\nНаистина ли излизаш ?",
			L"Изход ?", MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
		{
			pause = false;
			break;
		}
		GameOver();
		break;

	case WM_PAINT:
		PaintDC = BeginPaint(hwnd, &bPaint);
		FillRect(PaintDC, &bPaint.rcPaint, CreateSolidBrush(RGB(10, 10, 10)));
		EndPaint(hwnd, &bPaint);
		break;

	case WM_SETCURSOR:
		GetCursorPos(&cur_pos);
		ScreenToClient(hwnd, &cur_pos);
		if (LOWORD(lParam) == HTCLIENT)
		{
			if (cur_pos.y * scale_y <= 50)
			{
				if (!in_client)
				{
					in_client = true;
					pause = false;
				}

				if (cur_pos.x * scale_x >= b1Rect.left && cur_pos.x * scale_x <= b1Rect.right)
				{
					if (!b1Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
						b1Hglt = true;
						b2Hglt = false;
						b3Hglt = false;
					}
				}
				else if (cur_pos.x * scale_x >= b2Rect.left && cur_pos.x * scale_x <= b2Rect.right)
				{
					if (!b2Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
						b1Hglt = false;
						b2Hglt = true;
						b3Hglt = false;
					}
				}
				else if (cur_pos.x * scale_x >= b3Rect.left && cur_pos.x * scale_x <= b3Rect.right)
				{
					if (!b3Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
						b1Hglt = false;
						b2Hglt = false;
						b3Hglt = true;
					}
				}
				else
				{
					if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
					b1Hglt = false;
					b2Hglt = false;
					b3Hglt = false;
				}

				SetCursor(outCur);
				return true;
			}
			else if (b1Hglt || b2Hglt || b3Hglt)
			{
				if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
				b1Hglt = false;
				b2Hglt = false;
				b3Hglt = false;
			}

			SetCursor(mainCur);
			return true;
		}
		else
		{
			if (in_client)
			{
				in_client = false;
				pause = true;
			}

			if (b1Hglt || b2Hglt || b3Hglt)
			{
				if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
				b1Hglt = false;
				b2Hglt = false;
				b3Hglt = false;
			}

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			return true;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case mNew:
			pause = true;
			if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
			if (MessageBox(hwnd, L"Ако рестартираш, ще загубиш тази игра !\n\nНаистина ли рестартираш ?",
				L"Рестарт ?", MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
			{
				pause = false;
				break;
			}
			InitGame();
			break;

		case mExit:
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;

		}
		break;




	default: return DefWindowProc(hwnd, ReceivedMsg, wParam, lParam);
	}

	return (LRESULT)(FALSE);
}











/// ///////////////////////////////////////////////

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	setlocale(LOCALE_ALL, "");

	bIns = hInstance;
	if (!bIns)ErrExit(eClass);













	ReleaseResources();
	std::remove(tmp_file);

    return (int) bMsg.wParam;
}
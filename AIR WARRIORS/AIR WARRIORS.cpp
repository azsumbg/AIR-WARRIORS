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

D2D1_RECT_F b1TxtRect{ 110.0f, 10.0f, scr_width / 3 - 50.0f, 50.0f };
D2D1_RECT_F b2TxtRect{ scr_width / 3 + 60.0f, 10.0f, scr_width * 2 / 3 - 50.0f, 50.0f };
D2D1_RECT_F b3TxtRect{ scr_width * 2 / 3 + 50.0f, 10.0f, scr_width - 50.0f, 50.0f };

ID2D1Factory* iFactory{ nullptr };
ID2D1HwndRenderTarget* Draw{ nullptr };

ID2D1RadialGradientBrush* b1BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b2BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b3BckgBrush{ nullptr };

ID2D1SolidColorBrush* TextBrush{ nullptr };
ID2D1SolidColorBrush* InactBrush{ nullptr };
ID2D1SolidColorBrush* HgltBrush{ nullptr };
ID2D1SolidColorBrush* StatBrush{ nullptr };

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
ID2D1Bitmap* bmpLevelUpTxt{ nullptr };
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

ID2D1Bitmap* bmpBoss1[4]{ nullptr };

ID2D1Bitmap* bmpBoss2[2]{ nullptr };

ID2D1Bitmap* bmpBoss3[10]{ nullptr };

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
bool level_passed = false;

wchar_t current_player[16]{ L"TARLYO" };

dirs assets_dir{ dirs::stop };

struct TILE_ADD_INFO
{
	dirs dir;
	float need_point;
};

struct EXPLOSION
{
	FPOINT center;
	int delay = 5;
	int frame = 0;
};

int level = 1;
int mins = 0;
int secs = 300;
int score = 0;

float scale_x{ 0 };
float scale_y{ 0 };

//////////////////////////////////////////////

dll::RANDIT RandIt{};

std::vector<dll::TILE*>vTiles;

dll::HERO Hero{ scr_width / 2.0f, ground - 100.0f };

std::vector<dll::ASSETS*>vAssets;

std::vector<dll::SHOT*>vShots;

std::vector<dll::EVILS*>vEvils;

std::vector<EXPLOSION>vExplosions;

std::vector<dll::PROTON*> vSpareParts;

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
	static int frame{ 0 };
	static int delay{ 5 };

	--delay;
	if (delay < 0)
	{
		delay = 5;
		++frame;
		if (frame > 78)frame = 0;
	}
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
	if (!FreeMem(&StatBrush))LogErr(L"Error releasing D2D1 StatBrush !");

	if (!FreeMem(&iWriteFactory))LogErr(L"Error releasing D2D1 main WriteFactory !");
	if (!FreeMem(&nrmFormat))LogErr(L"Error releasing DWrite nrmFormat !");
	if (!FreeMem(&midFormat))LogErr(L"Error releasing DWrite midFormat !");
	if (!FreeMem(&bigFormat))LogErr(L"Error releasing DWrite bigFormat !");

	if (!FreeMem(&bmpTile))LogErr(L"Error releasing bmpTile !");
	if (!FreeMem(&bmpIntroTxt))LogErr(L"Error releasing bmpIntroTxt !");
	if (!FreeMem(&bmpLevelUpTxt))LogErr(L"Error releasing bmpLevelUpTxt !");
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
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroUL[i]))LogErr(L"Error releasing bmpHeroDR !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroDL[i]))LogErr(L"Error releasing bmpHeroDL !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpHeroDR[i]))LogErr(L"Error releasing bmpHeroDR !");

	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1U[i]))LogErr(L"Error releasing bmpFighter1U !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1D[i]))LogErr(L"Error releasing bmpFighter1D !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1L[i]))LogErr(L"Error releasing bmpFighter1L !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1R[i]))LogErr(L"Error releasing bmpFighter1R !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1UR[i]))LogErr(L"Error releasing bmpFighter1UR !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1DR[i]))LogErr(L"Error releasing bmpFighter1DR !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1DL[i]))LogErr(L"Error releasing bmpFighter1DL !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpFighter1UL[i]))LogErr(L"Error releasing bmpFighter1DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2U[i]))LogErr(L"Error releasing bmpFighter2U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2D[i]))LogErr(L"Error releasing bmpFighter2D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2L[i]))LogErr(L"Error releasing bmpFighter2L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2R[i]))LogErr(L"Error releasing bmpFighter2R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2UR[i]))LogErr(L"Error releasing bmpFighter2UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2DR[i]))LogErr(L"Error releasing bmpFighter2DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2DL[i]))LogErr(L"Error releasing bmpFighter2DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter2UL[i]))LogErr(L"Error releasing bmpFighter2DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3U[i]))LogErr(L"Error releasing bmpFighter3U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3D[i]))LogErr(L"Error releasing bmpFighter3D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3L[i]))LogErr(L"Error releasing bmpFighter3L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3R[i]))LogErr(L"Error releasing bmpFighter3R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3UR[i]))LogErr(L"Error releasing bmpFighter3UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3DR[i]))LogErr(L"Error releasing bmpFighter3DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3DL[i]))LogErr(L"Error releasing bmpFighter3DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter3UL[i]))LogErr(L"Error releasing bmpFighter3DR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4U[i]))LogErr(L"Error releasing bmpFighter4U !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4D[i]))LogErr(L"Error releasing bmpFighter4D !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4L[i]))LogErr(L"Error releasing bmpFighter4L !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4R[i]))LogErr(L"Error releasing bmpFighter4R !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4UR[i]))LogErr(L"Error releasing bmpFighter4UR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4DR[i]))LogErr(L"Error releasing bmpFighter4DR !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4DL[i]))LogErr(L"Error releasing bmpFighter4DL !");
	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpFighter4UL[i]))LogErr(L"Error releasing bmpFighter4DR !");

	for (int i = 0; i < 4; ++i)if (!FreeMem(&bmpBoss1[i]))LogErr(L"Error releasing bmpBoss1 !");
	
	for (int i = 0; i < 2; ++i)if (!FreeMem(&bmpBoss2[i]))LogErr(L"Error releasing bmpBoss2 !");
	
	for (int i = 0; i < 10; ++i)if (!FreeMem(&bmpBoss3[i]))LogErr(L"Error releasing bmpBoss3 !");
}
void ErrExit(int what)
{
	MessageBeep(MB_ICONERROR);
	MessageBox(NULL, ErrHandle(what), L"Критична грешка !", MB_OK | MB_APPLMODAL | MB_ICONERROR);

	ReleaseResources();
	std::remove(tmp_file);
	exit(1);
}
BOOL CheckRecord()
{
	if (score < 1)return no_record;

	int result{ 0 };

	CheckFile(record_file, &result);

	if (result == FILE_NOT_EXIST)
	{
		std::wofstream rec(record_file);
		rec << score << std::endl;
		for (int i = 0; i < 16; ++i)rec << static_cast<int>(current_player[i]) << std::endl;
		rec.close();
		return first_record;
	}
	else
	{
		std::wifstream check(record_file);
		check >> result;
		check.close();
	}

	if (result < score)
	{
		std::wofstream rec(record_file);
		rec << score << std::endl;
		for (int i = 0; i < 16; ++i)rec << static_cast<int>(current_player[i]) << std::endl;
		rec.close();
		return record;
	}

	return no_record;
}
void GameOver()
{
	KillTimer(bHwnd, bTimer);
	PlaySound(NULL, NULL, NULL);

	switch (CheckRecord())
	{
	case no_record:
		if (bigFormat && InactBrush)
		{
			Draw->BeginDraw();
			Draw->Clear(D2D1::ColorF(D2D1::ColorF::DarkCyan));
			Draw->DrawTextW(L"О, О, О ! ЗАГУБИ !", 19, bigFormat, D2D1::RectF(100.0F, 150.0F, scr_width, scr_height), InactBrush);
			Draw->EndDraw();
		}
		if (sound)
		{
			PlaySound(L".\\res\\snd\\loose.wav", NULL, SND_SYNC);
			Sleep(1500);
		}
		else Sleep(3000);
		break;

	case first_record:
		if (bigFormat && InactBrush)
		{
			Draw->BeginDraw();
			Draw->Clear(D2D1::ColorF(D2D1::ColorF::DarkCyan));
			Draw->DrawTextW(L"ПЪРВИ РЕКОРД НА ИГРАТА !", 25, bigFormat, D2D1::RectF(30.0F, 150.0F, scr_width, scr_height), InactBrush);
			Draw->EndDraw();
		}
		if (sound)
		{
			PlaySound(L".\\res\\snd\\record.wav", NULL, SND_SYNC);
			Sleep(1500);
		}
		else Sleep(3000);
		break;

	case record:
		if (bigFormat && InactBrush)
		{
			Draw->BeginDraw();
			Draw->Clear(D2D1::ColorF(D2D1::ColorF::DarkCyan));
			Draw->DrawTextW(L"СВЕТОВЕН РЕКОРД НА ИГРАТА !", 28, bigFormat, D2D1::RectF(10.0F, 150.0F, scr_width, scr_height), InactBrush);
			Draw->EndDraw();
		}
		if (sound)
		{
			PlaySound(L".\\res\\snd\\record.wav", NULL, SND_SYNC);
			Sleep(1500);
		}
		else Sleep(3000);
		break;
	}

	bMsg.message = WM_QUIT;
	bMsg.wParam = 0;
}
void InitGame()
{
	hero_killed = false;
	boss_active = false;
	level_passed = false;

	assets_dir = dirs::stop;

	wcscpy_s(current_player, L"TARLYO");

	level = 1;
	mins = 0;
	secs = 300 + level * 10;
	score = 0;

	if (!vTiles.empty())for (int i = 0; i < vTiles.size(); ++i)FreeMem(&vTiles[i]);
	vTiles.clear();

	for (float rows = 0; rows < 800.0f; rows += 50.0f)
	{
		for (float cols = -50.0f; cols <= scr_width + 50.0f; cols += 50.0f)
		{
			vTiles.push_back(dll::TILE::create(cols, rows));
		}
	}

	if (!vAssets.empty())for (int i = 0; i < vAssets.size(); ++i)FreeMem(&vAssets[i]);
	vAssets.clear();

	if (!vShots.empty())for (int i = 0; i < vShots.size(); ++i)FreeMem(&vShots[i]);
	vShots.clear();

	if (!vEvils.empty())for (int i = 0; i < vEvils.size(); ++i)FreeMem(&vEvils[i]);
	vEvils.clear();

	if (!vSpareParts.empty())for (int i = 0; i < vSpareParts.size(); ++i)FreeMem(&vSpareParts[i]);
	vSpareParts.clear();

	vExplosions.clear();
}
void LevelUp()
{
	Draw->BeginDraw();
	Draw->DrawBitmap(bmpLevelUpTxt, D2D1::RectF(0, 0, scr_width, scr_height));
	Draw->EndDraw();

	mciSendString(L".play .\\res\\snd\\levelup.wav", NULL, NULL, NULL);
	Sleep(3000);

	boss_active = false;
	level_passed = false;

	assets_dir = dirs::stop;

	++level;

	mins = 0;
	secs = 300 + level * 10;

	if (!vTiles.empty())for (int i = 0; i < vTiles.size(); ++i)FreeMem(&vTiles[i]);
	vTiles.clear();

	for (float rows = 0; rows < 800.0f; rows += 50.0f)
	{
		for (float cols = -50.0f; cols <= scr_width + 50.0f; cols += 50.0f)
		{
			vTiles.push_back(dll::TILE::create(cols, rows));
		}
	}

	if (!vAssets.empty())for (int i = 0; i < vAssets.size(); ++i)FreeMem(&vAssets[i]);
	vAssets.clear();

	if (!vShots.empty())for (int i = 0; i < vShots.size(); ++i)FreeMem(&vShots[i]);
	vShots.clear();

	if (!vEvils.empty())for (int i = 0; i < vEvils.size(); ++i)FreeMem(&vEvils[i]);
	vEvils.clear();

	if (!vSpareParts.empty())for (int i = 0; i < vSpareParts.size(); ++i)FreeMem(&vSpareParts[i]);
	vSpareParts.clear();

	vExplosions.clear();

	Hero.start.x = scr_width / 2.0f; 
	Hero.start.y = ground - 100.0f;
	Hero.set_edges();
	Hero.lifes = 100 + level * 20;

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
			if (!in_client)
			{
				in_client = true;
				pause = false;
			}

			if (cur_pos.y * scale_y <= 50)
			{
				

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

	case WM_TIMER:
		if (pause)break;
		if (secs <= 0)
		{
			if (!boss_active)
			{
				boss_active = true;
			
				vEvils.push_back(dll::EVILS::create(static_cast<planes>(RandIt(4, 6)), (float)(RandIt(0, 1000)), sky - 50.0f));
			}
			break;
		}
		--secs;
		mins = secs / 60;
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

	case WM_CHAR:
		switch (wParam)
		{
		case 'w':
			Hero.dir = dirs::up;
			break;

		case 'x':
			Hero.dir = dirs::down;
			break;

		case 'a':
			Hero.dir = dirs::left;
			break;

		case 'd':
			Hero.dir = dirs::right;
			break;

		case 'q':
			Hero.dir = dirs::up_left;
			break;

		case 'e':
			Hero.dir = dirs::up_right;
			break;

		case 'z':
			Hero.dir = dirs::down_left;
			break;

		case 'c':
			Hero.dir = dirs::down_right;
			break;

		case 's':
			Hero.dir = dirs::stop;
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_CONTROL:
			switch (Hero.dir)
			{
			case dirs::stop:
				vShots.push_back(dll::SHOT::create(Hero.center.x, Hero.start.y - 18.0f, Hero.center.x, 0));
				break;

			case dirs::up:
				vShots.push_back(dll::SHOT::create(Hero.center.x, Hero.start.y - 18.0f, Hero.center.x, 0));
				break;

			case dirs::down:
				vShots.push_back(dll::SHOT::create(Hero.center.x, Hero.end.y + 18.0f, Hero.center.x, scr_height));
				break;

			case dirs::left:
				vShots.push_back(dll::SHOT::create(Hero.start.x - 18.0f, Hero.center.y, 0, Hero.center.y));
				break;

			case dirs::right:
				vShots.push_back(dll::SHOT::create(Hero.end.x + 18.0f, Hero.center.y, scr_width, Hero.center.y));
				break;

			case dirs::up_left:
				vShots.push_back(dll::SHOT::create(Hero.start.x - 18.0f, Hero.start.y, 0, 0));
				break;

			case dirs::down_left:
				vShots.push_back(dll::SHOT::create(Hero.start.x - 18.0f, Hero.end.y, 0, scr_height));
				break;

			case dirs::up_right:
				vShots.push_back(dll::SHOT::create(Hero.end.x + 18.0f, Hero.start.y, scr_width, 0));
				break;

			case dirs::down_right:
				vShots.push_back(dll::SHOT::create(Hero.end.x + 18.0f, Hero.end.y, scr_width, scr_height));
				break;

			}
			if (!vShots.empty())
			{
				vShots.back()->strenght = 40;
			}
			break;

		case VK_SPACE:
			if (pause)pause = false;
			else pause = true;
			break;
		}
		break;


	default: return DefWindowProc(hwnd, ReceivedMsg, wParam, lParam);
	}

	return (LRESULT)(FALSE);
}

void CreateResources()
{
	int result{ 0 };
	CheckFile(Ltmp_file, &result);
	if (result == FILE_EXIST)ErrExit(eStarted);
	else
	{
		std::wofstream start{ Ltmp_file };
		start << L"Game started at: " << std::chrono::system_clock::now();
		start.close();
	}

	int win_x = (int)(GetSystemMetrics(SM_CXSCREEN) / 2 - (int)(scr_width / 2.0f));
	int win_y = 10;

	if (GetSystemMetrics(SM_CXSCREEN) < win_x + (int)(scr_width) || GetSystemMetrics(SM_CYSCREEN) < win_y + (int)(scr_height))
		ErrExit(eScreen);

	mainIcon = (HICON)(LoadImage(NULL, L".\\res\\main.ico", IMAGE_ICON, 255, 255, LR_LOADFROMFILE));
	if (!mainIcon)ErrExit(eIcon);
	mainCur = LoadCursorFromFile(L".\\res\\main.ani");
	outCur = LoadCursorFromFile(L".\\res\\out.ani");
	if (!mainCur || !outCur)ErrExit(eCursor);

	bWinClass.lpszClassName = bWinClassName;
	bWinClass.hInstance = bIns;
	bWinClass.lpfnWndProc = &WinProc;
	bWinClass.hbrBackground = CreateSolidBrush(RGB(10, 10, 10));
	bWinClass.hIcon = mainIcon;
	bWinClass.hCursor = mainCur;
	bWinClass.style = CS_DROPSHADOW;

	if (!RegisterClass(&bWinClass))ErrExit(eClass);

	bHwnd = CreateWindow(bWinClassName, L"БИТКА НА АСОВЕ", WS_CAPTION | WS_SYSMENU, win_x, win_y, (int)(scr_width),
		(int)(scr_height), NULL, NULL, bIns, NULL);
	if (!bHwnd)ErrExit(eWindow);
	else
	{
		ShowWindow(bHwnd, SW_SHOWDEFAULT);

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &iFactory);
		if (hr != S_OK)
		{
			LogErr(L"Error creating D2D1 main Factory !");
			ErrExit(eD2D);
		}

		if (iFactory)
		{
			hr = iFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(bHwnd,
				D2D1::SizeU((UINT32)(scr_width), (UINT32)(scr_height))), &Draw);
			if (hr != S_OK)
			{
				LogErr(L"Error creating D2D1 hwnd Render target !");
				ErrExit(eD2D);
			}

			if (Draw)
			{
				RECT ClRect{};
				D2D1_SIZE_F HwndRect = Draw->GetSize();

				GetClientRect(bHwnd, &ClRect);
				
				scale_x = HwndRect.width / (ClRect.right - ClRect.left);
				scale_y = HwndRect.height / (ClRect.bottom - ClRect.top);

				D2D1_GRADIENT_STOP gSt[2]{};
				ID2D1GradientStopCollection* gColl{ nullptr };

				gSt[0].position = 0;
				gSt[0].color = D2D1::ColorF(D2D1::ColorF::RosyBrown);
				gSt[1].position = 1.0f;
				gSt[1].color = D2D1::ColorF(D2D1::ColorF::Firebrick);

				hr = Draw->CreateGradientStopCollection(gSt, 2, &gColl);

				if (hr != S_OK)
				{
					LogErr(L"Error creating D2D1 GradientStopCollection !");
					ErrExit(eD2D);
				}

				if (gColl)
				{
					hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b1Rect.right - b1Rect.left) / 2.0f, 25.0f), D2D1::Point2F(0, 0), (b1Rect.right - b1Rect.left) / 2.0f, 25.0f), gColl, &b1BckgBrush);
					hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b2Rect.right - b2Rect.left) / 2.0f, 25.0f), D2D1::Point2F(0, 0), (b2Rect.right - b2Rect.left) / 2.0f, 25.0f), gColl, &b2BckgBrush);
					hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b3Rect.right - b3Rect.left) / 2.0f, 25.0f), D2D1::Point2F(0, 0), (b3Rect.right - b3Rect.left) / 2.0f, 25.0f), gColl, &b3BckgBrush);

					if (hr != S_OK)
					{
						LogErr(L"Error creating D2D1 Buttons background brushes !");
						ErrExit(eD2D);
					}

					FreeMem(&gColl);
				}

				hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lime), &TextBrush);
				hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Goldenrod), &HgltBrush);
				hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue), &InactBrush);
				hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkKhaki), &StatBrush);

				if (hr != S_OK)
				{
					LogErr(L"Error creating D2D1 Text brushes !");
					ErrExit(eD2D);
				}

				bmpTile = Load(L".\\res\\img\\tile.png", Draw);
				if (!bmpTile)
				{
					LogErr(L"Error loading bmpTile !");
					ErrExit(eD2D);
				}
				bmpCloud1 = Load(L".\\res\\img\\cloud1.png", Draw);
				if (!bmpCloud1)
				{
					LogErr(L"Error loading bmpCloud1 !");
					ErrExit(eD2D);
				}
				bmpCloud2 = Load(L".\\res\\img\\cloud2.png", Draw);
				if (!bmpCloud2)
				{
					LogErr(L"Error loading bmpCloud2 !");
					ErrExit(eD2D);
				}
				bmpRiff1 = Load(L".\\res\\img\\riff1.png", Draw);
				if (!bmpRiff1)
				{
					LogErr(L"Error loading bmpRiff1 !");
					ErrExit(eD2D);
				}
				bmpRiff2 = Load(L".\\res\\img\\riff2.png", Draw);
				if (!bmpRiff2)
				{
					LogErr(L"Error loading bmpRiff2 !");
					ErrExit(eD2D);
				}
				bmpRiff3 = Load(L".\\res\\img\\riff3.png", Draw);
				if (!bmpRiff3)
				{
					LogErr(L"Error loading bmpRiff3 !");
					ErrExit(eD2D);
				}
				bmpIntroTxt = Load(L".\\res\\img\\Intro_text.png", Draw);
				if (!bmpIntroTxt)
				{
					LogErr(L"Error loading bmpIntroTxt !");
					ErrExit(eD2D);
				}
				bmpLevelUpTxt = Load(L".\\res\\img\\levelup_text.png", Draw);
				if (!bmpLevelUpTxt)
				{
					LogErr(L"Error loading bmpLevelUpTxt !");
					ErrExit(eD2D);
				}
				bmpSpareParts = Load(L".\\res\\img\\Spare_Parts.png", Draw);
				if (!bmpSpareParts)
				{
					LogErr(L"Error loading bmpSpareParts !");
					ErrExit(eD2D);
				}

				for (int i = 0; i < 79; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\intro\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpIntro[i] = Load(name, Draw);
					if (!bmpIntro[i])
					{
						LogErr(L"Error loading bmpIntro !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\shot\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpShot[i] = Load(name, Draw);
					if (!bmpShot[i])
					{
						LogErr(L"Error loading bmpShot !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\explosion\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpExplosion[i] = Load(name, Draw);
					if (!bmpExplosion[i])
					{
						LogErr(L"Error loading bmpExplosion !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\up\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroU[i] = Load(name, Draw);
					if (!bmpHeroU[i])
					{
						LogErr(L"Error loading bmpHeroU !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\down\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroD[i] = Load(name, Draw);
					if (!bmpHeroD[i])
					{
						LogErr(L"Error loading bmpHeroD !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\left\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroL[i] = Load(name, Draw);
					if (!bmpHeroL[i])
					{
						LogErr(L"Error loading bmpHeroL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\right\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroR[i] = Load(name, Draw);
					if (!bmpHeroR[i])
					{
						LogErr(L"Error loading bmpHeroR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\upleft\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroUL[i] = Load(name, Draw);
					if (!bmpHeroUL[i])
					{
						LogErr(L"Error loading bmpHeroUL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\upright\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroUR[i] = Load(name, Draw);
					if (!bmpHeroUR[i])
					{
						LogErr(L"Error loading bmpHeroUR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\downleft\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroDL[i] = Load(name, Draw);
					if (!bmpHeroDL[i])
					{
						LogErr(L"Error loading bmpHeroDL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\hero\\downright\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpHeroDR[i] = Load(name, Draw);
					if (!bmpHeroDR[i])
					{
						LogErr(L"Error loading bmpHeroDR !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\up\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1U[i] = Load(name, Draw);
					if (!bmpFighter1U[i])
					{
						LogErr(L"Error loading bmpFighter1U !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\down\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1D[i] = Load(name, Draw);
					if (!bmpFighter1D[i])
					{
						LogErr(L"Error loading bmpFighter1D !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\left\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1L[i] = Load(name, Draw);
					if (!bmpFighter1L[i])
					{
						LogErr(L"Error loading bmpFighter1L !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\right\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1R[i] = Load(name, Draw);
					if (!bmpFighter1R[i])
					{
						LogErr(L"Error loading bmpFighter1R !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\upleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1UL[i] = Load(name, Draw);
					if (!bmpFighter1UL[i])
					{
						LogErr(L"Error loading bmpFighter1UL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\upright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1UR[i] = Load(name, Draw);
					if (!bmpFighter1UR[i])
					{
						LogErr(L"Error loading bmpFighter1UR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\downleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1DL[i] = Load(name, Draw);
					if (!bmpFighter1DL[i])
					{
						LogErr(L"Error loading bmpFighter1DL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter1\\downright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter1DR[i] = Load(name, Draw);
					if (!bmpFighter1DR[i])
					{
						LogErr(L"Error loading bmpFighter1DR !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\up\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2U[i] = Load(name, Draw);
					if (!bmpFighter2U[i])
					{
						LogErr(L"Error loading bmpFighter2U !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\down\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2D[i] = Load(name, Draw);
					if (!bmpFighter2D[i])
					{
						LogErr(L"Error loading bmpFighter2D !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\left\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2L[i] = Load(name, Draw);
					if (!bmpFighter2L[i])
					{
						LogErr(L"Error loading bmpFighter2L !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\right\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2R[i] = Load(name, Draw);
					if (!bmpFighter2R[i])
					{
						LogErr(L"Error loading bmpFighter2R !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\upleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2UL[i] = Load(name, Draw);
					if (!bmpFighter2UL[i])
					{
						LogErr(L"Error loading bmpFighter2UL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\upright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2UR[i] = Load(name, Draw);
					if (!bmpFighter2UR[i])
					{
						LogErr(L"Error loading bmpFighter2UR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\downleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2DL[i] = Load(name, Draw);
					if (!bmpFighter2DL[i])
					{
						LogErr(L"Error loading bmpFighter2DL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter2\\downright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter2DR[i] = Load(name, Draw);
					if (!bmpFighter2DR[i])
					{
						LogErr(L"Error loading bmpFighter2DR !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\up\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3U[i] = Load(name, Draw);
					if (!bmpFighter3U[i])
					{
						LogErr(L"Error loading bmpFighter3U !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\down\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3D[i] = Load(name, Draw);
					if (!bmpFighter3D[i])
					{
						LogErr(L"Error loading bmpFighter3D !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\left\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3L[i] = Load(name, Draw);
					if (!bmpFighter3L[i])
					{
						LogErr(L"Error loading bmpFighter3L !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\right\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3R[i] = Load(name, Draw);
					if (!bmpFighter3R[i])
					{
						LogErr(L"Error loading bmpFighter3R !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\upleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3UL[i] = Load(name, Draw);
					if (!bmpFighter3UL[i])
					{
						LogErr(L"Error loading bmpFighter3UL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\upright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3UR[i] = Load(name, Draw);
					if (!bmpFighter3UR[i])
					{
						LogErr(L"Error loading bmpFighter3UR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\downleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3DL[i] = Load(name, Draw);
					if (!bmpFighter3DL[i])
					{
						LogErr(L"Error loading bmpFighter3DL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter3\\downright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter3DR[i] = Load(name, Draw);
					if (!bmpFighter3DR[i])
					{
						LogErr(L"Error loading bmpFighter3DR !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\up\\0" };
					wchar_t add[4]{ L"\0" };

					if (i < 10)wcscat_s(name, L"0");
					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4U[i] = Load(name, Draw);
					if (!bmpFighter4U[i])
					{
						LogErr(L"Error loading bmpFighter4U !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\down\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4D[i] = Load(name, Draw);
					if (!bmpFighter4D[i])
					{
						LogErr(L"Error loading bmpFighter4D !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\left\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4L[i] = Load(name, Draw);
					if (!bmpFighter4L[i])
					{
						LogErr(L"Error loading bmpFighter4L !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\right\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4R[i] = Load(name, Draw);
					if (!bmpFighter4R[i])
					{
						LogErr(L"Error loading bmpFighter4R !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\upleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4UL[i] = Load(name, Draw);
					if (!bmpFighter4UL[i])
					{
						LogErr(L"Error loading bmpFighter4UL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\upright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4UR[i] = Load(name, Draw);
					if (!bmpFighter4UR[i])
					{
						LogErr(L"Error loading bmpFighter4UR !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\downleft\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4DL[i] = Load(name, Draw);
					if (!bmpFighter4DL[i])
					{
						LogErr(L"Error loading bmpFighter4DL !");
						ErrExit(eD2D);
					}
				}
				for (int i = 0; i < 24; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Fighter4\\downright\\0" };
					wchar_t add[4]{ L"\0" };
					if (i < 10)wcscat_s(name, L"0");

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpFighter4DR[i] = Load(name, Draw);
					if (!bmpFighter4DR[i])
					{
						LogErr(L"Error loading bmpFighter4DR !");
						ErrExit(eD2D);
					}
				}

				for (int i = 0; i < 4; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Boss1\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpBoss1[i] = Load(name, Draw);
					if (!bmpBoss1[i])
					{
						LogErr(L"Error loading bmpBoss1 !");
						ErrExit(eD2D);
					}
				}
				
				for (int i = 0; i < 2; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Boss2\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpBoss2[i] = Load(name, Draw);
					if (!bmpBoss2[i])
					{
						LogErr(L"Error loading bmpBoss2 !");
						ErrExit(eD2D);
					}
				}
				
				for (int i = 0; i < 10; ++i)
				{
					wchar_t name[100]{ L".\\res\\img\\Boss3\\0" };
					wchar_t add[4]{ L"\0" };

					wsprintf(add, L"%d", i);
					wcscat_s(name, add);
					wcscat_s(name, L".png");

					bmpBoss3[i] = Load(name, Draw);
					if (!bmpBoss3[i])
					{
						LogErr(L"Error loading bmpBoss3 !");
						ErrExit(eD2D);
					}
				}
			}
		}

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
			reinterpret_cast<IUnknown**>(&iWriteFactory));
		if (hr != S_OK)
		{
			LogErr(L"Error creating D2D1 main WriteFactory !");
			ErrExit(eD2D);
		}

		if (iWriteFactory)
		{
			hr = iWriteFactory->CreateTextFormat(L"GABRIOLA", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 16, L"", &nrmFormat);
			hr = iWriteFactory->CreateTextFormat(L"GABRIOLA", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 32, L"", &midFormat);
			hr = iWriteFactory->CreateTextFormat(L"GABRIOLA", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 72, L"", &bigFormat);
			if (hr != S_OK)
			{
				LogErr(L"Error creating D2D1 WriteFactory text formats!");
				ErrExit(eD2D);
			}
		}
	}

	if (Draw)
	{
		mciSendString(L"play .\\res\\snd\\intro.wav", NULL, NULL, NULL);

		for (int i = 0; i < 100; ++i)
		{
			Draw->BeginDraw();
			Draw->DrawBitmap(bmpIntro[GetIntroFrame()], D2D1::RectF(0, 0, scr_width, scr_height));
			Draw->DrawBitmap(bmpIntroTxt, D2D1::RectF(0, 0, scr_width, scr_height));
			Draw->EndDraw();
		}

		Draw->BeginDraw();
		Draw->DrawBitmap(bmpIntro[GetIntroFrame()], D2D1::RectF(0, 0, scr_width, scr_height));
		Draw->DrawBitmap(bmpIntroTxt, D2D1::RectF(0, 0, scr_width, scr_height));
		Draw->EndDraw();

		PlaySound(L".\\res\\snd\\boom.wav", NULL, SND_SYNC);
	}
}

/// ///////////////////////////////////////////////

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	setlocale(LOCALE_ALL, "");

	bIns = hInstance;
	if (!bIns)ErrExit(eClass);


	CreateResources();

	while (bMsg.message != WM_QUIT)
	{
		if ((bRet = PeekMessage(&bMsg, bHwnd, NULL, NULL, PM_REMOVE)) != 0)
		{
			if (bRet == -1)ErrExit(eMsg);

			TranslateMessage(&bMsg);
			DispatchMessage(&bMsg);
		}

		if (pause)
		{
			if (show_help)continue;

			if (bigFormat && TextBrush)
			{
				Draw->BeginDraw();
				Draw->DrawBitmap(bmpIntro[GetIntroFrame()], D2D1::RectF(0, 0, scr_width, scr_height));
				Draw->DrawText(L"ПАУЗА", 6, bigFormat, D2D1::RectF(scr_width / 2.0f - 100.0f,
					scr_height / 2.0f - 50.0f, scr_width, scr_height), TextBrush);
				Draw->EndDraw();
			}
			continue;
		}

		//////////////////////////////////////////////////////////////////////

		if (!hero_killed)Hero.move((float)(level));

		if (!vTiles.empty())
		{
			std::vector<TILE_ADD_INFO> vAdds;
			vAdds.clear();

			for (std::vector<dll::TILE*>::iterator tile = vTiles.begin(); tile < vTiles.end(); ++tile)
			{
				(*tile)->dir = assets_dir;

				if (!(*tile)->move())
				{
					(*tile)->to_erase = true;

					switch ((*tile)->dir)
					{
					case dirs::up:
						vAdds.push_back(TILE_ADD_INFO{ dirs::up,(*tile)->start.x });
						break;

					case dirs::down:
						vAdds.push_back(TILE_ADD_INFO{ dirs::down,(*tile)->start.x });;
						break;

					case dirs::left:
						vAdds.push_back(TILE_ADD_INFO{ dirs::left,(*tile)->start.y });
						break;

					case dirs::right:
						vAdds.push_back(TILE_ADD_INFO{ dirs::right,(*tile)->start.y });
						break;

					case dirs::up_left:
						vAdds.push_back(TILE_ADD_INFO{ dirs::left,(*tile)->start.y });
						break;

					case dirs::up_right:
						vAdds.push_back(TILE_ADD_INFO{ dirs::right,(*tile)->start.y });
						break;

					case dirs::down_left:
						vAdds.push_back(TILE_ADD_INFO{ dirs::left,(*tile)->start.y });
						break;

					case dirs::down_right:
						vAdds.push_back(TILE_ADD_INFO{ dirs::right,(*tile)->start.y });
						break;
					}
				}
			}

			if (!vAdds.empty())
			{
				for (int i = 0; i < vAdds.size(); ++i)
				{
					switch (vAdds[i].dir)
					{
					case dirs::up:
						vTiles.push_back(dll::TILE::create(vAdds[i].need_point, ground));
						break;

					case dirs::down:
						vTiles.push_back(dll::TILE::create(vAdds[i].need_point, 0));
						break;

					case dirs::left:
						vTiles.push_back(dll::TILE::create(scr_width, vAdds[i].need_point));
						break;

					case dirs::right:
						vTiles.push_back(dll::TILE::create(-50.0f, vAdds[i].need_point));
						break;

					case dirs::up_left:
						vTiles.push_back(dll::TILE::create(scr_width, vAdds[i].need_point));
						break;

					case dirs::up_right:
						vTiles.push_back(dll::TILE::create(-50.0f, vAdds[i].need_point));
						break;

					case dirs::down_left:
						vTiles.push_back(dll::TILE::create(scr_width, vAdds[i].need_point));
						break;

					case dirs::down_right:
						vTiles.push_back(dll::TILE::create(-50.0f, vAdds[i].need_point));
						break;
					}
				}
			}
		}

		if (!vTiles.empty())
		{
			bool cleaned = false;
			while (!cleaned)
			{
				cleaned = true;

				for (std::vector<dll::TILE*>::iterator tile = vTiles.begin(); tile < vTiles.end(); ++tile)
				{
					if ((*tile)->to_erase)
					{
						(*tile)->Release();
						vTiles.erase(tile);
						cleaned = false;
						break;
					}
				}
			}
		}

		if (vAssets.size() < 6 && RandIt(0, 80) == 66)
		{
			int type = RandIt(0, 4);
			int direction = RandIt(0, 3);

			if (type < 2)
			{
				if (direction == 0 || direction == 2)
				{
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type), -100.0f,
						(float)(RandIt((int)(sky), 300))));
					vAssets.back()->dir = dirs::right;
				}
				else
				{
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type), scr_width + 100.0f,
						(float)(RandIt((int)(sky), 300))));
					vAssets.back()->dir = dirs::left;
				}
			}
			else
			{
				switch (direction)
				{
				case 0:
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type), -100.0f,
						(float)(RandIt((int)(sky), (int)(ground)))));
					vAssets.back()->dir = dirs::right;
					break;

				case 1:
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type), scr_width + 100.0f,
						(float)(RandIt((int)(sky), (int)(ground)))));
					vAssets.back()->dir = dirs::left;
					break;

				case 2:
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type),
						(float)(RandIt(0, (int)(scr_width - 100.0f))), -100.0f));
					vAssets.back()->dir = dirs::down;
					break;

				case 3:
					vAssets.push_back(dll::ASSETS::create(static_cast<assets>(type),
						(float)(RandIt(0, (int)(scr_width - 100.0f))), ground + 100.0f));
					vAssets.back()->dir = dirs::up;
					break;
				}
			}

		}

		if (!vAssets.empty())
		{
			for (std::vector<dll::ASSETS*>::iterator asset = vAssets.begin(); asset < vAssets.end(); ++asset)
			{
				if ((*asset)->get_type() != assets::cloud1 && (*asset)->get_type() != assets::cloud2)(*asset)->dir = assets_dir;

				if (!(*asset)->move((float)(level)))
				{
					(*asset)->Release();
					vAssets.erase(asset);
					break;
				}
			}
		}

		if (!vShots.empty())
		{
			for (std::vector<dll::SHOT*>::iterator shot = vShots.begin(); shot < vShots.end(); ++shot)
			{
				if (!(*shot)->Move((float)(level)))
				{
					(*shot)->Release();
					vShots.erase(shot);
					break;
				}
			}
		}

		if (!vShots.empty())
		{
			for (std::vector<dll::SHOT*>::iterator shot = vShots.begin(); shot < vShots.end(); ++shot)
			{
				if (dll::Intersect((*shot)->center, Hero.center, (*shot)->radius_x, Hero.radius_x, (*shot)->radius_y,
					Hero.radius_y))
				{
					Hero.lifes -= (*shot)->strenght;
					if (Hero.lifes <= 0)hero_killed = true;
					(*shot)->Release();
					vShots.erase(shot);
					break;
				}
			}

		}

		if (vEvils.size() < 5 + level && RandIt(0, 60) == 33)
		{
			if (RandIt(0, 1) == 0)
			{
				float first_x = 0;
				float first_y = (float)(RandIt(60, 200));

				for (int i = 0; i < 3; ++i)
				{
					vEvils.push_back(dll::EVILS::create(static_cast<planes>(RandIt(0, 3)), first_x, first_y));
					vEvils.back()->SetPathInfo(scr_width, ground);
					
					first_x -= 40.0f;
					first_y += 55.0f;
				
				}
			}
			else
			{
				float first_x = scr_width + 30.0f;
				float first_y = (float)RandIt(60, 200);

				for (int i = 0; i < 3; ++i)
				{
					vEvils.push_back(dll::EVILS::create(static_cast<planes>(RandIt(0, 3)), first_x, first_y));
					vEvils.back()->SetPathInfo(0, ground);
					first_x += 40.0f;
					first_y += 55.0f;
				}
			}
		}

		if (!vEvils.empty())
		{
			for (std::vector<dll::EVILS*>::iterator evil = vEvils.begin(); evil < vEvils.end(); ++evil)
			{
				dll::BAG<FPOINT> EvilBag(vEvils.size());
				dll::BAG<FPOINT>ShotBag(vShots.size());

				for (int i = 0; i < vEvils.size(); ++i)EvilBag.push_back(vEvils[i]->center);
				if (!vShots.empty())for (int i = 0; i < vShots.size(); ++i)ShotBag.push_back(vShots[i]->center);

				actions action = (*evil)->AI_move(Hero.center, EvilBag, ShotBag);

				switch (action)
				{
				case actions::move:
					if (!(*evil)->move((float)(level)))
					{
						switch ((*evil)->dir)
						{
						case dirs::up:
							(*evil)->SetPathInfo((*evil)->start.x, (*evil)->start.y + 200.0f);
							break;

						case dirs::down:
							(*evil)->SetPathInfo((*evil)->start.x, (*evil)->start.y - 200.0f);
							break;

						case dirs::left:
							(*evil)->SetPathInfo(scr_width, (*evil)->start.y + 100.0f);
							break;

						case dirs::right:
							(*evil)->SetPathInfo(0, (*evil)->start.y + 100.0f);
							break;

						case dirs::up_left:
							(*evil)->SetPathInfo(scr_width, (*evil)->start.y + 200.0f);
							break;

						case dirs::down_left:
							(*evil)->SetPathInfo(scr_width, (*evil)->start.y - 200.0f);
							break;

						case dirs::up_right:
							(*evil)->SetPathInfo(0, (*evil)->start.y + 200.0f);
							break;

						case dirs::down_right:
							(*evil)->SetPathInfo(0, (*evil)->start.y - 200.0f);
							break;
						}
					}
					break;

				case actions::flee:
					switch ((*evil)->dir)
					{
					case dirs::up:
						(*evil)->SetPathInfo((*evil)->start.x, (*evil)->start.y + 200.0f);
						break;

					case dirs::down:
						(*evil)->SetPathInfo((*evil)->start.x, (*evil)->start.y - 200.0f);
						break;

					case dirs::left:
						(*evil)->SetPathInfo(scr_width, (*evil)->start.y + 100.0f);
						break;

					case dirs::right:
						(*evil)->SetPathInfo(0, (*evil)->start.y + 100.0f);
						break;

					case dirs::up_left:
						(*evil)->SetPathInfo(scr_width, (*evil)->start.y + 200.0f);
						break;

					case dirs::down_left:
						(*evil)->SetPathInfo(scr_width, (*evil)->start.y - 200.0f);
						break;

					case dirs::up_right:
						(*evil)->SetPathInfo(0, (*evil)->start.y + 200.0f);
						break;

					case dirs::down_right:
						(*evil)->SetPathInfo(0, (*evil)->start.y - 200.0f);
						break;
					}
					break;

				case actions::shoot:
				{
					int blast = (*evil)->attack();
					if (blast > 0)
					{
						switch ((*evil)->dir)
						{
						case dirs::stop:
							vShots.push_back(dll::SHOT::create((*evil)->center.x, (*evil)->start.y - 18.0f, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::up:
							vShots.push_back(dll::SHOT::create((*evil)->center.x, (*evil)->start.y - 18.0f,
								Hero.center.x, Hero.center.y));
							break;

						case dirs::down:
							vShots.push_back(dll::SHOT::create((*evil)->center.x, (*evil)->end.y + 18.0f, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::left:
							vShots.push_back(dll::SHOT::create((*evil)->start.x - 18.0f, (*evil)->center.y, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::right:
							vShots.push_back(dll::SHOT::create((*evil)->end.x + 18.0f, (*evil)->center.y, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::up_left:
							vShots.push_back(dll::SHOT::create((*evil)->start.x - 18.0f, (*evil)->start.y, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::down_left:
							vShots.push_back(dll::SHOT::create((*evil)->start.x - 18.0f, (*evil)->end.y, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::up_right:
							vShots.push_back(dll::SHOT::create((*evil)->end.x + 18.0f, (*evil)->start.y, Hero.center.x,
								Hero.center.y));
							break;

						case dirs::down_right:
							vShots.push_back(dll::SHOT::create((*evil)->end.x + 18.0f, (*evil)->end.y, Hero.center.x,
								Hero.center.y));
							break;

						}

						vShots.back()->strenght = blast;
					}
				}
					break;
				}
			}
		}

		if (!vEvils.empty() && !vShots.empty())
		{
			for (std::vector<dll::EVILS*>::iterator evil = vEvils.begin(); evil < vEvils.end(); ++evil)
			{
				bool killed = false;

				for (std::vector<dll::SHOT*>::iterator shot = vShots.begin(); shot < vShots.end(); ++shot)
				{
					if (dll::Intersect((*evil)->center, (*shot)->center, (*evil)->radius_x, (*shot)->radius_x,
						(*evil)->radius_y, (*shot)->radius_y))
					{
						(*evil)->lifes -= (*shot)->strenght;
						(*shot)->Release();
						vShots.erase(shot);

						if ((*evil)->lifes <= 0)
						{
							vExplosions.push_back(EXPLOSION{ FPOINT{(*evil)->center} });
							if (RandIt(0, 10) == 6)
								vSpareParts.push_back(dll::PROTON::create((*evil)->start.x, (*evil)->start.y, 40.0f, 40.0f));
							
							if ((*evil)->get_type() == planes::boss1 || (*evil)->get_type() == planes::boss2 ||
								(*evil)->get_type() == planes::boss3)
							{
								score += 50 + level * 20;
								level_passed = true;
							}
							(*evil)->Release();
							vEvils.erase(evil);
							killed = true;
							score += 10 * level;
						}
						break;
					}
				}

				if (killed)break;
			}
		}

		if (!vEvils.empty())
		{
			for (int i = 0; i < vEvils.size() - 1; ++i)
			{
				if (dll::Intersect(vEvils[i]->center, vEvils[i + 1]->center, vEvils[i]->radius_x, vEvils[i + 1]->radius_x,
					vEvils[i]->radius_y, vEvils[i + 1]->radius_y))
				{
					vExplosions.push_back(EXPLOSION{ vEvils[i]->center });
					vExplosions.push_back(EXPLOSION{ vEvils[i + 1]->center });

					vEvils[i]->lifes = 0;
					vEvils[i + 1]->lifes = 0;
					break;
				}
			}

			bool cleared = false;
			while (!cleared)
			{
				cleared = true;
				
				for (int i = 0; i < vEvils.size(); ++i)
				{
					if (vEvils[i]->lifes == 0)
					{
						vEvils[i]->Release();
						vEvils.erase(vEvils.begin() + i);
						cleared = false;
						break;
					}
				}
			}
		}

		if (!vShots.empty())
		{
			for (std::vector<dll::SHOT*>::iterator shot = vShots.begin(); shot < vShots.end(); ++shot)
			{
				if (dll::Intersect(Hero.center, (*shot)->center, Hero.radius_x, (*shot)->radius_x,
					Hero.radius_y, (*shot)->radius_y))
				{
					Hero.lifes -= (*shot)->strenght;
					(*shot)->Release();
					vShots.erase(shot);
					if (Hero.lifes <= 0)
					{
						vExplosions.push_back(EXPLOSION{ Hero.center });
						hero_killed = true;
					}
					break;
				}
			}
		}

		if (!vEvils.empty() && !hero_killed)
		{
			for (std::vector<dll::EVILS*>::iterator evil = vEvils.begin(); evil < vEvils.end(); ++evil)
			{
				if (dll::Intersect((*evil)->center, Hero.center, (*evil)->radius_x, Hero.radius_x,
					(*evil)->radius_y, Hero.radius_y))
				{
					Hero.lifes -= 30;
					vExplosions.push_back(EXPLOSION{ (*evil)->center });
					(*evil)->Release();
					vEvils.erase(evil);
					score += 10 * level;
					break;
				}
			}
		}

		if (!vSpareParts.empty())
		{
			for (std::vector<dll::PROTON*>::iterator spare = vSpareParts.begin(); spare < vSpareParts.end(); ++spare)
			{
				(*spare)->start.y += (float)(level);
				(*spare)->set_edges();
				if ((*spare)->start.y >= ground)
				{
					(*spare)->Release();
					vSpareParts.erase(spare);
					break;
				}
			}
		}

		if (!vSpareParts.empty())
		{
			FRECT HeroRect{ Hero.start.x,Hero.start.y,Hero.end.x,Hero.end.y };

			for (std::vector<dll::PROTON*>::iterator spare = vSpareParts.begin(); spare < vSpareParts.end(); ++spare)
			{
				FRECT spareRect{ (*spare)->start.x,(*spare)->start.y,(*spare)->end.x,(*spare)->end.y };

				if (dll::Intersect(HeroRect, spareRect))
				{
					Hero.heal(20);
					(*spare)->Release();
					vSpareParts.erase(spare);
					break;
				}
			}
		}

		if (!vSpareParts.empty() && !vEvils.empty())
		{
			for (std::vector<dll::EVILS*>::iterator evil = vEvils.begin(); evil < vEvils.end(); ++evil)
			{
				bool healed = false;

				FRECT evRect{ (*evil)->start.x,(*evil)->start.y, (*evil)->end.x,(*evil)->end.y };

				for (std::vector<dll::PROTON*>::iterator spare = vSpareParts.begin(); spare < vSpareParts.end(); ++spare)
				{
					FRECT spRect{ (*spare)->start.x,(*spare)->start.y, (*spare)->end.x,(*spare)->end.y };

					if (dll::Intersect(evRect, spRect))
					{
						(*evil)->heal(10);
						(*spare)->Release();
						vSpareParts.erase(spare);
						healed = true;
						break;
					}
				}
				
				if (healed)break;
			}
		}

		// DRAW THINGS ************************************************

		Draw->BeginDraw();

		if (!vTiles.empty())
		{
			for (int i = 0; i < vTiles.size(); ++i)
			{
				if (vTiles[i]->end.x >= 0 && vTiles[i]->start.x <= scr_width &&
					vTiles[i]->end.y >= sky && vTiles[i]->start.y <= ground)
					Draw->DrawBitmap(bmpTile, D2D1::RectF(vTiles[i]->start.x, vTiles[i]->start.y,
						vTiles[i]->end.x, vTiles[i]->end.y));
			}
		}

		if (!vAssets.empty())
		{
			for (int i = 0; i < vAssets.size(); ++i)
			{
				switch (vAssets[i]->get_type())
				{
				case assets::cloud1:
					Draw->DrawBitmap(bmpCloud1, D2D1::RectF(vAssets[i]->start.x, vAssets[i]->start.y,
						vAssets[i]->end.x, vAssets[i]->end.y));
					break;

				case assets::cloud2:
					Draw->DrawBitmap(bmpCloud2, D2D1::RectF(vAssets[i]->start.x, vAssets[i]->start.y,
						vAssets[i]->end.x, vAssets[i]->end.y));
					break;

				case assets::riff1:
					Draw->DrawBitmap(bmpRiff1, D2D1::RectF(vAssets[i]->start.x, vAssets[i]->start.y,
						vAssets[i]->end.x, vAssets[i]->end.y));
					break;

				case assets::riff2:
					Draw->DrawBitmap(bmpRiff2, D2D1::RectF(vAssets[i]->start.x, vAssets[i]->start.y,
						vAssets[i]->end.x, vAssets[i]->end.y));
					break;

				case assets::riff3:
					Draw->DrawBitmap(bmpRiff3, D2D1::RectF(vAssets[i]->start.x, vAssets[i]->start.y,
						vAssets[i]->end.x, vAssets[i]->end.y));
					break;
				}
			}
		}

		if (!vEvils.empty())
		{
			for (std::vector<dll::EVILS*>::iterator evil = vEvils.begin(); evil < vEvils.end(); ++evil)
			{
				switch ((*evil)->get_type())
				{
				case planes::evil1:
					switch ((*evil)->dir)
					{
					case dirs::stop:
						Draw->DrawBitmap(bmpFighter1U[(*evil)->get_frame()], Resizer(bmpFighter1U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up:
						Draw->DrawBitmap(bmpFighter1U[(*evil)->get_frame()], Resizer(bmpFighter1U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down:
						Draw->DrawBitmap(bmpFighter1D[(*evil)->get_frame()], Resizer(bmpFighter1D[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::left:
						Draw->DrawBitmap(bmpFighter1L[(*evil)->get_frame()], Resizer(bmpFighter1L[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::right:
						Draw->DrawBitmap(bmpFighter1R[(*evil)->get_frame()], Resizer(bmpFighter1R[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_left:
						Draw->DrawBitmap(bmpFighter1UL[(*evil)->get_frame()], Resizer(bmpFighter1UL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_right:
						Draw->DrawBitmap(bmpFighter1UR[(*evil)->get_frame()], Resizer(bmpFighter1UR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_left:
						Draw->DrawBitmap(bmpFighter1DL[(*evil)->get_frame()], Resizer(bmpFighter1DL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_right:
						Draw->DrawBitmap(bmpFighter1DR[(*evil)->get_frame()], Resizer(bmpFighter1DR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;
					}
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 1.5f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::evil2:
					switch ((*evil)->dir)
					{
					case dirs::stop:
						Draw->DrawBitmap(bmpFighter2U[(*evil)->get_frame()], Resizer(bmpFighter2U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up:
						Draw->DrawBitmap(bmpFighter2U[(*evil)->get_frame()], Resizer(bmpFighter2U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down:
						Draw->DrawBitmap(bmpFighter2D[(*evil)->get_frame()], Resizer(bmpFighter2D[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::left:
						Draw->DrawBitmap(bmpFighter2L[(*evil)->get_frame()], Resizer(bmpFighter2L[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::right:
						Draw->DrawBitmap(bmpFighter2R[(*evil)->get_frame()], Resizer(bmpFighter2R[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_left:
						Draw->DrawBitmap(bmpFighter2UL[(*evil)->get_frame()], Resizer(bmpFighter2UL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_right:
						Draw->DrawBitmap(bmpFighter2UR[(*evil)->get_frame()], Resizer(bmpFighter2UR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_left:
						Draw->DrawBitmap(bmpFighter2DL[(*evil)->get_frame()], Resizer(bmpFighter2DL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_right:
						Draw->DrawBitmap(bmpFighter2DR[(*evil)->get_frame()], Resizer(bmpFighter2DR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;
					}
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 1.8f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::evil3:
					switch ((*evil)->dir)
					{
					case dirs::stop:
						Draw->DrawBitmap(bmpFighter3U[(*evil)->get_frame()], Resizer(bmpFighter3U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up:
						Draw->DrawBitmap(bmpFighter3U[(*evil)->get_frame()], Resizer(bmpFighter3U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down:
						Draw->DrawBitmap(bmpFighter3D[(*evil)->get_frame()], Resizer(bmpFighter3D[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::left:
						Draw->DrawBitmap(bmpFighter3L[(*evil)->get_frame()], Resizer(bmpFighter3L[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::right:
						Draw->DrawBitmap(bmpFighter3R[(*evil)->get_frame()], Resizer(bmpFighter3R[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_left:
						Draw->DrawBitmap(bmpFighter3UL[(*evil)->get_frame()], Resizer(bmpFighter3UL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_right:
						Draw->DrawBitmap(bmpFighter3UR[(*evil)->get_frame()], Resizer(bmpFighter3UR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_left:
						Draw->DrawBitmap(bmpFighter3DL[(*evil)->get_frame()], Resizer(bmpFighter3DL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_right:
						Draw->DrawBitmap(bmpFighter3DR[(*evil)->get_frame()], Resizer(bmpFighter3DR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;
					}
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 1.8f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::evil4:
					switch ((*evil)->dir)
					{
					case dirs::stop:
						Draw->DrawBitmap(bmpFighter4U[(*evil)->get_frame()], Resizer(bmpFighter4U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up:
						Draw->DrawBitmap(bmpFighter4U[(*evil)->get_frame()], Resizer(bmpFighter4U[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down:
						Draw->DrawBitmap(bmpFighter4D[(*evil)->get_frame()], Resizer(bmpFighter4D[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::left:
						Draw->DrawBitmap(bmpFighter4L[(*evil)->get_frame()], Resizer(bmpFighter4L[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::right:
						Draw->DrawBitmap(bmpFighter4R[(*evil)->get_frame()], Resizer(bmpFighter4R[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_left:
						Draw->DrawBitmap(bmpFighter4UL[(*evil)->get_frame()], Resizer(bmpFighter4UL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::up_right:
						Draw->DrawBitmap(bmpFighter4UR[(*evil)->get_frame()], Resizer(bmpFighter4UR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_left:
						Draw->DrawBitmap(bmpFighter4DL[(*evil)->get_frame()], Resizer(bmpFighter4DL[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;

					case dirs::down_right:
						Draw->DrawBitmap(bmpFighter4DR[(*evil)->get_frame()], Resizer(bmpFighter4DR[(*evil)->get_frame()],
							(*evil)->start.x, (*evil)->start.y));
						break;
					}
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 1.8f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::boss1:
					Draw->DrawBitmap(bmpBoss1[(*evil)->get_frame()], Resizer(bmpBoss1[(*evil)->get_frame()],
						(*evil)->start.x, (*evil)->start.y));
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 4.0f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::boss2:
					Draw->DrawBitmap(bmpBoss2[(*evil)->get_frame()], Resizer(bmpBoss2[(*evil)->get_frame()],
						(*evil)->start.x, (*evil)->start.y));
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 4.0f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;

				case planes::boss3:
					Draw->DrawBitmap(bmpBoss3[(*evil)->get_frame()], Resizer(bmpBoss3[(*evil)->get_frame()],
						(*evil)->start.x, (*evil)->start.y));
					Draw->DrawLine(D2D1::Point2F((*evil)->start.x, (*evil)->end.y + 10.0f), D2D1::Point2F((*evil)->start.x +
						(*evil)->lifes / 4.0f, (*evil)->end.y + 10.0f), TextBrush, 8.0f);
					break;
				}
			}

		}

		if (StatBrush && TextBrush && HgltBrush && InactBrush && b1BckgBrush && b2BckgBrush && b3BckgBrush && nrmFormat)
		{
			Draw->FillRectangle(D2D1::RectF(0, 0, scr_width, 50.0f), StatBrush);
			Draw->FillRectangle(D2D1::RectF(0, ground, scr_width, scr_height), StatBrush);

			Draw->FillRoundedRectangle(D2D1::RoundedRect(b1Rect, 15.0f, 20.0f), b1BckgBrush);
			Draw->FillRoundedRectangle(D2D1::RoundedRect(b2Rect, 15.0f, 20.0f), b2BckgBrush);
			Draw->FillRoundedRectangle(D2D1::RoundedRect(b3Rect, 15.0f, 20.0f), b3BckgBrush);

			if (name_set)Draw->DrawTextW(L"ИМЕ НА ПИЛОТ", 13, nrmFormat, b1TxtRect, InactBrush);
			else
			{
				if (!b1Hglt)Draw->DrawTextW(L"ИМЕ НА ПИЛОТ", 13, nrmFormat, b1TxtRect, TextBrush);
				else Draw->DrawTextW(L"ИМЕ НА ПИЛОТ", 13, nrmFormat, b1TxtRect, HgltBrush);
			}
			if (!b2Hglt)Draw->DrawTextW(L"ЗВУЦИ ON / OFF", 15, nrmFormat, b2TxtRect, TextBrush);
			else Draw->DrawTextW(L"ЗВУЦИ ON / OFF", 15, nrmFormat, b2TxtRect, HgltBrush);
			if (!b3Hglt)Draw->DrawTextW(L"ПОМОЩ ЗА ИГРАТА", 16, nrmFormat, b3TxtRect, TextBrush);
			else Draw->DrawTextW(L"ПОМОЩ ЗА ИГРАТА", 16, nrmFormat, b3TxtRect, HgltBrush);
		}

		/////////////////////////////////////////////////////////////

		wchar_t stat_txt[100]{ L"пилот: " };
		wchar_t add[5]{ L"\0" };
		int txt_size = 0;

		wcscat_s(stat_txt, current_player);
		
		wsprintf(add, L"%d", level);
		wcscat_s(stat_txt, L", ниво: ");
		wcscat_s(stat_txt, add);

		wsprintf(add, L"%d", score);
		wcscat_s(stat_txt, add);
		wcscat_s(stat_txt, L" точки ");

		for (int i = 0; i < 100; ++i)
		{
			if (stat_txt[i] != '\0')++txt_size;
			else break;
		}

		if (midFormat && InactBrush)Draw->DrawTextW(stat_txt, txt_size, midFormat, D2D1::RectF(20.0f, ground - 10.0f, scr_width,
			scr_height), InactBrush);
		
		txt_size = 0;
		wsprintf(add, L"%d", mins);
		
		wcscpy_s(stat_txt, add);
		wcscat_s(stat_txt, L" : ");
		if (secs - mins * 60 < 10)wcscat_s(stat_txt, L"0");
		wsprintf(add, L"%d", secs - mins * 60);
		wcscat_s(stat_txt, add);

		for (int i = 0; i < 100; ++i)
		{
			if (stat_txt[i] != '\0')++txt_size;
			else break;
		}

		if (midFormat && HgltBrush)Draw->DrawTextW(stat_txt, txt_size, midFormat, D2D1::RectF(scr_width - 150.0f, 60.0f, scr_width, scr_height), HgltBrush);

		///////////////////////////////////////////////////////////////

		if (!hero_killed)
		{
			switch (Hero.dir)
			{
			case dirs::stop:
				assets_dir = dirs::stop;
				Draw->DrawBitmap(bmpHeroU[Hero.get_frame()], Resizer(bmpHeroU[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::up:
				assets_dir = dirs::down;
				Draw->DrawBitmap(bmpHeroU[Hero.get_frame()], Resizer(bmpHeroU[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::down:
				assets_dir = dirs::up;
				Draw->DrawBitmap(bmpHeroD[Hero.get_frame()], Resizer(bmpHeroD[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::left:
				assets_dir = dirs::right;
				Draw->DrawBitmap(bmpHeroL[Hero.get_frame()], Resizer(bmpHeroL[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::right:
				assets_dir = dirs::left;
				Draw->DrawBitmap(bmpHeroR[Hero.get_frame()], Resizer(bmpHeroR[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::up_left:
				assets_dir = dirs::down_right;
				Draw->DrawBitmap(bmpHeroUL[Hero.get_frame()], Resizer(bmpHeroUL[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::up_right:
				assets_dir = dirs::down_left;
				Draw->DrawBitmap(bmpHeroUR[Hero.get_frame()], Resizer(bmpHeroUR[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::down_left:
				assets_dir = dirs::up_right;
				Draw->DrawBitmap(bmpHeroDL[Hero.get_frame()], Resizer(bmpHeroDL[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;

			case dirs::down_right:
				assets_dir = dirs::up_left;
				Draw->DrawBitmap(bmpHeroDR[Hero.get_frame()], Resizer(bmpHeroDR[Hero.get_frame()], Hero.start.x, Hero.start.y));
				break;
			}
			Draw->DrawLine(D2D1::Point2F(Hero.start.x, Hero.end.y + 10.0f), D2D1::Point2F(Hero.start.x + Hero.lifes / 1.5f,
				Hero.end.y + 10.0f), TextBrush, 8.0f);
		}

		if (!vShots.empty())
		{
			for (int i = 0; i < vShots.size(); ++i)
			{
				int frame = vShots[i]->get_frame();

				Draw->DrawBitmap(bmpShot[frame], Resizer(bmpShot[frame], vShots[i]->start.x, vShots[i]->start.y));
			}
		}

		if (!vSpareParts.empty())
		{
			for (std::vector<dll::PROTON*>::iterator spare = vSpareParts.begin(); spare < vSpareParts.end(); ++spare)
			{
				Draw->DrawBitmap(bmpSpareParts, D2D1::RectF((*spare)->start.x, (*spare)->start.y, (*spare)->end.x, 
					(*spare)->end.y));
			}
		}
		
		if (!vExplosions.empty())
		{
			for (std::vector<EXPLOSION>::iterator explosion = vExplosions.begin(); explosion < vExplosions.end(); ++explosion)
			{
				--explosion->delay;

				if (explosion->delay <= 0)
				{
					++explosion->frame;
					if (explosion->frame > 23)
					{
						vExplosions.erase(explosion);
						break;
					}

					Draw->DrawBitmap(bmpExplosion[explosion->frame], D2D1::RectF(explosion->center.x - 30.0f, explosion->center.y -
						30.0f, explosion->center.x + 30.0f, explosion->center.y + 30.0f));
				}
			}
		}

		/////////////////////////////////////////////////////////////////

		Draw->EndDraw();

		if (level_passed)LevelUp();
	
		if (hero_killed)GameOver();
	}


	ReleaseResources();
	std::remove(tmp_file);

    return (int) bMsg.wParam;
}
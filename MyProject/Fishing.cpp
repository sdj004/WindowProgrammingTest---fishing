#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK hDlgLeftFishBait(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK hDlgRightFishBait(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditSubclassProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int GetY(int mx, int length, int my); //낚싯대 높이 구하는 함수
HINSTANCE hInst;

struct FishOrPosition {
	int xpos;
	int ypos;
	int u_power = 5;
	int level;
	int fish_bait[5] = { 10, 10, 10, 10, 10 };
	int left;
	int right;
	enum fishbait {Fish_Bait = 0, Gluten, Corn, Little_Fish, Shake};
}typedef FishOrPosition;

static FishOrPosition myPosition;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPSTR lpszCmdLine, _In_ int nCmdShow) {
	HWND hwnd;
	MSG msg;
	hInst = hInstance;
	WNDCLASSEX WndClass;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.hInstance = hInst;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.lpszMenuName = NULL;
	RegisterClassEx(&WndClass);

	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("My Fishing"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

int GetY(int mx, int length, int my) {
	return sqrt(pow(length, 2) - pow(mx, 2)) + my;
}

INT_PTR CALLBACK hDlgLeftFishBait(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int Radio;
	static TCHAR Text[200];
	static TCHAR fishbait[30], gluten[30], corn[30], littlefish[30], shake[30];

	switch (iMsg) {
	case WM_INITDIALOG:
		_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
		_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
		_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
		_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
		_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
		SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
		SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
		SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
		SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
		SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
		CheckRadioButton(hDlg, IDC_RADIO_fish_bait, IDC_RADIO_shake, IDC_RADIO_fish_bait);
		myPosition.left = 0;
		myPosition.right = 0;
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO_fish_bait:
			Radio = 0;
			_stprintf_s(Text, 200, _T("정말 냄새 좋은 떡밥"), NULL);
			_stprintf_s(fishbait, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_left_bait, Text);
			return 1;
		case IDC_RADIO_gluten:
			Radio = 1;
			_stprintf_s(Text, 200, _T("쫀득한 글루텐"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_left_bait, Text);
			return 1;
		case IDC_RADIO_corn:
			Radio = 2;
			_stprintf_s(Text, 200, _T("대물을 낚는 옥수수"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d - 1개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_left_bait, Text);
			return 1;
		case IDC_RADIO_little_fish:
			Radio = 3;
			_stprintf_s(Text, 200, _T("육식 어종을 낚는 작은 물고기"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d - 1개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_left_bait, Text);
			return 1;
		case IDC_RADIO_shake:
			Radio = 4;
			_stprintf_s(Text, 200, _T("은근히 성능 좋은 흔들이"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_left_bait, Text);
			return 1;
		case IDOK:
			switch (Radio) {
			case 0:
				MessageBox(hDlg, _T("정말 냄새 좋은 떡밥이 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[0] -= 1;
				myPosition.left = myPosition.Fish_Bait;
				break;
			case 1:
				MessageBox(hDlg, _T("쫀득한 글루텐이 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[1] -= 1;
				myPosition.left = myPosition.Gluten;
				break;
			case 2:
				MessageBox(hDlg, _T("대물을 낚는 옥수수가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[2] -= 1;
				myPosition.left = myPosition.Corn;
				break;
			case 3:
				MessageBox(hDlg, _T("육식 어종을 낚는 작은 물고기가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[3] -= 1;
				myPosition.left = myPosition.Little_Fish;
				break;
			case 4:
				MessageBox(hDlg, _T("은근히 성능 좋은 흔들이가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[4] -= 1;
				myPosition.left = myPosition.Shake;
				break;
			}
			EndDialog(hDlg, 0);
			return 1;
		case IDCLOSE:
			EndDialog(hDlg, 0);
			return 1;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 1;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return 1;
	}
	return 0;
}

INT_PTR CALLBACK hDlgRightFishBait(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int Radio;
	static TCHAR Text[200];
	static TCHAR fishbait[30], gluten[30], corn[30], littlefish[30], shake[30];

	switch (iMsg) {
	case WM_INITDIALOG:
		_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
		_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
		_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
		_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
		_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
		SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
		SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
		SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
		SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
		SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
		CheckRadioButton(hDlg, IDC_RADIO_fish_bait, IDC_RADIO_shake, IDC_RADIO_fish_bait);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO_fish_bait:
			Radio = 0;
			_stprintf_s(Text, 200, _T("정말 냄새 좋은 떡밥"), NULL);
			_stprintf_s(fishbait, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_right_bait, Text);
			return 1;
		case IDC_RADIO_gluten:
			Radio = 1;
			_stprintf_s(Text, 200, _T("쫀득한 글루텐"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_right_bait, Text);
			return 1;
		case IDC_RADIO_corn:
			Radio = 2;
			_stprintf_s(Text, 200, _T("대물을 낚는 옥수수"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d - 1개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_right_bait, Text);
			return 1;
		case IDC_RADIO_little_fish:
			Radio = 3;
			_stprintf_s(Text, 200, _T("육식 어종을 낚는 작은 물고기"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d - 1개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_right_bait, Text);
			return 1;
		case IDC_RADIO_shake:
			Radio = 4;
			_stprintf_s(Text, 200, _T("은근히 성능 좋은 흔들이"), NULL);
			_stprintf_s(fishbait, 30, _T("%d 개 남음"), myPosition.fish_bait[0]);
			_stprintf_s(gluten, 30, _T("%d 개 남음"), myPosition.fish_bait[1]);
			_stprintf_s(corn, 30, _T("%d 개 남음"), myPosition.fish_bait[2]);
			_stprintf_s(littlefish, 30, _T("%d 개 남음"), myPosition.fish_bait[3]);
			_stprintf_s(shake, 30, _T("%d - 1 개 남음"), myPosition.fish_bait[4]);
			SetDlgItemText(hDlg, IDC_EDIT_fish_bait, fishbait);
			SetDlgItemText(hDlg, IDC_EDIT_gluten, gluten);
			SetDlgItemText(hDlg, IDC_EDIT_corn, corn);
			SetDlgItemText(hDlg, IDC_EDIT_little_fish, littlefish);
			SetDlgItemText(hDlg, IDC_EDIT_shake, shake);
			SetDlgItemText(hDlg, IDC_EDIT_select_right_bait, Text);
			return 1;
		case IDOK:
			switch (Radio) {
			case 0:
				MessageBox(hDlg, _T("정말 냄새 좋은 떡밥이 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[0] -= 1;
				myPosition.right = myPosition.Fish_Bait;
				break;
			case 1:
				MessageBox(hDlg, _T("쫀득한 글루텐이 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[1] -= 1;
				myPosition.right = myPosition.Gluten;
				break;
			case 2:
				MessageBox(hDlg, _T("대물을 낚는 옥수수가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[2] -= 1;
				myPosition.right = myPosition.Corn;
				break;
			case 3:
				MessageBox(hDlg, _T("육식 어종을 낚는 작은 물고기가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[3] -= 1;
				myPosition.right = myPosition.Little_Fish;
				break;
			case 4:
				MessageBox(hDlg, _T("은근히 성능 좋은 흔들이가 1개 차감됩니다."), _T("알림"), MB_OK);
				myPosition.fish_bait[4] -= 1;
				myPosition.right = myPosition.Shake;
				break;
			}
			EndDialog(hDlg, 0);
			return 1;
		case IDCLOSE:
			EndDialog(hDlg, 0);
			return 1;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 1;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return 1;
	}
	return 0;
}



#define IDC_BUTTON_left_fish_bait 50000
#define IDC_BUTTON_right_fish_bait 50001
#define IDC_EDIT_MyChat 50002
#define IDC_EDIT_Chat 50003

WNDPROC OldEditProc; // 기존 에디트 프로시저를 저장할 변수

LRESULT CALLBACK EditSubclassProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			// 부모에게 전송 신호를 보냄
			SendMessage(GetParent(hWnd), WM_COMMAND, MAKEWPARAM(IDC_EDIT_MyChat, 999), (LPARAM)hWnd);
			return 0; // 메시지 처리 완료! (소리 방지 1단계)
		}
		break;

	case WM_CHAR:
		if (wParam == VK_RETURN) {
			// 엔터 키에 의한 문자 입력을 무시합니다.
			// 여기서 0을 리턴하면 "디리링" 소리가 나지 않습니다!
			return 0; // 메시지 처리 완료! (소리 방지 2단계)
		}
		break;
	}
	return CallWindowProc(OldEditProc, hWnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hwnd_left_fish_bait, hwnd_right_fish_bait, hDlg, hwnd_MyChat, hwnd_Chat;
	HDC hdc, memdc, memBackgrounddc, memfishingfloat; //memdc는 hdc 뒷면, memBackgrounddc는 배경칠하는 면, memfishingfloat는 찌 그리면 면
	PAINTSTRUCT ps;
	static HBITMAP hBit, OldBit, hBackground, OldBackground, FishingFloat[14], FishingFloatMask[14]; //hBit OldBit는 더블 버퍼링을 위한 비트맵, hBackground OldBackground는 배경 비트맵, FishingFloat FishingFloatMask는 찌의 비트맵과 마스크
	static RECT rectView; //클라이언트 화면의 크기를 담는 변수
	static int length = 100; //낚싯대의 길이
	static int mx, my, fish, bite_count, X, sensitive, count, b_count, ypos, high_tention, lb_count, size;
	//마우스x좌표 마우스y좌표, 물고기 수, 물고기가 물고있는 시간, 텐션의 정도(위치), 민감도, 찌가 입수할 때를 보여주는 수, 입질을 할 때 찌의 모양을 잡아주는 수, 찌의 위치(뭍에서 살짝 아래쪽), 낚싯줄의 텐션(엄청 높거나 엄청 낮음), 헛챔질 했을 때의 찌의 크기 및 위치
	
	static double Radian[10], My[100], Mx[100]; //포물선으로 낚싯대를 만드려고 했으나, MoveToEx와 LineTo가 int형만 받아져서 만들다가 접음
	static bool Hit, Nthrow, bite, ready, throwing, line_break; //물고기가 걸렸는지 안걸렸는지, 낚싯대를 캐스팅안했는지 했는지, 입질을 했는지 안했는지, 모든 준비가 맞춰졌는지, 던지는 중인지, 줄이 끊어졌는지 혹은 물고기가 도망갔는지
	static TCHAR text[100], MyChat[100], Total_Chat[10][100]; //왼쪽 위에 모인 물고기 수와 my를 출력하기 위한 버퍼, 내가 쓴 채팅, 전체 채팅 - 개발중
	int power; //물고기가 끌고 가는 힘을 랜덤으로 저장할 변수
	static HBRUSH hLow, OldLow, hMid, OldMid, hHigh, OldHigh, htention, Oldtention; //텐션이 낮은 쪽 중간인쪽 높은 쪽을 나타내기 위한 브러쉬와 현재 텐션을 나타내기 위한 브러쉬
	static HPEN hFishingRod, OldFishingRod, hLine, OldLine; //낚싯대를 칠하기 위한 HPEN들
	
	

	switch (iMsg) {
	case WM_CREATE:
		high_tention = 0;
		line_break = false;
		lb_count = 13;
		size = 0;
		myPosition.u_power = 5;
		srand((unsigned)time(NULL));
		GetClientRect(hwnd, &rectView); //클라이언트 화면 크기 측정
		myPosition.xpos = rectView.right / 2;
		myPosition.ypos = rectView.bottom;
		mx = rectView.right / 2;
		ypos = rectView.bottom;
		X = rectView.right / 2; //물고기를 낚았을 때 항상 텐션은 Mid에서 시작
		Hit = bite = ready = false; //입질과 물고기를 걸었는지를 알려주는 bool형 변수를 다 false로 초기화
		count = 0; //찌가 들어가는 모션의 시작을 0으로 만듦 (찌가 다 보이는 상태)
		Nthrow = true; //안던진 상태이므로 true
		sensitive = 5; //물고기의 민감도를 5로 설정
		hdc = GetDC(hwnd);
		hBit = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //더블 버퍼링을 구현하기 위한 비트맵 생성
		hBackground = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Background)); //낚시터의 배경을 칠할 비트맵 불러오기

		//찌의 상태를 표현하는 비트맵 여러개 불러오기 - 0쪽이 다 보이는 상태, 내려갈수록 찌가 물에 잠긴 상태
		FishingFloat[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float));
		FishingFloat[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float1));
		FishingFloat[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float2));
		FishingFloat[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float3));
		FishingFloat[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float4));
		FishingFloat[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float5));
		FishingFloat[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float6));
		FishingFloat[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float7));
		FishingFloat[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float8));
		FishingFloat[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float9));
		FishingFloat[10] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float10));
		FishingFloat[11] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float11));
		FishingFloat[12] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float12));
		FishingFloat[13] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float13));
		
		//찌를 이쁘게 프린팅하기 위한 마스크 여러개 불러오기 - 위 와 동일
		FishingFloatMask[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK));
		FishingFloatMask[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK1));
		FishingFloatMask[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK2));
		FishingFloatMask[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK3));
		FishingFloatMask[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK4));
		FishingFloatMask[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK5));
		FishingFloatMask[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK6));
		FishingFloatMask[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK7));
		FishingFloatMask[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK8));
		FishingFloatMask[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK9));
		FishingFloatMask[10] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK10));
		FishingFloatMask[11] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK11));
		FishingFloatMask[12] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK12));
		FishingFloatMask[13] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_Fishing_float_MASK13));
		
		ReleaseDC(hwnd, hdc);

		hwnd_left_fish_bait = CreateWindow(
			_T("Button"),
			_T("왼쪽 바늘"),
			WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD,
			30, rectView.top + 100, 100, 50,
			hwnd,
			(HMENU)IDC_BUTTON_left_fish_bait,
			hInst,
			NULL
		);

		hwnd_left_fish_bait = CreateWindow(
			_T("Button"),
			_T("오른쪽 바늘"),
			WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD,
			150, rectView.top + 100, 100, 50,
			hwnd,
			(HMENU)IDC_BUTTON_right_fish_bait,
			hInst,
			NULL
		);

		hwnd_MyChat = CreateWindow(
			_T("Edit"),
			_T(""),
			WS_VISIBLE | WS_CHILD,
			30, rectView.bottom - 30, 250, 30,
			hwnd,
			(HMENU)IDC_EDIT_MyChat,
			hInst,
			NULL
		);

		hwnd_Chat = CreateWindow(
			_T("Edit"),
			_T(""),
			WS_VISIBLE | WS_CHILD | ES_READONLY,
			30, rectView.bottom - 350, 250, 300,
			hwnd,
			(HMENU)IDC_EDIT_Chat,
			hInst,
			NULL
		);

		// hwnd_MyChat 생성 후
		OldEditProc = (WNDPROC)SetWindowLongPtr(hwnd_MyChat, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);

		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rectView);
		memdc = CreateCompatibleDC(hdc); //memdc를 hdc 뒤로 보내기
		memBackgrounddc = CreateCompatibleDC(memdc); //memBackgrounddc를 memdc 뒤로 보내기
		memfishingfloat = CreateCompatibleDC(memdc); //memfishingfloat를 memdc 뒤로 보내기
		OldBit = (HBITMAP)SelectObject(memdc, hBit); //비트맵을 동적으로 관리 하기 위한 초기화
		OldBackground = (HBITMAP)SelectObject(memBackgrounddc, hBackground); //비트맵을 동적으로 관리 하기 위한 초기화
		FillRect(memdc, &rectView, WHITE_BRUSH); //화면을 하얀 배경으로 채움

		StretchBlt(memdc, 0, 0, rectView.right, rectView.bottom, memBackgrounddc, 0, 0, 1000, 770, SRCCOPY); //낚시터 배경 비트맵으로 화면을 꽉 채움

		

		

		if (throwing) { //날아가는 중
			SelectObject(memfishingfloat, FishingFloatMask[0]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCAND);
			SelectObject(memfishingfloat, FishingFloat[0]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCPAINT);
		}

		if (!Nthrow && !bite) { //찌가 물속으로 떨어지게끔 ypos값을 조금씩 바꾸면서 테스트 하여 이와 같이 만듦 + 찌가 점점 내려가야 하므로(비트맵을 내리기 위해서 count에 적당한 수를 곱해서 더함)
			SelectObject(memfishingfloat, FishingFloatMask[count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200 + count * 7, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCAND);
			SelectObject(memfishingfloat, FishingFloat[count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200 + count * 7, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCPAINT);
		}
		if (bite && !Hit) { //입질을 할 때! 왼쪽 위에 Bite!를 출력하고 찌가 위로 움직이게 만듦
			TextOut(memdc, 0, 0, _T("Bite!"), _tcslen(_T("Bite!")));
			SelectObject(memfishingfloat, FishingFloatMask[b_count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200 + b_count * 7, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCAND);
			SelectObject(memfishingfloat, FishingFloat[b_count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 200 + b_count * 7, 100 + ypos / 4 * 3, 100 + ypos / 4 * 3, memfishingfloat, 0, 0, 926, 1162, SRCPAINT);
		}

		if (line_break) { //낚싯줄이 끊어지거나 물고기가 빠져나갔을 때,
			TextOut(memdc, 0, 0, _T("line break!"), _tcslen(_T("line break!")));
			SelectObject(memfishingfloat, FishingFloatMask[lb_count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 130 + lb_count * 7 + my, 100 + ypos / 4 * 3 + size, 100 + ypos / 4 * 3 + size, memfishingfloat, 0, 0, 926, 1162, SRCAND);
			SelectObject(memfishingfloat, FishingFloat[lb_count]);
			StretchBlt(memdc, myPosition.xpos - (100 + ypos / 4 * 3) / 2, myPosition.ypos - (100 + ypos / 4 * 3) / 2 + 130 + lb_count * 7 + my, 100 + ypos / 4 * 3 + size, 100 + ypos / 4 * 3 + size, memfishingfloat, 0, 0, 926, 1162, SRCPAINT);
		}

		if (Hit) { //물고기가 걸렸을 때, Hit!를 왼쪽 위에 출력하고 텐션을 나타내는 직사각형과 현재 텐션을 알려주는 원 출력
			TextOut(memdc, 0, 0, _T("Hit!"), _tcslen(_T("Hit!")));

			//텐션이 낮은 쪽은 파란색으로 칠함
			hLow = CreateSolidBrush(RGB(0, 0, 255));
			OldLow = (HBRUSH)SelectObject(memdc, hLow);
			Rectangle(memdc, 100, 30, (rectView.right - 100) / 5 * 1, 100);
			SelectObject(memdc, OldLow);
			DeleteObject(hLow);

			//텐션이 중간인 지점은 초록색으로 칠함
			hMid = CreateSolidBrush(RGB(0, 255, 0));
			OldMid = (HBRUSH)SelectObject(memdc, hMid);
			Rectangle(memdc, (rectView.right - 100) / 5 * 1, 30, (rectView.right - 100) / 5 * 4, 100);
			SelectObject(memdc, OldMid);
			DeleteObject(hMid);

			//텐션이 높은 지점은 빨간색으로 칠함
			hHigh = CreateSolidBrush(RGB(255, 0, 0));
			OldHigh = (HBRUSH)SelectObject(memdc, hHigh);
			Rectangle(memdc, (rectView.right - 100) / 5 * 4, 30, (rectView.right - 100) / 5 * 5, 100);
			SelectObject(memdc, OldHigh);
			DeleteObject(hHigh);

			//현재 텐션은 푸른색으로 칠한 원을 텐션의 위치에 그림
			htention = CreateSolidBrush(RGB(0, 255, 255));
			Oldtention = (HBRUSH)SelectObject(memdc, htention);
			Ellipse(memdc, X - 30, 65 - 30, X + 30, 65 + 30);
			SelectObject(memdc, Oldtention);
			DeleteObject(htention);
		}

		hLine = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //찌가 물에 잠기면 낚싯줄도 잠기므로 찌가 내려간 상태에서는 낚싯줄이 안보이도록 만듦
		OldLine = (HPEN)SelectObject(memdc, hLine);
		if (throwing || line_break || Hit) {
			MoveToEx(memdc, mx, GetY(mx % 10, length, my), NULL);
			LineTo(memdc, myPosition.xpos, myPosition.ypos);
		}
		SelectObject(memdc, OldLine);
		DeleteObject(hLine);

		hFishingRod = CreatePen(PS_SOLID, 9, RGB(255, 255, 255)); //9의 두께 하얀색으로 펜을 생성
		OldFishingRod = (HPEN)SelectObject(memdc, hFishingRod); //펜을 동적으로 관리하기 위한 초기화
		MoveToEx(memdc, rectView.right / 2, rectView.bottom, NULL); //클라이언트 화면의 중앙 맨 아래에서
		LineTo(memdc, mx, GetY(mx % 10, length, my)); //마우스의 위치의 적당한 높이로 낚싯대를 표현하는 직선을 그림
		SelectObject(memdc, OldFishingRod);
		DeleteObject(hFishingRod); //핸들 반납
		
		
		//만약 미끼를 던진 상태이면 집중!이라는 문구를 왼쪽 위에 출력하고 그 아래에 몇 마리가 모였는지와 my의 크기를 출력 -> 개발자가 보기 편하기 위한 출력이므로 나중에 삭제 가능
		if (!Nthrow) TextOut(memdc, 0, 15, _T("집중!"), _tcslen(_T("집중!")));
		_stprintf_s(text, 100, _T("%d 마리 모임\nmx = %d\nmy = %d"), fish, mx, my);
		TextOut(memdc, 0, 30, text, _tcslen(text));

		BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc, 0, 0, SRCCOPY); //memdc에 그려진 모든 비트맵을 hdc에 그림

		//비트맵과 디바이스콘텍스트 반납 핸들을 지우는 것은 WM_DESTROY에서 진행
		SelectObject(memdc, OldBit);
		DeleteDC(memdc);
		SelectObject(memBackgrounddc, OldBackground);
		DeleteDC(memfishingfloat);
		DeleteDC(memBackgrounddc);
		EndPaint(hwnd, &ps);
		break;
	case WM_MOUSEMOVE: //마우스가 움직이면 낚싯대 방향 이동
	{
		if (Nthrow) mx = LOWORD(lParam); //던지지 않았을 때에만 이동할 수 있게 만듦
		if (!Hit && Nthrow && my > rectView.bottom - 500) my = HIWORD(lParam); //낚싯대 끝이 뒤로 안젖혀지게 만듦

		if (X <= rectView.left + 100) { //텐션이 너무 낮으면 10번 기다렸다가 물고기가 도망갔다고 판정 -> 훨을 안굴려도 마우스가 미세하게 움직인다면 물고기가 도망간 것으로 처리
			if (high_tention < 10) high_tention += 1;
			else if(!Nthrow){
				line_break = true;
				SetTimer(hwnd, 7, 100, NULL);
				high_tention = 0;
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	}
	case WM_MOUSEWHEEL: //마우스 휠을 내리거나 올리면 챔질을 하는 것임
		mx = LOWORD(lParam);
		my = 0; //챔질을 하면 낚싯대가 다시 올라오고
		count = 0; //모여있던 물고기가 도망감
		if (!Nthrow) { //헛챔질의 경우 낚싯바늘을 회수한다(찌 원래 자리로 복구)
			my = 0;
			line_break = true;
			SetTimer(hwnd, 7, 10, NULL);
			myPosition.xpos = mx;
			//myPosition.ypos = rectView.bottom;
		}
		//
		if (bite || Hit || ready) { //만약 입질중이었거나 물고기가 걸리면
			ready = false;
			if (X >= rectView.right - 155) { //텐션이 가장 높은 상태이면 현재 텐션이 더 높아지지 않음
				if(high_tention < 10) high_tention += 1; //마찬가지로 10번 기다려주고 줄이 끊어짐 판정
				else {
					line_break = true;
					SetTimer(hwnd, 7, 50, NULL);
					high_tention = 0;
				}
			}
			else if (X <= rectView.left + 100) { //텐션이 너무 낮은 상태이면 10번 기다렸다가 물고기가 도망간 판정
				if (high_tention < 10) high_tention += 1; 
				else {
					line_break = true;
					SetTimer(hwnd, 7, 50, NULL);
					high_tention = 0;
				}
			}
			else{
				X += sensitive; //그렇지 않으면 텐션이 높아짐
				myPosition.ypos += myPosition.u_power;
			}
			SetTimer(hwnd, 2, 100, NULL); //물고기가 걸렸을 때 발동되는 타이머
		}
		
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN: 
		switch (LOWORD(wParam)) {
		case VK_SPACE: //스페이스바를 누르면 미끼를 던지기(캐스팅)이 / 가 된다
			if (!throwing && Nthrow && !line_break) {
				ypos = rectView.bottom;
				throwing = true;
				SetTimer(hwnd, 6, 10, NULL); //낚시 찌가 날아가는 모션을 나타내는 타이머
				
				if (!Nthrow || !Hit) { //던진 상태이거나 물고기가 안걸린 상태이면,
					SetTimer(hwnd, 3, 500, NULL); //물고기가 유인되는 타이머를 시작
					InvalidateRgn(hwnd, NULL, FALSE);
					break;
				}
			}
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_left_fish_bait: //왼쪽 낚싯 바늘에 미끼 달기
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_left_fish_bait), hDlg, hDlgLeftFishBait);
			break;
		case IDC_BUTTON_right_fish_bait: //오른쪽 낚싯 바늘에 미끼 달기
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_right_fish_bait), hDlg, hDlgRightFishBait);
			break;
		case IDC_EDIT_MyChat: //내가 채팅을 입력하는 칸
			// wParam 전체를 VK_RETURN과 비교하지 말고, 
			// 우리가 약속한 알림 코드(999)가 왔는지만 확인하세요!
			if (HIWORD(wParam) == 999) { //엔터를 눌렀으면 채팅창에 내가 쓴 메시지 세팅
				GetDlgItemText(hwnd, IDC_EDIT_MyChat, MyChat, 100);
				SetDlgItemText(hwnd, IDC_EDIT_Chat, MyChat);
				SetWindowText(hwnd_MyChat, _T(""));
				SetFocus(hwnd_MyChat); // 전송 후 바로 다시 칠 수 있게!
			}
			break;
		}
		break;
	case WM_TIMER:
		switch (LOWORD(wParam)) {
		case 1: //낚싯대 내려놓는 모션
			if (my < rectView.bottom - 450) my += 10; //만약 my가 맨 아래에서 450만큼 뺀 값보다 작다면 my를 10씩 더함 -> 낚싯대가 맨 아래에서 450만큼 뺀 높이가 될때까지 내려감
			else {
				KillTimer(hwnd, 1); //다 내려갔으면 낚싯대 내려놓는 모션을 끈다
				ready = true;
				Hit = false; //물고기가 아직은 안걸린 상태로 만든다 -> 이걸 하지 않으면 물고기를 유인할 때 작동되는 타이머에서 던지자 마자 물고기가 잡히는 아이러니한 문제가 발생함
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case 2: //물고기가 걸렸을 때
			if (!line_break) {
				KillTimer(hwnd, 3);
				fish = 0; //모인 물고리를 0으로 만듦
				Hit = true; //물고기가 잡혔다고 전환
				power = rand() % sensitive; //물고기가 힘을 쓰는 것을 랜덤으로 만듦
				if (power % 2 == 0 && myPosition.xpos < rectView.right) myPosition.xpos += power * 6;
				else  myPosition.xpos -= power * 6;
				if (myPosition.ypos >= rectView.top + 350) myPosition.ypos -= power * 6;
				else myPosition.ypos = rectView.top + 350;
				if (X > 100)X -= power * 6; //텐션이 가장 낮은 상태보다 높으면 텐션을 지속적으로 낮춤 (힘을 안쓰는 상태이고, 휠을 계속 내려야 힘을 쓰는 걸로 인식됨)
				if (my < rectView.bottom - 450) my += power * 12; //낚싯대의 높이를 물고기의 힘에 비례해서 낮춤(낚싯대가 물속으로 끌려가는 모션을 만듦)
				
				InvalidateRgn(hwnd, NULL, FALSE);
				break;
			}
		case 3: //물고기가 유인됨
			fish = rand() % 2;
			if (fish % 2 == 0) fish += rand() % 3;
			else if(fish % 2 == 1 && fish > 0) fish -= rand() % 3;
			if (rand() % 10 <= fish && ready) bite = true; //모인 물고기가 랜덤으로 뽑은 수보다 많으면 물고기가 입질한 상태로 만듦
			if (bite) {
				b_count = (rand() % 3) + 10; //물고기의 입질을 표현하는 것으로 찌의 높이를 순간적으로 조금(이 조금도 랜덤임) 높임
				SetTimer(hwnd, 5, 100, NULL); //물고기로 인해 높아진 찌를 다시 낮추는 타이머 시작
				bite_count += 1; //bite_count는 0부터 시작하는데, 타이머 3이 돌아갈 때마다 1씩 늘어남 -> 타이머 3이 3번 돌면 입질을 안한 상태로 만듦
				if (bite_count >= 2) {
					bite = false;
					bite_count = 0;
				}
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case 4: //던졌을 때 찌 모션
			if (count < 13) {
				++count; //점점 내려가게 만듦
			}
			else {
				KillTimer(hwnd, 4); //다 내려갔으면 타이머 종료
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case 5: //물고기의 입질로 처음 찌가 다 가라앉았을 때의 높이와 같아지면 찌가 더이상 가라앉지 않게 만듦
			if (b_count < 13) ++b_count; //높아진 상태에서 점점 내려가게 만듦
			else KillTimer(hwnd, 5); //다 내려갔으면 타이머 종료
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case 6: //찌가 점점 가라앉을 때 비트맵을 밑으로 조금씩 내림
			if (ypos >= GetY(mx % 10, length, my) + 100) {
				ypos -= 20;
			}
			else {
				KillTimer(hwnd, 6);
				Nthrow = false; //미끼를 던진 상태가 됨
				throwing = false;
				SetTimer(hwnd, 1, 100, NULL); //낚싯대를 서서히 내리는 모션을 나타내는 타이머
				SetTimer(hwnd, 4, 300, NULL);
			}
			myPosition.xpos = mx; //찌의 위치 업데이트
			myPosition.ypos = ypos;

			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case 7: //헛챔질 했을 때,
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 1);
			Hit = false;
			Nthrow = true;
			bite = false;
			if (lb_count > 0) {
				--lb_count; //찌가 나타남
				myPosition.ypos += 30;
				myPosition.xpos += 1;
				size += 10;
			}
			else {
				KillTimer(hwnd, 7);
				myPosition.xpos = rectView.right;
				myPosition.ypos = rectView.bottom;
				lb_count = 13;
				size = 0;
				line_break = false;
				ready = false;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		}
		break;
	case WM_SIZE: //윈도우의 크기가 중간에 변동 되었을 때,
		DeleteObject(hBit);
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rectView);
		//윈도우 크기 재설정 명령어 필요.
		hBit = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //더블 버퍼링을 구현하기 위한 비트맵 생성
		ReleaseDC(hwnd, hdc);
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		DeleteObject(hBit); //핸들들을 반납
		DeleteObject(hBackground);
		for (int i = 13; i >= 0; --i) {
			DeleteObject(FishingFloat[i]);
			DeleteObject(FishingFloatMask[i]);
		}
		PostQuitMessage(0); //윈도우 종료
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
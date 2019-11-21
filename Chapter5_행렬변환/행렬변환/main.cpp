﻿#include "defines.h"


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 19-11-20, 전역변수,  ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
HINSTANCE	g_hInst;						//인스턴스의 핸들선언(운영체제에서 정해줄 번호)
char  		g_ClassName[128] = "행렬변환";		//클래스 이름
char  		g_WinName[128] = "행렬변환";		//윈도우 이름
HWND		g_hWnd;							//윈도우의 핸들(윈도우를 대표하는 번호)

cMainGame	g_cMainGame;

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 19-11-20, 함수 프로토 타입,  ─━☆(함수의 원형 선언)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 19-11-20, 윈도우 메인 함수,  ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// apientry			==  winmain함수의 호출 방식을 의미한다
// hInstance		==	프로그램의 인스턴스 핸들이다(윈도우즈 운영체제에서 정해줄 윈도우의 코드번호(고유명사)).
// hPrevInstance	==	바로 앞에 실행된 프로그램의 인스턴스 핸들.
// lpszCmdParam		==	실행 직후에 열 파일의 경로가 전달된다.
// nCmdShow			==  윈도우를 화면에 출력할 방법(윈도우를 활성화 하여 보여준다라는 의미,또는 숨긴다.)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
					 ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;		//메세지 구조체 선언
	WNDCLASS	WndClass;		//윈도우 클래스 선언
	g_hInst =	hInstance;		//인스턴스선언과 동시에 대입한다.
	int			nWidth, nHeight;//윈도우 크기 

	//윈도우창 크기 만들기.
	nWidth = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 2;
	nHeight = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 2 +
		GetSystemMetrics(SM_CYCAPTION);

	// 1 윈도우 클래스 작성 (윈도우의 속성을 정의 한다)
	WndClass.cbClsExtra		= 0;									//윈도우즈가 내부적으로 사용할 여분메모리	
	WndClass.cbWndExtra		= 0;									//윈도우즈가 내부적으로 사용할 여분메모리
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색상 지정
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//커서를 설정한다(리소스를 통해서 원하는 그래픽를 등록 할수도 있다)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//아이콘을 읽는다(리소스를 통해서 원하는 그래픽를 등록 할수도 있다)
	WndClass.hInstance		= hInstance;							//윈도우 클래스의 인스턴스(윈도우즈 운영체제에서 정해줄 윈도우의 코드번호(고유명사))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//윈도우 프로시저의 이름(윈도우의 메시지 처리 함수를 지정)
	WndClass.lpszClassName	= g_ClassName;							//윈도우 클래스의 이름(어디까지나 클래스 이름일 뿐이다)
	WndClass.lpszMenuName	= NULL;									//메뉴의 이름(리소스 에디터 의해 별도로 만들어짐, 사용을 안하면 NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//윈도우의 스타일(윈도우의 크기가 변할때 다시 그린다.)

	// 2 클래스를 등록한다 (정의한 윈도우 클래스를 등록한다)
	RegisterClass(&WndClass);										

	// 3 윈도우를 만든다 (메모리 상에 윈도우를 생성한다)

	g_hWnd = CreateWindow(g_ClassName,				// 윈도우클래스 문자열 
		g_WinName,				// 타이틀바에 나타날 문자열
		WS_OVERLAPPEDWINDOW,		// 윈도우의 형태 옵션(OR 연산자 사용)타이틀바, 스크롤바, 크기조절가능 등등
		START_X, START_Y,			// 윈도우 시작위치
		nWidth, nHeight,			// 윈도우 크기
		NULL,						// 부모윈도우의 핸들 (부모 윈도우가 없고 자신이 최상위 윈도우 일때 NULL)
		(HMENU)NULL,				// 메뉴의 핸들 (메뉴를 사용 안하므로 NULL)			
		hInstance,				// 인스턴스
		NULL);					// createStruct라는 구조체의 주소 (여러개의 윈도우를 만들때 사용 되나 거의 사용하지 않는다.)


	if( !g_cMainGame.Init() )
		return 0;

	// 4 윈도우를 화면에 보여준다
	ShowWindow(g_hWnd, nCmdShow);


	while(true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			g_cMainGame.Update();
		}
	}

	g_cMainGame.Release();


	return Message.wParam;
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 19-11-20, 윈도우 프로시저, (메세지 처리 함수) ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;


	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
			//(esc key)
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//wndProc에서 처리 되지 않은 나머지 메시지들을 처리해준다.
	// 윈도우크기 변경이나, 이동 등를 처리해준다.
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
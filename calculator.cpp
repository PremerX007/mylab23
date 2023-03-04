#include <windows.h>
#include <stdio.h>

HWND textfield,textbox,textbox2,btplus,btminus,btmultiply,btdivide;
char textsave1[50];
char textsave2[50];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
		textfield = CreateWindow("STATIC","  Please input two numbers", WS_VISIBLE | WS_CHILD, 25, 23, 190, 20, hwnd, NULL, NULL, NULL);

		textbox = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE, 55, 55, 135, 25, hwnd, NULL, NULL, NULL);
		textbox2 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE, 55, 85, 135, 25, hwnd, NULL, NULL, NULL);

		btplus = CreateWindow("BUTTON","+",WS_BORDER|WS_CHILD|WS_VISIBLE, 55, 115, 30, 25, hwnd, (HMENU) 1, NULL, NULL);
		btminus = CreateWindow("BUTTON","-",WS_BORDER|WS_CHILD|WS_VISIBLE, 90, 115, 30, 25, hwnd, (HMENU) 2, NULL, NULL);
		btmultiply = CreateWindow("BUTTON","*",WS_BORDER|WS_CHILD|WS_VISIBLE, 125, 115, 30, 25, hwnd, (HMENU) 3, NULL, NULL);
		btdivide = CreateWindow("BUTTON","/",WS_BORDER|WS_CHILD|WS_VISIBLE, 160, 115, 30, 25, hwnd, (HMENU) 4, NULL, NULL);
		
		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND: {
			int temp=0;
			int temp2=0;
			temp = GetWindowText(textbox, &textsave1[0],50);
			temp2 = GetWindowText(textbox2, &textsave2[0],50);
			double result;
			char numtochar[100];

			switch (LOWORD(wParam))
			{
			case 1:
				result = atof(textsave1) + atof(textsave2);
				sprintf(numtochar,"%f",result);
				::MessageBox(hwnd,numtochar,"Result",MB_OK);
				break;
			case 2:
				result = atof(textsave1) - atof(textsave2);
				sprintf(numtochar,"%f",result);
				::MessageBox(hwnd,numtochar,"Result",MB_OK);
				break;
			case 3:
				result = atof(textsave1) * atof(textsave2);
				sprintf(numtochar,"%f",result);
				::MessageBox(hwnd,numtochar,"Result",MB_OK);
				break;
			case 4:
				result = atof(textsave1) / atof(textsave2);
				sprintf(numtochar,"%f",result);
				::MessageBox(hwnd,numtochar,"Result",MB_OK);
				break;
			}
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

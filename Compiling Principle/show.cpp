#include <windows.h>

#include <iostream>

#include <fstream>
using namespace std;

/*  Declare Windows procedure  */

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */

char szClassName[ ] = "编译器";

int WINAPI

WinMain (HINSTANCE hThisInstance,

HINSTANCE hPrevInstance,

LPSTR lpszArgument,

int nFunsterStil)

{

HWND hwnd;               /* This is the handle for our window */

MSG messages;            /* Here messages to the application are saved */

WNDCLASSEX wincl;        /* Data structure for the windowclass */

/* The Window structure */

wincl.hInstance = hThisInstance;

wincl.lpszClassName = szClassName;

wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */

wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */

wincl.cbSize = sizeof (WNDCLASSEX);

/* Use default icon and mouse-pointer */

wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);

wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

wincl.hCursor = LoadCursor (NULL, IDC_ARROW);

wincl.lpszMenuName = NULL;                 /* No menu */

wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */

wincl.cbWndExtra = 0;                      /* structure or the window instance */

/* Use Windows's default color as the background of the window */

wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

/* Register the window class, and if it fails quit the program */

if (!RegisterClassEx (&wincl))

return 0;

/* The class is registered, let's create the program*/

hwnd = CreateWindowEx (

0,                   /* Extended possibilites for variation */

szClassName,         /* Classname */

"编译器",       /* Title Text */

WS_OVERLAPPEDWINDOW, /* default window */

CW_USEDEFAULT,       /* Windows decides the position */

CW_USEDEFAULT,       /* where the window ends up on the screen */

650,                 /* The programs width */

500,                 /* and height in pixels */

HWND_DESKTOP,        /* The window is a child-window to desktop */

NULL,                /* No menu */

hThisInstance,       /* Program Instance handler */

NULL                 /* No Window Creation data */

);

/* Make the window visible on the screen */

ShowWindow (hwnd, nFunsterStil);

/* Run the message loop. It will run until GetMessage() returns 0 */

while (GetMessage (&messages, NULL, 0, 0))

{

/* Translate virtual-key messages into character messages */

TranslateMessage(&messages);

/* Send message to WindowProcedure */

DispatchMessage(&messages);

}

/* The program return-value is 0 - The value that PostQuitMessage() gave */

return messages.wParam;

}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK

WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{

static HWND hEdit;

static HWND hBtn;
static HWND hBtn1;
static HWND hBtn2;
static HWND hBtn3;
switch (message)                  /* handle the messages */
{

	case WM_CREATE:// ------------->
	
	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
	
	WS_CHILDWINDOW|WS_VSCROLL|ES_MULTILINE|ES_WANTRETURN, 10, 20, 500, 700,
	
	hwnd, NULL, NULL, NULL);
	
	ShowWindow(hEdit, SW_SHOW);
	
	hBtn = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("词法分析"),
	
	WS_CHILDWINDOW, 520, 100, 80, 30,
	
	hwnd, NULL, NULL, NULL);
	
	ShowWindow(hBtn, SW_SHOW);
	
	hBtn1 = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("语法分析"),
	
	WS_CHILDWINDOW, 520, 150, 80, 30,
	
	hwnd, NULL, NULL, NULL);
	
	ShowWindow(hBtn1, SW_SHOW);
	
	hBtn2 = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("中间代码"),
	
	WS_CHILDWINDOW, 520, 200, 80, 30,
	
	hwnd, NULL, NULL, NULL);
	
	ShowWindow(hBtn2, SW_SHOW);
	
	hBtn3 = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("目标代码"),
	
	WS_CHILDWINDOW, 520, 250, 80, 30,
	
	hwnd, NULL, NULL, NULL);
	
	ShowWindow(hBtn3, SW_SHOW);
	break;

   case WM_COMMAND:

	if(lParam == (LPARAM)hBtn)
	{
	
	filebuf *pbuf;
	
	ifstream filestr;
	
	long size;
	
	char * buffer;
	
	filestr.open ("词法分析.txt",ios::in|ios::binary);
	
	pbuf=filestr.rdbuf();
	
	size=pbuf->pubseekoff (0,ios::end,ios::in);
	
	pbuf->pubseekpos (0,ios::in);
	
	buffer=new char[size];
	
	pbuf->sgetn(buffer,size-1);
	
	filestr.close();
	
	SetWindowText(hEdit, buffer);
	
	delete [] buffer;

	}
	if(lParam == (LPARAM)hBtn1)
	{
	
	filebuf *pbuf;
	
	ifstream filestr;
	
	long size;
	
	char * buffer;
	
	filestr.open ("语法分析.txt",ios::in|ios::binary);
	
	pbuf=filestr.rdbuf();
	
	size=pbuf->pubseekoff (0,ios::end,ios::in);
	
	pbuf->pubseekpos (0,ios::in);
	
	buffer=new char[size];
	
	pbuf->sgetn(buffer,size);
	
	filestr.close();
	
	SetWindowText(hEdit, buffer);
	
	delete [] buffer;

	}
	
	if(lParam == (LPARAM)hBtn2)
	{
	
	filebuf *pbuf;
	
	ifstream filestr;
	
	long size;
	
	char * buffer;
	
	filestr.open ("中间代码.txt",ios::in|ios::binary);
	
	pbuf=filestr.rdbuf();
	
	size=pbuf->pubseekoff (0,ios::end,ios::in);
	
	pbuf->pubseekpos (0,ios::in);
	
	buffer=new char[size];
	
	pbuf->sgetn(buffer,size);
	
	filestr.close();
	
	SetWindowText(hEdit, buffer);
	
	delete [] buffer;

	}
	
	if(lParam == (LPARAM)hBtn3)
	{
	
	filebuf *pbuf;
	
	ifstream filestr;
	
	long size;
	
	char * buffer;
	
	filestr.open ("目标代码.txt",ios::in|ios::binary);
	
	pbuf=filestr.rdbuf();
	
	size=pbuf->pubseekoff (0,ios::end,ios::in);
	
	pbuf->pubseekpos (0,ios::in);
	
	buffer=new char[size];
	
	pbuf->sgetn(buffer,size);
	
	filestr.close();
	
	SetWindowText(hEdit, buffer);
	
	delete [] buffer;

	}
  break;// <-------------

case WM_DESTROY:

PostQuitMessage(0);       /* send a WM_QUIT to the message queue */

break;

default:                      /* for messages that we don't deal with */

return DefWindowProc (hwnd, message, wParam, lParam);

}

return 0;

}

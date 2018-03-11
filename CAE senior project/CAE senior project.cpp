// CAE senior project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CAE senior project.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/********************************************************************
simple GDI+ draw a line function to test GDI+
	in Win32, to draw something, we first need an HDC
		HDC -> a handle to the device context
	in this case, the window we're drawing to is the device context
*********************************************************************/
void MyOnPaint(HDC hdc)
{
	//create Graphics object using handle to the window device context
	Graphics graphics(hdc);
	//create a pen with a color
	Pen pen(Color(255, 0, 0, 255));
	//use the DrawLine function to draw a line on the device context
	graphics.DrawLine(&pen, 0, 0, 200, 100);
}

void createBitmapFromFile(HDC hdc)
{	
	//to display bitmap, need Image and Graphics objects
	Graphics graphics(hdc);
	//pass name of file or pointer to a stream to Image constructor 
	Image image(L"C:\\Users\\Katy\\Pictures\\checkerboard pattern.jpg");
	//after create Image, pass its address to DrawImage method of Graphics object 
	graphics.DrawImage(&image, 60, 10);
	
}

Bitmap* createBitmapPixels(HDC hdc, int totalFOV_width, int totalFOV_height)
{
	Bitmap* bitmap = new Bitmap(totalFOV_width, totalFOV_height, 2498570);
	return bitmap;
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	//initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	//shut down GDI+
	//GdiplusShutdown(gdiplusToken);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CAESENIORPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAESENIORPROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); //WNDCLASSEX size in bytes

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	//window class styles
    wcex.lpfnWndProc    = WndProc;	//window procedure associated to this window, used for message processing
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAESENIORPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);	//window cursor
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);		//window background brush color
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CAESENIORPROJECT);
    wcex.lpszClassName  = szWindowClass;	//window class name
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//example inputs for white test pattern
	std::string fileName; 


    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            } //end switch(wmId)
        } //end case WM_COMMAND
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

			//call GDI+ test function 
				//MyOnPaint(hdc);		
			//call create bitmap function
			//createBitmapFromFile(hdc);


			/**************************************************************
			/			CREATE TOTAL FOV BITMAP FROM PIXELS
			***************************************************************/
			int totalFOV_width = 400;	//NEED TO READ-IN LATER
			int totalFOV_height = 400;	//NEED TO READ-IN LATER
			Bitmap* totalFOV_Image = createBitmapPixels(hdc, totalFOV_width, totalFOV_height);
			std::string testPattern = "grayscale";	//NEED TO READ-IN LATER			
			Color pixelColor(255,0,0,0);	//default of black

			/*****************************
			/		GRAYSCALE
			******************************/

			if (testPattern == "grayscale")
			{
				int i = 0;
				int j = 0;
				int stripeSize = totalFOV_height / 10;
				//1st stripe - white
				for (int i = 0; i < stripeSize; i++)
				{
					ARGB argb = Color::MakeARGB(0, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 1st stripe for
				} //end 1st stripe for

				//2nd stripe
				for (int i = stripeSize; i < stripeSize * 2; i++)
				{
					ARGB argb = Color::MakeARGB(28, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 2nd stripe for
				} //end 2nd stripe for

				//3rd stripe
				for (int i = stripeSize * 2; i < stripeSize * 3; i++)
				{
					ARGB argb = Color::MakeARGB(56, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 3rd stripe for 
				} //end 3rd stripe for 

				//4th stripe
				for (int i = stripeSize * 3; i < stripeSize * 4; i++)
				{
					ARGB argb = Color::MakeARGB(84, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 4th stripe for 
				} //end 4th stripe for 

				//5th stripe
				for (int i = stripeSize * 4; i < stripeSize * 5; i++)
				{
					ARGB argb = Color::MakeARGB(112, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 5th stripe for
				} //end 5th stripe for

				//6th stripe
				for (int i = stripeSize * 5; i < stripeSize * 6; i++)
				{
					ARGB argb = Color::MakeARGB(140, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 6th stripe for 
				} //end 6th stripe for 

				//7th stripe
				for (int i = stripeSize * 6; i < stripeSize * 7; i++)
				{
					ARGB argb = Color::MakeARGB(168, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 7th stripe for 
				} //end 7th stripe for 

				//8th stripe
				for (int i = stripeSize * 7; i < stripeSize * 8; i++)
				{
					ARGB argb = Color::MakeARGB(196, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 8th stripe for 
				} //end 8th stripe for 

				//9th stripe
				for (int i = stripeSize * 8; i < stripeSize * 9; i++)
				{
					ARGB argb = Color::MakeARGB(224, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //9th stripe for 
				} //end 9th stripe for 

				//10th stripe - black
				for (int i = stripeSize * 9; i < totalFOV_height; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 0, 0);
					for (int j = 0; j < totalFOV_width; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					} //end 10th stripe for 
				} //end 10th stripe for 
				Graphics graphics(hdc);
				graphics.DrawImage(&*totalFOV_Image, 0, 0);
			} //end if test pattern grayscale
            EndPaint(hWnd, &ps);
        } //end case WM_PAINT
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    } //end switch(message)
    return 0;
}  //end LRESULT CALLBACK

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

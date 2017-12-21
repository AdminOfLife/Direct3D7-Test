// make sure to link to the libraries libd3d9.a and libd3dx9_43.a
// - copy the two files from the lib directory of your compiler
// - open project options >> parameters and add both using "Add Library or Object"

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <d3d.h>

// Defines


// Globals
LPDIRECTDRAW7   lpDD;               // IDirectDraw7 Interface
LPDIRECT3D7     lpD3D;              // IDirect3D7 Interface

// this is the function that puts the 3D models into video RAM
void init_graphics() {


}

// this function initializes and prepares Direct3D for use
void initD3D(HWND hwnd) {

	HRESULT hr;
	 
	// Get an IDirectDraw7 interface.
	// Use the current display driver.
	hr = DirectDrawCreateEx (NULL, (void **)&lpDD, IID_IDirectDraw7, NULL); 
	if (FAILED (hr))
	{
	    // Code to handle an error goes here.
	}
	 
	// Get D3D interface
	hr = lpDD->QueryInterface (IID_IDirect3D7, (void **)&lpD3D);
	if (FAILED (hr))
	{
	    // Code to handle the error goes here.
	}


}

// this is the function used to render a single frame
void render_frame() {
	

}

// this is the function that cleans up Direct3D and COM
void cleanD3D() {
	lpD3D->Release();
	lpD3D->Release();
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  {
	switch(message) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd;
    WNDCLASSEX wc;
    MSG msg;

    memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WindowProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = NULL;
	wc.hIconSm		 = NULL;

    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(0, "WindowClass", "Direct3D FFP Example", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    // set up and initialize Direct3D
    initD3D(hwnd);

    // enter the main loop
    while(msg.message != WM_QUIT) {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        render_frame();
    }

    // clean up DirectX and COM
    cleanD3D();

    return msg.wParam;
}

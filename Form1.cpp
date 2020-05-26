#include "stdafx.h"
#include "Form1.h"
#include <windows.h>
#include <ctime>

using namespace random_password_generator;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	srand(clock());
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new Form1());
	return 0;
}

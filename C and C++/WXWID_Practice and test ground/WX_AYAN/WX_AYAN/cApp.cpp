#include "cApp.h"


wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}


cApp::~cApp()
{

}


bool cApp::OnInit()
{
	new_Frame1 = new cMain();

	new_Frame1->Show();

	return true;
}



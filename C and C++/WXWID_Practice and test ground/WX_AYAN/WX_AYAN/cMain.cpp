#include "cMain.h"



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "TEST APP", wxPoint(30,30), wxSize(600, 400))
{
	btn_1 = new wxButton(this, wxID_ANY, "Click Me", wxPoint(30, 30), wxSize(150, 50));
	txt_1 = new wxTextCtrl(this , wxID_ANY, "Enter Text", wxPoint(10, 70), wxSize(300, 40));
	lst_1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}



cMain::~cMain()
{

}



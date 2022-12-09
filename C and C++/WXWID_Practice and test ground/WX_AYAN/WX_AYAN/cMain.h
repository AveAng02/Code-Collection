#pragma once

#include "wx/wx.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:

	wxButton* btn_1;
	wxTextCtrl* txt_1;
	wxListBox* lst_1;
};


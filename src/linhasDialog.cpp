/*
 * BasicDialog.cpp
 *
 *  Created on: 27 de ago de 2015
 *      Author: x
 */

#include "wx/button.h"
#include "linhasDialog.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

BEGIN_EVENT_TABLE(LinhasDialog, wxDialog)
//  EVT_SIZE (PlanWindow::OnSize)       // Example size handler
END_EVENT_TABLE();


LinhasDialog::LinhasDialog ( wxWindow * parent, wxWindowID id,
		const wxString & title,
		const std::string arquivo,
		const wxPoint & position, const wxSize & size, long style )
: wxDialog( parent, id, title, position, size, style)
{
	wxString text = "", s;
	wxPoint p;
	wxSize  sz;

	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);

	p.x = 6; p.y = 2;
	//s.Printf(_(" x = %d y = %d\n"), p.x, p.y);
//	dimensions.append(s);
	//s.Printf(_(" width = %d height = %d\n"), sz.GetWidth(), sz.GetHeight());
//	dimensions.append(s);
//	dimensions.append("");

	std::string line;
	  ifstream myfile (arquivo.c_str());
	  if (myfile.is_open())
	  {
		while ( getline (myfile,line) )
		{
		  text.append(line);
		}
		myfile.close();
	  }

	  else text.append("não foi possível abrir o arquivo");


	dialogText = new wxTextCtrl ( this, -1, text, p, sz, wxTE_MULTILINE );

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton( this, wxID_OK, _("OK"), p, wxDefaultSize );
	p.x += 110;
	wxButton * c = new wxButton( this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize );

	result = "";
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &LinhasDialog::OnOk,
	            this, b->GetId());


}

std::string LinhasDialog::GetText() {
	return result;
}

void LinhasDialog::OnOk(wxCommandEvent& event) {
	result = dialogText->GetValue().ToStdString();
	EndModal(wxID_OK);
	Destroy();

}

/*
 * ListaDialog.cpp
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#include "ListaDialog.h"

/*
 * BasicDialog.cpp
 *
 *  Created on: 27 de ago de 2015
 *      Author: x
 */

#include "wx/button.h"
#include "ListaDialog.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

BEGIN_EVENT_TABLE(ListaDialog, wxDialog)
//  EVT_SIZE (PlanWindow::OnSize)       // Example size handler
END_EVENT_TABLE();


ListaDialog::ListaDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
		const std::string lista,
		const wxPoint & position, const wxSize & size, long style )
: wxDialog( parent, id, title, position, size, style)
{
	wxPoint p;
	wxSize  sz;
	wxString text = "";
	text.append (lista);

	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);

	p.x = 6; p.y = 2;

	dialogText = new wxTextCtrl ( this, -1, text, p, sz, wxTE_MULTILINE );

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton( this, wxID_OK, _("OK"), p, wxDefaultSize );
	p.x += 110;

	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ListaDialog::OnOk,
	            this, b->GetId());


}

void ListaDialog::OnOk(wxCommandEvent& event) {
	EndModal(wxID_OK);
	Destroy();

}

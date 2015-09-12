
#include "ConfigDialog.h"
#include "wx/button.h"

BEGIN_EVENT_TABLE(ConfigDialog, wxDialog)
//  EVT_SIZE (PlanWindow::OnSize)       // Example size handler
END_EVENT_TABLE();


ConfigDialog::ConfigDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & position, const wxSize & size, long style )
: wxDialog( parent, id, title, position, size, style)
{
	wxString dimensions = "", s;
	wxPoint p;
	wxSize  sz, sizebox;

	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);
	sizebox.SetWidth(size.GetWidth()/2 - 10);
	sizebox.SetHeight(20);

	p.x = 6; p.y = 2;
	//s.Printf(_(" x = %d y = %d\n"), p.x, p.y);
	dimensions.append(s);
//	s.Printf(_(" width = %d height = %d\n"), sz.GetWidth(), sz.GetHeight());
	dimensions.append(s);
	dimensions.append("");

	raioText = new wxTextCtrl ( this, -1, dimensions, wxPoint(size.GetWidth()/2, 2),
			sizebox, wxTE_MULTILINE );
//
//	raioText = new wxTextCtrl ( this, -1, dimensions, wxPoint(size.GetWidth()/2, 2),
//			sizebox, wxTE_MULTILINE );

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton( this, wxID_OK, _("OK"), p, wxDefaultSize );
	p.x += 110;
	wxButton * c = new wxButton( this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize );

	raio = "";
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ConfigDialog::OnOk,
	            this, b->GetId());



}

std::string ConfigDialog::GetText() {
	return raio;
}

void ConfigDialog::OnOk(wxCommandEvent& event) {
	raio = raioText->GetValue().ToStdString();
	EndModal(wxID_OK);
	Destroy();

}

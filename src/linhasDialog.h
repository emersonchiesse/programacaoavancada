

#ifndef LINHASDIALOG_H_
#define LINHASDIALOG_H_

#include <wx/dialog.h>
#include "wx/textctrl.h"
#include <string>

class LinhasDialog: public wxDialog
{
public:

	LinhasDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
			const std::string arquivo,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );

	wxTextCtrl * dialogText;
	std::string  GetText();

private:

	void OnOk( wxCommandEvent & event );

	std::string result;

	DECLARE_EVENT_TABLE()
};
#endif /* LINHASDIALOG_H_ */


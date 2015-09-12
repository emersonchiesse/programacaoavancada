/*
 *
 *  Created on: 27 de ago de 2015
 *      Author: x
 */

#ifndef CONFIGDIALOG_H_
#define CONFIGDIALOG_H_

#include <wx/dialog.h>
#include "wx/textctrl.h"
#include <string>

class ConfigDialog: public wxDialog
{
public:

	ConfigDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );

	wxTextCtrl * raioText;
	wxTextCtrl * showPesosText;

	std::string  GetText();

private:

	void OnOk( wxCommandEvent & event );

	std::string raio;

	DECLARE_EVENT_TABLE()
};
#endif /* BASICDIALOG_H_ */


/*
 *
 *  Created on: 27 de ago de 2015
 *      Author: x
 */

#ifndef CONFIGDIALOG_H_
#define CONFIGDIALOG_H_

#include <wx/dialog.h>
#include "wx/textctrl.h"
#include "wx/checkbox.h"
#include <string>
#include "Config.h"

class ConfigDialog: public wxDialog
{
public:

	ConfigDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
				config::Config *c,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );
	~ConfigDialog ();

	std::string  GetText();

private:

	config::Config *config;
	void OnOk( wxCommandEvent & event );

	std::string raio;
	wxTextCtrl * raioText;
	wxTextCtrl * showPesosText;
	wxCheckBox * chkDesenhaPontos;
	wxCheckBox * chkDesenhaContornos;
	wxCheckBox * chkDesenhaMapa;
	wxCheckBox * chkDesenhaVeiculos;

	DECLARE_EVENT_TABLE()
};
#endif /* BASICDIALOG_H_ */


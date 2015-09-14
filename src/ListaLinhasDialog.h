/*
 * ListaLinhasDialog.h
 *
 *  Created on: 13 de set de 2015
 *      Author: x
 */

#ifndef LISTALINHASDIALOG_H_
#define LISTALINHASDIALOG_H_

#include <wx/dialog.h>
#include "wx/textctrl.h"
#include <string>
#include <vector>
#include "wx/listbox.h"
#include "Linha.h"

using namespace std;

class ListaLinhasDialog: public wxDialog
{
public:

	ListaLinhasDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
			//const std::string arquivo,
			//std::vector<std::string> *lista,
			vector<Linha> *l,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );

	wxTextCtrl * dialogText;
	wxListBox * list;

private:

	vector<Linha> *linhas;

	void OnOk( wxCommandEvent & event );
	void OnVeiculos(wxCommandEvent& event);

	std::string result;

	DECLARE_EVENT_TABLE()
};

#endif /* LISTALINHASDIALOG_H_ */

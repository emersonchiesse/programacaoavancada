/*
 * ListaDialog.h
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#ifndef LISTADIALOG_H_
#define LISTADIALOG_H_


#include <wx/dialog.h>
#include "wx/textctrl.h"
#include "wx/listbox.h"

#include <string>
#include <vector>

class ListaDialog: public wxDialog
{
public:

	ListaDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
			//const std::string arquivo,
			std::vector<std::string> *lista,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );

	wxTextCtrl * dialogText;
	wxListBox * list;

private:

	void OnOk( wxCommandEvent & event );

	DECLARE_EVENT_TABLE()
};
#endif /* LISTADIALOG_H_ */

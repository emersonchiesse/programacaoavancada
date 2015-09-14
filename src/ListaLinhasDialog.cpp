/*
 * ListaLinhasDialog.cpp
 *
 *  Created on: 13 de set de 2015
 *      Author: x
 */

#include "ListaLinhasDialog.h"

#include "wx/button.h"
#include "Lista2.h"
#include "ListaDialog.h"
#include "LocalVeiculo.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

BEGIN_EVENT_TABLE(ListaLinhasDialog, wxDialog)
END_EVENT_TABLE();


ListaLinhasDialog::ListaLinhasDialog(wxWindow * parent, wxWindowID id, const wxString & title,
			//std::vector<string> *lista,
			vector<Linha> *l,
			const wxPoint & position, const wxSize & size, long style )
	: wxDialog( parent, id, title, position, size, style)
{
	wxPoint p;
	wxSize  sz;
	wxString text = "";

	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);
	p.x = 6; p.y = 2;

	linhas = l;
	list = new wxListBox(this, -1, p, sz);

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton( this, wxID_OK, _("OK"), p, wxDefaultSize );
	p.x += 110;
	wxButton * b2 = new wxButton( this, wxID_FILE1, _("Veiculos"), p, wxDefaultSize );

	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ListaLinhasDialog::OnOk,
			this, b->GetId());
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ListaLinhasDialog::OnVeiculos,
			this, b2->GetId());

	string s = "";
	Linha *_l;
	for (vector<Linha>::iterator i = linhas->begin();
			i != linhas->end(); i++)
	{
		_l = (Linha*)&(*i);
		s = _l->getId() + "\t" + _l->getNome();
		list->Append(wxString::FromUTF8(s.c_str()));
	}
}

void ListaLinhasDialog::OnOk(wxCommandEvent& event) {
	EndModal(wxID_OK);
	Destroy();
}

void ListaLinhasDialog::OnVeiculos(wxCommandEvent& event) {

	// if not selected
	// return;
	int i = list->GetSelection();
	if (i == wxNOT_FOUND)
		return;

	wxString s = list->GetString(list->GetSelection());
	vector<string> lista;

	// lista veiculos da linha selecionada
	string linha = s.SubString(0,2).ToStdString();
	//lista.push_back(linha);

	List<LocalVeiculo> *local = NULL;
	bool achou = false;
	Linha *l;
	vector<Linha>::iterator il;
	for ( il = linhas->begin();
			il != linhas->end(); il++)
	{
		l = (Linha*)&(*il);
		if (l->getId()==linha)
		{
			local = l->getPosicoesVeiculos();
			if ((local != NULL) && (local->getTamanho() > 0))
			{
				for ( List<LocalVeiculo>::iterator it  = local->begin();
						it != local->end(); it++)
				{
					LocalVeiculo veic = (LocalVeiculo)(*it);
					string p = veic.getPrefixo();
					//cout << veic.getPrefixo() << endl;

					vector<string>::iterator it2 =find (lista.begin(), lista.end(), p);
					if (it2 == lista.end())
						lista.push_back(p);
				}
			}
			achou = true;
			break;
		}
	}
	if (!achou)
		return;

	ListaDialog dialog ( this, -1, s, //_("Veiculos"),
			&lista,
			wxPoint(100, 100), wxSize(400, 400) );
	dialog.ShowModal();
}


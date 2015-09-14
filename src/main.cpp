

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "Lista.h"
#include "defs.h"
#include <wx/wx.h>
#include "linhasDialog.h"
#include "ListaDialog.h"
#include "ListaLinhasDialog.h"
#include "ConfigDialog.h"
#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Linha.h"
#include "Coordenada.h"
#include "PontoLinha.h"
#include "SistemaTransportePublico.h"
#include "Config.h"
#include "log.h"
#include "ColetaLinhas.h"


using namespace std;
using namespace rapidjson;
// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
//#if !defined(__WXMSW__) && !defined(__WXPM__)
//    #include "../sample.xpm"
//#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};



class MyFrame;


// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnOpen(wxCommandEvent& event);
    void OnLinhasAbreArquivo(wxCommandEvent& event);
	void OnPontosAbreArquivo(wxCommandEvent& event);
    void OnLinhasMostraLista(wxCommandEvent& event);
    void OnRotasAbreArquivo(wxCommandEvent& event);
    void OnOnibusAbreArquivo(wxCommandEvent& event);
    void OnConfiguracoes(wxCommandEvent& event);
    void OnSumario(wxCommandEvent& event);
    void OnCarregaTudo(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);

    double converteLat(int x);
    double converteLon(int y);
    int converteX(double lat);
    int converteY(double lon);


private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()

    wxBitmap image;
    int raioPonto;

    float margemEsquerda;
    float margemDireita;
    float margemSuperior;
    float margemInferior;

	SistemaTransportePublico RIT;
	config::Config config;
	Log log;
	ColetaLinhas coletaLinhas;

	void desenhaPontos (wxPaintDC *dc, string id);
	void desenhaContorno (wxPaintDC *dc, string linha);
	void desenhaVeiculos (wxPaintDC *dc, string id);

};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    menu_FileOpen = wxID_OPEN,
    menuArquivoLinhas= wxID_FILE1,
	menuArquivoRotas,
	menuArquivoPontos,
	menuArquivoVeiculos,
	menuArquivoHorarios,
	menuLinhasLista,
	menuConfiguracoes,
	menuSumario,
	menuCarregaTudo,

	menuSair = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

void MyFrame::desenhaPontos (wxPaintDC *dc, string id)
{
	List<PontoLinha> *pontos = RIT.getPontos(id);
	if ((pontos != NULL) && pontos->getTamanho() >0)
	{
		log.debug("plota pontos da linha: " + id);;

		for (List<PontoLinha>::iterator i = pontos->begin();
				i != pontos->end(); i++)
		{
			PontoLinha p = (PontoLinha)(*i);
			Coordenada *c = p.getCoordenada();
			dc->DrawCircle(converteX(c->getLongitude()),
					converteY(c->getLatitude()), raioPonto);
		}
	}
}

void MyFrame::desenhaContorno (wxPaintDC *dc, string id)
{
	List<Coordenada> *contorno = RIT.getContorno(id);
	if ((contorno != NULL) || contorno->getTamanho() > 0)
	{
		for (List<Coordenada>::iterator i = contorno->begin();
				i != contorno->end(); i++)
		{
			Coordenada c = (Coordenada)(*i);
			dc->DrawPoint(converteX(c.getLongitude()),
					converteY(c.getLatitude()));
		}
	}
}

inline void MyFrame::OnSumario(wxCommandEvent& event) {

//	string s = RIT.sumario();
//
//    ListaDialog dialog ( this, -1, _("Sumario"),
//    		 s,
//			wxPoint(100, 100), wxSize(400, 400) );
//	if ( dialog.ShowModal() == wxID_OK )
//	{
//	}
}

void MyFrame::desenhaVeiculos (wxPaintDC *dc, string id)
{
	List<LocalVeiculo> *local = RIT.getPosicoesVeiculos(id);
	if ((local != NULL) || local->getTamanho() > 0)
	{
		for (List<LocalVeiculo>::iterator i = local->begin();
				i != local->end(); i++)
		{
			LocalVeiculo l = (LocalVeiculo)(*i);
			Coordenada *c = l.getCoordenada();
			dc->DrawPoint(converteX(c->getLongitude()),
					converteY(c->getLatitude()));
		}
	}
}

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    // desenha mapa
    if (config.getBool(CONFIG_DESENHA_MAPA))
    	dc.DrawBitmap( image, 0, 0, false );

    //wxSize size = GetClientSize();
    wxColor vermelho (255,0,0);
    wxColor verde (0,255,0);
    wxColor azul (0,0,255);

	dc.SetBrush(*wxGREEN_BRUSH); // green filling
	dc.SetPen( wxPen( vermelho, 1 ) ); // 5-pixels-thick red outline

    // plota pontos
    // para todas as linhas (selecionadas)
    vector<Linha> *linhas2 = RIT.getLinhas2();
    vector<Linha>::iterator ilinhas;
    for (ilinhas = linhas2->begin(); ilinhas != linhas2->end(); ilinhas++)
    {
    	Linha *l = (Linha*)&(*ilinhas);
    	// procura linha
    	string id = l->getId();
    	int ind = RIT.procuraLinha(id);
    	if (ind < 0)
    		continue;

    	// desenha pontos de onibus
    	if (config.getBool(CONFIG_DESENHA_PONTOS, true))
    	{
    		dc.SetPen( wxPen( vermelho, 1 ) );
    		desenhaPontos (&dc, id);
    	}

    	// desenha contorno
		if (config.getBool(CONFIG_DESENHA_CONTORNOS, true))
		{
			dc.SetPen( wxPen( verde, 1 ) );
			desenhaContorno (&dc, id);
		}

		// desenha posicoes de veiculos
		if (config.getBool(CONFIG_DESENHA_VEICULOS, true))
		{
			dc.SetPen( wxPen( azul, 1 ) );
			desenhaVeiculos (&dc, id);
		}
    }
}

inline void MyFrame::OnRotasAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();

	    LinhasDialog dialog ( this, -1, _("Digite numero de nós"),
	    		string(fileName.ToAscii()),
				wxPoint(100, 100), wxSize(200, 200) );
		if ( dialog.ShowModal() == wxID_OK )
		{

		}

	}
}

inline void MyFrame::OnOnibusAbreArquivo(wxCommandEvent& event) {
	wxDirDialog * dirDialog = new wxDirDialog(this);
	if (dirDialog->ShowModal() == wxID_OK){
		wxString fileName = dirDialog->GetPath();

		RIT.carregaVeiculos(string(fileName.ToAscii()));

		this->Refresh(true);
		this->Update();
	}
}

void MyFrame::OnConfiguracoes (wxCommandEvent& event) {
	ConfigDialog dialog ( this, -1, _("Configurações"), &config,
				wxPoint(100, 100), wxSize(400, 400) );
	if ( dialog.ShowModal() == wxID_OK )
	{
		this->Refresh(true);
		this->Update();
	}
}

void MyFrame::OnLinhasMostraLista(wxCommandEvent& event) {
	ListaLinhasDialog dialog ( this, -1, _("Linhas"),
			RIT.getLinhas2(),
			wxPoint(100, 100), wxSize(400, 400) );
	dialog.ShowModal();
}

void MyFrame::OnPontosAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

		wxString fileName = openFileDialog->GetPath();

		// extrai o nome da linha, do nome do arquivo
		int ind = fileName.Find("-")+1;
		string linha = fileName.SubString(ind, ind+2).ToStdString();

		LinhasDialog dialog ( this, -1, _("Abre arquivo de pontos"),
				string(fileName.ToAscii()),
				wxPoint(100, 100), wxSize(400, 400) );
		if ( dialog.ShowModal() == wxID_OK )
		{
			RIT.carregaPontos(linha, string(fileName.ToAscii()));

			this->Refresh(true);
			this->Update();
		}
	}
}

void MyFrame::OnCarregaTudo(wxCommandEvent& event) {
	RIT.carregaLinhas();
	RIT.carregaPontos();
	// carrega shapes

}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(menu_FileOpen,  MyFrame::OnOpen)
	EVT_MENU(menuArquivoLinhas,  MyFrame::OnLinhasAbreArquivo)
	EVT_MENU(menuArquivoPontos,  MyFrame::OnPontosAbreArquivo)
	EVT_MENU(menuArquivoVeiculos,  MyFrame::OnOnibusAbreArquivo)
	EVT_MENU(menuLinhasLista,  MyFrame::OnLinhasMostraLista)
	EVT_MENU(menuConfiguracoes,  MyFrame::OnConfiguracoes)
	EVT_MENU(menuSumario,  MyFrame::OnSumario)
	EVT_MENU(menuCarregaTudo,  MyFrame::OnCarregaTudo)
    EVT_MENU(menuSair,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MOUSE_EVENTS(MyFrame::OnMouse)
	EVT_PAINT(MyFrame::OnPaint)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame(_T("URBS App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->SetSize(640, 640);
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));

#if wxUSE_MENUS
    // cria árvore de menus
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
    wxMenu *menuLinhas = new wxMenu;
    wxMenu *menuFerramentas = new wxMenu;
    wxMenu *menuCarregaDados = new wxMenu;

    fileMenu->Append(menuArquivoLinhas, _T("Carrega linhas..."), _T(""));
	fileMenu->Append(menuArquivoPontos, _T("Carrega pontos..."), _T(""));
	//fileMenu->Append(menuArquivoRotas, _T("Carrega rotas..."), _T(""));
    //fileMenu->Append(menuArquivoHorarios, _T("Carrega horarios..."), _T(""));
    fileMenu->Append(menuArquivoVeiculos, _T("Carrega veiculos..."), _T(""));
    fileMenu->Append(menuSair, _T("E&ncerra\tAlt-X"), _T("Encerra este programa"));

    menuLinhas->Append(menuLinhasLista, _T("Lista todas linhas..."), _T(""));

    menuFerramentas->Append(menuConfiguracoes, _T("Configurações..."), _T(""));
    menuFerramentas->Append(menuSumario, _T("Sumario..."), _T(""));
//    menuFerramentas->Append(menuColetas, _T("Sumario..."), _T(""));

    menuCarregaDados->Append(menuCarregaTudo, _T("Carrega todos os dados..."), _T(""));

    helpMenu->Append(Minimal_About, _T("&Sobre...\tF1"), _T(""));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&Arquivo"));
    menuBar->Append(menuLinhas, _T("&Linhas"));
    menuBar->Append(menuFerramentas, _T("&Ferramentas"));
    menuBar->Append(menuCarregaDados,_T("Carrega Dados"));
    menuBar->Append(helpMenu, _T("&Ajuda"));

    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    //SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR

   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
	   cout <<"Current working dir: " << cwd << endl;;

	config.setLog(&log);
	config.parse("urbs.cfg");
    RIT.Init(&config, &log);
    raioPonto=config.getInt(CONFIG_RAIO_PONTO, 2);
    string mapa = config.get(CONFIG_IMAGEM_MAPA);
    image.LoadFile(mapa, wxBITMAP_TYPE_PNG);

    margemEsquerda = -49.456909;
	margemDireita = -49.097456;
	margemSuperior = -25.218254;
	margemInferior = -25.658483;

	coletaLinhas.setConfig(&config);
	coletaLinhas.inicia();
}


// event handlers
void MyFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
//	wxTextCtrl *tc;
//	tc = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1),
//	    wxSize(-1, -1), wxTE_MULTILINE);

	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();
	    //grafo.load(string(fileName.ToAscii()));
	    this->Refresh(true);
	    this->Update();
	}
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("Olá!\n")
                    _T("\n")
                    _T("\n")
                    _T("rodando em %s."),
                   // wxVERSION_STRING,
                    wxGetOsDescription().c_str()
                 ),
                 _T("Sobre UTFPR - URBS App"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnLinhasAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();

	    LinhasDialog dialog ( this, -1, _(""),
	    		string(fileName.ToAscii()),
				wxPoint(100, 100), wxSize(400, 400) );
	    if ( dialog.ShowModal() == wxID_OK )
	    	RIT.carregaLinhas(string(fileName.ToAscii()));
	}
}

double MyFrame::converteLat(int x)
{
	if (x == 0)
		return margemEsquerda;
	return (margemEsquerda - x*(margemEsquerda-margemDireita)/640);
}

double MyFrame::converteLon(int y)
{
	if (y == 0)
		return margemSuperior;
	return (margemSuperior - y*(margemSuperior-margemInferior)/640);
}

int MyFrame::converteX(double lat)
{
	return (-(lat - margemEsquerda)*640)/(margemEsquerda-margemDireita);
}

int MyFrame::converteY(double lon)
{
	return (-(lon-margemSuperior)*640/(margemSuperior-margemInferior));
}

void MyFrame::OnMouse(wxMouseEvent& event) {
	int x = event.GetX();
	int y = event.GetY();

	SetStatusText(wxString::Format(_T("x: %f, y: %f"),
			converteLat(x), converteLon(y)));
}

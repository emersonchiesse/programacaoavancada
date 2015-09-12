/*
 * Board.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: x
 */

#include "Board.h"

Board::Board(wxFrame *parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition,
             wxDefaultSize, wxBORDER_NONE)
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
}

Board::~Board() {
}

void Board::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    dc.DrawCircle(170, 230, 20);
}

void Board::OnKeyDown(wxKeyEvent& event) {
}

void Board::OnTimer(wxCommandEvent& event) {
}

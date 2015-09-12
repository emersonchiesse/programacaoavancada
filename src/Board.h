/*
 * Board.h
 *
 *  Created on: Aug 3, 2015
 *      Author: x
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <wx/wx.h>

class Board : public wxPanel {
public:
	Board(wxFrame *parent);
	virtual ~Board();

protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

};

#endif /* BOARD_H_ */

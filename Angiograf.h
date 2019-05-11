//---------------------------------------------------------------------------

#ifndef AngiografH
#define AngiografH

#include <System.Classes.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <DateUtils.hpp>
#include "IniFiles.hpp"
#include "test366.h"

//---------------------------------------------------------------------------
extern TIniFile *Ini366;
//---------------------------------------------------------------------------
class Angiograph {
 private:
	bool stopFlag;
	AnsiString str;
	TDateTime start_time;
	TDateTime final_count;
	int PanelHeight;
	int sN;

	TLabel *label,*startlabel,*label1,*label2;
	TTimer *timer;

	TPanel *stop_panel,*panel;

	TLabel *stop_panel_label,*stop_panel_time_label;
	TLabel *stop_fill_label;
	TButton *start_button,*yes_button,*no_button;
	TShape *tln;
	TImage *image;


	void __fastcall show_stop_panel();
	void __fastcall time_tick(TObject *Sender);
	void __fastcall start_click(TObject *Sender, TMouseButton Button, TShiftState Shift,int X, int Y);
	void __fastcall yes_button_click(TObject *Sender);
	void __fastcall no_button_click(TObject *Sender);
	void __fastcall stop_procedure();
	void __fastcall check_status();
	void __fastcall check_final_count();

	void __fastcall Locations(TForm* form);


 public:
	Angiograph(int i,TForm* form){sN=i+1;Locations(form);};
	~Angiograph(){delete panel;}//end of destructor

	int getSN(void){return sN;}
	int getHeight(void){return PanelHeight;}
	void setStartTime(TDateTime st){start_time=st;}
 };
#endif

//---------------------------------------------------------------------------
#pragma hdrstop
#include "Angiograf.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall Angiograph::yes_button_click(TObject *Sender){
	stop_procedure();
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::no_button_click(TObject *Sender){
		stop_panel->Visible=false;
		startlabel->Enabled=true;
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::check_status(){
	startlabel->Caption=stopFlag?"Завершить процедуру досрочно":"Начать процедуру";
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::check_final_count(){
AnsiString astr;
TDateTime now_time;
float difference;
int iRC;
	now_time=Now();
	if(stop_panel->Visible){               	
		iRC=CompareTime(now_time,final_count);
		difference=SecondsBetween(now_time,final_count);
		if (iRC==-1&&difference!=0){
			str.sprintf("Осталось: %d сек.",(int)difference);
			stop_panel_time_label->Caption=str;
		}//end of if
		else{
			no_button_click(NULL);
		}//end of else
	}//end of if
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::time_tick(TObject *Sender){
	AnsiString astr,bstr,astart_time;
	TDateTime remain_time,now_time;
	float difference;
	int iRC;
	now_time=Now();
	astart_time=start_time.FormatString("hh:mm:ss");
	if (astart_time!="00:00:00") {
		bstr.sprintf("Начало: %s",astart_time.c_str());
		label1->Caption=bstr;
		stopFlag=1;
	}//end of if
	
	remain_time=IncMinute(start_time,90);
	iRC=CompareDateTime(now_time,remain_time);
	difference=SecondsBetween(now_time,remain_time);

	if (iRC==1 || difference==0) {
		stop_procedure();
	}//end of if
	else{
		remain_time-=now_time;
		astr=remain_time.FormatString("hh:mm:ss");
		str.sprintf("Осталось: %s",astr.c_str());
		label2->Caption=str;
		check_final_count();
	}//end of if
	check_status();
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::show_stop_panel(){
	if(stop_panel->Visible==false){
		final_count=Now();
		final_count=IncSecond(final_count,11);
		stop_panel->Visible=true;
		startlabel->Enabled=false;
		check_final_count();
	}//end of if
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::stop_procedure(){
AnsiString astr; 
	label1->Caption="Начало: 00:00:00";
	start_time=TTime("00:00:00");
	label2->Caption="Осталось: 00:00:00";
	stop_panel->Visible=false;
	startlabel->Enabled=true;

	astr.sprintf("Ангиограф%d",sN+1);
	Ini366->WriteString(astr, "Начало", "00:00:00");
	stopFlag=0;
	check_status();		
}//end of proc
//---------------------------------------------------------------------------
void __fastcall Angiograph::start_click(TObject *Sender, TMouseButton Button, TShiftState Shift,int X, int Y){ 
AnsiString str,astr,bstr;
	if(!stopFlag){
		stopFlag=1;
		start_time=Now();
		bstr=start_time.FormatString("hh:mm:ss");
		str.sprintf("Начало: %s",bstr.c_str());

		astr.sprintf("Ангиограф%d",sN+1);
		bstr=start_time.FormatString("dd.mm.yyyy hh:mm:ss");
		Ini366->WriteString(astr, "Начало", bstr);
		
		label1->Caption=str;
		str.sprintf("Осталось: %s","01:30:00");
		label2->Caption=str;
	}//end of if
	else{
		show_stop_panel();
	}//end of else
	check_status();
}//end of proc
//-----------------------------------------------------------------------------
void __fastcall Angiograph::Locations(TForm* form){

	sN=number_Of_Angiograph++;
	stopFlag=0;

	panel= new TPanel(form);
	panel->Parent = form;
	panel->Font->Size=14;
	panel->Alignment=taLeftJustify;
	panel->VerticalAlignment=taAlignTop;
	panel->Top=10;
	panel->Left=1;
	panel->Visible=true;
	str.sprintf("Ангиограф%d",number_Of_Angiograph);
	panel->Caption=str;

	start_button=new TButton(panel);
	start_button->Parent = panel;
	start_button->Top=22;
	start_button->Left=10;
	start_button->Width=130;
	start_button->Height=95;

	startlabel=new TLabel(start_button);
	startlabel->Parent = start_button;
	startlabel->AutoSize=false;
	startlabel->Transparent=true;
	startlabel->Top=1;
	startlabel->Left=1;
	startlabel->Width=start_button->Width-2;
	startlabel->Height=start_button->Height-2;
	startlabel->Caption="Начать процедуру";
	startlabel->Layout=tlCenter;
	startlabel->Alignment=taCenter;
	startlabel->WordWrap=true;
	startlabel->Font->Size=14;
	startlabel->OnMouseDown = start_click;

	label1=new TLabel(panel);
	label1->Parent = panel;
	label1->Top=start_button->Top+14;
	label1->Left=start_button->Left+start_button->Width+10;
	label1->AutoSize=false;
	label1->Width=170;
	label1->Height=30;
	label1->Alignment=taRightJustify;
	str.sprintf("Начало: 00:00:00");
	label1->Caption=str;
	label1->Font->Size=14;

	label2=new TLabel(panel);
	label2->Parent = panel;
	label2->AutoSize=false;
	label2->Top=label1->Top+label1->Height+5;
	label2->Left=label1->Left;
	label2->Width=label1->Width;
	label2->Height=label1->Height;
	label2->Alignment=taRightJustify;
	str.sprintf("Осталось: 00:00:00");
	label2->Caption=str;
	label2->Font->Size=label1->Font->Size;

	stop_panel= new TPanel(panel);
	stop_panel->Parent = panel;
	stop_panel->Top=start_button->Top;
	stop_panel->Height=start_button->Height;
	stop_panel->Width=300;
	stop_panel->Left=label1->Left+label1->Width+14;
	stop_panel->Visible=false;

	stop_fill_label= new TLabel(stop_panel);
	stop_fill_label->Parent = stop_panel;
	stop_fill_label->AutoSize=false;
	stop_fill_label->Transparent=false;
	stop_fill_label->Alignment=taCenter;
	stop_fill_label->Font->Size=10;
	stop_fill_label->Caption="Завершить ангиографию досрочно?";
	stop_fill_label->Color=clCream;
	stop_fill_label->Top=1;
	stop_fill_label->Left=1;
	stop_fill_label->Height=stop_panel->Height-2;
	stop_fill_label->Width=stop_panel->Width-2;
	stop_fill_label->WordWrap=true;

	stop_panel_time_label=new TLabel(stop_panel);
	stop_panel_time_label->Parent = stop_panel;
	stop_panel_time_label->AutoSize=false;	
	stop_panel_time_label->Font->Color=clRed;
    stop_panel_time_label->Font->Size=10;
	stop_panel_time_label->Top=24;
	stop_panel_time_label->Left=43;
	stop_panel_time_label->Width=label1->Width;
	stop_panel_time_label->Height=label1->Height;
	stop_panel_time_label->Alignment=taLeftJustify;
	str.sprintf("Осталось: 00:00:00");
	stop_panel_time_label->Caption=str;

	tln = new TShape(stop_panel);
	tln->Parent = stop_panel;	
	tln->Top= stop_panel_time_label->Top+stop_panel_time_label->Height;
	tln->Left= 1;
	tln->Height= 1;
	tln->Width= stop_panel->Width;
	tln->Visible=true;

	yes_button=new TButton(stop_panel);
	yes_button->Parent = stop_panel;
	yes_button->Height=27;
	yes_button->Width=80;
	yes_button->Font->Size=11;
	yes_button->Top=stop_fill_label->Height-yes_button->Height-5;
	yes_button->Left=stop_fill_label->Width/2-yes_button->Width-3;
	yes_button->Caption="Да";
	yes_button->OnClick = yes_button_click;

	no_button=new TButton(stop_panel);
	no_button->Parent = stop_panel;
	no_button->Font->Size=yes_button->Font->Size;
	no_button->Height=yes_button->Height;
	no_button->Top=yes_button->Top;
	no_button->Left=stop_fill_label->Width/2+3;
	no_button->Width=yes_button->Width;
	no_button->Caption="Нет";
	no_button->OnClick = no_button_click;

	image=new TImage(stop_panel);
	image->Parent = stop_panel;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
	image->Picture=F366->Image1->Picture;
	panel->Height=start_button->Height+30;
	panel->Top=10+panel->Height* sN;
	panel->Width= stop_panel->Left+stop_panel->Width+10;
	form->Width=panel->Width+22;

	timer=new TTimer(NULL);
	timer->OnTimer = time_tick;
	timer->Interval = 500;
}//end of proc
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "test366.h"
#include "Angiograf.h"
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//readme updated
TF366 *F366;
int number_Of_Angiograph;
Angiograph *angarray[20];
TIniFile *Ini366;
//---------------------------------------------------------------------------
__fastcall TF366::TF366(TComponent* Owner): TForm(Owner){
AnsiString astr,bstr;
int ii;
	Ini366=new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ));
	try{
		ii=Ini366->ReadInteger("Ангиографы","Number",0);
	}//end of try
	catch(...){
		ii=4;
        Ini366->WriteInteger("Ангиографы","Number",ii);
	}//end of catch

	for (int i=1;i<=ii;i++){
		angarray[number_Of_Angiograph-1]=new Angiograph(F366);
		astr.sprintf("Ангиограф%d",i);
		bstr=Ini366->ReadString(astr, "Начало", "");
		try{
			angarray[number_Of_Angiograph-1]->start_time=TDateTime(bstr);
		}//end of try
		catch(...){
			angarray[number_Of_Angiograph-1]->start_time=TDateTime("00:00:00");
		}//end of catch
	}//end of if
	F366->Height=60+number_Of_Angiograph*angarray[0]->panel->Height;
}//end of if
//---------------------------------------------------------------------------
void __fastcall TF366::Timer1Timer(TObject *Sender){
	AnsiString astr;
	TDateTime tdt=Now();
	astr=DateTimeToStr(tdt);
	F366->Caption="Test 36.6 by AlexeiPivovarov "+astr;
}//end of proc
//---------------------------------------------------------------------------
void __fastcall TF366::FormClose(TObject *Sender, TCloseAction &Action){
	delete Ini366;
    Ini366 = NULL;
}
//---------------------------------------------------------------------------


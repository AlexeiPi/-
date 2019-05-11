//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "test366.h"
#include "Angiograf.h"
#include "IniFiles.hpp"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//файл формы
std::vector <Angiograph*> ANGR;

TF366 *F366;
int number_Of_Angiograph;
Angiograph *angarray[20];
TIniFile *Ini366;
//---------------------------------------------------------------------------
__fastcall TF366::TF366(TComponent* Owner): TForm(Owner){
AnsiString astr,bstr;
int ii;
Angiograph *temp;
	Ini366=new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ));
	try{
		number_Of_Angiograph=Ini366->ReadInteger("Ангиографы","Number",0);
	}//end of try
	catch(...){
		number_Of_Angiograph=4;
		Ini366->WriteInteger("Ангиографы","Number",ii);
	}//end of catch
	for (int i=0;i<number_Of_Angiograph;i++){
		//angarray[i]=new Angiograph(i,F366);
		temp=NULL;
		temp=new Angiograph(i,F366);
		ANGR.push_back(temp);
		temp=NULL;
		temp=ANGR[i];
		astr.sprintf("Ангиограф%d",ANGR[i]->getSN());
		bstr=Ini366->ReadString(astr, "Начало", "");
		try{
			ANGR[i]->setStartTime(TDateTime((UnicodeString)bstr));
		}//end of try
		catch(...){
			ANGR[i]->setStartTime(TDateTime("00:00:00"));
		}//end of catch
	}//end of if
//	ii=angarray[0]->getHeight();
	F366->Height=60+number_Of_Angiograph*ANGR[0]->getHeight();
}//end of if
//---------------------------------------------------------------------------
void __fastcall TF366::Timer1Timer(TObject *Sender){
	F366->Caption="Test 36.6 by AlexeiPivovarov "+DateTimeToStr(Now());
}//end of proc
//---------------------------------------------------------------------------
void __fastcall TF366::FormClose(TObject *Sender, TCloseAction &Action){
	delete Ini366;
	Ini366 = NULL;
}//end of proc
//---------------------------------------------------------------------------


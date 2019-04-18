//---------------------------------------------------------------------------

#ifndef test366H
#define test366H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TF366 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPanel *Panel1;
	TImage *Image1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TF366(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF366 *F366;
//---------------------------------------------------------------------------
#endif

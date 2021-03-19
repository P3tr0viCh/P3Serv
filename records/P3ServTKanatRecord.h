// ---------------------------------------------------------------------------

#ifndef P3ServTKanatRecordH
#define P3ServTKanatRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

// ---------------------------------------------------------------------------
class TKanatRecord : public TObject {
private:
	int FID;
	TDateTime FDateTime;
	float FBrutto;
	float FTare;
	float FNetto;

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property int ID = {read = FID, write = FID};
	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};
	__property float Brutto = {read = FBrutto, write = FBrutto};
	__property float Tare = {read = FTare, write = FTare};
	__property float Netto = {read = FNetto, write = FNetto};
};

// ---------------------------------------------------------------------------
typedef TObjList<TKanatRecord>TKanatRecordList;

// ---------------------------------------------------------------------------
#endif

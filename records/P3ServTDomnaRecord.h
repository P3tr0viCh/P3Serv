// ---------------------------------------------------------------------------

#ifndef P3ServTDomnaRecordH
#define P3ServTDomnaRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

// ---------------------------------------------------------------------------
class TDomnaRecord : public TObject {
private:
	int FID;
	TDateTime FDateTime;
	String FWeighName;
	int FWeighNameCode;
	String FProduct;
	int FProductCode;
	bool FLeftSide;
	float FNetto;
	int FPartCode;
	float FHumidity;

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property int ID = {read = FID, write = FID};
	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};
	__property String WeighName = {read = FWeighName, write = FWeighName};
	__property int WeighNameCode = {
		read = FWeighNameCode, write = FWeighNameCode};
	__property String Product = {read = FProduct, write = FProduct};
	__property int ProductCode = {read = FProductCode, write = FProductCode};
	__property bool LeftSide = {read = FLeftSide, write = FLeftSide};
	__property float Netto = {read = FNetto, write = FNetto};
	__property int PartCode = {read = FPartCode, write = FPartCode};
	__property float Humidity = {read = FHumidity, write = FHumidity};
};

// ---------------------------------------------------------------------------
typedef TObjList<TDomnaRecord>TDomnaRecordList;

// ---------------------------------------------------------------------------
#endif

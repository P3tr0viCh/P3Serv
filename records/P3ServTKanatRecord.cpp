// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTKanatRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TKanatRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TKanatRecord * Record = (TKanatRecord*) Obj;

	if (ID != Record->ID)
		return false;
	if (DateTime != Record->DateTime)
		return false;
	if (Brutto != Record->Brutto)
		return false;
	if (Tare != Record->Tare)
		return false;
	if (Netto != Record->Netto)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TKanatRecord::Assign(TObject * Source) {
	TKanatRecord * Record = (TKanatRecord*) Source;

	ID = Record->ID;
	DateTime = Record->DateTime;
	Brutto = Record->Brutto;
	Tare = Record->Tare;
	Netto = Record->Netto;
}

// ---------------------------------------------------------------------------
String __fastcall TKanatRecord::ToString() {
	String S;

	S = "TKanatRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "Brutto='" + FloatToStr(Brutto) + "'";
	S += ",";
	S += "Tare='" + FloatToStr(Tare) + "'";
	S += ",";
	S += "Netto='" + FloatToStr(Netto) + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------

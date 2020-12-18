// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTKoksohimRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TKoksohimRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TKoksohimRecord * Record = (TKoksohimRecord*) Obj;

	if (DateTime != Record->DateTime)
		return false;
	if (DozatorNum != Record->DozatorNum)
		return false;
	if (Netto != Record->Netto)
		return false;
	if (Material != Record->Material)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TKoksohimRecord::Assign(TObject * Source) {
	TKoksohimRecord * Record = (TKoksohimRecord*) Source;

	DateTime = Record->DateTime;
	DozatorNum = Record->DozatorNum;
	Netto = Record->Netto;
	Material = Record->Material;
}

// ---------------------------------------------------------------------------
String __fastcall TKoksohimRecord::ToString() {
	String S;

	S = "TKoksohimRecord{";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "DozatorNum='" + IntToStr(DozatorNum) + "'";
	S += ",";
	S += "Netto='" + FloatToStr(Netto) + "'";
	S += ",";
	S += "Material='" + IntToStr(Material) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------

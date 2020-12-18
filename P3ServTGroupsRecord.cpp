// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTGroupsRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TGroupsRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TGroupsRecord * Record = (TGroupsRecord*) Obj;

	if (ID != Record->ID)
		return false;
	if (FullName != Record->FullName)
		return false;
	if (ShortName != Record->ShortName)
		return false;
	if (Order != Record->Order)
		return false;
	if (MaxPro != Record->MaxPro)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TGroupsRecord::Assign(TObject * Source) {
	TGroupsRecord * Record = (TGroupsRecord*) Source;

	ID = Record->ID;
	FullName = Record->FullName;
	ShortName = Record->ShortName;
	Order = Record->Order;
	MaxPro = Record->MaxPro;
}

// ---------------------------------------------------------------------------
String __fastcall TGroupsRecord::ToString() {
	String S;

	S = "TGroupsRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "FullName='" + FullName + "'";
	S += ",";
	S += "ShortName='" + ShortName + "'";
	S += ",";
	S += "Order='" + IntToStr(Order) + "'";
	S += ",";
	S += "MaxPro='" + IntToStr(MaxPro) + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------

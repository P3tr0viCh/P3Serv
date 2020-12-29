// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTAglodozaGroupsRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TAglodozaGroupsRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TAglodozaGroupsRecord * Record = (TAglodozaGroupsRecord*) Obj;

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
void __fastcall TAglodozaGroupsRecord::Assign(TObject * Source) {
	TAglodozaGroupsRecord * Record = (TAglodozaGroupsRecord*) Source;

	ID = Record->ID;
	FullName = Record->FullName;
	ShortName = Record->ShortName;
	Order = Record->Order;
	MaxPro = Record->MaxPro;
}

// ---------------------------------------------------------------------------
String __fastcall TAglodozaGroupsRecord::ToString() {
	String S;

	S = "TAglodozaGroupsRecord{";
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

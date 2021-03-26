// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTWD30SensorsRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TWD30SensorsRecord::TWD30SensorsRecord() {
	FWD30ZRecord = new TWD30ZRecord();
	FWD30TRecord = new TWD30TRecord();
}

// ---------------------------------------------------------------------------
__fastcall TWD30SensorsRecord::~TWD30SensorsRecord() {
	FWD30TRecord->Free();
	FWD30ZRecord->Free();
}

// ---------------------------------------------------------------------------
bool __fastcall TWD30SensorsRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TWD30SensorsRecord * Record = (TWD30SensorsRecord*) Obj;

	if (DateTime != Record->DateTime)
		return false;

	if (Z != Record->Z)
		return false;
	if (T != Record->T)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TWD30SensorsRecord::Assign(TObject * Source) {
	TWD30SensorsRecord * Record = (TWD30SensorsRecord*) Source;

	DateTime = Record->DateTime;

	FWD30ZRecord = Record->Z;
	FWD30TRecord = Record->T;
}

// ---------------------------------------------------------------------------
String __fastcall TWD30SensorsRecord::ToString() {
	String S;

	S = "TWD30SensorsRecord{";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "Z='" + Z->ToString() + "'";
	S += ",";
	S += "T='" + T->ToString() + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTWD30SRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TWD30SRecord::TWD30SRecord() {
	FWD30ZRecord = new TWD30ZRecord();
	FWD30TRecord = new TWD30TRecord();
}

// ---------------------------------------------------------------------------
__fastcall TWD30SRecord::~TWD30SRecord() {
	FWD30TRecord->Free();
	FWD30ZRecord->Free();
}

// ---------------------------------------------------------------------------
bool __fastcall TWD30SRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TWD30SRecord * Record = (TWD30SRecord*) Obj;

	if (DateTime != Record->DateTime)
		return false;

	if (!Z->Equals(Record->Z))
		return false;
	if (!T->Equals(Record->T))
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TWD30SRecord::Assign(TObject * Source) {
	TWD30SRecord * Record = (TWD30SRecord*) Source;

	DateTime = Record->DateTime;

	FWD30ZRecord = Record->Z;
	FWD30TRecord = Record->T;
}

// ---------------------------------------------------------------------------
String __fastcall TWD30SRecord::ToString() {
	String S;

	S = "TWD30SRecord{";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "Z='" + Z->ToString() + "'";
	S += ",";
	S += "T='" + T->ToString() + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------

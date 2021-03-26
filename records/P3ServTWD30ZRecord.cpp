// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTWD30ZRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TWD30ZRecord::TWD30ZRecord() {
	for (int i = 1; i <= WD30_Z_COUNT; i++) {
		Z[i] = WD30_Z_NULL_VALUE;
	}
}

// ---------------------------------------------------------------------------
bool __fastcall TWD30ZRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TWD30ZRecord * Record = (TWD30ZRecord*) Obj;

	if (DateTime != Record->DateTime)
		return false;

	// TODO :
	throw EMethodNotFound("TWD30ZRecord::Assign");

	// return true;
}

// ---------------------------------------------------------------------------
void __fastcall TWD30ZRecord::Assign(TObject * Source) {
	TWD30ZRecord * Record = (TWD30ZRecord*) Source;

	DateTime = Record->DateTime;

	// TODO :
	throw EMethodNotFound("TWD30ZRecord::Assign");
}

// ---------------------------------------------------------------------------
String __fastcall TWD30ZRecord::ToString() {
	String S;

	S = "TWD30ZRecord{";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";

	S += "Z=";
	S += "{";
	for (int i = 1; i <= WD30_Z_COUNT; i++) {
		S += IntToStr(Z[i]) + "|";
	}
	S += "}";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
int __fastcall TWD30ZRecord::GetZ(int Index) {
	if (Index >= 1 && Index <= WD30_Z_COUNT) {
		return FZ[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TWD30ZRecord::SetZ(int Index, int Value) {
	if (Index >= 1 && Index <= WD30_Z_COUNT) {
		FZ[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------

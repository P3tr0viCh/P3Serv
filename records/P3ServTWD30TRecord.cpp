// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTWD30TRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TWD30TRecord::TWD30TRecord() {
	for (int i = 1; i <= WD30_T_COUNT; i++) {
		T[i] = WD30_T_NULL_VALUE;
	}
}

// ---------------------------------------------------------------------------
bool __fastcall TWD30TRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TWD30TRecord * Record = (TWD30TRecord*) Obj;

	if (DateTime != Record->DateTime)
		return false;

	// TODO :
	throw EMethodNotFound("TWD30TRecord::Assign");

	// return true;
}

// ---------------------------------------------------------------------------
void __fastcall TWD30TRecord::Assign(TObject * Source) {
	TWD30TRecord * Record = (TWD30TRecord*) Source;

	DateTime = Record->DateTime;

	// TODO :
	throw EMethodNotFound("TWD30TRecord::Assign");
}

// ---------------------------------------------------------------------------
String __fastcall TWD30TRecord::ToString() {
	String S;

	S = "TWD30TRecord{";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";

	S += "T=";
	S += "{";
	for (int i = 1; i <= WD30_T_COUNT; i++) {
		S += FloatToStr(T[i]) + "|";
	}
	S += "}";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
float __fastcall TWD30TRecord::GetT(int Index) {
	if (Index >= 1 && Index <= WD30_T_COUNT) {
		return FT[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TWD30TRecord::SetT(int Index, float Value) {
	if (Index >= 1 && Index <= WD30_T_COUNT) {
		FT[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTDozSumRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TDozSumRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TDozSumRecord * Record = (TDozSumRecord*) Obj;

	if (ID != Record->ID)
		return false;

	if (Line != Record->Line)
		return false;

	if (DateTime != Record->DateTime)
		return false;

	// TODO :
	throw EMethodNotFound("TDozSumRecord::Assign");

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TDozSumRecord::Assign(TObject * Source) {
	TDozSumRecord * Record = (TDozSumRecord*) Source;

	ID = Record->ID;

	Line = Record->Line;

	DateTime = Record->DateTime;

	// TODO :
	throw EMethodNotFound("TDozSumRecord::Assign");
}

// ---------------------------------------------------------------------------
String __fastcall TDozSumRecord::ToString() {
	String S;

	S = "TDozSumRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "Line='" + IntToStr(Line) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";

	S += "DozatorSum=";
	S += "{";
	for (int i = 1; i <= DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorSum[i]) + "|";
	}
	S += "}";
	S += ",";

	S += "DozatorProd=";
	S += "{";
	for (int i = 1; i <= DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorProd[i]) + "|";
	}
	S += "}";
	S += ",";

	S += "DozatorGroup=";
	S += "{";
	for (int i = 1; i <= DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorGroup[i]) + "|";
	}
	S += "}";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
float __fastcall TDozSumRecord::GetDozatorSum(int Index) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		return FDozatorSum[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TDozSumRecord::SetDozatorSum(int Index, float Value) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		FDozatorSum[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
float __fastcall TDozSumRecord::GetDozatorProd(int Index) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		return FDozatorProd[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TDozSumRecord::SetDozatorProd(int Index, float Value) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		FDozatorProd[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
float __fastcall TDozSumRecord::GetDozatorGroup(int Index) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		return FDozatorGroup[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TDozSumRecord::SetDozatorGroup(int Index, float Value) {
	if (Index >= 1 && Index <= DOZATOR_COUNT) {
		FDozatorGroup[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------

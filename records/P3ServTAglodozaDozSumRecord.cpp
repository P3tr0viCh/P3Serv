// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTAglodozaDozSumRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TAglodozaDozSumRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TAglodozaDozSumRecord * Record = (TAglodozaDozSumRecord*) Obj;

	if (ID != Record->ID)
		return false;

	if (Line != Record->Line)
		return false;

	if (DateTime != Record->DateTime)
		return false;

	// TODO :
	throw EMethodNotFound("TAglodozaDozSumRecord::Assign");

	// return true;
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaDozSumRecord::Assign(TObject * Source) {
	TAglodozaDozSumRecord * Record = (TAglodozaDozSumRecord*) Source;

	ID = Record->ID;

	Line = Record->Line;

	DateTime = Record->DateTime;

	// TODO :
	throw EMethodNotFound("TAglodozaDozSumRecord::Assign");
}

// ---------------------------------------------------------------------------
String __fastcall TAglodozaDozSumRecord::ToString() {
	String S;

	S = "TAglodozaDozSumRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "Line='" + IntToStr(Line) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";

	S += "DozatorSum=";
	S += "{";
	for (int i = 1; i <= AGLODOZA_DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorSum[i]) + "|";
	}
	S += "}";
	S += ",";

	S += "DozatorProd=";
	S += "{";
	for (int i = 1; i <= AGLODOZA_DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorProd[i]) + "|";
	}
	S += "}";
	S += ",";

	S += "DozatorGroup=";
	S += "{";
	for (int i = 1; i <= AGLODOZA_DOZATOR_COUNT; i++) {
		S += FloatToStr(DozatorGroup[i]) + "|";
	}
	S += "}";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
float __fastcall TAglodozaDozSumRecord::GetDozatorSum(int Index) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		return FDozatorSum[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaDozSumRecord::SetDozatorSum(int Index, float Value) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		FDozatorSum[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
float __fastcall TAglodozaDozSumRecord::GetDozatorProd(int Index) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		return FDozatorProd[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaDozSumRecord::SetDozatorProd(int Index, float Value) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		FDozatorProd[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
float __fastcall TAglodozaDozSumRecord::GetDozatorGroup(int Index) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		return FDozatorGroup[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaDozSumRecord::SetDozatorGroup(int Index, float Value) {
	if (Index >= 1 && Index <= AGLODOZA_DOZATOR_COUNT) {
		FDozatorGroup[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------

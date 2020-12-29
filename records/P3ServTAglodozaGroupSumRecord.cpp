// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTAglodozaGroupSumRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TAglodozaGroupSumRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TAglodozaGroupSumRecord * Record = (TAglodozaGroupSumRecord*) Obj;

	if (ID != Record->ID)
		return false;

	if (Line != Record->Line)
		return false;

	if (DateTime != Record->DateTime)
		return false;

	// TODO :
	throw EMethodNotFound("TP3SumRecord::Assign");

	// return true;
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaGroupSumRecord::Assign(TObject * Source) {
	TAglodozaGroupSumRecord * Record = (TAglodozaGroupSumRecord*) Source;

	ID = Record->ID;

	Line = Record->Line;

	DateTime = Record->DateTime;

	// TODO :
	throw EMethodNotFound("TP3SumRecord::Assign");
}

// ---------------------------------------------------------------------------
String __fastcall TAglodozaGroupSumRecord::ToString() {
	String S;

	S = "TAglodozaGroupSumRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "Line='" + IntToStr(Line) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";

	S += "GroupId=";
	S += "{";
	for (int i = 1; i <= AGLODOZA_GROUPS_COUNT; i++) {
		S += FloatToStr(GroupId[i]) + "|";
	}
	S += "}";
	S += ",";

	S += "GroupSum=";
	S += "{";
	for (int i = 1; i <= AGLODOZA_GROUPS_COUNT; i++) {
		S += FloatToStr(GroupSum[i]) + "|";
	}
	S += "}";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
float __fastcall TAglodozaGroupSumRecord::GetGroupId(int Index) {
	if (Index >= 1 && Index <= AGLODOZA_GROUPS_COUNT) {
		return FGroupId[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaGroupSumRecord::SetGroupId(int Index, float Value) {
	if (Index >= 1 && Index <= AGLODOZA_GROUPS_COUNT) {
		FGroupId[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
float __fastcall TAglodozaGroupSumRecord::GetGroupSum(int Index) {
	if (Index >= 1 && Index <= AGLODOZA_GROUPS_COUNT) {
		return FGroupSum[Index];
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------
void __fastcall TAglodozaGroupSumRecord::SetGroupSum(int Index, float Value) {
	if (Index >= 1 && Index <= AGLODOZA_GROUPS_COUNT) {
		FGroupSum[Index] = Value;

		return;
	}

	throw EArgumentOutOfRangeException("index out of bounds: " +
		IntToStr(Index));
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

#ifndef P3ServTDozSumRecordH
#define P3ServTDozSumRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "P3ServTLocalRecord.h"

const DOZATOR_COUNT = 19;

// ---------------------------------------------------------------------------
class TDozSumRecord : public TLocalRecord {
private:
	char FLine;

	TDateTime FDateTime;

	float FDozatorSum[DOZATOR_COUNT];
	float FDozatorProd[DOZATOR_COUNT];
	float FDozatorGroup[DOZATOR_COUNT];

	float __fastcall GetDozatorSum(int Index);
	void __fastcall SetDozatorSum(int Index, float Value);
	float __fastcall GetDozatorProd(int Index);
	void __fastcall SetDozatorProd(int Index, float Value);
	float __fastcall GetDozatorGroup(int Index);
	void __fastcall SetDozatorGroup(int Index, float Value);

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property char Line = {read = FLine, write = FLine};

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property float DozatorSum[int Index] = {
		read = GetDozatorSum, write = SetDozatorSum};
	__property float DozatorProd[int Index] = {
		read = GetDozatorProd, write = SetDozatorProd};
	__property float DozatorGroup[int Index] = {
		read = GetDozatorGroup, write = SetDozatorGroup};
};

// ---------------------------------------------------------------------------
typedef TObjList<TDozSumRecord>TDozSumRecordList;

// ---------------------------------------------------------------------------
#endif

// ---------------------------------------------------------------------------

#ifndef P3ServTAglodozaGroupSumRecordH
#define P3ServTAglodozaGroupSumRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "P3ServTAglodozaRecord.h"

const AGLODOZA_GROUPS_COUNT = 20;

// ---------------------------------------------------------------------------
class TAglodozaGroupSumRecord : public TAglodozaRecord {
private:
	char FLine;

	TDateTime FDateTime;

	float FGroupId[AGLODOZA_GROUPS_COUNT];
	float FGroupSum[AGLODOZA_GROUPS_COUNT];

	float __fastcall GetGroupId(int Index);
	void __fastcall SetGroupId(int Index, float Value);
	float __fastcall GetGroupSum(int Index);
	void __fastcall SetGroupSum(int Index, float Value);

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property char Line = {read = FLine, write = FLine};

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property float GroupId[int Index] = {read = GetGroupId, write = SetGroupId
	};
	__property float GroupSum[int Index] = {
		read = GetGroupSum, write = SetGroupSum};
};

// ---------------------------------------------------------------------------
typedef TObjList<TAglodozaGroupSumRecord>TAglodozaGroupSumRecordList;

// ---------------------------------------------------------------------------
#endif

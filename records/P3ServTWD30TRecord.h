// ---------------------------------------------------------------------------

#ifndef P3ServTWD30TRecordH
#define P3ServTWD30TRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

const WD30_T_COUNT = 10;
const WD30_T_NULL_VALUE = 42000;

// ---------------------------------------------------------------------------
class TWD30TRecord : public TObject {
private:
	TDateTime FDateTime;

	float FT[WD30_T_COUNT + 1];

	float __fastcall GetT(int Index);
	void __fastcall SetT(int Index, float Value);

public:
	__fastcall TWD30TRecord();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property float T[int Index] = {read = GetT, write = SetT};
};

// ---------------------------------------------------------------------------
typedef TObjList<TWD30TRecord>TWD30TRecordList;

// ---------------------------------------------------------------------------
#endif

// ---------------------------------------------------------------------------

#ifndef P3ServTWD30ZRecordH
#define P3ServTWD30ZRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

const WD30_Z_COUNT = 16;
const WD30_Z_NULL_VALUE = 42000;

// ---------------------------------------------------------------------------
class TWD30ZRecord : public TObject {
private:
	TDateTime FDateTime;

	int FZ[WD30_Z_COUNT + 1];

	int __fastcall GetZ(int Index);
	void __fastcall SetZ(int Index, int Value);

public:
	__fastcall TWD30ZRecord();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property int Z[int Index] = {read = GetZ, write = SetZ};
};

// ---------------------------------------------------------------------------
typedef TObjList<TWD30ZRecord>TWD30ZRecordList;

// ---------------------------------------------------------------------------
#endif

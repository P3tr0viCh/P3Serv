// ---------------------------------------------------------------------------

#ifndef P3ServTWD30SRecordH
#define P3ServTWD30SRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "P3ServTWD30ZRecord.h"
#include "P3ServTWD30TRecord.h"

// ---------------------------------------------------------------------------
class TWD30SRecord : public TObject {
private:
	TDateTime FDateTime;

	TWD30ZRecord * FWD30ZRecord;
	TWD30TRecord * FWD30TRecord;

public:
	__fastcall TWD30SRecord();
	__fastcall ~TWD30SRecord();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property TWD30ZRecord * Z = {read = FWD30ZRecord};
	__property TWD30TRecord * T = {read = FWD30TRecord};
};

// ---------------------------------------------------------------------------
typedef TObjList<TWD30SRecord>TWD30SRecordList;

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------

#ifndef P3ServTLocalRecordH
#define P3ServTLocalRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

// ---------------------------------------------------------------------------
class TAglodozaRecord : public TObject {
private:
	int FID;

public:
	virtual bool __fastcall Equals(TObject * Obj) = 0;
	virtual void __fastcall Assign(TObject * Source) = 0;
	virtual String __fastcall ToString() = 0;

	__property int ID = {read = FID, write = FID};
};

// ---------------------------------------------------------------------------
typedef TObjList<TAglodozaRecord>TAglodozaRecordList;

// ---------------------------------------------------------------------------
#endif

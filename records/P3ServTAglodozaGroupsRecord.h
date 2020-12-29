// ---------------------------------------------------------------------------

#ifndef P3ServTAglodozaGroupsRecordH
#define P3ServTAglodozaGroupsRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "P3ServTAglodozaRecord.h"

// ---------------------------------------------------------------------------
class TAglodozaGroupsRecord : public TAglodozaRecord {
private:
	String FFullName;
	String FShortName;
	int FOrder;
	int FMaxPro;

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property String FullName = {read = FFullName, write = FFullName};
	__property String ShortName = {read = FShortName, write = FShortName};
	__property int Order = {read = FOrder, write = FOrder};
	__property int MaxPro = {read = FMaxPro, write = FMaxPro};
};

// ---------------------------------------------------------------------------
typedef TObjList<TAglodozaGroupsRecord>TAglodozaGroupsRecordList;

// ---------------------------------------------------------------------------
#endif

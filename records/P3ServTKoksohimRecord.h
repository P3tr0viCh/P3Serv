// ---------------------------------------------------------------------------

#ifndef P3ServTKoksohimRecordH
#define P3ServTKoksohimRecordH

#include <System.Classes.hpp>

#include <ObjList.h>

const HEADER_SIZE = 32;

const FIELD_SIZE = 32;
const FIELD_COUNT = 6;
const RECORD_SIZE = 25;

const FIELD_TMSTAMP_SIZE = 8;
const FIELD_DOZN_SIZE = 2;
const FIELD_SMENA_SIZE = 1;
const FIELD_VIRABOTKA_SIZE = 10;
const FIELD_MATERIAL_SIZE = 2;
const FIELD_GROUP_SIZE = 1;
const FIELD_MAX_SIZE = 255;

// ---------------------------------------------------------------------------
class TKoksohimRecord : public TObject {
private:
	TDateTime FDateTime;
	int FDozatorNum;
	float FNetto;
	int FMaterial;

public:
	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TObject * Source);
	String __fastcall ToString();

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};
	__property int DozatorNum = {read = FDozatorNum, write = FDozatorNum};
	__property float Netto = {read = FNetto, write = FNetto};
	__property int Material = {read = FMaterial, write = FMaterial};
};

// ---------------------------------------------------------------------------
typedef TObjList<TKoksohimRecord>TKoksohimRecordList;

// ---------------------------------------------------------------------------
#endif

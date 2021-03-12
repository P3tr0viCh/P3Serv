// ---------------------------------------------------------------------------

#pragma hdrstop

#include "P3ServTDomnaRecord.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TDomnaRecord::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TDomnaRecord * Record = (TDomnaRecord*) Obj;

	if (ID != Record->ID)
		return false;
	if (DateTime != Record->DateTime)
		return false;
	if (WeighName != Record->WeighName)
		return false;
	if (WeighNameCode != Record->WeighNameCode)
		return false;
	if (Product != Record->Product)
		return false;
	if (ProductCode != Record->ProductCode)
		return false;
	if (LeftSide != Record->LeftSide)
		return false;
	if (Netto != Record->Netto)
		return false;
	if (PartCode != Record->PartCode)
		return false;
	if (Humidity != Record->Humidity)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TDomnaRecord::Assign(TObject * Source) {
	TDomnaRecord * Record = (TDomnaRecord*) Source;

	ID = Record->ID;
	DateTime = Record->DateTime;
	WeighName = Record->WeighName;
	WeighNameCode = Record->WeighNameCode;
	Product = Record->Product;
	ProductCode = Record->ProductCode;
	LeftSide = Record->LeftSide;
	Netto = Record->Netto;
	PartCode = Record->PartCode;
	Humidity = Record->Humidity;
}

// ---------------------------------------------------------------------------
String __fastcall TDomnaRecord::ToString() {
	String S;

	S = "TDomnaRecord{";
	S += "ID='" + IntToStr(ID) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "WeighName='" + WeighName + "'";
	S += ",";
	S += "WeighNameCode='" + IntToStr(WeighNameCode) + "'";
	S += ",";
	S += "Product='" + Product + "'";
	S += ",";
	S += "ProductCode='" + IntToStr(ProductCode) + "'";
	S += ",";
	S += "LeftSide='" + BoolToStr(LeftSide) + "'";
	S += ",";
	S += "Netto='" + FloatToStr(Netto) + "'";
	S += ",";
	S += "PartCode='" + IntToStr(PartCode) + "'";
	S += ",";
	S += "Humidity='" + FloatToStr(Humidity) + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------

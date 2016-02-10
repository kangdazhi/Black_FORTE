/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: SI_parseSTRING2STRING
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     0.0: 2015-11-26/4DIAC-IDE - 4DIAC-Consortium - 
 *************************************************************************/

#ifndef _SI_PARSESTRING2STRING_H_
#define _SI_PARSESTRING2STRING_H_

#include <funcbloc.h>
#include <forte_string.h>

class FORTE_SI_parseSTRING2STRING: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_SI_parseSTRING2STRING)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_STRING &IN() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_STRING &OUT() {
    return *static_cast<CIEC_STRING*>(getDO(0));
  };

  static const TEventID scm_nEventREQID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(1, 1, 1, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_SI_parseSTRING2STRING){
  };

  virtual ~FORTE_SI_parseSTRING2STRING(){};

};

#endif //close the ifdef sequence from the beginning of the file

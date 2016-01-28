/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: F_CONCAT
 *** Description: concatenation
 *** Version: 
 ***     0.0: 2013-04-25/4DIAC-IDE - 4DIAC-Consortium - null
 *************************************************************************/

#ifndef _F_CONCAT_H_
#define _F_CONCAT_H_

#include <funcbloc.h>
#include <forte_any_string.h>

class FORTE_F_CONCAT: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_F_CONCAT)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_ANY_STRING &IN1() {
    return *static_cast<CIEC_ANY_STRING*>(getDI(0));
  };

  CIEC_ANY_STRING &IN2() {
    return *static_cast<CIEC_ANY_STRING*>(getDI(1));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_ANY_STRING &OUT() {
    return *static_cast<CIEC_ANY_STRING*>(getDO(0));
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

   FORTE_FB_DATA_ARRAY(1, 2, 1, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_F_CONCAT){
  };

  template<typename T> void calculateValueString(){
    T oIn1;
    T oIn2;
    oIn1.saveAssign(IN1());
    oIn2.saveAssign(IN2());
    OUT().saveAssign(CONCAT(oIn1,oIn2));
  }

  virtual ~FORTE_F_CONCAT(){};

};

#endif //close the ifdef sequence from the beginning of the file

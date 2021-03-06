/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: BBBio_PWM
 *** Description: Service Interface Function Block Type
 *** Version: 
 ***     0.0: 2015-09-10/EQUEROL - UJI - 
 *************************************************************************/

#ifndef _BBBIO_PWM_H_
#define _BBBIO_PWM_H_

#include <funcbloc.h>
#include <forte_real.h>
#include <forte_string.h>
#include <forte_bool.h>
#include "CBBBiolib.h"
#include "BBBiolib.h"

class FORTE_BBBio_PWM: public CFunctionBlock, public CBBBiolib{
  DECLARE_FIRMWARE_FB(FORTE_BBBio_PWM)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_STRING &PARAMS() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_REAL &DutyA() {
    return *static_cast<CIEC_REAL*>(getDI(2));
  };

  CIEC_REAL &DutyB() {
    return *static_cast<CIEC_REAL*>(getDI(3));
  };

  CIEC_REAL &Frequency() {
    return *static_cast<CIEC_REAL*>(getDI(4));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_STRING &STATUS() {
    return *static_cast<CIEC_STRING*>(getDO(1));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventUpdateID = 1;
  static const TEventID scm_nEventStartID = 2;
  static const TEventID scm_nEventStopID = 3;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;
  unsigned int m_nPWMID;
  bool m_bIsInit;
  bool m_bIsRunning;
   FORTE_FB_DATA_ARRAY(2, 5, 2, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_BBBio_PWM){
	  m_bIsInit = false;
	  m_bIsRunning = false;
	  m_nPWMID = 5; //invalid value
  };

  virtual ~FORTE_BBBio_PWM(){};

};

#endif //close the ifdef sequence from the beginning of the file


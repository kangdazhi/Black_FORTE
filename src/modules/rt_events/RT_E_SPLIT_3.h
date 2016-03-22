/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: RT_E_SPLIT_3
 *** Description: Split an event to two event chain branches
 *** Version: 
 ***     0.0: 2016-15-03/EQUEROL - UJI-ESDID - 
 *************************************************************************/

#ifndef _RT_E_SPLIT_3_H_
#define _RT_E_SPLIT_3_H_

#include <funcbloc.h>
#include <ecet.h>
#include <forte_time.h>
#include <forte_bool.h>


class FORTE_RT_E_SPLIT_3: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_RT_E_SPLIT_3)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_TIME &Tmin() {
    return *static_cast<CIEC_TIME*>(getDI(1));
  };

  CIEC_TIME &Deadline_EO1() {
    return *static_cast<CIEC_TIME*>(getDI(2));
  };

  CIEC_TIME &WCET_EO1() {
    return *static_cast<CIEC_TIME*>(getDI(3));
  };

  CIEC_TIME &Deadline_EO2() {
    return *static_cast<CIEC_TIME*>(getDI(4));
  };

  CIEC_TIME &WCET_EO2() {
    return *static_cast<CIEC_TIME*>(getDI(5));
  };

  CIEC_TIME &Deadline_EO3() {
    return *static_cast<CIEC_TIME*>(getDI(6));
  };

  CIEC_TIME &WCET_EO3() {
    return *static_cast<CIEC_TIME*>(getDI(7));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventEIID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventEO1ID = 1;
  static const TEventID scm_nEventEO2ID = 2;
  static const TEventID scm_nEventEO3ID = 3;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(4, 8, 1, 0);

   CEventChainExecutionThread m_oECEO1, m_oECEO2, m_oECEO3;
   bool m_bInitialized;

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_RT_E_SPLIT_3){
	  m_bInitialized = false;
  };

  virtual ~FORTE_RT_E_SPLIT_3(){};

};

#endif //close the ifdef sequence from the beginning of the file


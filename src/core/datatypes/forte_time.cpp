/*******************************************************************************
 * Copyright (c) 2007 4DIAC - consortium.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *******************************************************************************/
#include "forte_time.h"

#include "../../arch/timerha.h"
#include <stdlib.h>
#include <ctype.h>

#ifdef FORTE_USE_64BIT_DATATYPES
  #include "forte_lint.h"
	//Time factor defined in nanoseconds
	#define TIME_FACTOR_PER_DAY 86400000000000U
	#define TIME_FACTOR_PER_HOUR 3600000000000U
	#define TIME_FACTOR_PER_MINUTE 60000000000U
	#define TIME_FACTOR_PER_SECOND 1000000000U
	#define TIME_FACTOR_PER_MILISECOND 1000000U
	#define TIME_FACTOR_PER_MICROSECOND 1000U
	#define TIME_FACTOR_PER_NANOSECOND 1U
#else
  #include "forte_dint.h"
	//Time factor defined in ms
	#define TIME_FACTOR_PER_DAY 86400000U
	#define TIME_FACTOR_PER_HOUR 3600000U
	#define TIME_FACTOR_PER_MINUTE 60000U
	#define TIME_FACTOR_PER_SECOND 1000U
	#define TIME_FACTOR_PER_MILISECOND 1U
	#define TIME_FACTOR_PER_MICROSECOND 0
	#define TIME_FACTOR_PER_NANOSECOND 0
#endif


#define MILISECONDS_PER_SECOND 1000
#define MICROSECONDS_PER_SECOND 1000000
#define NANOSECONDS_PER_SECOND 1000000000



DEFINE_FIRMWARE_DATATYPE(TIME, g_nStringIdTIME)

const TForteUInt16 CIEC_TIME::scm_unMaxStringBufSize = 100;

int CIEC_TIME::fromString(const char *pa_pacValue){
  int nRetVal = -1;
  char* pcEnd;

  TValueType nIntVal = 0;

  if((pa_pacValue[0] == 'T') || (pa_pacValue[0] == 't')){
      nRetVal = 1;
      pa_pacValue++;
      if(('i' == tolower(pa_pacValue[0])) && ('m' == tolower(pa_pacValue[1])) && ('e' == tolower(pa_pacValue[2]))){
        pa_pacValue += 3;
        nRetVal += 3;
      }

      if(*pa_pacValue == '#'){ // the string has to start with T#
        pa_pacValue++;
        nRetVal++;
        TLargestIntValueType nTimeFactor = 1;
        bool bEnd = false;
        do{
          long nBuf = forte::core::util::strtol(pa_pacValue, &pcEnd, 10);
          switch (tolower(*pcEnd)){
            case 'd':
              nTimeFactor = TIME_FACTOR_PER_DAY;
              break;

            case 'h':
              nTimeFactor = TIME_FACTOR_PER_HOUR;
              break;

            case 'm':
              if('s' == *(pcEnd + 1) || 'S' == *(pcEnd + 1)){
                nTimeFactor = TIME_FACTOR_PER_MILISECOND;
                ++pcEnd;
              }
              else{
                nTimeFactor = TIME_FACTOR_PER_MINUTE;
              }
              break;
            case 'u' :
			  #ifndef FORTE_USE_64BIT_DATATYPES
            	DEVLOG_ERROR("microsecond parsing requires 64bit datatypes");
			  #endif
          	  nTimeFactor = TIME_FACTOR_PER_MICROSECOND;
          	  break;
            case 'n' :
			  #ifndef FORTE_USE_64BIT_DATATYPES
				DEVLOG_ERROR("nanosecond parsing requires 64bit datatypes");
			  #endif
              nTimeFactor = TIME_FACTOR_PER_NANOSECOND;
              break;
            case 's':
              nTimeFactor = TIME_FACTOR_PER_SECOND;
              break;
            case '_':
              //ignore leading underscores
              break;
            default:
              if(pa_pacValue == pcEnd){
                //we couldn't parse anything
                return -1;
              }
              bEnd = true;
              break;
          }
          nRetVal += static_cast<int>(pcEnd - pa_pacValue);
          if(!bEnd){
            ++nRetVal;
          }
          pa_pacValue = pcEnd + 1;
          nIntVal += (nBuf * nTimeFactor);
        } while(('\0' != *pa_pacValue) && (!bEnd));
      }
      else{
        return -1;
      }
    }
    else{
      nIntVal = forte::core::util::strtol(pa_pacValue, &pcEnd, 10);
      nRetVal = static_cast<int>(pcEnd - pa_pacValue);
    }

    //the intval is represented in ns if 64bit datatypes are used and in ms if not
    setFromNanoSeconds(nIntVal);
    return nRetVal;

}

int CIEC_TIME::toString(char* pa_pacValue, unsigned int pa_nBufferSize) const{
  int nRetVal = -1;

  if(pa_nBufferSize > 4){

#ifdef FORTE_USE_64BIT_DATATYPES
    CIEC_LINT timeInMilliSeconds(getInMiliSeconds());
#else
    CIEC_DINT timeInMilliSeconds(getInMiliSeconds());
#endif
    nRetVal = timeInMilliSeconds.toString(pa_pacValue + 2, pa_nBufferSize - 4);
    if(-1 != nRetVal){
      pa_pacValue[0] = 'T';
      pa_pacValue[1] = '#';
      pa_pacValue[nRetVal + 2] = 'm';
      pa_pacValue[nRetVal + 3] = 's';
      pa_pacValue[nRetVal + 4] = '\0';
      nRetVal += 4;
    }
  }
  return nRetVal;
}

CIEC_TIME::TValueType CIEC_TIME::getInSeconds() const {
  return (TValueType) *this / FORTE_TIME_BASE_UNITS_PER_SECOND;
}

CIEC_TIME::TValueType CIEC_TIME::getInMiliSeconds() const{
  TValueType nRetVal;
  #if MILISECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    nRetVal = (TValueType) *this / (FORTE_TIME_BASE_UNITS_PER_SECOND / MILISECONDS_PER_SECOND);
  #else
    nRetVal = (TValueType) *this * (MILISECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
  return nRetVal;
}

CIEC_TIME::TValueType CIEC_TIME::getInMicroSeconds() const{
  TValueType nRetVal;
  #if MICROSECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    nRetVal = (TValueType) *this / (FORTE_TIME_BASE_UNITS_PER_SECOND / MICROSECONDS_PER_SECOND);
  #else
    nRetVal = (TValueType) *this * (MICROSECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
    //fprintf(stderr,"time us: %lld\n",nRetVal);
  return nRetVal;
}

CIEC_TIME::TValueType CIEC_TIME::getInNanoSeconds() const{
  TValueType nRetVal;
  #if NANOSECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    nRetVal = (TValueType) *this / (FORTE_TIME_BASE_UNITS_PER_SECOND / NANOSECONDS_PER_SECOND);
  #else
    nRetVal = (TValueType) *this * (NANOSECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
  return nRetVal;
}

void CIEC_TIME::setFromSeconds(TValueType pa_nValue){
  *this = pa_nValue * FORTE_TIME_BASE_UNITS_PER_SECOND;
}

void CIEC_TIME::setFromMiliSeconds(TValueType pa_nValue){
  #if MILISECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    *this = pa_nValue * (FORTE_TIME_BASE_UNITS_PER_SECOND / MILISECONDS_PER_SECOND);
  #else
    *this = pa_nValue / (MILISECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
}

void CIEC_TIME::setFromMicroSeconds(TValueType pa_nValue){
  #if MICROSECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    *this = pa_nValue * (FORTE_TIME_BASE_UNITS_PER_SECOND / MICROSECONDS_PER_SECOND);
  #else
    *this = pa_nValue / (MICROSECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
}

void CIEC_TIME::setFromNanoSeconds(TValueType pa_nValue){
  #if NANOSECONDS_PER_SECOND < FORTE_TIME_BASE_UNITS_PER_SECOND
    *this = pa_nValue * (FORTE_TIME_BASE_UNITS_PER_SECOND / NANOSECONDS_PER_SECOND);
  #else
    *this = pa_nValue / (NANOSECONDS_PER_SECOND / FORTE_TIME_BASE_UNITS_PER_SECOND);
  #endif
}

const CIEC_TIME TIME(){
  SForteTime tx = CTimerHandler::sm_poFORTETimer->getForteTime();
  TForteUInt64 temp = ((((TForteUInt64) tx.m_nUpperValue) << 32) & 0xFFFFFFFF00000000ULL) + (((TForteUInt64) tx.m_nLowerValue) & 0xFFFFFFFFULL);
  //fprintf(stderr,"time: %lld, %lld\n",temp, temp * (1000000 / cg_nForteTicksPerSecond));
  return CIEC_TIME( temp * (FORTE_TIME_BASE_UNITS_PER_SECOND / cg_nForteTicksPerSecond) );
};


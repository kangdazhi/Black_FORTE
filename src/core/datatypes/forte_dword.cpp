/*******************************************************************************
 * Copyright (c) 2007 4DIAC - consortium.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *******************************************************************************/
#include "forte_dword.h"

DEFINE_FIRMWARE_DATATYPE(DWORD, g_nStringIdDWORD)

const TForteUInt16 CIEC_DWORD::scm_unMaxStringBufSize = 100;

const CIEC_DWORD::TValueType CIEC_DWORD::scm_nMaxVal = std::numeric_limits<CIEC_DWORD::TValueType>::max();

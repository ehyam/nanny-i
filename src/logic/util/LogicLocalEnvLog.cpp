/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

#include "stdafx.h"
#include "com_struct.h"
#include "LogicLocalEnvLog.h"

//---------------------------------------------------------------------------

CLogicLocalEnvLog*	t_LogicLocalEnvLog = NULL;

CLogicLocalEnvLog::CLogicLocalEnvLog()
{
	t_ManageLocalEnvLog			= new CManageLocalEnvLog();
	t_ManageLocalEnvLog->LoadDBMS();

	m_strLogicName		= "logic event handler";
}
//---------------------------------------------------------------------------

CLogicLocalEnvLog::~CLogicLocalEnvLog()
{
	SAFE_DELETE(t_ManageLocalEnvLog);
}
//---------------------------------------------------------------------------

INT32		CLogicLocalEnvLog::ResetDocLogID()
{
	INT32 nLastID = 0;
	TListID tIDList;
	TListIDItor begin, end;
	t_ManageLogDoc->GetItemIDList(tIDList);
	for(begin; begin != end; begin++)
	{
		PDB_LOG_DOC pdld = t_ManageLogDoc->FindItem(*begin);
		if(!pdld)	continue;

		nLastID = *begin;

		if(pdld->nRemoveTime)		continue;

		break;
	}	

	if(nLastID)
	{
		PDB_LOCAL_ENV_LOG pdlel = t_ManageLocalEnvLog->FirstItem();
		if(!pdlel)	return 0;

		pdlel->nLogDocID = nLastID;
		t_ManageLocalEnvLog->EditLocalEnvLog(*pdlel);
	}
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2011 EMC Corp.
//
//	@filename:
//		CLogicalLeftOuterJoin.cpp
//
//	@doc:
//		Implementation of left outer join operator
//---------------------------------------------------------------------------

#include "gpos/base.h"

#include "gpopt/base/CColRefSet.h"
#include "gpopt/operators/CExpression.h"
#include "gpopt/operators/CExpressionHandle.h"

#include "gpopt/operators/CLogicalLeftOuterJoin.h"

using namespace gpopt;


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterJoin::CLogicalLeftOuterJoin
//
//	@doc:
//		ctor
//
//---------------------------------------------------------------------------
CLogicalLeftOuterJoin::CLogicalLeftOuterJoin
	(
	CMemoryPool *mp
	)
	:
	CLogicalJoin(mp)
{
	GPOS_ASSERT(NULL != mp);
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterJoin::DeriveMaxCard
//
//	@doc:
//		Derive max card
//
//---------------------------------------------------------------------------
CMaxCard
CLogicalLeftOuterJoin::DeriveMaxCard
	(
	CMemoryPool *, // mp
	CExpressionHandle &exprhdl
	)
	const
{
	return CLogical::Maxcard(exprhdl, 2 /*ulScalarIndex*/, exprhdl.DeriveMaxCard(0));
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterJoin::PxfsCandidates
//
//	@doc:
//		Get candidate xforms
//
//---------------------------------------------------------------------------
CXformSet *
CLogicalLeftOuterJoin::PxfsCandidates
	(
	CMemoryPool *mp
	) 
	const
{
	CXformSet *xform_set = GPOS_NEW(mp) CXformSet(mp);

	(void) xform_set->ExchangeSet(CXform::ExfPushDownLeftOuterJoin);
	(void) xform_set->ExchangeSet(CXform::ExfSimplifyLeftOuterJoin);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2BitmapIndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2IndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2NLJoin);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2HashJoin);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuter2InnerUnionAllLeftAntiSemiJoin);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoinWithInnerSelect2BitmapIndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoinWithInnerSelect2IndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2DynamicBitmapIndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoin2DynamicIndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoinWithInnerSelect2DynamicBitmapIndexGetApply);
	(void) xform_set->ExchangeSet(CXform::ExfLeftOuterJoinWithInnerSelect2DynamicIndexGetApply);

	return xform_set;
}



// EOF


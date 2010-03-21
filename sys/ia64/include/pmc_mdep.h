/*-
 * This file is in the public domain.
 *
 * $FreeBSD: src/sys/ia64/include/pmc_mdep.h,v 1.2.10.1.2.1 2010/02/10 00:26:20 kensmith Exp $
 */

#ifndef _MACHINE_PMC_MDEP_H_
#define	_MACHINE_PMC_MDEP_H_

union pmc_md_op_pmcallocate {
	uint64_t		__pad[4];
};

/* Logging */
#define	PMCLOG_READADDR		PMCLOG_READ64
#define	PMCLOG_EMITADDR		PMCLOG_EMIT64

#if	_KERNEL
union pmc_md_pmc {
};

#define	PMC_TRAPFRAME_TO_PC(TF)	(0)	/* Stubs */
#define	PMC_TRAPFRAME_TO_FP(TF)	(0)
#define	PMC_TRAPFRAME_TO_SP(TF)	(0)

#endif

#endif /* !_MACHINE_PMC_MDEP_H_ */

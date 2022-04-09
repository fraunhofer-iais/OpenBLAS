/* f2c.h  --  Standard Fortran to C header file */

/**  barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."

	- From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition) */

#ifndef F2C_INCLUDE
#define F2C_INCLUDE

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#ifdef complex
#undef complex
#endif
#ifdef I
#undef I
#endif

#if defined(_WIN64)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef LAPACK_ILP64
typedef BLASLONG blasint;
#if defined(_WIN64)
#define blasabs(x) llabs(x)
#else
#define blasabs(x) labs(x)
#endif
#else
typedef int blasint;
#define blasabs(x) abs(x)
#endif

typedef blasint integer;

typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
static inline _Complex float Cf(complex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex double Cd(doublecomplex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex float * _pCf(complex *z) {return (_Complex float*)z;}
static inline _Complex double * _pCd(doublecomplex *z) {return (_Complex double*)z;}
#define pCf(z) (*_pCf(z))
#define pCd(z) (*_pCd(z))
typedef int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef int flag;
typedef int ftnlen;
typedef int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (fabs(x))
#define f2cmin(a,b) ((a) <= (b) ? (a) : (b))
#define f2cmax(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (f2cmin(a,b))
#define dmax(a,b) (f2cmax(a,b))
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

#define abort_() { sig_die("Fortran abort routine called", 1); }
#define c_abs(z) (cabsf(Cf(z)))
#define c_cos(R,Z) { pCf(R)=ccos(Cf(Z)); }
#define c_div(c, a, b) {pCf(c) = Cf(a)/Cf(b);}
#define z_div(c, a, b) {pCd(c) = Cd(a)/Cd(b);}
#define c_exp(R, Z) {pCf(R) = cexpf(Cf(Z));}
#define c_log(R, Z) {pCf(R) = clogf(Cf(Z));}
#define c_sin(R, Z) {pCf(R) = csinf(Cf(Z));}
//#define c_sqrt(R, Z) {*(R) = csqrtf(Cf(Z));}
#define c_sqrt(R, Z) {pCf(R) = csqrtf(Cf(Z));}
#define d_abs(x) (fabs(*(x)))
#define d_acos(x) (acos(*(x)))
#define d_asin(x) (asin(*(x)))
#define d_atan(x) (atan(*(x)))
#define d_atn2(x, y) (atan2(*(x),*(y)))
#define d_cnjg(R, Z) { pCd(R) = conj(Cd(Z)); }
#define r_cnjg(R, Z) { pCf(R) = conj(Cf(Z)); }
#define d_cos(x) (cos(*(x)))
#define d_cosh(x) (cosh(*(x)))
#define d_dim(__a, __b) ( *(__a) > *(__b) ? *(__a) - *(__b) : 0.0 )
#define d_exp(x) (exp(*(x)))
#define d_imag(z) (cimag(Cd(z)))
#define r_imag(z) (cimag(Cf(z)))
#define d_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define r_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define d_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define r_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define d_log(x) (log(*(x)))
#define d_mod(x, y) (fmod(*(x), *(y)))
#define u_nint(__x) ((__x)>=0 ? floor((__x) + .5) : -floor(.5 - (__x)))
#define d_nint(x) u_nint(*(x))
#define u_sign(__a,__b) ((__b) >= 0 ? ((__a) >= 0 ? (__a) : -(__a)) : -((__a) >= 0 ? (__a) : -(__a)))
#define d_sign(a,b) u_sign(*(a),*(b))
#define r_sign(a,b) u_sign(*(a),*(b))
#define d_sin(x) (sin(*(x)))
#define d_sinh(x) (sinh(*(x)))
#define d_sqrt(x) (sqrt(*(x)))
#define d_tan(x) (tan(*(x)))
#define d_tanh(x) (tanh(*(x)))
#define i_abs(x) abs(*(x))
#define i_dnnt(x) ((integer)u_nint(*(x)))
#define i_len(s, n) (n)
#define i_nint(x) ((integer)u_nint(*(x)))
#define i_sign(a,b) ((integer)u_sign((integer)*(a),(integer)*(b)))
#define pow_dd(ap, bp) ( pow(*(ap), *(bp)))
#define pow_si(B,E) spow_ui(*(B),*(E))
#define pow_ri(B,E) spow_ui(*(B),*(E))
#define pow_di(B,E) dpow_ui(*(B),*(E))
#define pow_zi(p, a, b) {pCd(p) = zpow_ui(Cd(a), *(b));}
#define pow_ci(p, a, b) {pCf(p) = cpow_ui(Cf(a), *(b));}
#define pow_zz(R,A,B) {pCd(R) = cpow(Cd(A),*(B));}
#define s_cat(lpp, rpp, rnp, np, llp) { 	ftnlen i, nc, ll; char *f__rp, *lp; 	ll = (llp); lp = (lpp); 	for(i=0; i < (int)*(np); ++i) {         	nc = ll; 	        if((rnp)[i] < nc) nc = (rnp)[i]; 	        ll -= nc;         	f__rp = (rpp)[i]; 	        while(--nc >= 0) *lp++ = *(f__rp)++;         } 	while(--ll >= 0) *lp++ = ' '; }
#define s_cmp(a,b,c,d) ((integer)strncmp((a),(b),f2cmin((c),(d))))
#define s_copy(A,B,C,D) { int __i,__m; for (__i=0, __m=f2cmin((C),(D)); __i<__m && (B)[__i] != 0; ++__i) (A)[__i] = (B)[__i]; }
#define sig_die(s, kill) { exit(1); }
#define s_stop(s, n) {exit(0);}
static char junk[] = "\n@(#)LIBF77 VERSION 19990503\n";
#define z_abs(z) (cabs(Cd(z)))
#define z_exp(R, Z) {pCd(R) = cexp(Cd(Z));}
#define z_sqrt(R, Z) {pCd(R) = csqrt(Cd(Z));}
#define myexit_() break;
#define mycycle() continue;
#define myceiling(w) {ceil(w)}
#define myhuge(w) {HUGE_VAL}
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc(w,s,e,n) {dmaxloc_(w,*(s),*(e),n)}

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1
#ifdef __cplusplus
typedef logical (*L_fp)(...);
#else
typedef logical (*L_fp)();
#endif

static float spow_ui(float x, integer n) {
	float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static double dpow_ui(double x, integer n) {
	double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static _Complex float cpow_ui(_Complex float x, integer n) {
	_Complex float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static _Complex double zpow_ui(_Complex double x, integer n) {
	_Complex double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer pow_ii(integer x, integer n) {
	integer pow; unsigned long int u;
	if (n <= 0) {
		if (n == 0 || x == 1) pow = 1;
		else if (x != -1) pow = x == 0 ? 1/x : 0;
		else n = -n;
	}
	if ((n > 0) || !(n == 0 || x == 1 || x != -1)) {
		u = n;
		for(pow = 1; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer dmaxloc_(double *w, integer s, integer e, integer *n)
{
	double m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static integer smaxloc_(float *w, integer s, integer e, integer *n)
{
	float m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static inline void cdotc_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i])) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i*incx])) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
static inline void zdotc_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i])) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i*incx])) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}	
static inline void cdotu_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i]) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i*incx]) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
static inline void zdotu_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i]) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i*incx]) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif
/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/



/* Table of constant values */

static complex c_b1 = {0.f,0.f};
static complex c_b2 = {1.f,0.f};
static integer c__1 = 1;
static integer c_n1 = -1;

/* > \brief \b CHETRF_AA_2STAGE */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CHETRF_AA_2STAGE + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/chetrf_
aa_2stage.f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/chetrf_
aa_2stage.f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/chetrf_
aa_2stage.f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*      SUBROUTINE CHETRF_AA_2STAGE( UPLO, N, A, LDA, TB, LTB, IPIV, */
/*                                   IPIV2, WORK, LWORK, INFO ) */

/*       CHARACTER          UPLO */
/*       INTEGER            N, LDA, LTB, LWORK, INFO */
/*       INTEGER            IPIV( * ), IPIV2( * ) */
/*       COMPLEX            A( LDA, * ), TB( * ), WORK( * ) */

/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CHETRF_AA_2STAGE computes the factorization of a real hermitian matrix A */
/* > using the Aasen's algorithm.  The form of the factorization is */
/* > */
/* >    A = U**T*T*U  or  A = L*T*L**T */
/* > */
/* > where U (or L) is a product of permutation and unit upper (lower) */
/* > triangular matrices, and T is a hermitian band matrix with the */
/* > bandwidth of NB (NB is internally selected and stored in TB( 1 ), and T is */
/* > LU factorized with partial pivoting). */
/* > */
/* > This is the blocked version of the algorithm, calling Level 3 BLAS. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] UPLO */
/* > \verbatim */
/* >          UPLO is CHARACTER*1 */
/* >          = 'U':  Upper triangle of A is stored; */
/* >          = 'L':  Lower triangle of A is stored. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension (LDA,N) */
/* >          On entry, the hermitian matrix A.  If UPLO = 'U', the leading */
/* >          N-by-N upper triangular part of A contains the upper */
/* >          triangular part of the matrix A, and the strictly lower */
/* >          triangular part of A is not referenced.  If UPLO = 'L', the */
/* >          leading N-by-N lower triangular part of A contains the lower */
/* >          triangular part of the matrix A, and the strictly upper */
/* >          triangular part of A is not referenced. */
/* > */
/* >          On exit, L is stored below (or above) the subdiaonal blocks, */
/* >          when UPLO  is 'L' (or 'U'). */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] TB */
/* > \verbatim */
/* >          TB is COMPLEX array, dimension (LTB) */
/* >          On exit, details of the LU factorization of the band matrix. */
/* > \endverbatim */
/* > */
/* > \param[in] LTB */
/* > \verbatim */
/* >          LTB is INTEGER */
/* >          The size of the array TB. LTB >= 4*N, internally */
/* >          used to select NB such that LTB >= (3*NB+1)*N. */
/* > */
/* >          If LTB = -1, then a workspace query is assumed; the */
/* >          routine only calculates the optimal size of LTB, */
/* >          returns this value as the first entry of TB, and */
/* >          no error message related to LTB is issued by XERBLA. */
/* > \endverbatim */
/* > */
/* > \param[out] IPIV */
/* > \verbatim */
/* >          IPIV is INTEGER array, dimension (N) */
/* >          On exit, it contains the details of the interchanges, i.e., */
/* >          the row and column k of A were interchanged with the */
/* >          row and column IPIV(k). */
/* > \endverbatim */
/* > */
/* > \param[out] IPIV2 */
/* > \verbatim */
/* >          IPIV2 is INTEGER array, dimension (N) */
/* >          On exit, it contains the details of the interchanges, i.e., */
/* >          the row and column k of T were interchanged with the */
/* >          row and column IPIV(k). */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX workspace of size LWORK */
/* > \endverbatim */
/* > */
/* > \param[in] LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >          The size of WORK. LWORK >= N, internally used to select NB */
/* >          such that LWORK >= N*NB. */
/* > */
/* >          If LWORK = -1, then a workspace query is assumed; the */
/* >          routine only calculates the optimal size of the WORK array, */
/* >          returns this value as the first entry of the WORK array, and */
/* >          no error message related to LWORK is issued by XERBLA. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit */
/* >          < 0:  if INFO = -i, the i-th argument had an illegal value. */
/* >          > 0:  if INFO = i, band LU factorization failed on i-th column */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date November 2017 */

/* > \ingroup complexSYcomputational */

/*  ===================================================================== */
/* Subroutine */ int chetrf_aa_2stage_(char *uplo, integer *n, complex *a, 
	integer *lda, complex *tb, integer *ltb, integer *ipiv, integer *
	ipiv2, complex *work, integer *lwork, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    real r__1;
    complex q__1;

    /* Local variables */
    integer ldtb, i__, j, k;
    extern /* Subroutine */ int cgemm_(char *, char *, integer *, integer *, 
	    integer *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, integer *);
    extern logical lsame_(char *, char *);
    integer iinfo;
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *), cswap_(integer *, complex *, integer *, 
	    complex *, integer *), ctrsm_(char *, char *, char *, char *, 
	    integer *, integer *, complex *, complex *, integer *, complex *, 
	    integer *);
    integer i1;
    logical upper;
    integer i2, jb, kb, nb, td;
    extern /* Subroutine */ int clacgv_(integer *, complex *, integer *);
    integer nt;
    extern /* Subroutine */ int cgbtrf_(integer *, integer *, integer *, 
	    integer *, complex *, integer *, integer *, integer *), cgetrf_(
	    integer *, integer *, complex *, integer *, integer *, integer *),
	     clacpy_(char *, integer *, integer *, complex *, integer *, 
	    complex *, integer *), claset_(char *, integer *, integer 
	    *, complex *, complex *, complex *, integer *), xerbla_(
	    char *, integer *, ftnlen);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int chegst_(integer *, char *, integer *, complex 
	    *, integer *, complex *, integer *, integer *);
    logical tquery, wquery;
    complex piv;


/*  -- LAPACK computational routine (version 3.8.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     November 2017 */



/*  ===================================================================== */


/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --tb;
    --ipiv;
    --ipiv2;
    --work;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    wquery = *lwork == -1;
    tquery = *ltb == -1;
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < f2cmax(1,*n)) {
	*info = -4;
    } else if (*ltb < *n << 2 && ! tquery) {
	*info = -6;
    } else if (*lwork < *n && ! wquery) {
	*info = -10;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHETRF_AA_2STAGE", &i__1, (ftnlen)16);
	return 0;
    }

/*     Answer the query */

    nb = ilaenv_(&c__1, "CHETRF_AA_2STAGE", uplo, n, &c_n1, &c_n1, &c_n1, (
	    ftnlen)16, (ftnlen)1);
    if (*info == 0) {
	if (tquery) {
	    i__1 = (nb * 3 + 1) * *n;
	    tb[1].r = (real) i__1, tb[1].i = 0.f;
	}
	if (wquery) {
	    i__1 = *n * nb;
	    work[1].r = (real) i__1, work[1].i = 0.f;
	}
    }
    if (tquery || wquery) {
	return 0;
    }

/*     Quick return */

    if (*n == 0) {
	return 0;
    }

/*     Determine the number of the block size */

    ldtb = *ltb / *n;
    if (ldtb < nb * 3 + 1) {
	nb = (ldtb - 1) / 3;
    }
    if (*lwork < nb * *n) {
	nb = *lwork / *n;
    }

/*     Determine the number of the block columns */

    nt = (*n + nb - 1) / nb;
    td = nb << 1;
    kb = f2cmin(nb,*n);

/*     Initialize vectors/matrices */

    i__1 = kb;
    for (j = 1; j <= i__1; ++j) {
	ipiv[j] = j;
    }

/*     Save NB */

    tb[1].r = (real) nb, tb[1].i = 0.f;

    if (upper) {

/*        ..................................................... */
/*        Factorize A as U**T*D*U using the upper triangle of A */
/*        ..................................................... */

	i__1 = nt - 1;
	for (j = 0; j <= i__1; ++j) {

/*           Generate Jth column of W and H */

/* Computing MIN */
	    i__2 = nb, i__3 = *n - j * nb;
	    kb = f2cmin(i__2,i__3);
	    i__2 = j - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (i__ == 1) {
/*                  H(I,J) = T(I,I)*U(I,J) + T(I+1,I)*U(I+1,J) */
		    if (i__ == j - 1) {
			jb = nb + kb;
		    } else {
			jb = nb << 1;
		    }
		    i__3 = ldtb - 1;
		    cgemm_("NoTranspose", "NoTranspose", &nb, &kb, &jb, &c_b2,
			     &tb[td + 1 + i__ * nb * ldtb], &i__3, &a[(i__ - 
			    1) * nb + 1 + (j * nb + 1) * a_dim1], lda, &c_b1, 
			    &work[i__ * nb + 1], n);
		} else {
/*                 H(I,J) = T(I,I-1)*U(I-1,J) + T(I,I)*U(I,J) + T(I,I+1)*U(I+1,J) */
		    if (i__ == j - 1) {
			jb = (nb << 1) + kb;
		    } else {
			jb = nb * 3;
		    }
		    i__3 = ldtb - 1;
		    cgemm_("NoTranspose", "NoTranspose", &nb, &kb, &jb, &c_b2,
			     &tb[td + nb + 1 + (i__ - 1) * nb * ldtb], &i__3, 
			    &a[(i__ - 2) * nb + 1 + (j * nb + 1) * a_dim1], 
			    lda, &c_b1, &work[i__ * nb + 1], n);
		}
	    }

/*           Compute T(J,J) */

	    i__2 = ldtb - 1;
	    clacpy_("Upper", &kb, &kb, &a[j * nb + 1 + (j * nb + 1) * a_dim1],
		     lda, &tb[td + 1 + j * nb * ldtb], &i__2);
	    if (j > 1) {
/*              T(J,J) = U(1:J,J)'*H(1:J) */
		i__2 = (j - 1) * nb;
		q__1.r = -1.f, q__1.i = 0.f;
		i__3 = ldtb - 1;
		cgemm_("Conjugate transpose", "NoTranspose", &kb, &kb, &i__2, 
			&q__1, &a[(j * nb + 1) * a_dim1 + 1], lda, &work[nb + 
			1], n, &c_b2, &tb[td + 1 + j * nb * ldtb], &i__3);
/*              T(J,J) += U(J,J)'*T(J,J-1)*U(J-1,J) */
		i__2 = ldtb - 1;
		cgemm_("Conjugate transpose", "NoTranspose", &kb, &nb, &kb, &
			c_b2, &a[(j - 1) * nb + 1 + (j * nb + 1) * a_dim1], 
			lda, &tb[td + nb + 1 + (j - 1) * nb * ldtb], &i__2, &
			c_b1, &work[1], n);
		q__1.r = -1.f, q__1.i = 0.f;
		i__2 = ldtb - 1;
		cgemm_("NoTranspose", "NoTranspose", &kb, &kb, &nb, &q__1, &
			work[1], n, &a[(j - 2) * nb + 1 + (j * nb + 1) * 
			a_dim1], lda, &c_b2, &tb[td + 1 + j * nb * ldtb], &
			i__2);
	    }
	    if (j > 0) {
		i__2 = ldtb - 1;
		chegst_(&c__1, "Upper", &kb, &tb[td + 1 + j * nb * ldtb], &
			i__2, &a[(j - 1) * nb + 1 + (j * nb + 1) * a_dim1], 
			lda, &iinfo);
	    }

/*           Expand T(J,J) into full format */

	    i__2 = kb;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = td + 1 + (j * nb + i__ - 1) * ldtb;
		i__4 = td + 1 + (j * nb + i__ - 1) * ldtb;
		r__1 = tb[i__4].r;
		tb[i__3].r = r__1, tb[i__3].i = 0.f;
		i__3 = kb;
		for (k = i__ + 1; k <= i__3; ++k) {
		    i__4 = td + (k - i__) + 1 + (j * nb + i__ - 1) * ldtb;
		    r_cnjg(&q__1, &tb[td - (k - (i__ + 1)) + (j * nb + k - 1) 
			    * ldtb]);
		    tb[i__4].r = q__1.r, tb[i__4].i = q__1.i;
		}
	    }

	    if (j < nt - 1) {
		if (j > 0) {

/*                 Compute H(J,J) */

		    if (j == 1) {
			i__2 = ldtb - 1;
			cgemm_("NoTranspose", "NoTranspose", &kb, &kb, &kb, &
				c_b2, &tb[td + 1 + j * nb * ldtb], &i__2, &a[(
				j - 1) * nb + 1 + (j * nb + 1) * a_dim1], lda,
				 &c_b1, &work[j * nb + 1], n);
		    } else {
			i__2 = nb + kb;
			i__3 = ldtb - 1;
			cgemm_("NoTranspose", "NoTranspose", &kb, &kb, &i__2, 
				&c_b2, &tb[td + nb + 1 + (j - 1) * nb * ldtb],
				 &i__3, &a[(j - 2) * nb + 1 + (j * nb + 1) * 
				a_dim1], lda, &c_b1, &work[j * nb + 1], n);
		    }

/*                 Update with the previous column */

		    i__2 = *n - (j + 1) * nb;
		    i__3 = j * nb;
		    q__1.r = -1.f, q__1.i = 0.f;
		    cgemm_("Conjugate transpose", "NoTranspose", &nb, &i__2, &
			    i__3, &q__1, &work[nb + 1], n, &a[((j + 1) * nb + 
			    1) * a_dim1 + 1], lda, &c_b2, &a[j * nb + 1 + ((j 
			    + 1) * nb + 1) * a_dim1], lda);
		}

/*              Copy panel to workspace to call CGETRF */

		i__2 = nb;
		for (k = 1; k <= i__2; ++k) {
		    i__3 = *n - (j + 1) * nb;
		    ccopy_(&i__3, &a[j * nb + k + ((j + 1) * nb + 1) * a_dim1]
			    , lda, &work[(k - 1) * *n + 1], &c__1);
		}

/*              Factorize panel */

		i__2 = *n - (j + 1) * nb;
		cgetrf_(&i__2, &nb, &work[1], n, &ipiv[(j + 1) * nb + 1], &
			iinfo);
/*               IF (IINFO.NE.0 .AND. INFO.EQ.0) THEN */
/*                  INFO = IINFO+(J+1)*NB */
/*               END IF */

/*              Copy panel back */

		i__2 = nb;
		for (k = 1; k <= i__2; ++k) {

/*                  Copy only L-factor */

		    i__3 = *n - k - (j + 1) * nb;
		    ccopy_(&i__3, &work[k + 1 + (k - 1) * *n], &c__1, &a[j * 
			    nb + k + ((j + 1) * nb + k + 1) * a_dim1], lda);

/*                  Transpose U-factor to be copied back into T(J+1, J) */

		    clacgv_(&k, &work[(k - 1) * *n + 1], &c__1);
		}

/*              Compute T(J+1, J), zero out for GEMM update */

/* Computing MIN */
		i__2 = nb, i__3 = *n - (j + 1) * nb;
		kb = f2cmin(i__2,i__3);
		i__2 = ldtb - 1;
		claset_("Full", &kb, &nb, &c_b1, &c_b1, &tb[td + nb + 1 + j * 
			nb * ldtb], &i__2);
		i__2 = ldtb - 1;
		clacpy_("Upper", &kb, &nb, &work[1], n, &tb[td + nb + 1 + j * 
			nb * ldtb], &i__2);
		if (j > 0) {
		    i__2 = ldtb - 1;
		    ctrsm_("R", "U", "N", "U", &kb, &nb, &c_b2, &a[(j - 1) * 
			    nb + 1 + (j * nb + 1) * a_dim1], lda, &tb[td + nb 
			    + 1 + j * nb * ldtb], &i__2);
		}

/*              Copy T(J,J+1) into T(J+1, J), both upper/lower for GEMM */
/*              updates */

		i__2 = nb;
		for (k = 1; k <= i__2; ++k) {
		    i__3 = kb;
		    for (i__ = 1; i__ <= i__3; ++i__) {
			i__4 = td - nb + k - i__ + 1 + (j * nb + nb + i__ - 1)
				 * ldtb;
			r_cnjg(&q__1, &tb[td + nb + i__ - k + 1 + (j * nb + k 
				- 1) * ldtb]);
			tb[i__4].r = q__1.r, tb[i__4].i = q__1.i;
		    }
		}
		claset_("Lower", &kb, &nb, &c_b1, &c_b2, &a[j * nb + 1 + ((j 
			+ 1) * nb + 1) * a_dim1], lda);

/*              Apply pivots to trailing submatrix of A */

		i__2 = kb;
		for (k = 1; k <= i__2; ++k) {
/*                 > Adjust ipiv */
		    ipiv[(j + 1) * nb + k] += (j + 1) * nb;

		    i1 = (j + 1) * nb + k;
		    i2 = ipiv[(j + 1) * nb + k];
		    if (i1 != i2) {
/*                    > Apply pivots to previous columns of L */
			i__3 = k - 1;
			cswap_(&i__3, &a[(j + 1) * nb + 1 + i1 * a_dim1], &
				c__1, &a[(j + 1) * nb + 1 + i2 * a_dim1], &
				c__1);
/*                    > Swap A(I1+1:M, I1) with A(I2, I1+1:M) */
			if (i2 > i1 + 1) {
			    i__3 = i2 - i1 - 1;
			    cswap_(&i__3, &a[i1 + (i1 + 1) * a_dim1], lda, &a[
				    i1 + 1 + i2 * a_dim1], &c__1);
			    i__3 = i2 - i1 - 1;
			    clacgv_(&i__3, &a[i1 + 1 + i2 * a_dim1], &c__1);
			}
			i__3 = i2 - i1;
			clacgv_(&i__3, &a[i1 + (i1 + 1) * a_dim1], lda);
/*                    > Swap A(I2+1:M, I1) with A(I2+1:M, I2) */
			if (i2 < *n) {
			    i__3 = *n - i2;
			    cswap_(&i__3, &a[i1 + (i2 + 1) * a_dim1], lda, &a[
				    i2 + (i2 + 1) * a_dim1], lda);
			}
/*                    > Swap A(I1, I1) with A(I2, I2) */
			i__3 = i1 + i1 * a_dim1;
			piv.r = a[i__3].r, piv.i = a[i__3].i;
			i__3 = i1 + i1 * a_dim1;
			i__4 = i2 + i2 * a_dim1;
			a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
			i__3 = i2 + i2 * a_dim1;
			a[i__3].r = piv.r, a[i__3].i = piv.i;
/*                    > Apply pivots to previous columns of L */
			if (j > 0) {
			    i__3 = j * nb;
			    cswap_(&i__3, &a[i1 * a_dim1 + 1], &c__1, &a[i2 * 
				    a_dim1 + 1], &c__1);
			}
		    }
		}
	    }
	}
    } else {

/*        ..................................................... */
/*        Factorize A as L*D*L**T using the lower triangle of A */
/*        ..................................................... */

	i__1 = nt - 1;
	for (j = 0; j <= i__1; ++j) {

/*           Generate Jth column of W and H */

/* Computing MIN */
	    i__2 = nb, i__3 = *n - j * nb;
	    kb = f2cmin(i__2,i__3);
	    i__2 = j - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (i__ == 1) {
/*                  H(I,J) = T(I,I)*L(J,I)' + T(I+1,I)'*L(J,I+1)' */
		    if (i__ == j - 1) {
			jb = nb + kb;
		    } else {
			jb = nb << 1;
		    }
		    i__3 = ldtb - 1;
		    cgemm_("NoTranspose", "Conjugate transpose", &nb, &kb, &
			    jb, &c_b2, &tb[td + 1 + i__ * nb * ldtb], &i__3, &
			    a[j * nb + 1 + ((i__ - 1) * nb + 1) * a_dim1], 
			    lda, &c_b1, &work[i__ * nb + 1], n);
		} else {
/*                 H(I,J) = T(I,I-1)*L(J,I-1)' + T(I,I)*L(J,I)' + T(I,I+1)*L(J,I+1)' */
		    if (i__ == j - 1) {
			jb = (nb << 1) + kb;
		    } else {
			jb = nb * 3;
		    }
		    i__3 = ldtb - 1;
		    cgemm_("NoTranspose", "Conjugate transpose", &nb, &kb, &
			    jb, &c_b2, &tb[td + nb + 1 + (i__ - 1) * nb * 
			    ldtb], &i__3, &a[j * nb + 1 + ((i__ - 2) * nb + 1)
			     * a_dim1], lda, &c_b1, &work[i__ * nb + 1], n);
		}
	    }

/*           Compute T(J,J) */

	    i__2 = ldtb - 1;
	    clacpy_("Lower", &kb, &kb, &a[j * nb + 1 + (j * nb + 1) * a_dim1],
		     lda, &tb[td + 1 + j * nb * ldtb], &i__2);
	    if (j > 1) {
/*              T(J,J) = L(J,1:J)*H(1:J) */
		i__2 = (j - 1) * nb;
		q__1.r = -1.f, q__1.i = 0.f;
		i__3 = ldtb - 1;
		cgemm_("NoTranspose", "NoTranspose", &kb, &kb, &i__2, &q__1, &
			a[j * nb + 1 + a_dim1], lda, &work[nb + 1], n, &c_b2, 
			&tb[td + 1 + j * nb * ldtb], &i__3);
/*              T(J,J) += L(J,J)*T(J,J-1)*L(J,J-1)' */
		i__2 = ldtb - 1;
		cgemm_("NoTranspose", "NoTranspose", &kb, &nb, &kb, &c_b2, &a[
			j * nb + 1 + ((j - 1) * nb + 1) * a_dim1], lda, &tb[
			td + nb + 1 + (j - 1) * nb * ldtb], &i__2, &c_b1, &
			work[1], n);
		q__1.r = -1.f, q__1.i = 0.f;
		i__2 = ldtb - 1;
		cgemm_("NoTranspose", "Conjugate transpose", &kb, &kb, &nb, &
			q__1, &work[1], n, &a[j * nb + 1 + ((j - 2) * nb + 1) 
			* a_dim1], lda, &c_b2, &tb[td + 1 + j * nb * ldtb], &
			i__2);
	    }
	    if (j > 0) {
		i__2 = ldtb - 1;
		chegst_(&c__1, "Lower", &kb, &tb[td + 1 + j * nb * ldtb], &
			i__2, &a[j * nb + 1 + ((j - 1) * nb + 1) * a_dim1], 
			lda, &iinfo);
	    }

/*           Expand T(J,J) into full format */

	    i__2 = kb;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = td + 1 + (j * nb + i__ - 1) * ldtb;
		i__4 = td + 1 + (j * nb + i__ - 1) * ldtb;
		r__1 = tb[i__4].r;
		tb[i__3].r = r__1, tb[i__3].i = 0.f;
		i__3 = kb;
		for (k = i__ + 1; k <= i__3; ++k) {
		    i__4 = td - (k - (i__ + 1)) + (j * nb + k - 1) * ldtb;
		    r_cnjg(&q__1, &tb[td + (k - i__) + 1 + (j * nb + i__ - 1) 
			    * ldtb]);
		    tb[i__4].r = q__1.r, tb[i__4].i = q__1.i;
		}
	    }

	    if (j < nt - 1) {
		if (j > 0) {

/*                 Compute H(J,J) */

		    if (j == 1) {
			i__2 = ldtb - 1;
			cgemm_("NoTranspose", "Conjugate transpose", &kb, &kb,
				 &kb, &c_b2, &tb[td + 1 + j * nb * ldtb], &
				i__2, &a[j * nb + 1 + ((j - 1) * nb + 1) * 
				a_dim1], lda, &c_b1, &work[j * nb + 1], n);
		    } else {
			i__2 = nb + kb;
			i__3 = ldtb - 1;
			cgemm_("NoTranspose", "Conjugate transpose", &kb, &kb,
				 &i__2, &c_b2, &tb[td + nb + 1 + (j - 1) * nb 
				* ldtb], &i__3, &a[j * nb + 1 + ((j - 2) * nb 
				+ 1) * a_dim1], lda, &c_b1, &work[j * nb + 1],
				 n);
		    }

/*                 Update with the previous column */

		    i__2 = *n - (j + 1) * nb;
		    i__3 = j * nb;
		    q__1.r = -1.f, q__1.i = 0.f;
		    cgemm_("NoTranspose", "NoTranspose", &i__2, &nb, &i__3, &
			    q__1, &a[(j + 1) * nb + 1 + a_dim1], lda, &work[
			    nb + 1], n, &c_b2, &a[(j + 1) * nb + 1 + (j * nb 
			    + 1) * a_dim1], lda);
		}

/*              Factorize panel */

		i__2 = *n - (j + 1) * nb;
		cgetrf_(&i__2, &nb, &a[(j + 1) * nb + 1 + (j * nb + 1) * 
			a_dim1], lda, &ipiv[(j + 1) * nb + 1], &iinfo);
/*               IF (IINFO.NE.0 .AND. INFO.EQ.0) THEN */
/*                  INFO = IINFO+(J+1)*NB */
/*               END IF */

/*              Compute T(J+1, J), zero out for GEMM update */

/* Computing MIN */
		i__2 = nb, i__3 = *n - (j + 1) * nb;
		kb = f2cmin(i__2,i__3);
		i__2 = ldtb - 1;
		claset_("Full", &kb, &nb, &c_b1, &c_b1, &tb[td + nb + 1 + j * 
			nb * ldtb], &i__2);
		i__2 = ldtb - 1;
		clacpy_("Upper", &kb, &nb, &a[(j + 1) * nb + 1 + (j * nb + 1) 
			* a_dim1], lda, &tb[td + nb + 1 + j * nb * ldtb], &
			i__2);
		if (j > 0) {
		    i__2 = ldtb - 1;
		    ctrsm_("R", "L", "C", "U", &kb, &nb, &c_b2, &a[j * nb + 1 
			    + ((j - 1) * nb + 1) * a_dim1], lda, &tb[td + nb 
			    + 1 + j * nb * ldtb], &i__2);
		}

/*              Copy T(J+1,J) into T(J, J+1), both upper/lower for GEMM */
/*              updates */

		i__2 = nb;
		for (k = 1; k <= i__2; ++k) {
		    i__3 = kb;
		    for (i__ = 1; i__ <= i__3; ++i__) {
			i__4 = td - nb + k - i__ + 1 + (j * nb + nb + i__ - 1)
				 * ldtb;
			r_cnjg(&q__1, &tb[td + nb + i__ - k + 1 + (j * nb + k 
				- 1) * ldtb]);
			tb[i__4].r = q__1.r, tb[i__4].i = q__1.i;
		    }
		}
		claset_("Upper", &kb, &nb, &c_b1, &c_b2, &a[(j + 1) * nb + 1 
			+ (j * nb + 1) * a_dim1], lda);

/*              Apply pivots to trailing submatrix of A */

		i__2 = kb;
		for (k = 1; k <= i__2; ++k) {
/*                 > Adjust ipiv */
		    ipiv[(j + 1) * nb + k] += (j + 1) * nb;

		    i1 = (j + 1) * nb + k;
		    i2 = ipiv[(j + 1) * nb + k];
		    if (i1 != i2) {
/*                    > Apply pivots to previous columns of L */
			i__3 = k - 1;
			cswap_(&i__3, &a[i1 + ((j + 1) * nb + 1) * a_dim1], 
				lda, &a[i2 + ((j + 1) * nb + 1) * a_dim1], 
				lda);
/*                    > Swap A(I1+1:M, I1) with A(I2, I1+1:M) */
			if (i2 > i1 + 1) {
			    i__3 = i2 - i1 - 1;
			    cswap_(&i__3, &a[i1 + 1 + i1 * a_dim1], &c__1, &a[
				    i2 + (i1 + 1) * a_dim1], lda);
			    i__3 = i2 - i1 - 1;
			    clacgv_(&i__3, &a[i2 + (i1 + 1) * a_dim1], lda);
			}
			i__3 = i2 - i1;
			clacgv_(&i__3, &a[i1 + 1 + i1 * a_dim1], &c__1);
/*                    > Swap A(I2+1:M, I1) with A(I2+1:M, I2) */
			if (i2 < *n) {
			    i__3 = *n - i2;
			    cswap_(&i__3, &a[i2 + 1 + i1 * a_dim1], &c__1, &a[
				    i2 + 1 + i2 * a_dim1], &c__1);
			}
/*                    > Swap A(I1, I1) with A(I2, I2) */
			i__3 = i1 + i1 * a_dim1;
			piv.r = a[i__3].r, piv.i = a[i__3].i;
			i__3 = i1 + i1 * a_dim1;
			i__4 = i2 + i2 * a_dim1;
			a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
			i__3 = i2 + i2 * a_dim1;
			a[i__3].r = piv.r, a[i__3].i = piv.i;
/*                    > Apply pivots to previous columns of L */
			if (j > 0) {
			    i__3 = j * nb;
			    cswap_(&i__3, &a[i1 + a_dim1], lda, &a[i2 + 
				    a_dim1], lda);
			}
		    }
		}

/*              Apply pivots to previous columns of L */

/*               CALL CLASWP( J*NB, A( 1, 1 ), LDA, */
/*     $                     (J+1)*NB+1, (J+1)*NB+KB, IPIV, 1 ) */
	    }
	}
    }

/*     Factor the band matrix */
    cgbtrf_(n, n, &nb, &nb, &tb[1], &ldtb, &ipiv2[1], info);

    return 0;

/*     End of CHETRF_AA_2STAGE */

} /* chetrf_aa_2stage__ */


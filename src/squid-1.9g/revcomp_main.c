/*****************************************************************
 * SQUID - a library of functions for biological sequence analysis
 * Copyright (C) 1992-2002 Washington University School of Medicine
 * 
 *     This source code is freely distributed under the terms of the
 *     GNU General Public License. See the files COPYRIGHT and LICENSE
 *     for details.
 *****************************************************************/

/* main for revcomp
 *
 * revcomp - generate reverse complement of sequences
 * SRE, Thu Aug  5 17:36:57 1993
 * RCS $Id: revcomp_main.c,v 1.4 2001/02/21 21:09:10 eddy Exp $
 */

#include <stdio.h>
#include <string.h>
#include "squid.h"
#include "version.h"

#define OPTIONS "h"

char usage[]  = "Usage: revcomp [-options] <seqfile>\n\
  Reverse complement a nucleic acid sequence.\n\
  Available options:\n\
  -h    : help; print version and usage info\n";

int
main(int argc, char **argv)
{
  char  *seqfile;               /* name of sequence file */
  SQFILE *dbfp;			/* open sequence file */
  int    fmt;			/* format of seqfile  */
  char  *seq;			/* sequence */
  SQINFO sqinfo;                /* additional sequence info */
  char  *rev;			/* reverse complement */
  int    swap;

  int    optchar;		/* option character, command line */
  extern int   optind;

  /***********************************************
   * Parse command line
   ***********************************************/

  fmt = SQFILE_UNKNOWN;

  while ((optchar = getopt(argc, argv, OPTIONS)) != -1)
    switch (optchar) {
    case 'h': 
      printf("revcomp %s, %s\n%s\n", RELEASE, RELEASEDATE, usage);
      exit(EXIT_SUCCESS);
    default:
      Die("%s\n", usage);
    }

  if (argc - optind != 1) Die("%s\n", usage); 
  seqfile = argv[optind];
		 
  if ((dbfp = SeqfileOpen(seqfile, fmt, NULL)) == NULL)
    Die("Failed to open sequence file %s for reading", seqfile);
  
  while (ReadSeq(dbfp, dbfp->format, &seq, &sqinfo))
    {
      if ((rev = (char *) malloc ((sqinfo.len + 1) * sizeof(char))) == NULL)
	Die("malloc failed");

      revcomp(rev, seq);
      if (sqinfo.flags & (SQINFO_START | SQINFO_STOP))
	{
	  swap         = sqinfo.start;
	  sqinfo.start = sqinfo.stop;
	  sqinfo.stop  = swap;
	}
	/* secondary structure of reverse strand is nonsense
	 */
      if (sqinfo.flags & SQINFO_SS)
	{
	  sqinfo.flags = sqinfo.flags & ~SQINFO_SS;
	  free(sqinfo.ss);
	}

      WriteSeq(stdout, SQFILE_FASTA, rev, &sqinfo);

      free(rev);
      FreeSequence(seq, &sqinfo);
    }

  SeqfileClose(dbfp);
  return 0;
}

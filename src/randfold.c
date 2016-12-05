/*******************************************************************************
 * RANDFOLD - a randomization test for sequence secondary structure
 * Copyright (C) 2005 Eric Bonnet - Bioinformatics & Evolutionary Genomics - VIB
 * 
 *     This source code is freely distributed under the terms of the
 *     GNU General Public License. See the files COPYRIGHT and LICENSE
 *     for details.
 ******************************************************************************/



/******************************************************************************* 
*  RANDFOLD version 2.0 
*
*  This C verion is using functions from Sean Eddy's SQUID library and
*  Ivo Hofacker's ViennaRNA package. Thanks guys !
*
*  See Readme.txt for more details.
*
*******************************************************************************/

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<squid.h>
#include<fold.h>
#include<sre_random.h>

int main(int argc, char *argv[]) {
	
	SQFILE *sqfp;
	char   seqfile[255];			/* file name */
	char   *seq;					/* sequence */
	char   *shuff;					/* shuffled sequence */
	char   *structure;				/* seq. sec. structure */
	char   *structure_shuff;		/* shuffled seq sec. structure */
	double mfe=0;					/* minimum free energy */
	double mfe_shuff=0;				/* mfe for shuffled seq. */
	SQINFO sqinfo;
	int    opt=0;					/* randomization method */
	int    rand_num=0;				/* number of shuffled seq. generated */
	int    c;
	int    i;
	int    ct_eq;					/* counter for equal mfe */
	int    ct_less;					/* counter for mfe less than original */
	int    ct_above;				/* counter for mfe above original */
	double epsilon = 0.0000001;		/* epsilon value for comparing doubles */
	double proba;					/* probability of mfe */
	int    seed = (int) time ((time_t *) NULL);
	char   *usage;
	
	usage = "Usage: randfold <method> <file name> <number of randomizations>\n\n\
methods:\n\
-s simple mononucleotide shuffling\n\
-d dinucleotide shuffling\n\
-m markov chain 1 shuffling\n\n\
Example: randfold -d let7.tfa 999\n\n";
	
	/* parse command line arguments */
	if (argc != 4 || *argv[1] != '-') {
		Die (usage);
	}
	else {
		while (--argc > 0 && (*++argv)[0] == '-')
			while (c = *++argv[0])
				switch (c) {
					case 's':
					opt = 0;
					break;
					case 'm':
					opt = 1;
					break;
					case 'd':
					opt = 2;
					break;
					case 'h':
					opt = -1;
					break;
					default:
					opt = -1;
					break;
				}
	}

	/* help */
	if (opt == -1) 
		Die (usage);
	
	/* initialize file name and number of randomizations */
	strcpy(seqfile,*argv);
	rand_num = atoi(*++argv);	

	/* initialize random generator */
	sre_srandom(seed);
	
	/* open fasta file */
	if ((sqfp = SeqfileOpen(seqfile, SQFILE_FASTA, NULL)) == NULL)
		Die("Failed to open sequence file %s\n", seqfile);
	
	/* loop through all sequences */
	while (ReadSeq(sqfp, sqfp->format, &seq, &sqinfo)) {
		
		/* allocate memory for shuffled sequence and secondary structures */
		structure = malloc(sizeof(char) * (strlen(seq)+1));
		shuff = malloc(sizeof(char) * (strlen(seq)+1));
		structure_shuff = malloc(sizeof(char) * (strlen(seq)+1));
		
		/* fold original sequence */
		mfe = fold(seq,structure);
		
		/* initialize counting and proba variables */
		ct_eq=1;
		ct_less=0;
		ct_above=0;
		proba=0;
		
		/* main randomization loop */
		for (i=0;i<rand_num;i++) {
		
			/* shuffle according to option chosed */
			switch(opt) {
				case 0:
				StrShuffle(shuff,seq);
				break;
				case 1:
				StrMarkov1(shuff,seq);
				break;
				case 2:
				StrDPShuffle(shuff,seq);
				break;
			}
			
			/* fold shuffled sequence */
			mfe_shuff = fold(shuff,structure_shuff);
			
			/* compare mfe to mfe value for shuffled sequence */
			if (fabs (mfe_shuff - mfe) <= epsilon) {
				ct_eq++;
			}
			else {
				if (mfe_shuff < mfe) 
					ct_less++;
				if (mfe_shuff > mfe) 
					ct_above++;
			}
			
		/* free folding arrays */
		free_arrays;
		}
		
		/* compute one-tailed probability */
		proba = (double)(ct_eq + ct_less) / (rand_num + 1);
		
		/* output seq name, mfe value, probability */
		printf("%s\t%.2f\t%f\n",sqinfo.name,mfe,proba);

		/* freedom for memory */
		FreeSequence(seq, &sqinfo);
		free(structure);
		free(shuff);
		free(structure_shuff);
	}
	SeqfileClose(sqfp);

return 0;
}

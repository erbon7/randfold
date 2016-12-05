RANDFOLD - A randsomization test for sequence secondary structure 
Copyright (C) 2005 Eric Bonnet - Bioinformatics & Evolutionary Genomics - VIB
-----------------------------------------------------------------------------

This is RANDFOLD version 2. The software compute the probability that, for a 
given sequence, the Minimum Free Energy (MFE) of the secondary structure is 
different from MFE computed with random sequences. 

For more information, see the paper published in Bioinformatics:

Bonnet E, Wuyts J, Rouze P, Van de Peer Y.
Evidence that microRNA precursors, unlike other non-coding RNAs, have lower 
folding free energies than random sequences.
Bioinformatics. 2004 Nov 22;20(17):2911-7.
PMID: 15217813

http://bioinformatics.psb.ugent.be/supplementary_data/erbon/nov2003/

If you have any questions about redistributing RANDFOLD or using 
RANDFOLD code in your own work, see the files:
COPYRIGHT    -- copyright notice
LICENSE      -- version 2 of the GNU Public License (see COPYRIGHT)

Installation
------------

You must install first Sean Eddy's SQUID library, available from:
http://selab.wustl.edu/cgi-bin/selab.pl?mode=software#squid

Then proceed like this:
  tar xzvf randfold.tar.gz (create randfold-2.0 dirextory)
  cd randfold-2.0
  (optional) edit the Makefile
  make
  cp randfold /usr/local/bin (or whatever destination)
  You're done.
  
The code is using Ivo Hofacker's ViennaRNA library to fold sequences.
Installation is not required but you can get it at:
http://www.tbi.univie.ac.at/~ivo/RNA/

Usage
-----

./randfold <method> <file name> <number of randomizations>

Methods available:
-s  simple mononucleotide shuffling
-d  dinucleotide shuffling
-m  markov chain 1 shuffling

Example:
randfold -d let7.tfa 999

Output:
<sequence name> tab <mfe> tab <probability>

Example:
cel-let-7       -42.90  0.001000

------------

Eric Bonnet
eric.bonnet at psb.ugent.be
Bioinformatics & Evolutionary Genomics
Technologiepark 927
9052 - Gent
BELGIUM

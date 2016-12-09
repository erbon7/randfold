# randfold

Most non-coding RNAs are characterized by a specific secondary and tertiary structure that determines their function. We investigated the folding energy of the secondary structure of non-coding RNA sequences, such as microRNA precursors, transfer RNAs and ribosomal RNAs in several eukaryotic taxa. Statistical biases are assessed by a randomization test, in which the predicted minimum free energy of folding is compared with values obtained for structures inferred from randomly shuffling the original sequences.

In contrast with transfer RNAs and ribosomal RNAs, the majority of the microRNA sequences clearly exhibit a folding free energy that is considerably lower than that for shuffled sequences, indicating a high tendency in the sequence towards a stable secondary structure. 

This test can be used together with other indicators to predict and charaterize microRNA sequences. For more information, see Bonnet et al. ["Evidence that microRNA precursors, unlike other non-coding RNAs, have lower folding free energies than random sequences"](http://bioinformatics.oxfordjournals.org/content/20/17/2911.abstract).


## Download and Installation

Clone the github repository with the command:

```
git clone https://github.com/eb00/randfold randfold_src
```
Go to the newly created `randfold_src` directory, and then to `src`.

The code needs the SQUID library (written by [Sean Eddy](http://eddylab.org/software.html)). A copy of this library (version 1.9g) is distributed with this software. To compile it, go to the `squid-1.9g` directory and then type:

```
./configure && make
```
If everything goes well, you should have a file named `libsquid.a` in the directory.

Then move up one level (`src`) and type:
```
make
```
You should now see the compiled program `randfold`. You can copy this program to `/usr/local/bin` or any directory within your PATH and you're ready to go.

NB: the code is using Ivo Hofacker's [ViennaRNA library](http://www.tbi.univie.ac.at/~ivo/RNA/) to fold sequences (installation not required).


## Usage

```
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

```

## Fee

This software is free of charge for academics and non-profit organizations. Please contact the authors for
any commercial usage.



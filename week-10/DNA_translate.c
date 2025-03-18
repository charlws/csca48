////////////////////////////////////////////////////////////
// CSC A48 - DNA alignment Pt. 1
//
// The goal of this assignment is to write a function that
// translates tripled (sets of 3) DNA nucleotide bases to
// the corresponding aminoacid.
//
// As a brief review of your Biology lessons, DNA is a double
// stranded chain of nucleic-acids, there are 4 types of
// nucleotides denoted by the letters:
//
// A, C, T, G
//
// The sequence of these nucleotides specifies the sequence
// in which aminoacids (the building blocks of proteins)
// are assembled into every single one of the proteins that
// make up the cells of most licing things (there are a 
// few that do not use DNA, opting instead to use the single
// stranded version called RNA, viruses tend to be sneaky
// that way!)
//
// Each set of 3 nucleotides specifies one aminoacid in
// a protein's specification.
//
// The goal of this exercise is for you to write a small
// function that takes in a DNA sequence (a string made up
// of letters ATCG in some sequence) and determines the
// corresponding sequence of aminoacids. Below, you will
// find a table listing each aminoacid, and the sequences
// of DNA nucleotides that specify that aminoacid.
// 
// Note that many aminoacids can be specified by more than
// one triplet!
//
//  Aminoacid   Single letter name	Triplets
//  Isoleucine 		I 		ATT, ATC, ATA
//  Leucine 		L 		CTT, CTC, CTA, CTG, TTA, TTG
//  Valine 		    V 		GTT, GTC, GTA, GTG
//  Phenylalanine 	F 		TTT, TTC
//  Methionine 		M 		ATG
//  Cysteine 		C 		TGT, TGC
//  Alanine 		A 		GCT, GCC, GCA, GCG
//  Glycine 		G 		GGT, GGC, GGA, GGG
//  Proline 		P 		CCT, CCC, CCA, CCG
//  Threonine 		T		ACT, ACC, ACA, ACG
//  Serine 		    S 		TCT, TCC, TCA, TCG, AGT, AGC
//  Tyrosine 		Y 		TAT, TAC
//  Tryptophan 		W 		TGG
//  Glutamine 		Q 		CAA, CAG
//  Asparagine 		N 		AAT, AAC
//  Histidine 		H 		CAT, CAC
//  Glutamic acid 	E 		GAA, GAG
//  Aspartic acid 	D 		GAT, GAC
//  Lysine 		    K 		AAA, AAG
//  Arginine 		R 		CGT, CGC, CGA, CGG, AGA, AGG
//
//  Your task is to determine whether two DNA sequences use the
//  same number of each type of aminoacid (the order of the
//  amino-acids doesn't matter here).
//  To that end, you need to write a function that
//  takes a DNA sequence and converts it to the corresponding
//  sequence of aminoacids, for instance if the input sequence is:
//
//  AAGGAGTGTTTT
//
//  Your function must return
//
//  KECF
//
//  Then you need to write a function that takes in two DNA
//  sequences and determines whether they produce the same
//  numbers of each aminoacid. For example, if the sequence
//  of aminoacids for each of the input DNA sequences is
//
//  AATVKFAA    and    TAAVKAAF
//
//  The function must return 1 (they produce the same number
//  of each aminoacid). However, if the aminoacid sequences
//  are
//
//  TVFAAKVV    and    ECVAATFK
//
//  the function will return 0 (not the same number of each
//  aminoacid).
//
// (c) F. Estrada, March, 2022
///////////////////////////////////////////////////////////

// We encode A = 1, C = 2, G = 3, T = 4
// For each triplets XYZ, we encode it as 100*X + 10*Y + Z
// We maintain a 500-length array that maps triplet -> aminocaid code

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void DNA_sequencing(char inputDNA[1024], char outputAminoAcids[1024])
{
    // This function receives two strings, one that contains a sequence
    // of DNA nucleotides (which MUST be composed of the letters
    // ACGT, no spaces or other symbols can appear here!), and
    // updates an initially empty string 'outputAminoAcids' with the
    // sequence of aminoacids corresponding to the input DNA sequence
    //
    // Try to make this function as compact (fewer lines of code, more
    // elegant, easier to read code) as possible. APply what you've
    // learned in Exercises 6-8, all of which helped you practice
    // using strings!

    // To Do:
    // Complete this function

	// We create a const list of "XYZA" (triplet + aminoacid)
	const char XYZA[61][4] = {
		"ATTI", "ATCI", "ATAI", "CTTL", "CTCL", "CTAL",
		"CTGL", "TTAL", "TTGL", "GTTV", "GTCV", "GTAV",
		"GTGV", "TTTF", "TTCF", "ATGM", "TGTC", "TGCC",
		"GCTA", "GCCA", "GCAA", "GCGA", "GGTG", "GGCG",
		"GGAG", "GGGG", "CCTP", "CCCP", "CCAP", "CCGP",
		"ACTT", "ACCT", "ACAT", "ACGT", "TCTS", "TCCS",
		"TCAS", "TCGS", "AGTS", "AGCS", "TATY", "TACY",
		"TGGW", "CAAQ", "CAGQ", "AATN", "AACN", "CATH",
		"CACH", "GAAE", "GAGE", "GATD", "GACD", "AAAK",
		"AAGK", "CGTR", "CGCR", "CGAR", "CGGR", "AGAR",
		"AGGR"
	};
	
	// We generate the map of triplet -> aminoacid
	char MAP[500];
	for(int i=0;i<500;i++) MAP[i] = '\0';
	for(int i=0;i<61;i++){
		int code = 100 * XYZA[i][0] + 10 * XYZA[i][1] + XYZA[i][2];
		MAP[code] = XYZA[i][3];
	}

	// We process the DNA sequence
	for(int i=0;i+3<=strlen(inputDNA);i+=3){
		int code = 100 * inputDNA[i] + 10 * inputDNA[i+1] + inputDNA[i+2];
		outputAminoAcids[i/3] = MAP[code];
		// all code should be mapped
		// otherwise we produce an undefined behavior
	}
}

int amino_matching(char inputDNA1[1024], char inputDNA2[1024])
{
    // This function receives two strings representing DNA
    // sequences. It returns 1 if the sequences produce the
    // same number of each type of aminoacid. Think carefully
    // about the best (simplest?) way to to this.

    // To Do:
    // Complete this function

	if(strlen(inputDNA1) != strlen(inputDNA2)) return 0; // auto fail

	int cnt1[26], cnt2[26];
	for(int i=0;i<26;i++) cnt1[i] = cnt2[i] = 0;

	char aminoAcids1[1024], aminoAcids2[1024];
	DNA_sequencing(inputDNA1, aminoAcids1);
	DNA_sequencing(inputDNA2, aminoAcids2);
	for(int i=0;i<strlen(aminoAcids1);i++){
		cnt1[aminoAcids1[i]-'A']++;
		cnt2[aminoAcids2[i]-'A']++;
	}

	for(int i=0;i<26;i++){
		if(cnt1[i] != cnt2[i]) return 0;
	}
    return 1;
}

#ifndef __testing

int main()
{
	char DNAseq1[1024]="CTTATTGTTCCAATGTGGCGGCACTACACGTGCGTTATC";
	char DNAseq2[1024]="ATTTATTGTACATATCATCGTTGGATGCCCGTAATATTG";
        char DNAseq3[1024]="ATCGTTTGCACGTACCACCGGTGGATGCCAGTTATTCTT";
	char aminoAcids[1024]="";

	printf("Input DNA sequence 1: %s\n",DNAseq1);
	DNA_sequencing(DNAseq1,aminoAcids);
	printf("Output aminoacid sequence 1: %s\n",aminoAcids);

	printf("Input DNA sequence 2: %s\n",DNAseq2);
	DNA_sequencing(DNAseq2,aminoAcids);
	printf("Output aminoacid sequence 2: %s\n",aminoAcids);

	printf("Input DNA sequence 3: %s\n",DNAseq3);
	DNA_sequencing(DNAseq3,aminoAcids);
	printf("Output aminoacid sequence 3: %s\n",aminoAcids);

	if (amino_matching(DNAseq1,DNAseq2)==1)
	{
		printf("Sequence 1 matches sequence 2 in aminoacids\n");
	}
	else
	{
		printf("Sequence 1 does not match sequence 2 in aminoacids\n");
	}

	if (amino_matching(DNAseq1,DNAseq3)==1)
	{
		printf("Sequence 1 matches sequence 3 in aminoacids\n");
	}
	else
	{
		printf("Sequence 1 does not match sequence 3 in aminoacids\n");
	}

	if (amino_matching(DNAseq2,DNAseq3)==1)
	{
		printf("Sequence 2 matches sequence 3 in aminoacids\n");
	}
	else
	{
		printf("Sequence 2 does not match sequence 3 in aminoacids\n");
	}

	return 0;
}

#endif
